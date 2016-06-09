#!/usr/bin/php -q
<?php
/*
 * @file
 * 
 * Script to automatically load images from Dropbox
 *
 * Read in configuration file   DRUPAL_ROOT/sites/cows13/files/dsConf/imageloader.cnf
 *  - Lists all users with permission to load images into COWS from 
 *    their Dropbox directory
 *  - Dropbox directory: /home/cows/Dropbox/$user->name/<new image files>
 *  foreach user in Dropbox directory
 *    foreach image in the users directory
 *     - Extract EXIF GPS and find facility using proximity search
 *     - Extract EXIF Photo date
 *     - Check Users tickets, if one was active at the time picture was taken
 *       and the facility is the same, then add the ticket to the image
 *     - Set the media_status to New
 *     - Save the image 
 * 
 */

// $drupalRoot = '/var/www/dug';
// $bootstrap  = '../../includes/bootstrap.inc';
// $chdir      = '/var/www/dug/sites/dug1';

error_reporting(E_ALL);
//ini_set('display_errors',TRUE);
//ini_set('display_startup_errors',TRUE);
//ini_set('max_execution_time',18000);

global $php_errormsg;
$tzoffset = -21600;

if (checkRunning("imageloader\.php")) {
   print "  Exited: process already running\n";
   exit(0);
}

if (!isset($argv[1])) {
   print "You must specify a Drupal installation: imageloader.php [randy|cows]\n";
   exit(0);
}

if ($argv[1] == "cows") {
   $user = "cows";
   $host = "www.dairyspecialists.com";
   $sitename = "c15";
} else if ($argv[1] == "randy") {
   $user = "randy";
   $host = "www.dairyspecialists.com";
   $sitename = "r1";
} else {
   print "Unknown Drupal installation (cows|randy): " . $argv[1] . "\n";
   exit(0);
}

$drupalRoot = "/home/cows/drupal/current";
$bootstrap  = "includes/bootstrap.inc";
$siteRoot   = "/home/$user/drupal/current/sites/$sitename";
$srcDir     = "/home/$user/media.input";
$dstDir     = "/home/$user/media.archive";
$filesDir   = "/home/$user/sites/$sitename/files";
$_SERVER['SCRIPT_NAME'] = "/bin/imageloader.php";  // Path must start with a /
$_SERVER['REMOTE_ADDR'] = $host;
$_SERVER['HTTP_HOST'] = $sitename;

print "\nStarting imageloader.php - " . date("Y-m-d H:i:s") . "\n";
print "   drupalRoot: $drupalRoot\n";
print "   siteRoot:   $siteRoot\n";
print "   bootstrap:  $bootstrap\n";
print "   srcDir:     $srcDir\n\n";
print "   dstDir:     $dstDir\n\n";

chdir($drupalRoot);

// prevent this from running under apache:
if (array_key_exists('REQUEST_METHOD', $_SERVER)) {
    echo 'nope.  not executing except from the command line.';
    exit(1);
}

// set HTTP_HOST or drupal will refuse to bootstrap


define('DRUPAL_ROOT', $drupalRoot);

print "call bootstrap\n";
require_once $bootstrap;
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
//print "\n"; // Clear a space output somewhere in drupal_bootstrap
print "dude\n";

global $user;
$user->uid = 1;


$facilities = _imageloader_getFacilities();

// foreach user in /home/cows/Dropbox/$USERNAME

if (!$UD = opendir($srcDir)) die("Could not open dir $srcDir");
while (($username = readdir($UD))) {
  if ($username[0] == '.') continue;
  $inDir  = "$srcDir/$username";
  $outDir = "$dstDir/$username";
  if (is_dir($inDir)) {
    $puser = user_load_by_name($username);
    print("   Check Directory: $username - uid=" . $puser->uid . "\n");
    if (!$id = opendir($inDir)) die("Could not open dir $inDir");
    while (($file = readdir($id))) {
      if ($file[0] == '.') continue;
      $srcPath = "$inDir/$file";
      $outPath = "$outDir/$file";
      if (is_file($srcPath)) {
        print("   File: $file\n");
      	_imageloader_loadFile($srcPath,$username);
//      if (-f $outPath) unlink $outPath;
        `mv "$srcPath" "$outDir"`; 
      }
      else {
        print("  File not loaded: $inDir -- $srcPath\n");
      }
    }
    closedir($id);
  }
  else {
    print("Ignored, not a directory: $inDir\n");
  }
}
closedir($UD);

function checkRunning ($pname) {
  $pid = getmypid();
  $running = 0;
  $cmd = "ps -ef | grep \"\-q.*$pname\" | cut -d ' ' -f 3";
  $cmd = "ps -ef | grep \"\-q.*$pname\"";
  $handle = popen($cmd,"r");
  while ($in = fgets($handle,160)) {
    $in = preg_replace("/  */"," ",$in);
    list($user,$tpid) = explode(" ",$in);
    if ($pid != $tpid) $running = 1;
  }
  pclose($handle);
  return $running;
}

/**
  * Helper function to change GPS co-ords into decimals.
  */
function _imageloader_reformat_DMS2D($value, $ref) {
  if (!is_array($value)) {
    $value = array($value);
  }
  $dec = 0;
  $granularity = 0;
  foreach ($value as $element) {
    $parts = explode('/', $element);
    $dec += (float) (((float) $parts[0] /  (float) $parts[1]) / pow(60, $granularity));
    $granularity++;
  }
  if ($ref == 'S' || $ref == 'W') {
    $dec *= -1;
  }
  return $dec;
}

/**
 * Extract the Exif data from a file
 *   Date, Longitude, Latitude
 * @param type $inPath - path of the file to extract data from
 */
function _imageloader_extractExif($inPath) {
  $exifdata = exif_read_data($inPath);
  $datetime =  $exifdata[DateTime];
  print "      Time: $datetime\n";
  if (!empty($exifdata[GPSLatitude])) {
    $latitude  = _imageloader_reformat_DMS2D($exifdata[GPSLatitude],$exifdata[GPSLatitudeRef]);
    $longitude = _imageloader_reformat_DMS2D($exifdata[GPSLongitude],$exifdata[GPSLongitudeRef]);
    print("      Latitude:  $latitude\n");
    print("      Longitude: $longitude\n");
  }
  return array($datetime,$latitude,$longitude);
}

/**
 * Given a Source path for the file, make the destination path
 *
 **/

function makeFilePath($inPath,$createDate,$suffix) {
  global $filesDir;

  // Convert anthing that is not a character or number to _, delete duplicated _'s
  if (!isset($createDate)) {
     $createDate = date();
  }
  $createDate = preg_replace('?[:/]?','-',$createDate);
  $dirname = substr($createDate,0,10);
  $time = substr($createDate,11);
  $basename = $dirname . "_" . $time;
  $path = "pictures/$dirname";

  // Append number to each file to make it unique
  $i = 0;
  do {
    $filename = sprintf("%s_%g.%s",$basename,$i++,$suffix);
    $tpath = "$filesDir/$path/$filename";
    print("makeFilePath tpath $tpath -- $dirname  -- $filename\n");
  } while (file_exists($tpath));
  return array($path,$filename,$suffix);
}


function _imageloader_loadFile ($inPath,$username) {
  global $facilities;
  global $filesDir;
  global $puser;
  $tzoffset = -21600;

  if (preg_match('/\.jpg/i',$inPath))  {$type = "image"; $suffix = "jpg"; }
  if (preg_match('/\.png/i',$inPath))  {$type = "image"; $suffix = "png"; }
  if (preg_match('/\.jpeg/i',$inPath)) {$type = "image"; $suffix = "jpeg"; }
  if (preg_match('/\.gif/i',$inPath))  {$type = "image"; $suffix = "gif"; }
  if (preg_match('/\.mp4/i',$inPath))  {$type = "video"; $suffix = "mp4"; }
  if (!isset($suffix)) {
     print("File has invalid suffix: $inPath\n");
     return;
  }

  // extract EXIF time, latitude, longitude
  if ($type == "image") {
    list($createDate,$latitude,$longitude) = _imageloader_extractExif($inPath);
  } else {
     $createDate = preg_replace("/\.$suffix/i","",drupal_basename($inPath));
  }

  // do proximity search on latitude and longitude to find Facility
  if (isset($latitude))
    $facility = _imageloader_matchFacility($latitude,$longitude,$facilities);
  if (!isset($facility['name'])) {
    $facility['name'] = "New";
  }

  list($path,$filename,$suffix) = makeFilePath($inPath,$createDate,$suffix);
  if (!isset($path)) return; // Invalid file, cannot be loaded

  $ms = reset(taxonomy_get_term_by_name('New','media_status'));
  $msTid = $ms->tid;

  $user = user_load_by_name($username);
  $dpath = "$filesDir/$path/$filename";
  $uri   = "public://$path/$filename";

  // Move Image from Dropbox/Camera Uploads to Dropbox/Uploaded
  $cmd = "cp \"$inPath\" \"$dpath\"; chmod 666 $dpath";
  print "Execute: $cmd\n   $php_errormsg\n";
  if (!dir("$filesDir/$path")) {
    `mkdir $filesDir/$path; chmod 777 $filesDir/$path`; 
  }
  `$cmd`;
  //unlink($inPath);

  print "File: $filename $suffix $type\n";
  // Create the $file object and initialize it
  $file = new StdClass();
  $file->filemime  = "$type/$suffix";
  $file->filename  = $filename;
    
  $file->status    = '1';
  $file->timestamp = '';
  $file->type      = $type;
  $file->uid       = $puser->uid;
  $file->uri       = $uri;
  $file->field_create_date = array(
      'und'        => array (
        0             => array (
          'offset2'     => $tzoffset,
          'offset'      => $tzoffset,
          'show_todate' => 0,
          'timezone'    => 'America/Denver',
          'value'       => $createDate,
//        'value2'      => '2010-05-01 06:00:00',
      ),
    ),
  );
  $file->field_exif_date = array(
      'und'        => array (
        0             => array (
          'offset2'     => $tzoffset,
          'offset'      => $tzoffset,
          'show_todate' => 0,
          'timezone'    => 'America/Denver',
          'value'       => $createDate,
//        'value2'      => '2010-05-01 06:00:00',
      ),
    ),
  );
  $file->field_facility = array(
      'und'       => array(),
  );
  $file->field_media_status = array(
      'und'     => array (
        0         => array (
          'tid'     => $msTid,
      ),
    ),
  );
  if (isset($latitude)) {
    $file->field_geofield = array(
        'und'     => array (
          0         => array (
            'geo_type'   => 'point',
            'lat'   => $latitude,
            'lon'   => $longitude,
        ),
      ),
    );
  }
  $file->field_name = array(
      'und'     => array (
        0         => array (
          'value'   => '',
      ),
    ),
  );
  $file->field_search_field = array(
      'und'     => array (
        0         => array (
          'value'   => '',
      ),
    ),
  );

  file_save($file);

  $args = array(
    '@type' => file_entity_type_get_name($file),
    '%title' => entity_label('file', $file),
  );
  watchdog('file', '@type: updated %title.', $args);
  drupal_set_message(t('@type %title has been updated.', $args));
}

/**
 * Retrieve an array of facilities that have a latitude and longitude
 */
function _imageloader_getFacilities () {
  module_load_include('inc', 'node', 'content_types');
  drupal_load_module;
//module_load_include('inc','database','database.inc');
  $results = db_query('SELECT title,nid,geo.field_geofield_lat,geo.field_geofield_lon 
                       FROM {node} 
                       LEFT JOIN {field_data_field_geofield} geo ON nid = geo.entity_id
                       WHERE type = :type',array(':type' => 'facility'));
  $facilities = array();
  foreach ($results as $facility) {
    if (!empty($facility->field_geofield_lat)) {
      $facilities[$facility->title] = array(
        'nid'       => $facility->nid,
        'latitude'  => $facility->field_geofield_lat,
        'longitude' => $facility->field_geofield_lon,
      );
    }
  }
  return $facilities;
}


function _imageloader_matchFacility($latitude,$longitude) {
  global $facilities;
  foreach ($facilities as $facilityname => $facility) {
    $adistance = abs($latitude  - $facility['latitude']);
    $odistance = abs($longitude - $facility['longitude']);
    $distance = abs($latitude  - $facility['latitude']) 
              + abs($longitude - $facility['longitude']);
    if (!isset($match)) {
      $match = $facility;
      $match['distance']  = $distance;
    } 
    else {
      if ($distance < $match['distance']) {
        $match = $facility;
        $match['distance'] = $distance;
        $match['name'] = $facilityname;
      }
    }
  }
  print "Facility found - " . $match['name'] . "\n";
  return $match;
}
