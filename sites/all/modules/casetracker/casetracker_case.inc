<?php

/**
 * 
 * @file This file concentrates all general functionality related to Cases in 
 * Case Tracker, leaving to the other files in /admin the stuff related to CRUD
 * and structural configuration
 */

/**
 * Determines whether the given user has access to a casetracker_case.
 *
 * @param $op
 *   The operation being performed. One of 'view', 'update', 'create', 'delete'
 *   or just 'edit' (being the same as 'create' or 'update').
 * @param $case
 *   Optionally a casetracker_case or a casetracker_case type to check 
 *   access for. If nothing is given, access for all casetracker_cases 
 *   is determined.
 * @param $account
 *   The user to check for. Leave it to NULL to check for the global user.
 * @return boolean
 *   Whether access is allowed or not.
 */
function casetracker_case_access($op, $case = NULL, $account = NULL) {
  if (user_access('administer casetracker_cases', $account)) {
    return TRUE;
  }
  if (isset($case) && $type_name = $case->type) {
    $op = ($op == 'view') ? 'view' : 'edit';
    if (user_access("$op any $type_name casetracker_case", $account)) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Access callback for the entity API.
 */
function casetracker_case_type_access($op, $type = NULL, $account = NULL) {
  return user_access('administer casetracker_case types', $account);
}

/**
 * Gets an array of all casetracker_case types, keyed by the type name.
 *
 * @param $type_name
 *   If set, the type with the given name is returned.
 * @return CaseTrackerCaseType[]
 *   Depending whether $type isset, an array of casetracker_case types or
 *   a single one.
 */
function casetracker_case_get_types($type_name = NULL) {
  // entity_load will get the Entity controller for our casetracker_case entity
  // and call the load function of that object - we are loading entities by name here.
  $types = entity_load_multiple_by_name('casetracker_case_type', isset($type_name) ? array($type_name) : FALSE);
  return isset($type_name) ? reset($types) : $types;
}

/**
 * Menu argument loader; Load a casetracker_case type by string.
 *
 * @param $type
 *   The machine-readable name of a casetracker_case type to load.
 * @return
 *   A casetracker_case type array or FALSE if $type does not exist.
 */
function casetracker_case_type_load($type) {
  return casetracker_case_get_types($type);
}

/**
 * Fetch a casetracker_case object. Make sure that the wildcard you choose 
 * in the casetracker_case entity definition fits the function name here.
 *
 * @param $cid
 *   Integer specifying the casetracker_case id.
 * @param $reset
 *   A boolean indicating that the internal cache should be reset.
 * @return
 *   A fully-loaded $case object or FALSE if it cannot be loaded.
 *
 * @see casetracker_case_load_multiple()
 */
function casetracker_case_load($cid, $reset = FALSE) {
  $cases = casetracker_case_load_multiple(array($cid), array(), $reset);
  return reset($cases);
}

/**
 * Load multiple casetracker_cases based on certain conditions.
 *
 * @param $cids
 *   An array of case IDs.
 * @param $conditions
 *   An array of conditions to match against the {casetracker_case} table.
 * @param $reset
 *   A boolean indicating that the internal cache should be reset.
 * @return
 *   An array of casetracker_case objects, indexed by pid.
 *
 * @see entity_load()
 * @see casetracker_case_load()
 */
function casetracker_case_load_multiple($cids = array(), $conditions = array(), $reset = FALSE) {
  return entity_load('casetracker_case', $cids, $conditions, $reset);
}

/**
 * Deletes a casetracker_case.
 */
function casetracker_case_delete(CaseTrackerCase $case) {
  $case->delete();
}

/**
 * Delete multiple casetracker_cases.
 *
 * @param $cids
 *   An array of casetracker_case IDs.
 */
function casetracker_case_delete_multiple(array $cids) {
  entity_get_controller('casetracker_case')->delete($cids);
}

/**
 * Create a casetracker_case object.
 */
function casetracker_case_create($values = array()) {
  return entity_get_controller('casetracker_case')->create($values);
}

/**
 * Saves a casetracker_case to the database.
 *
 * @param $casetracker_case
 *   The casetracker_case object.
 */
function casetracker_case_save(CaseTrackerCase $case) {
  return $case->save();
}

/**
 * Saves a casetracker_case type to the db.
 */
function casetracker_case_type_save(CaseTrackerCaseType $type) {
  $type->save();
}

/**
 * Deletes a casetracker_case type from the db.
 */
function casetracker_case_type_delete(CaseTrackerCaseType $type) {
  $type->delete();
}

/**
 * URI callback for casetracker_cases
 */
function casetracker_case_uri(CaseTrackerCase $case) {
  return $case->defaultUri();
}

/**
 * Menu title callback for showing individual entities
 */
function casetracker_case_page_title(CaseTrackerCase $case) {
  return $case->title;
}

/**
 * Sets up content to show an individual casetracker_case
 * @todo - get rid of drupal_set_title();
 */
function casetracker_case_page_view(CaseTrackerCase $case, $view_mode = 'full') {

  drupal_set_title($case->title . ' (#ID ' . $case->cid . ')');

  $case_wrapper = entity_metadata_wrapper('casetracker_case', $case);

  casetracker_case_set_breadcrumb();

  $project = casetracker_project_load($case->field_project_ref['und'][0]['target_id']);
  $content = entity_get_controller('casetracker_case')->view(array($case->cid => $case), 'full');

  $account = user_load($case->uid);
  $assigned_to_link = theme('username', array('account' => $case_wrapper->field_casetracker_case_assign_to->value()));
  $reported_by_link = theme('username', array('account' => $account));

  $due_date = $case_wrapper->field_casetracker_case_due_date->value();
  if (!empty($due_date)) {
    $due_date = format_date($case_wrapper->field_casetracker_case_due_date->value(), 'short');
  }
  else {
    $due_date = t('Not specified');
  }
  $status = $case_wrapper->field_casetracker_case_status->value();

  $rows = array();
  $rows[] = array(t('Project'), l($project->title, 'casetracker/project/' . $project->pid), t('Status'), $status);
  $rows[] = array(t('Reported by'), $reported_by_link, t('Assigned to'), $assigned_to_link);
  $rows[] = array(t('Opened on'), format_date($case->created, 'short'), t('Last modified'), format_date($case->changed, 'short'));
  $rows[] = array(t('Due date'), $due_date, NULL, NULL);

  $output = '<div class="class">';
  $output .= theme('table', array('header' => NULL, 'rows' => $rows, 'attributes' => array('class' => 'summary')));
  $output .= '</div>';

  array_unshift($content, array(
    '#type' => 'markup',
    '#markup' => $output
      )
  );

  return $content;
}

/**
 * The class used for case entities
 */
class CaseTrackerCase extends Entity {

  public function __construct($values = array()) {
    parent::__construct($values, 'casetracker_case');
  }

  protected function defaultLabel() {
    return $this->title;
  }

  protected function defaultUri() {
    return array('path' => 'casetracker/case/' . $this->cid);
  }

}

/**
 * The class used for case type entities
 */
class CaseTrackerCaseType extends Entity {

  public $type;
  public $label;

  public function __construct($values = array()) {
    parent::__construct($values, 'casetracker_case_type');
  }

  function isLocked() {
    return isset($this->status) && empty($this->is_new)
        && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
  }

}

/**
 * The Controller for CaseTrackerCase entities
 */
class CaseTrackerCaseController extends EntityAPIController {

  public function __construct($entityType) {
    parent::__construct($entityType);
  }

  /**
   * 
   * @param $type
   *   The machine-readable type of the case.
   *
   * @return
   *   A case object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Case
    $values += array(
      'pid' => '',
      'is_new' => TRUE,
      'title' => '',
      'language' => '',
      'uid' => '',
      'created' => '',
      'changed' => '',
    );

    $case = parent::create($values);
    return $case;
  }

}

/**
 * The Controller for Case entities
 */
class CaseTrackerCaseTypeController extends EntityAPIControllerExportable {

  public function __construct($entityType) {
    parent::__construct($entityType);
  }

  /**
   * 
   * @param $type
   *   The machine-readable type of the case.
   *
   * @return
   *   A case type object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Case
    $values += array(
      'id' => '',
      'is_new' => TRUE,
    );
    $case_type = parent::create($values);
    return $case_type;
  }

}