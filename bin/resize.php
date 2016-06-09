#!/usr/bin/php -q
<?php
/*
 * @file
 * 
 * Script to create a resized image - debugging a problem with thumbnails not displaying
 *
 * 
 */

error_reporting(E_ALL);
//ini_set('display_errors',TRUE);
//ini_set('display_startup_errors',TRUE);
//ini_set('max_execution_time',18000);

global $php_errormsg;
$tzoffset = -21600;

if (!isset($argv[1])) {
   print "You must specify a Drupal installation: imageloader.php [randy|cows]\n";
   exit(0);
}

if ($argv[1] == "cows") {
   $user = "cows";
   $host = "d";
   $sitename = "c15";
} else if ($argv[1] == "randy") {
   $user = "randy";
   $host = "d";
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
print "   user:       $user\n";
print "   host:       $host\n";
print "   sitename:   $sitename\n";
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
print "dude\n";

global $user;
$user->uid = 1;


$style = "ds_thumbnail";
$source = "public://pictures/2012-12-20/2012-12-20_M-&-J-Dairy---Kersey_3.jpg";
$destination = "public://styles/ds_thumbnail/public/pictures/2012-12-20/2012-12-20_M-&-J-Dairy---Kersey_3.jpg";

print "call _imageresize\n";
_imageresize($style,$source,$destination);
print "done _imageresize\n";

function _imageresize($style, $source, $destination) {
  // If the source file doesn't exist, return FALSE without creating folders.
  print "image_load $source\n";
  if (!$image = image_load($source)) {
    return FALSE;
  }
  print "done loaded\n";

  // Get the folder for the final location of this style.
  $directory = drupal_dirname($destination);

  // Build the destination folder tree if it doesn't already exist.
  if (!file_prepare_directory($directory, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
    watchdog('image', 'Failed to create style directory: %directory', array('%directory' => $directory), WATCHDOG_ERROR);
    return FALSE;
  }
  $width = 150;
  $height = 150;
  $res = image_gd_create_tmp($image,$width,$height);
  if (!imagecopyresampled($res, $image->resource, 0, 0, 0, 0, $width, $height, $image->info['width'], $image->info['height'])) {
    return FALSE;
  }
  imagedestroy($image_data->resource);
  $image->resource = $res;
  $image->info['width'] = $width;
  $image->info['height'] = $height;
  
  
//foreach ($style['effects'] as $effect) {
//  image_effect_apply($image, $effect);
//}

  if (!image_save($image, $destination)) {
    if (file_exists($destination)) {
      watchdog('image', 'Cached image file %destination already exists. There may be an issue with your rewrite configuration.', array('%destination' => $destination), WATCHDOG_ERROR);
    }
    return FALSE;
  }

  return TRUE;
}

