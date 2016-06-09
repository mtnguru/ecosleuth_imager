<?php

/**
 * 
 * @file This file have the page callback functions that are called in hook_menu()
 */
function casetracker_overview() {

  try {

    $query = db_query("
      SELECT p.pid, p.title as project, s.field_casetracker_case_status_value as status, count(s.field_casetracker_case_status_value) as qtd
      FROM {casetracker_case} c 
      JOIN {field_data_field_project_ref} pr ON pr.bundle = 'casetracker_case_basic' AND pr.entity_id = c.cid
      INNER JOIN {casetracker_project} p ON pr.field_project_ref_target_id = p.pid
      JOIN {field_data_field_casetracker_case_status} s ON s.bundle = 'casetracker_case_basic' AND s.entity_id = c.cid
      GROUP BY p.title, status"
    );
    $results = $query->fetchAll();

    $field_status = field_read_field('field_casetracker_case_status');

    $header[] = t('Project');
    foreach ($field_status['settings']['allowed_values'] as $key => $value) {
      $header[] = $value;
    }

    $data = array();
    $i = 0;
    foreach ($results as $item) {
      if (!isset($data[$item->pid])) {
        $data[$item->pid] = array('project' => l($item->project, 'casetracker/project/' . $item->pid . '/cases'), 'cases' => array());
        foreach ($field_status['settings']['allowed_values'] as $key => $value) {
          $data[$item->pid]['cases'][$key] = 0;
        }
      }
      $data[$item->pid]['cases'][$item->status] = $item->qtd;
    }

//    print_r($data);

    $i = 0;
    $rows = array();
    foreach ($data as $item) {
      $rows[$i] = array($item['project']);
      foreach ($item['cases'] as $case_status) {
        $rows[$i][] = $case_status;
      }
      $i++;
    }

    $table_element = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t("You don't have any cases yet."),
    );

    return drupal_render($table_element);
  } catch (PDOException $e) {
    drupal_set_message(t('You need at least 1 Project Type and 1 Case type configured to start using Case Tracker'), 'error');
    watchdog('ERROR', $e->getMessage());
    return '';
  }
}

function casetracker_admin_dashboard() {

  $local_cases = menu_local_tasks();
  $content = array();
  foreach ($local_cases['tabs']['output'] as $case) {
    $content[] = $case['#link'];
  }

  if ($content) {
    $output = theme('admin_block_content', array('content' => $content));
  }
  else {
    $output = t('You do not have any Case Tracker items. Some module may be removing'
        . 'the default Case Tracker items.');
  }
  return $output;
}