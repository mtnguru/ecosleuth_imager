#!/usr/bin/php -q
<?php
/*
 * This script is used to manually create nodes
 *
 */

$drupalRoot = "/var/www/dug";
$bootstrap  = "../../includes/bootstrap.inc";
$chdir      = "/var/www/dug/sites/dug1";

// $drupalRoot = "/home/drupal/drupal-7.16/";
// $bootstrap  = "../../includes/bootstrap.inc";
// $chdir      = "/home/drupal/drupal-7.16/sites/cows10";

print "\n";
print "drupalRoot: $drupalRoot\n";
print "chdir:      $chdir\n";
print "bootstrap:  $bootstrap\n\n";

chdir($chdir);

$uid = 1;

// prevent this from running under apache:
if (array_key_exists('REQUEST_METHOD', $_SERVER)) {
    echo 'nope.  not executing except from the command line.';
    exit(1);
}

// set HTTP_HOST or drupal will refuse to bootstrap
$_SERVER['HTTP_HOST'] = 'dug';
$_SERVER['REMOTE_ADDR'] = '127.0.0.1';

define('DRUPAL_ROOT', $drupalRoot);

include_once $bootstrap;
print "Try bootstrap\n";
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

print "damn\n";
print '<pre>';
print_r(node_load(1));
print '</pre>';
