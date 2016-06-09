<?php
/**
 * Implements hook_views_data().
 */
function ecoMedia_views_data() {
  // Build an array named after each DB table you're describing. In our case,
  // just mymodule_table.
  $data['ecoMedia_table'] = array();
//$data['mymodule_table'] = array(
    // First give some general information about the table as a data source.
//  'table' => array(
      // The grouping for this field/filter/sort in the Views UI.
//    'group' => t('Example Views Stuff'),
//    'base' => array(
//      'field' => 'naid', // This is the identifier field for the view.
//      'title' => t('Example Views API Data'),
//      'help' => t('Names provided by the Mymodule module.'),
//    ),
//  ),
//);
  return $data;
}

