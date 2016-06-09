<?php

/**
 * @file
 * Providing extra functionality for the Model UI via views.
 */

/**
 * Implements hook_views_default_views().
 */
function casetracker_views_default_views() {

  $view = new view;
  $view->name = 'casetracker_case_listing';
  $view->description = 'Listing of all cases';
  $view->tag = 'Case Tracker';
  $view->base_table = 'casetracker_case';
  $view->human_name = 'Cases - Listing';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Case Tracker - Cases';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access case tracker pages';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'cid' => 'cid',
    'pid' => 'pid',
    'title_1' => 'title_1',
    'title' => 'title',
    'changed' => 'changed',
    'field_casetracker_case_due_date' => 'field_casetracker_case_due_date',
    'field_casetracker_case_status' => 'field_casetracker_case_status',
    'field_casetracker_case_assign_to' => 'field_casetracker_case_assign_to',
    'edit_casetracker_case' => 'edit_casetracker_case',
    'delete_casetracker_case' => 'delete_casetracker_case',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'cid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'pid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_casetracker_case_due_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_casetracker_case_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_casetracker_case_assign_to' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_casetracker_case' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_casetracker_case' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No cases available.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_project_ref_target_id']['id'] = 'field_project_ref_target_id';
  $handler->display->display_options['relationships']['field_project_ref_target_id']['table'] = 'field_data_field_project_ref';
  $handler->display->display_options['relationships']['field_project_ref_target_id']['field'] = 'field_project_ref_target_id';
  $handler->display->display_options['relationships']['field_project_ref_target_id']['label'] = 'Project ref';
  $handler->display->display_options['relationships']['field_project_ref_target_id']['required'] = 0;
  /* Field: Case: Case ID */
  $handler->display->display_options['fields']['cid']['id'] = 'cid';
  $handler->display->display_options['fields']['cid']['table'] = 'casetracker_case';
  $handler->display->display_options['fields']['cid']['field'] = 'cid';
  $handler->display->display_options['fields']['cid']['label'] = 'ID';
  $handler->display->display_options['fields']['cid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['cid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['cid']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['cid']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['cid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['cid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['cid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['cid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['cid']['format_plural'] = 0;
  /* Field: Project: Project ID */
  $handler->display->display_options['fields']['pid']['id'] = 'pid';
  $handler->display->display_options['fields']['pid']['table'] = 'casetracker_project';
  $handler->display->display_options['fields']['pid']['field'] = 'pid';
  $handler->display->display_options['fields']['pid']['relationship'] = 'field_project_ref_target_id';
  $handler->display->display_options['fields']['pid']['label'] = '';
  $handler->display->display_options['fields']['pid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['pid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['pid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['pid']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['pid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['pid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['pid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['pid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['pid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['pid']['format_plural'] = 0;
  /* Field: Project: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'casetracker_project';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'field_project_ref_target_id';
  $handler->display->display_options['fields']['title_1']['label'] = 'Project';
  $handler->display->display_options['fields']['title_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['title_1']['alter']['path'] = 'casetracker/project/[pid]';
  $handler->display->display_options['fields']['title_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title_1']['hide_alter_empty'] = 1;
  /* Field: Case: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'casetracker_case';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  /* Field: Case: Last update */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'casetracker_case';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Last updated';
  $handler->display->display_options['fields']['changed']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['external'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['changed']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['changed']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['html'] = 0;
  $handler->display->display_options['fields']['changed']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['changed']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['changed']['hide_empty'] = 0;
  $handler->display->display_options['fields']['changed']['empty_zero'] = 0;
  $handler->display->display_options['fields']['changed']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['changed']['date_format'] = 'time span';
  /* Field: Case: Due Date */
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['id'] = 'field_casetracker_case_due_date';
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['table'] = 'field_data_field_casetracker_case_due_date';
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['field'] = 'field_casetracker_case_due_date';
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['field_api_classes'] = 0;
  /* Field: Case: Status */
  $handler->display->display_options['fields']['field_casetracker_case_status']['id'] = 'field_casetracker_case_status';
  $handler->display->display_options['fields']['field_casetracker_case_status']['table'] = 'field_data_field_casetracker_case_status';
  $handler->display->display_options['fields']['field_casetracker_case_status']['field'] = 'field_casetracker_case_status';
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_status']['field_api_classes'] = 0;
  /* Field: Case: Assign to */
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['id'] = 'field_casetracker_case_assign_to';
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['table'] = 'field_data_field_casetracker_case_assign_to';
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['field'] = 'field_casetracker_case_assign_to';
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['label'] = 'Assigned to';
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_casetracker_case_assign_to']['field_api_classes'] = 0;
  /* Field: Case: Edit Link */
  $handler->display->display_options['fields']['edit_casetracker_case']['id'] = 'edit_casetracker_case';
  $handler->display->display_options['fields']['edit_casetracker_case']['table'] = 'casetracker_case';
  $handler->display->display_options['fields']['edit_casetracker_case']['field'] = 'edit_casetracker_case';
  $handler->display->display_options['fields']['edit_casetracker_case']['label'] = '';
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['external'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['html'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_casetracker_case']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['edit_casetracker_case']['hide_empty'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['empty_zero'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['hide_alter_empty'] = 1;
  /* Field: Case: Delete Link */
  $handler->display->display_options['fields']['delete_casetracker_case']['id'] = 'delete_casetracker_case';
  $handler->display->display_options['fields']['delete_casetracker_case']['table'] = 'casetracker_case';
  $handler->display->display_options['fields']['delete_casetracker_case']['field'] = 'delete_casetracker_case';
  $handler->display->display_options['fields']['delete_casetracker_case']['label'] = '';
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['external'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['html'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['delete_casetracker_case']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['delete_casetracker_case']['hide_empty'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['empty_zero'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['hide_alter_empty'] = 1;
  /* Sort criterion: Case: Last update */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'casetracker_case';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  /* Filter criterion: Case: Status (field_casetracker_case_status) */
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['id'] = 'field_casetracker_case_status_value';
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['table'] = 'field_data_field_casetracker_case_status';
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['field'] = 'field_casetracker_case_status_value';
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['value'] = array(
    'open' => 'open',
  );
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['group'] = 1;
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['expose']['operator_id'] = 'field_casetracker_case_status_value_op';
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['expose']['operator'] = 'field_casetracker_case_status_value_op';
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['expose']['identifier'] = 'field_casetracker_case_status_value';
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['expose']['multiple'] = 1;
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['expose']['reduce'] = 0;
  /* Filter criterion: Case: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'casetracker_case';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title contains';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['required'] = 0;
  $handler->display->display_options['filters']['title']['expose']['multiple'] = FALSE;
  /* Filter criterion: Case: Assign to (field_casetracker_case_assign_to) */
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['id'] = 'field_casetracker_case_assign_to_target_id';
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['table'] = 'field_data_field_casetracker_case_assign_to';
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['field'] = 'field_casetracker_case_assign_to_target_id';
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['group'] = 1;
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['expose']['operator_id'] = 'field_casetracker_case_assign_to_target_id_op';
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['expose']['label'] = 'Assigned to';
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['expose']['operator'] = 'field_casetracker_case_assign_to_target_id_op';
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['expose']['identifier'] = 'field_casetracker_case_assign_to_target_id';
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['expose']['multiple'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/content/casetracker/cases';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Cases';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Case Tracker';
  $handler->display->display_options['tab_options']['weight'] = '0';

  $views['casetracker_case_listing'] = $view;

  $view = new view;
  $view->name = 'casetracker_project_listing';
  $view->description = 'Listing of projects';
  $view->tag = 'Case Tracker';
  $view->base_table = 'casetracker_project';
  $view->human_name = 'Projects - Listing';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Case Tracker - Projects';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access case tracker pages';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'pid' => 'pid',
    'type' => 'type',
    'title' => 'title',
    'created' => 'created',
    'nothing_1' => 'nothing_1',
    'operations' => 'operations',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'pid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No projects available.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Field: Project: Project ID */
  $handler->display->display_options['fields']['pid']['id'] = 'pid';
  $handler->display->display_options['fields']['pid']['table'] = 'casetracker_project';
  $handler->display->display_options['fields']['pid']['field'] = 'pid';
  $handler->display->display_options['fields']['pid']['label'] = 'ID';
  $handler->display->display_options['fields']['pid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['pid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['pid']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['pid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['pid']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['pid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['pid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['pid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['pid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['pid']['format_plural'] = 0;
  /* Field: Project: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'casetracker_project';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'casetracker/project/[pid]';
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  /* Field: Project: Creation date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'casetracker_project';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created in';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'm/d/Y';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = 'view all cases';
  $handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['nothing_1']['alter']['path'] = 'casetracker/project/[pid]/cases';
  $handler->display->display_options['fields']['nothing_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nothing_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing_1']['hide_alter_empty'] = 0;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['edit_casetracker_project']['id'] = 'edit_casetracker_project';
  $handler->display->display_options['fields']['edit_casetracker_project']['table'] = 'casetracker_project';
  $handler->display->display_options['fields']['edit_casetracker_project']['field'] = 'edit_casetracker_project';
  $handler->display->display_options['fields']['edit_casetracker_project']['label'] = '';
  $handler->display->display_options['fields']['edit_casetracker_project']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_project']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_project']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_project']['alter']['external'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_project']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_project']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_project']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_project']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['edit_casetracker_project']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['edit_casetracker_project']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_project']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_project']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_project']['alter']['html'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_project']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_casetracker_project']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['edit_casetracker_project']['hide_empty'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_project']['empty_zero'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_project']['hide_alter_empty'] = 1;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['delete_casetracker_project']['id'] = 'delete_casetracker_project';
  $handler->display->display_options['fields']['delete_casetracker_project']['table'] = 'casetracker_project';
  $handler->display->display_options['fields']['delete_casetracker_project']['field'] = 'delete_casetracker_project';
  $handler->display->display_options['fields']['delete_casetracker_project']['label'] = '';
  $handler->display->display_options['fields']['delete_casetracker_project']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_project']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_project']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_project']['alter']['external'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_project']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_project']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_project']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_project']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['delete_casetracker_project']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['delete_casetracker_project']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_project']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_project']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_project']['alter']['html'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_project']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['delete_casetracker_project']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['delete_casetracker_project']['hide_empty'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_project']['empty_zero'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_project']['hide_alter_empty'] = 1;
  /* Sort criterion: Project: Last update */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'casetracker_project';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  /* Filter criterion: Project: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'casetracker_project';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title contains';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['required'] = 0;
  $handler->display->display_options['filters']['title']['expose']['multiple'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/content/casetracker/projects';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Projects';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;

  $views['casetracker_project_listing'] = $view;

  $view = new view;
  $view->name = 'casetracker_project_cases';
  $view->description = 'Listing of cases from a particular project';
  $view->tag = 'Case Tracker';
  $view->base_table = 'casetracker_case';
  $view->human_name = 'Project - Cases';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access case tracker pages';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'cid' => 'cid',
    'type' => 'type',
    'title' => 'title',
    'field_casetracker_case_status' => 'field_casetracker_case_status',
    'field_casetracker_case_due_date' => 'field_casetracker_case_due_date',
    'changed' => 'changed',
    'name' => 'name',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'cid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_casetracker_case_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_casetracker_case_due_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No cases available.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_project_ref_target_id']['id'] = 'field_project_ref_target_id';
  $handler->display->display_options['relationships']['field_project_ref_target_id']['table'] = 'field_data_field_project_ref';
  $handler->display->display_options['relationships']['field_project_ref_target_id']['field'] = 'field_project_ref_target_id';
  $handler->display->display_options['relationships']['field_project_ref_target_id']['label'] = 'Project';
  $handler->display->display_options['relationships']['field_project_ref_target_id']['required'] = 1;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_casetracker_case_assign_to_target_id']['id'] = 'field_casetracker_case_assign_to_target_id';
  $handler->display->display_options['relationships']['field_casetracker_case_assign_to_target_id']['table'] = 'field_data_field_casetracker_case_assign_to';
  $handler->display->display_options['relationships']['field_casetracker_case_assign_to_target_id']['field'] = 'field_casetracker_case_assign_to_target_id';
  $handler->display->display_options['relationships']['field_casetracker_case_assign_to_target_id']['label'] = 'Assign to';
  $handler->display->display_options['relationships']['field_casetracker_case_assign_to_target_id']['required'] = 0;
  /* Field: Case: Case ID */
  $handler->display->display_options['fields']['cid']['id'] = 'cid';
  $handler->display->display_options['fields']['cid']['table'] = 'casetracker_case';
  $handler->display->display_options['fields']['cid']['field'] = 'cid';
  $handler->display->display_options['fields']['cid']['label'] = 'ID';
  $handler->display->display_options['fields']['cid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['cid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['cid']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['cid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['cid']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['cid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['cid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['cid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['cid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['cid']['format_plural'] = 0;
  /* Field: Case: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'casetracker_case';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  /* Field: Case: Last update */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'casetracker_case';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Last updated';
  $handler->display->display_options['fields']['changed']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['external'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['changed']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['changed']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['html'] = 0;
  $handler->display->display_options['fields']['changed']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['changed']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['changed']['hide_empty'] = 0;
  $handler->display->display_options['fields']['changed']['empty_zero'] = 0;
  $handler->display->display_options['fields']['changed']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* Field: Case: Due Date */
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['id'] = 'field_casetracker_case_due_date';
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['table'] = 'field_data_field_casetracker_case_due_date';
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['field'] = 'field_casetracker_case_due_date';
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['type'] = 'format_interval';
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['settings'] = array(
    'interval' => '2',
    'interval_display' => 'time ago',
  );
  $handler->display->display_options['fields']['field_casetracker_case_due_date']['field_api_classes'] = 0;
  /* Field: Case: Status */
  $handler->display->display_options['fields']['field_casetracker_case_status']['id'] = 'field_casetracker_case_status';
  $handler->display->display_options['fields']['field_casetracker_case_status']['table'] = 'field_data_field_casetracker_case_status';
  $handler->display->display_options['fields']['field_casetracker_case_status']['field'] = 'field_casetracker_case_status';
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_casetracker_case_status']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_casetracker_case_status']['field_api_classes'] = 0;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'field_casetracker_case_assign_to_target_id';
  $handler->display->display_options['fields']['name']['label'] = 'Assigned to';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 1;
  $handler->display->display_options['fields']['name']['format_username'] = 0;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['edit_casetracker_case']['id'] = 'edit_casetracker_case';
  $handler->display->display_options['fields']['edit_casetracker_case']['table'] = 'casetracker_case';
  $handler->display->display_options['fields']['edit_casetracker_case']['field'] = 'edit_casetracker_case';
  $handler->display->display_options['fields']['edit_casetracker_case']['label'] = '';
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['external'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['alter']['html'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_casetracker_case']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['edit_casetracker_case']['hide_empty'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['empty_zero'] = 0;
  $handler->display->display_options['fields']['edit_casetracker_case']['hide_alter_empty'] = 1;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['delete_casetracker_case']['id'] = 'delete_casetracker_case';
  $handler->display->display_options['fields']['delete_casetracker_case']['table'] = 'casetracker_case';
  $handler->display->display_options['fields']['delete_casetracker_case']['field'] = 'delete_casetracker_case';
  $handler->display->display_options['fields']['delete_casetracker_case']['label'] = '';
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['external'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['alter']['html'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['delete_casetracker_case']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['delete_casetracker_case']['hide_empty'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['empty_zero'] = 0;
  $handler->display->display_options['fields']['delete_casetracker_case']['hide_alter_empty'] = 1;
  /* Sort criterion: Case: Last update */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'casetracker_case';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  /* Contextual filter: Project: Project ID */
  $handler->display->display_options['arguments']['pid']['id'] = 'pid';
  $handler->display->display_options['arguments']['pid']['table'] = 'casetracker_project';
  $handler->display->display_options['arguments']['pid']['field'] = 'pid';
  $handler->display->display_options['arguments']['pid']['relationship'] = 'field_project_ref_target_id';
  $handler->display->display_options['arguments']['pid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['pid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['pid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['pid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['pid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['pid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['pid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['pid']['not'] = 0;
  /* Filter criterion: Case: Status (field_casetracker_case_status) */
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['id'] = 'field_casetracker_case_status_value';
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['table'] = 'field_data_field_casetracker_case_status';
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['field'] = 'field_casetracker_case_status_value';
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['value'] = array(
    'open' => 'open',
  );
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['group'] = 1;
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['expose']['operator_id'] = 'field_casetracker_case_status_value_op';
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['expose']['operator'] = 'field_casetracker_case_status_value_op';
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['expose']['identifier'] = 'field_casetracker_case_status_value';
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['expose']['multiple'] = 1;
  $handler->display->display_options['filters']['field_casetracker_case_status_value']['expose']['reduce'] = 0;
  /* Filter criterion: Case: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'casetracker_case';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title contains';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['required'] = 0;
  $handler->display->display_options['filters']['title']['expose']['multiple'] = FALSE;
  /* Filter criterion: Case: Assign to (field_casetracker_case_assign_to) */
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['id'] = 'field_casetracker_case_assign_to_target_id';
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['table'] = 'field_data_field_casetracker_case_assign_to';
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['field'] = 'field_casetracker_case_assign_to_target_id';
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['group'] = 1;
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['expose']['operator_id'] = 'field_casetracker_case_assign_to_target_id_op';
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['expose']['label'] = 'Assigned to';
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['expose']['operator'] = 'field_casetracker_case_assign_to_target_id_op';
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['expose']['identifier'] = 'field_casetracker_case_assign_to_target_id';
  $handler->display->display_options['filters']['field_casetracker_case_assign_to_target_id']['expose']['multiple'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'casetracker/project/%/cases';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'View all cases';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Case Tracker';
  $handler->display->display_options['tab_options']['weight'] = '0';

  $views['casetracker_project_cases'] = $view;
  return $views;
}