<?php

/**
 * 
 * @file This file concentrates all general functionality related to Projects in 
 * Case Tracker, leaving to the other files in /admin the stuff related to CRUD
 * and structural configuration
 */

/**
 * Determines whether the given user has access to a casetracker_project.
 *
 * @param $op
 *   The operation being performed. One of 'view', 'update', 'create', 'delete'
 *   or just 'edit' (being the same as 'create' or 'update').
 * @param $project
 *   Optionally a casetracker_project or a casetracker_project type to check 
 *   access for. If nothing is given, access for all casetracker_projects 
 *   is determined.
 * @param $account
 *   The user to check for. Leave it to NULL to check for the global user.
 * @return boolean
 *   Whether access is allowed or not.
 */
function casetracker_project_access($op, $project = NULL, $account = NULL) {
  if (user_access('administer casetracker_projects', $account)) {
    return TRUE;
  }
  if (isset($project) && $type_name = $project->type) {
    $op = ($op == 'view') ? 'view' : 'edit';
    if (user_access("$op any $type_name casetracker_project", $account)) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Access callback for the entity API.
 */
function casetracker_project_type_access($op, $type = NULL, $account = NULL) {
  return user_access('administer casetracker_project types', $account);
}

/**
 * Gets an array of all casetracker_project types, keyed by the type name.
 *
 * @param $type_name
 *   If set, the type with the given name is returned.
 * @return CaseTrackerProjectType[]
 *   Depending whether $type isset, an array of casetracker_project types or
 *   a single one.
 */
function casetracker_project_get_types($type_name = NULL) {
  // entity_load will get the Entity controller for our casetracker_project entity
  // and call the load function of that object - we are loading entities by name here.
  $types = entity_load_multiple_by_name('casetracker_project_type', isset($type_name) ? array($type_name) : FALSE);
  return isset($type_name) ? reset($types) : $types;
}

/**
 * Menu argument loader; Load a casetracker_project type by string.
 *
 * @param $type
 *   The machine-readable name of a casetracker_project type to load.
 * @return
 *   A casetracker_project type array or FALSE if $type does not exist.
 */
function casetracker_project_type_load($type) {
  return casetracker_project_get_types($type);
}

/**
 * Fetch a casetracker_project object. Make sure that the wildcard you choose 
 * in the casetracker_project entity definition fits the function name here.
 *
 * @param $pid
 *   Integer specifying the casetracker_project id.
 * @param $reset
 *   A boolean indicating that the internal cache should be reset.
 * @return
 *   A fully-loaded $project object or FALSE if it cannot be loaded.
 *
 * @see casetracker_project_load_multiple()
 */
function casetracker_project_load($pid, $reset = FALSE) {
  $projects = casetracker_project_load_multiple(array($pid), array(), $reset);
  return reset($projects);
}

/**
 * Load multiple casetracker_projects based on certain conditions.
 *
 * @param $pids
 *   An array of project IDs.
 * @param $conditions
 *   An array of conditions to match against the {casetracker_project} table.
 * @param $reset
 *   A boolean indicating that the internal cache should be reset.
 * @return
 *   An array of casetracker_project objects, indexed by pid.
 *
 * @see entity_load()
 * @see casetracker_project_load()
 */
function casetracker_project_load_multiple($pids = array(), $conditions = array(), $reset = FALSE) {
  return entity_load('casetracker_project', $pids, $conditions, $reset);
}

/**
 * Deletes a casetracker_project.
 */
function casetracker_project_delete(CaseTrackerProject $project) {
  $project->delete();
}

/**
 * Delete multiple casetracker_projects.
 *
 * @param $pids
 *   An array of casetracker_project IDs.
 */
function casetracker_project_delete_multiple(array $pids) {
  entity_get_controller('casetracker_project')->delete($pids);
}

/**
 * Create a casetracker_project object.
 */
function casetracker_project_create($values = array()) {
  return entity_get_controller('casetracker_project')->create($values);
}

/**
 * Saves a casetracker_project to the database.
 *
 * @param $casetracker_project
 *   The casetracker_project object.
 */
function casetracker_project_save(CaseTrackerProject $project) {
  return $project->save();
}

/**
 * Saves a casetracker_project type to the db.
 */
function casetracker_project_type_save(CaseTrackerProjectType $type) {
  $type->save();
}

/**
 * Deletes a casetracker_project type from the db.
 */
function casetracker_project_type_delete(CaseTrackerProjectType $type) {
  $type->delete();
}

/**
 * URI callback for casetracker_projects
 */
function casetracker_project_uri(CaseTrackerProject $project) {
  return $project->defaultUri();
}

/**
 * Menu title callback for showing individual entities
 */
function casetracker_project_page_title(CaseTrackerProject $project) {
  return $project->title;
}

function _casetracker_project_get_amount() {
  return db_select('casetracker_project', 'p')->fields('p')->execute()->rowCount();
}

/**
 * Sets up content to show an individual casetracker_project
 * @todo - get rid of drupal_set_title();
 */
function casetracker_project_page_view(CaseTrackerProject $project, $view_mode = 'full') {

  drupal_set_title($project->title);

  casetracker_project_set_breadcrumb();

  $account = user_load($project->uid);

  $rows = array();
  $rows[] = array(t('Project number'), $project->pid);
  $rows[] = array(t('Opened by'), theme('username', array('account' => $account)));
  $rows[] = array(t('Opened on'), format_date($project->created, 'long'));
  $rows[] = array(t('Last modified'), format_date($project->changed, 'long'));

  $rows[] = array(t('Total amount of cases'), $project->getCasesAmount());

  $output = '<div class="project">';
  $output .= theme('table', array('header' => NULL, 'rows' => $rows, 'attributes' => array('class' => 'summary')));
  $output .= '</div>';

  $content = entity_build_content('casetracker_project', $project);

  $content['table'] = array(
    '#type' => 'markup',
    '#markup' => $output
  );

  return $content;
}

/**
 * The class used for project entities
 */
class CaseTrackerProject extends Entity {

  public function __construct($values = array()) {
    parent::__construct($values, 'casetracker_project');
  }

  /**
   * Count the number of cases related to this project
   */
  public function getCasesAmount() {
    $query = db_select('casetracker_case');
    $query->join('field_data_field_project_ref', 'p', 'p.entity_id = casetracker_case.cid');
    return $query->condition('p.field_project_ref_target_id', $this->pid, '=')
            ->fields('casetracker_case')
            ->execute()->rowCount();
  }

  protected function defaultLabel() {
    return $this->title;
  }

  protected function defaultUri() {
    return array('path' => 'casetracker/project/' . $this->pid);
  }

}

/**
 * The class used for project type entities
 */
class CaseTrackerProjectType extends Entity {

  public $type;
  public $label;

  public function __construct($values = array()) {
    parent::__construct($values, 'casetracker_project_type');
  }

  function isLocked() {
    return isset($this->status) && empty($this->is_new)
        && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
  }

}

/**
 * The Controller for CaseTrackerProject entities
 */
class CaseTrackerProjectController extends EntityAPIController {

  public function __construct($entityType) {
    parent::__construct($entityType);
  }

  /**
   * 
   * @param $type
   *   The machine-readable type of the project.
   *
   * @return
   *   A project object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Project
    $values += array(
      'pid' => '',
      'is_new' => TRUE,
      'title' => '',
      'language' => '',
      'uid' => '',
      'created' => '',
      'changed' => '',
    );

    $project = parent::create($values);
    return $project;
  }

}

/**
 * The Controller for Project entities
 */
class CaseTrackerProjectTypeController extends EntityAPIControllerExportable {

  public function __construct($entityType) {
    parent::__construct($entityType);
  }

  /**
   * 
   * @param $type
   *   The machine-readable type of the project.
   *
   * @return
   *   A project type object with all default fields initialized.
   */
  public function create(array $values = array()) {
    // Add values that are specific to our Project
    $values += array(
      'id' => '',
      'is_new' => TRUE,
    );
    $project_type = parent::create($values);
    return $project_type;
  }

}