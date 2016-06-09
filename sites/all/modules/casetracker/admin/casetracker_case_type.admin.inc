<?php

/**
 * @file
 * CaseTrackerCase type editing UI.
 */

/**
 * UI controller.
 */
class CaseTrackerCaseTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    $items[$this->path]['description'] = 'Manage case entity types, including adding
		and removing fields and the display of fields.';
    return $items;
  }

}

/**
 * Generates the case type editing form.
 */
function casetracker_case_type_form($form, &$form_state, $case_type, $op = 'edit') {

  if ($op == 'clone') {
    $case_type->label .= ' (cloned)';
    $case_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $case_type->label,
    '#description' => t('The human-readable name of this case type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($case_type->type) ? $case_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'casetracker_case_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this case type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save case type'),
    '#weight' => 40,
    '#suffix' => l(t('Cancel'), 'admin/structure/casetracker/case-types')
  );

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function casetracker_case_type_form_submit(&$form, &$form_state) {
  $case_type = entity_ui_form_submit_build_entity($form, $form_state);

  // If we create new case type we need to add default fields to it.
  if ($form_state['op'] == 'add') {
    casetracker_case_type_add_default_fields($case_type);
    drupal_set_message(t('Case type "@title" was created successfully', array('@title' => $case_type->label)));
  }
  else {
    drupal_set_message(t('Case type "@title" was edited successfully', array('@title' => $case_type->label)));
  }

  $case_type->save();
  $form_state['redirect'] = 'admin/structure/casetracker/case-types';
}

/**
 * Form API submit callback for the delete button.
 */
function casetracker_case_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/casetracker/case-types/manage/' . $form_state['casetracker_case_type']->type . '/delete';
}

/**
 * Add default fields to newly created case type.
 * P.S: needs to be in this file, because casetracker.install doesn't found 
 * the casetracker.fields file to create and remove fields
 */
function casetracker_case_type_add_default_fields($case_type) {

  $type = $case_type->type;

  module_load_include('inc', 'casetracker', 'casetracker_case.fields');
  $fields = _casetracker_case_type_default_fields();

  // Create the fields if they don't exist
  foreach ($fields as $field) {
    $info = field_info_field($field['field_name']);
    if (empty($info)) {
      field_create_field($field);
    }
  }

  // Create field instances for the type if they don't exist
  $instances = array();

  // Project related field.
  $instances[] = array(
    'field_name' => 'field_project_ref',
    'entity_type' => 'casetracker_case',
    'bundle' => $type,
    'label' => t('Project'),
    'required' => TRUE,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'weight' => 1,
      'type' => 'entityreference_autocomplete_tags',
      'module' => 'entityreference',
      'active' => 1,
      'settings' => array(
        'match_operator' => 'CONTAINS',
        'size' => 60,
        'path' => '',
      ),
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );

  // Date field.
  $instances[] = array(
    'field_name' => 'field_casetracker_case_due_date',
    'entity_type' => 'casetracker_case',
    'bundle' => $type,
    'label' => t('Due Date'),
    'required' => FALSE,
    'settings' => array(
      'default_value' => 'blank',
      'default_value_code' => '',
      'default_value2' => 'blank',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'weight' => 2,
      'type' => 'date_popup',
      'module' => 'date',
      'active' => 1,
      'settings' => array(
        'input_format' => 'm/d/Y',
        'input_format_custom' => '',
        'year_range' => '-3:+3',
        'increment' => '15',
        'label_position' => 'above',
        'text_parts' => array(),
        'repeat_collapsed' => 0,
      ),
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );

  // Description field.
  $instances[] = array(
    'field_name' => 'field_casetracker_case_desc',
    'entity_type' => 'casetracker_case',
    'bundle' => $type,
    'label' => t('Description'),
    'required' => FALSE,
    'settings' => array(
      'text_processing' => '1',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'weight' => 3,
      'type' => 'text_textarea',
      'module' => 'text',
      'active' => 1,
      'settings' => array(
        'rows' => 5,
      ),
    ),
    'display' => array(
      'default' => array(
        'label' => 'above',
        'type' => 'text_default',
        'settings' => array(),
        'module' => 'text',
        'weight' => 2,
      ),
    ),
  );

  // Status field.
  $instances[] = array(
    'field_name' => 'field_casetracker_case_status',
    'entity_type' => 'casetracker_case',
    'bundle' => $type,
    'label' => t('Status'),
    'required' => TRUE,
    'default_value_function' => 'casetracker_case_status_set_default_value',
    'widget' => array(
      'weight' => 4,
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
  );

  // Priority field.
  $instances[] = array(
    'field_name' => 'field_casetracker_case_priority',
    'entity_type' => 'casetracker_case',
    'bundle' => $type,
    'label' => t('Priority'),
    'required' => TRUE,
    'widget' => array(
      'weight' => 5,
    ),
  );

  // Assign to field.
  $instances[] = array(
    'field_name' => 'field_casetracker_case_assign_to',
    'entity_type' => 'casetracker_case',
    'bundle' => $type,
    'label' => t('Assign to'),
    'required' => FALSE,
    'widget' => array(
      'weight' => 6,
    ),
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden',
      ),
    ),
    'foreign keys' => array(
      'node' => array(
        'columns' => array(
          'target_id' => 'nid',
        ),
        'table' => 'node',
      ),
    ),
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => '0',
    'module' => 'entityreference',
    'settings' => array(
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'sort' => array(
          'direction' => 'ASC',
          'field' => 'property',
          'property' => 'name',
          'type' => 'property',
        ),
        'target_bundles' => array(),
      ),
      'handler_submit' => 'Change handler',
      'target_type' => '',
    ),
    'translatable' => '0', 'type' => 'entityreference',
  );

  // Create field instances if they don't exist
  foreach ($instances as $instance) {
    $info_instance = field_info_instance('casetracker_case', $instance['field_name'], $type);
    if (empty($info_instance)) {
      field_create_instance($instance);
    }
  }
}

/**
 * @return
 *   Return default fields definition that have to be attached to newly created
 *   case type.
 *
 * @see field_create_field()
 */
function _casetracker_case_type_default_fields() {

  $fields = array();

  // Project related field.
  $fields[] = array(
    'field_name' => 'field_project_ref',
    'type' => 'entityreference',
    'entity_types' => array('casetracker_case'),
    'translatable' => FALSE,
    'locked' => TRUE,
    'settings' => array(
      'target_type' => 'casetracker_project',
      'handler' => 'base',
      'handler_submit' => 'Change handler',
      'handler_settings' => array('target_bundles' => array()),
    ),
    'cardinality' => -1,
  );

  // Date field.
  $fields[] = array(
    'field_name' => 'field_casetracker_case_due_date',
    'type' => 'datetime',
    'module' => 'date',
    'active' => TRUE,
    'entity_types' => array('casetracker_case'),
    'translatable' => FALSE,
    'locked' => TRUE,
    'settings' => array(
      'repeat' => 0,
      'granularity' => array(
        'month' => 'month',
        'day' => 'day',
        'year' => 'year',
      ),
      'tz_handling' => 'site',
      'timezone_db' => 'UTC',
      'todate' => '',
    ),
    'cardinality' => 1,
  );

  // Description field.
  $fields[] = array(
    'field_name' => 'field_casetracker_case_desc',
    'type' => 'text_long',
    'entity_types' => array('casetracker_case'),
    'translatable' => FALSE,
    'locked' => TRUE,
    'module' => 'text',
    'settings' => array(),
    'cardinality' => 1,
  );

  // Status field.
  $fields[] = array(
    'field_name' => 'field_casetracker_case_status',
    'type' => 'list_text',
    'entity_types' => array('casetracker_case'),
    'translatable' => TRUE,
    'locked' => TRUE,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'open' => t('Open'),
        'resolved' => t('Resolved'),
        'deferred' => t('Deferred'),
        'duplicate' => t('Duplicate'),
        'closed' => t('Closed'),
      ),
    ),
    'cardinality' => 1,
  );

  // Status field.
  $fields[] = array(
    'field_name' => 'field_casetracker_case_priority',
    'type' => 'list_text',
    'entity_types' => array('casetracker_case'),
    'translatable' => TRUE,
    'locked' => FALSE,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'high' => t('High'),
        'normal' => t('Normal'),
        'low' => t('Low'),
      ),
    ),
    'cardinality' => 1,
  );

  // Assign to field.
  $fields[] = array(
    'field_name' => 'field_casetracker_case_assign_to',
    'type' => 'entityreference',
    'entity_types' => array('casetracker_case'),
    'translatable' => TRUE,
    'locked' => TRUE,
    'active' => '1',
    'cardinality' => '1',
    'deleted' => '0',
    'foreign keys' => array(
      'node' => array(
        'columns' => array(
          'target_id' => 'uid',
        ),
        'table' => 'users',
      ),
    ),
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'module' => 'casetracker',
    'settings' => array(
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'sort' => array(
          'direction' => 'ASC',
          'field' => 'property',
          'property' => 'name',
          'type' => 'property',
        ),
        'target_bundles' => array(),
      ),
      'handler_submit' => 'Change handler',
      'target_type' => 'user',
    ),
  );

  return $fields;
}

/**
 * Specify the value to be used as default value in the status field
 */
function casetracker_case_status_set_default_value() {
  // This is enough for now. Will evolve in time.
  return 'open';
}

/**
 * Specify the value to be used as default value in the priority field
 */
function casetracker_case_priority_set_default_value() {
  // This is enough for now. Will evolve in time.
  return 'normal';
}