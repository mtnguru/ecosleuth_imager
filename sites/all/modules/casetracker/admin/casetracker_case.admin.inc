<?php

/**
 * @file
 * CaseTrackerCase editing UI.
 *
 * We make very little use of the EntityAPI interface for this - preferring instead to use
 * views. That offers more flexibility to change a UI that will, more often than not,
 * be end-user facing.
 */

/**
 * UI controller.
 */
class CaseTrackerCaseUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {

    $items = array();
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a case',
      'description' => 'Add a new case',
      'page callback' => 'casetracker_case_add_page',
      'access callback' => 'casetracker_case_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'admin/casetracker_case.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );

    // Add menu items to add each different type of entity.
    foreach (casetracker_case_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'casetracker_case_form_wrapper',
        'page arguments' => array(casetracker_case_create(array('type' => $type->type))),
        'access callback' => 'casetracker_case_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => 'admin/casetracker_case.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
      );
    }

    $case_path = 'casetracker/case';
    $items[$case_path . '/' . $wildcard . '/edit'] = array(
      'page callback' => 'casetracker_case_form_wrapper',
      'page arguments' => array(2),
      'access callback' => 'casetracker_case_access',
      'access arguments' => array('edit', 2),
      'title' => 'Edit',
      'type' => MENU_LOCAL_TASK,
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );

    $items[$case_path . '/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'casetracker_case_delete_form_wrapper',
      'page arguments' => array(2),
      'access callback' => 'casetracker_case_access',
      'access arguments' => array('edit', 2),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'admin/casetracker_case.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );

    // Menu item for viewing casetracker_cases
    $items[$case_path . '/' . $wildcard] = array(
      'page callback' => 'casetracker_case_page_view',
      'page arguments' => array(2),
      'access callback' => 'casetracker_case_access',
      'access arguments' => array('view', 2),
    );

    $items[$case_path . '/' . $wildcard . '/view'] = array(
      'title' => 'View',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
    );

    return $items;
  }

  /**
   * Create the markup for the add CaseTrackerCase Entities page within the class
   * so it can easily be extended/overriden.
   */
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 0) {
      drupal_set_message(t('There isn\'t any Case Type configured. To setup now, go to the <a href="@link">@link_text</a>.', array(
            '@link' => base_path() . 'admin/structure/casetracker/case-types',
            '@link_text' => 'administrative page'
          )), 'error');
    }
    elseif (count($content) == 1) {
      $item = array_shift($content);
      // Check to see if a project is being referenced, to pass the reference 
      $project_ref = arg(5);
      if(is_numeric($project_ref)) {
        drupal_goto($item['href'] . '/' . $project_ref);
      }
      else {
        drupal_goto($item['href']);
      }
    }

    return theme('casetracker_case_add_list', array('content' => $content));
  }

}

/**
 * Form callback wrapper: create or edit a casetracker_case.
 *
 * @param $casetracker_case
 *   The casetracker_case object being edited by this form.
 *
 * @see casetracker_case_edit_form()
 */
function casetracker_case_form_wrapper($case) {
  return drupal_get_form('casetracker_case_edit_form', $case);
}

/**
 * Form callback wrapper: delete a casetracker_case.
 *
 * @param $case
 *   The casetracker_case object being edited by this form.
 *
 * @see casetracker_case_edit_form()
 */
function casetracker_case_delete_form_wrapper($case) {
  // Add the breadcrumb for the form's location.
  //casetracker_case_set_breadcrumb();
  return drupal_get_form('casetracker_case_delete_form', $case);
}

/**
 * Form callback: create or edit a casetracker_case.
 *
 * @param $case
 *   The casetracker_case object to edit or for a create form an empty 
 *   casetracker_case object with only a casetracker_case type defined.
 */
function casetracker_case_edit_form($form, &$form_state, $case) {

  $amount_of_projects = _casetracker_project_get_amount();
  if ($amount_of_projects == 0) {
    drupal_set_message(t('You need to have at least 1 project to relate your cases to. If you wish, you can go to the <a href="@link">projects creation page</a> now to create one.'
            , array('@link' => base_path() . 'admin/content/casetracker/projects/add')), 'error');
  }

  casetracker_case_set_breadcrumb();

  if (!empty($case->cid)) {
    drupal_set_title(t('@case (editing case info)', array('@case' => $case->title)));
  }

  // Add the default field elements.
  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => isset($case->title) ? $case->title : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );

  // Add the field related form elements.
  $form_state['casetracker_case'] = $case;
  field_attach_form('casetracker_case', $case, $form, $form_state);

  // If the entity is being created, try to prepopulate the project reference
  // from the URL argument
  if (isset($case->is_new) && $case->is_new) {
    // If the project was informed via URL argument, prepopulate the field
    $pid = arg(6);
    if (!empty($pid)) {
      $project = casetracker_project_load($pid);
      if ($project) {
        $case_wrapper = entity_metadata_wrapper('casetracker_case', $case);
        $selected_project = $project->title . ' (' . $pid . ')';
        $form['field_project_ref']['und']['#default_value'] = $selected_project;
        drupal_set_title(t('Add Case to project "@title"', array('@title' => $project->title)));
      }
    }
  }

  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $case->uid,
  );

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
    '#value' => t('Save case'),
    '#submit' => $submit + array('casetracker_case_edit_form_submit'),
  );

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'casetracker_case_edit_form_validate';
  return $form;
}

/**
 * Form API validate callback for the casetracker_case form
 */
function casetracker_case_edit_form_validate(&$form, &$form_state) {
  $case = $form_state['casetracker_case'];

  // Notify field widgets to validate their data.
  field_attach_form_validate('casetracker_case', $case, $form, $form_state);
}

/**
 * Form API submit callback for the casetracker_case form.
 * 
 * @todo remove hard-coded link
 */
function casetracker_case_edit_form_submit(&$form, &$form_state) {

  $case = entity_ui_controller('casetracker_case')->entityFormSubmitBuildEntity($form, $form_state);

  if ($case->is_new = isset($case->is_new) ? $case->is_new : 0) {
    $case->created = time();
    global $user;
    $case->uid = $user->uid;
  }
  $case->changed = time();

  $case->save();

  // Save the casetracker_case and go back to the list of casetracker_cases
  // Add in created and changed times.
  if ($case->is_new = isset($case->is_new) ? $case->is_new : 0) {
    drupal_set_message(t('The case "!title" was created successfully.', array('!title' => l($case->title, 'casetracker/case/' . $case->cid))));
  }
  else {
    drupal_set_message(t('The case "!title" was updated successfully.', array('!title' => l($case->title, 'casetracker/case/' . $case->cid))));
  }
}

/**
 * Form API submit callback for the delete button.
 * 
 * @todo Remove hard-coded path
 */
function casetracker_case_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'casetracker/case/' . $form_state['casetracker_case']->pid . '/delete';
}

/**
 * Form callback: confirmation form for deleting a casetracker_case.
 *
 * @param $case
 *   The casetracker_case to delete
 *
 * @see confirm_form()
 */
function casetracker_case_delete_form($form, &$form_state, $case) {

  casetracker_case_set_breadcrumb();

  $form_state['casetracker_case'] = $case;

  $form['#submit'][] = 'casetracker_case_delete_form_submit';

  $form = confirm_form($form, t('Are you sure you want to delete case "@title"?', array('@title' => $case->title)), 'admin/content/casetracker/cases', '<p>' . t('This action cannot be undone.') . '</p>', t('Delete'), t('Cancel'), 'confirm'
  );

  return $form;
}

/**
 * Submit callback for casetracker_case_delete_form
 */
function casetracker_case_delete_form_submit($form, &$form_state) {
  $case = $form_state['casetracker_case'];

  casetracker_case_delete($case);

  drupal_set_message(t('The case "%title" has been deleted.', array('%title' => $case->title)));
  watchdog('casetracker_case', 'Deleted case "%title".', array('%title' => $case->title));
}

/**
 * Page to add CaseTrackerCase Entities.
 *
 * @todo Pass this through a proper theme function
 */
function casetracker_case_add_page() {
  $controller = entity_ui_controller('casetracker_case');
  return $controller->addPage();
}

/**
 * Displays the list of available casetracker_case types for casetracker_case creation.
 *
 * @ingroup themeable
 */
function theme_casetracker_case_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="casetracker-case-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer casetracker_case types')) {
      $output = '<p>' . t('CaseTrackerCase Entities cannot be added because you have not created any casetracker_case types yet. Go to the <a href="@create-casetracker-case-type">casetracker_case type creation page</a> to add a new casetracker_case type.', array('@create-casetracker-case-type' => url('admin/structure/casetracker_case_types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No casetracker_case types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}

/**
 * Sets the breadcrumb for administrative casetracker_case pages.
 */
function casetracker_case_set_breadcrumb($items = array()) {

  $breadcrumb = array();
  $breadcrumb[] = l(t('Home'), NULL);
  if (user_access('access administration pages')) {
    $breadcrumb[] = l(t('Administration'), 'admin');
    $breadcrumb[] = l(t('Content'), 'admin/content');
  }
  $breadcrumb[] = l(t('Case Tracker'), 'admin/content/casetracker');
  $breadcrumb[] = l(t('Cases'), 'admin/content/casetracker/cases');

  if (!empty($items)) {
    $breadcrumb += $items;
  };

  drupal_set_breadcrumb($breadcrumb);
}
