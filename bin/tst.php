#!/usr/bin/php -q
<?php
function convDate ($sdate) {
   $s = sscanf($sdate,"%g deg %g' %g %s");
   return $m = $s[0] + (float)($s[1])/60.0 + (float)($s[2])/3600.0;   
}



$date = _imageloader_getfiledate("/tmp/rewrite.log");
print "Date $date\n";

function _imageloader_getfiledate($path) {
   $stat = stat($path);
   $ctime = $stat[ctime];
   print "ctime $ctime\n";
   print date("Y:m:d G:i:s",$ctime);
   $date = "wow";
   return $date;
}
