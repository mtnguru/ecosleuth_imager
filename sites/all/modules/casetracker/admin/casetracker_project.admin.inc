<?php

/**
 * @file
 * CaseTrackerProject editing UI.
 *
 * We make very little use of the EntityAPI interface for this - preferring instead to use
 * views. That offers more flexibility to change a UI that will, more often than not,
 * be end-user facing.
 */

/**
 * UI controller.
 */
class CaseTrackerProjectUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {

    $items = array();
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a project',
      'description' => 'Add a new project',
      'page callback' => 'casetracker_project_add_page',
      'access callback' => 'casetracker_project_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'admin/casetracker_project.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );

    // Add menu items to add each different type of entity.
    foreach (casetracker_project_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'casetracker_project_form_wrapper',
        'page arguments' => array(casetracker_project_create(array('type' => $type->type))),
        'access callback' => 'casetracker_project_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => 'admin/casetracker_project.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
      );
    }

    $project_path = 'casetracker/project';
    $items[$project_path . '/' . $wildcard . '/edit'] = array(
      'page callback' => 'casetracker_project_form_wrapper',
      'page arguments' => array(2),
      'access callback' => 'casetracker_project_access',
      'access arguments' => array('edit', 2),
      'title' => 'Edit',
      'type' => MENU_LOCAL_TASK,
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );

    $items[$project_path . '/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'casetracker_project_delete_form_wrapper',
      'page arguments' => array(2),
      'access callback' => 'casetracker_project_access',
      'access arguments' => array('edit', 2),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'admin/casetracker_project.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );

    // Menu item for viewing casetracker_projects
    $items[$project_path . '/' . $wildcard] = array(
      'page callback' => 'casetracker_project_page_view',
      'page arguments' => array(2),
      'access callback' => 'casetracker_project_access',
      'access arguments' => array('view', 2),
    );

    $items[$project_path . '/' . $wildcard . '/view'] = array(
      'title' => 'View',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
    );

    return $items;
  }

  /**
   * Create the markup for the add CaseTrackerProject Entities page within the class
   * so it can easily be extended/overriden.
   */
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 0) {
      drupal_set_message(t('There isn\'t any Project Type configured. To setup now, go to the <a href="@link">@link_text</a>.', array(
            '@link' => base_path() . 'admin/structure/casetracker/project-types',
            '@link_text' => 'administrative page'
          )), 'error');
    }

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }

    return theme('casetracker_project_add_list', array('content' => $content));
  }

}

/**
 * Form callback wrapper: create or edit a casetracker_project.
 *
 * @param $casetracker_project
 *   The casetracker_project object being edited by this form.
 *
 * @see casetracker_project_edit_form()
 */
function casetracker_project_form_wrapper($project) {
  return drupal_get_form('casetracker_project_edit_form', $project);
}

/**
 * Form callback wrapper: delete a casetracker_project.
 *
 * @param $project
 *   The casetracker_project object being edited by this form.
 *
 * @see casetracker_project_edit_form()
 */
function casetracker_project_delete_form_wrapper($project) {
  return drupal_get_form('casetracker_project_delete_form', $project);
}

/**
 * Form callback: create or edit a casetracker_project.
 *
 * @param $project
 *   The casetracker_project object to edit or for a create form an empty 
 *   casetracker_project object with only a casetracker_project type defined.
 */
function casetracker_project_edit_form($form, &$form_state, $project) {

  casetracker_project_set_breadcrumb();

  if (!empty($project->pid)) {
    drupal_set_title(t('@project (editing project info)', array('@project' => $project->title)));
  }

  // Add the default field elements.
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => isset($project->title) ? $project->title : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );

  // Add the field related form elements.
  $form_state['casetracker_project'] = $project;
  field_attach_form('casetracker_project', $project, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save project'),
    '#submit' => $submit + array('casetracker_project_edit_form_submit'),
  );
  
  /**
   * There is some bug that in this module code that makes the submit callback
   * being ignored
   */
  // Show Delete button if the project.is being edited
//  if (!empty($project->pid) && casetracker_project_access('edit', $project)) {
//    $form['actions']['delete'] = array(
//      '#type' => 'submit',
//      '#value' => t('Delete'),
//      '#submit' => array('casetracker_project_form_submit_delete'),
//    );
//  }

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'casetracker_project_edit_form_validate';
  return $form;
}

/**
 * Form API validate callback for the casetracker_project form
 */
function casetracker_project_edit_form_validate(&$form, &$form_state) {
  $project = $form_state['casetracker_project'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('casetracker_project', $project, $form, $form_state);
}

/**
 * Form API submit callback for the casetracker_project form.
 * 
 * @todo remove hard-coded link
 */
function casetracker_project_edit_form_submit(&$form, &$form_state) {

  $project = entity_ui_controller('casetracker_project')->entityFormSubmitBuildEntity($form, $form_state);

  if ($project->is_new = isset($project->is_new) ? $project->is_new : 0) {
    $project->created = time();
    global $user;
    $project->uid = $user->uid;
  }
  $project->changed = time();

  $project->save();
  
  // Save the casetracker_project and go back to the list of casetracker_projects
  // Add in created and changed times.
  if ($project->is_new = isset($project->is_new) ? $project->is_new : 0) {
    drupal_set_message(t('The project "!title" was created successfully.', array('!title' => l($project->title, 'casetracker/project/' . $project->pid))));
  }
  else {
    drupal_set_message(t('The project "!title" was updated successfully.', array('!title' => l($project->title, 'casetracker/project/' . $project->pid))));
  }
}

/**
 * Form API submit callback for the delete button.
 * 
 * @todo Remove hard-coded path
 */
function casetracker_project_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'casetracker/project/' . $form_state['casetracker_project']->pid . '/delete';
}

/**
 * Form callback: confirmation form for deleting a casetracker_project.
 *
 * @param $project
 *   The casetracker_project to delete
 *
 * @see confirm_form()
 */
function casetracker_project_delete_form($form, &$form_state, $project) {
  
  casetracker_project_set_breadcrumb();
  
  $form_state['casetracker_project'] = $project;

  $form['#submit'][] = 'casetracker_project_delete_form_submit';

  $form = confirm_form($form, t('Are you sure you want to delete project "@title"?', array('@title' => $project->title)), 'admin/content/casetracker/projects', '<p>' . t('This action cannot be undone.') . '</p>', t('Delete'), t('Cancel'), 'confirm'
  );

  return $form;
}

/**
 * Submit callback for casetracker_project_delete_form
 */
function casetracker_project_delete_form_submit($form, &$form_state) {
  $project = $form_state['casetracker_project'];

  casetracker_project_delete($project);

  drupal_set_message(t('The project "%title" has been deleted.', array('%title' => $project->title)));
  watchdog('casetracker_project', 'Deleted project %title.', array('%title' => $project->title));
}

/**
 * Page to add CaseTrackerProject Entities.
 *
 * @todo Pass this through a proper theme function
 */
function casetracker_project_add_page() {
  $controller = entity_ui_controller('casetracker_project');
  return $controller->addPage();
}

/**
 * Displays the list of available casetracker_project types for casetracker_project creation.
 *
 * @ingroup themeable
 */
function theme_casetracker_project_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="casetracker-project-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer casetracker_project types')) {
      $output = '<p>' . t('CaseTrackerProject Entities cannot be added because you have not created any casetracker_project types yet. Go to the <a href="@create-casetracker-project-type">casetracker_project type creation page</a> to add a new casetracker_project type.', array('@create-casetracker-project-type' => url('admin/structure/casetracker/project-types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No casetracker_project types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}

/**
 * Sets the breadcrumb for administrative casetracker_project pages.
 */
function casetracker_project_set_breadcrumb($items = array()) {

  $breadcrumb = array();
  $breadcrumb[] = l(t('Home'), NULL);
  if (user_access('access administration pages')) {
    $breadcrumb[] = l(t('Administration'), 'admin');
    $breadcrumb[] = l(t('Content'), 'admin/content');
  }
  $breadcrumb[] = l(t('Case Tracker'), 'admin/content/casetracker');
  $breadcrumb[] = l(t('Projects'), 'admin/content/casetracker/projects');

  if (!empty($items)) {
    $breadcrumb += $items;
  }

  drupal_set_breadcrumb($breadcrumb);
}
