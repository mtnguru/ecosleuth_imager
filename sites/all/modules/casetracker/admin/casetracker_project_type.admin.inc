<?php

/**
 * @file
 * CaseTrackerProject type editing UI.
 */

/**
 * UI controller.
 */
class CaseTrackerProjectTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    $items[$this->path]['description'] = 'Manage project entity types, including adding
		and removing fields and the display of fields.';
    return $items;
  }

}

/**
 * Generates the project type editing form.
 */
function casetracker_project_type_form($form, &$form_state, $project_type, $op = 'edit') {

  if ($op == 'clone') {
    $project_type->label .= ' (cloned)';
    $project_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $project_type->label,
    '#description' => t('The human-readable name of this project type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($project_type->type) ? $project_type->type : '',
    '#maxlength' => 32,
    '#machine_name' => array(
      'exists' => 'casetracker_project_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this project type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save project type'),
    '#weight' => 40,
    '#suffix' => l(t('Cancel'), 'admin/structure/casetracker/project-types')
  );

  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function casetracker_project_type_form_submit(&$form, &$form_state) {
  $project_type = entity_ui_form_submit_build_entity($form, $form_state);

  // If we create new project type we need to add default fields to it.
  if ($form_state['op'] == 'add') {
    casetracker_project_type_add_default_fields($project_type);
    drupal_set_message(t('Project type "@title" was created successfully', array('@title' => $project_type->label)));
  }
  else {
    drupal_set_message(t('Project type "@title" was edited successfully', array('@title' => $project_type->label)));
  }

  $project_type->save();
  $form_state['redirect'] = 'admin/structure/casetracker/project-types';
}

/**
 * Form API submit callback for the delete button.
 */
function casetracker_project_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/casetracker/project-types/manage/' . $form_state['casetracker_project_type']->type . '/delete';
}

/**
 * Add default fields to newly created project type.
 */
function casetracker_project_type_add_default_fields($project_type) {

  $type = $project_type->type;

  $fields = _casetracker_project_type_default_fields();

  // Create the fields if they don't exist
  foreach ($fields as $field) {
    $info = field_info_field($field['field_name']);
    if (empty($info)) {
      field_create_field($field);
    }
  }

  // Create field instances for the type if they don't exist
  $instances = array();

  // Description field.
  $instances[] = array(
    'field_name' => 'field_casetracker_project_desc',
    'entity_type' => 'casetracker_project',
    'bundle' => $type,
    'label' => t('Description'),
    'required' => FALSE,
    'settings' => array(
      'text_processing' => '1',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'weight' => 1,
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

  // Create field instances if they don't exist
  foreach ($instances as $instance) {
    $info_instance = field_info_instance('casetracker_project', $instance['field_name'], $type);
    if (empty($info_instance)) {
      field_create_instance($instance);
    }
  }
}

/**
 * @return
 *   Return default fields definition that have to be attached to newly created
 *   project type.
 *
 * @see field_create_field()
 */
function _casetracker_project_type_default_fields() {

  $fields = array();

  // Description field.
  $fields[] = array(
    'field_name' => 'field_casetracker_project_desc',
    'type' => 'text_long',
    'entity_types' => array('casetracker_project'),
    'translatable' => TRUE,
    'locked' => FALSE,
    'module' => 'text',
    'settings' => array(),
    'cardinality' => 1,
  );

  return $fields;
}