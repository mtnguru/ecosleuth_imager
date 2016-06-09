#!/usr/bin/php -q
<?php
function convDate ($sdate) {
   $s = sscanf($sdate,"%g deg %g' %g %s");
   return $m = $s[0] + (float)($s[1])/60.0 + (float)($s[2])/3600.0;   
}


$latitude  = "40 deg 24' 32.18 W";
$longitude = "104 deg 41' 1.43 W";

$lat  = convDate($latitude);
$long = convDate($longitude);

print "Latitude: $latitude $lat\n";
print "Longitude: $longitude $long\n";

$dirs = array("/home/cows/cows9",
              "/home/cows/Dropbox/James Sorensen",
              "/home/cows/Dropbox/James Sorensen/Camera Uploads",
              "/home/cows/Dropbox/James Sorensen/Camera Uploads/2013-06-20 08.52.47.jpg",
              "/home/cows/Dropbox/James Sorensen/Camera Uploads/2013-06-20 08.52.47.jph",
              "/home/cows/Dropbox/James Sorensen/Uploaded",
              "/var/www/cows");

print "Dude " . $argv[1] . "\n";
