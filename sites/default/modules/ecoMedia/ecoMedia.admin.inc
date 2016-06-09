<?php

/**
 * @file
 * Ticket editing UI.
 *
 * We make very little use of the EntityAPI interface for this - preferring instead to use
 * views. That offers more flexibility to change a UI that will, more often than not,
 * be end-user facing.
 */

include_once('ecoMedia.utils.inc');

/**
 * UI controller.
 */
class TicketUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {
    
    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    $items[$this->path] = array(
      'title' => 'Tickets',
      'description' => 'Add edit and update ecoMedias.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
    );
    
    // Change the overview menu type for the list of ecoMedias.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    
    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a ecoMedia',
      'description' => 'Add a new ecoMedia',
      'page callback'  => 'ecoMedia_add_page',
      'access callback'  => 'ecoMedia_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'ecoMedia.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])

    );
    
    // Add menu items to add each different type of entity.
    foreach (ecoMedia_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'ecoMedia_form_wrapper',
        'page arguments' => array(ecoMedia_create(array('type' => $type->type))),
        'access callback' => 'ecoMedia_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => 'ecoMedia.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
      );
    }

    // Loading and editing ecoMedia entities
    $items[$this->path . '/ecoMedia/' . $wildcard] = array(
      'page callback' => 'ecoMedia_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'ecoMedia_access',
      'access arguments' => array('edit', $id_count + 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'ecoMedia.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    $items[$this->path . '/ecoMedia/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );
    
    $items[$this->path . '/ecoMedia/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'ecoMedia_delete_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'ecoMedia_access',
      'access arguments' => array('edit', $id_count + 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'ecoMedia.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    
    // Menu item for viewing ecoMedias
    $items['ecoMedia/' . $wildcard] = array(
      //'title' => 'Title',
      'title callback' => 'ecoMedia_page_title',
      'title arguments' => array(1),
      'page callback' => 'ecoMedia_page_view',
      'page arguments' => array(1),
      'access callback' => 'ecoMedia_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
    return $items;
  }
  
  
  /**
   * Create the markup for the add Ticket Entities page within the class
   * so it can easily be extended/overriden.
   */ 
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }    
        
    return theme('ecoMedia_add_list', array('content' => $content));
  }
  
}


/**
 * Form callback wrapper: create or edit a ecoMedia.
 *
 * @param $ecoMedia
 *   The ecoMedia object being edited by this form.
 *
 * @see ecoMedia_edit_form()
 */
function ecoMedia_form_wrapper($ecoMedia) {
  // Add the breadcrumb for the form's location.
  ecoMedia_set_breadcrumb();
  return drupal_get_form('ecoMedia_edit_form', $ecoMedia);
}


/**
 * Form callback wrapper: delete a ecoMedia.
 *
 * @param $ecoMedia
 *   The ecoMedia object being edited by this form.
 *
 * @see ecoMedia_edit_form()
 */
function ecoMedia_delete_form_wrapper($ecoMedia) {
  // Add the breadcrumb for the form's location.
  //ecoMedia_set_breadcrumb();
  return drupal_get_form('ecoMedia_delete_form', $ecoMedia);
}

function _ecoMedia_get_arguments () {
  $q = $_GET['q'];
  $str = preg_replace('|^.*/z\?|','',$q);
  if ($str == $q) return;
  $flds = explode('?',$str);
  foreach ($flds as $fld) {
    list($key,$val) = explode('=',$fld);
    if (isset($val)) $args[$key] = $val;
  }
  return $args;
}

function _ecoMedia_add_name($form, &$form_state, $ecoMedia, $ecoMedia_type, $args) {
  // Ticket Name
  $items =  array(
    '#type' => 'fieldset',
    '#title' => 'Ticket Name',
    '#tree' => FALSE,
    'name' => array(
      '#type' => 'textfield',
      '#default_value' => (!empty($ecoMedia->name)) ? $ecoMedia->name : '',
//    'length' => 60,
      '#maxlength' => 255,
      '#required' => TRUE,
    ),
  );
  return $items;
}

function _ecoMedia_add_owner($form, &$form_state, $ecoMedia, $ecoMedia_type, $args) {
  // Owner
  $owner = "James Sorensen";
  $items = array(
    '#type' => 'fieldset',
    '#title' => 'Ticket Owner',
    '#tree' => FALSE,
  );
  $items['owner'] = array(
    '#type' => 'textfield',
    '#default_value' => $owner,
    '#autocomplete_path' => 'people/autocomplete/employee',
    '#maxlength' => 32,
    '#required' => TRUE,
  );
  return $items;
}

function _ecoMedia_add_department($form, &$form_state, $ecoMedia, $ecoMedia_type, $args) {
  // Department
  return array(
    '#type' => 'fieldset',
    '#title' => 'Department',
    '#tree' => FALSE,
    'department' => array(
      '#type' => 'radios',
      '#default_value' => !empty($ecoMedia->department) ? $ecoMedia->department : $ecoMedia_type->attr['department_default'],
      '#options' => _ecoMedia_get_taxonomy_terms('departments'),
      '#required' => TRUE,
    ),
  );
  return $items;
}

function _ecoMedia_add_personnel($form, &$form_state, $ecoMedia, $ecoMedia_type, $args) {
  // List Personnel here - show some links
  // Add Personnel by department fieldsets - arrange by department
  $departments = _ecoMedia_get_departments();
  $personnel   = _ecoMedia_get_personnel_by_dept();
  if ($ecoMedia_type->attr['kind'] == 'full') {
    $items = array(
      '#type' => 'fieldset',
      '#tree' => FALSE,
      '#collapsible' => FALSE,
      '#collapsed' => TRUE,
      '#title' => t('Personnel'),
    );
    foreach ($departments as $did => $dept) {
      if ($dept == 'Employees' || $dept == 'All') continue;
      
      $items[$did] = array(
        '#type' => 'fieldset',
        '#attributes' => array('class' => array('ds-Department','department-' . $dept)),
  //    '#attributes' => array('class' => "ds-$dept"),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#title' => t($dept),
  //    '#default_value' => !empty($ecoMedia_type->attr['status']['collect']),
      );
      unset($defs);
      $defs = array();
      foreach ($form['ecoMedia_personnel']['und'] as $ind => $fld) {
  //    $fld['#validated'] = TRUE;
        if ($ind[0] == '#' || (empty($fld['target_id']))) continue;                   // ignore if starts with #
        $val = $fld['target_id']['#default_value'];
        if (!empty($val)) {                             // if it has a default value
          if ($c = strchr($val,'(')) {                  //   if the default has (xxxx)
            $ind2 = substr($c,1,4);                //     extract the xxxx
            if (isset($personnel[$did][$ind2])) {
              $defs[] = $ind2;
            }
          }
        }
      }
      if (!empty($defs)) {
         $items[$did]['#collapsed'] = FALSE;
      }
      $items[$did]['personnel'] = array(
  //   '#tree' => TRUE,
        '#type' => 'checkboxes',
        '#validated' => TRUE,
        '#attributes' => array('class' => array('department-' . $dept)),
        '#options' => $personnel[$did],
        '#default_value' => $defs,
      );
    } 
    return $items;
  }
  return;
}

function _ecoMedia_add_facility($form, &$form_state, $ecoMedia, $ecoMedia_type, $args) {
  // Facility
  if (!empty($ecoMedia->facility)) {
    $fac = entity_load('node',array($ecoMedia->facility));
    $facility = $fac[$ecoMedia->facility]->title . ' (' . $ecoMedia->facility . ')';
  } else {
    $facility = $ecoMedia_type->attr['facility_default'];
  }
  // Facility
  $items = array(
    '#type' => 'fieldset',
    '#title' => 'Facility',
    '#tree' => FALSE,
  );
  $items['facility'] = array(
    '#type' => 'textfield',
    '#default_value' => $facility,
    '#autocomplete_path' => 'facility/autocomplete/dairy',
    '#maxlength' => 32,
    '#required' => TRUE,
  );
  return $items;
}

function _ecoMedia_add_importance($form, &$form_state, $ecoMedia, $ecoMedia_type, $args) {
  // Importance
  return array(
    '#type' => 'fieldset',
    '#title' => 'Importance',
    '#tree' => FALSE,
    'importance' => array(
      '#type' => 'radios',
      '#default_value' => !empty($ecoMedia->importance) ? $ecoMedia->importance : $ecoMedia_type->attr['importance_default'],
      '#options' => _ecoMedia_get_taxonomy_terms('importance'),
      '#required' => TRUE,
    ),
  );
}

function _ecoMedia_add_status($form, &$form_state, $ecoMedia, $ecoMedia_type, $args) {
  // Status
  return array(
    '#type' => 'fieldset',
    '#title' => 'Status',
    '#tree' => FALSE,
    'status' => array(
      '#type' => 'select',
      '#default_value' => !empty($ecoMedia->status) ? $ecoMedia->status : $ecoMedia_type->attr['status_default'],
      '#options' => _ecoMedia_get_taxonomy_terms('ecoMedia_status'),
      '#required' => TRUE,
    ),
  ); 
}

function _ecoMedia_add_date($form, &$form_state, $ecoMedia, $ecoMedia_type, $args) {
  // Scheduled date
  $now = format_date(time(),'short');
  return array(
    '#type' => 'fieldset',
    '#title' => 'Date',
    '#tree' => FALSE,
    'sch_date_begin' => array(
      '#type' => 'date_popup',
      '#date_year_range' => '-6:+3',
      '#date_increment' => '5',
      '#title' => t('Date this ecoMedia is expected to begin'),
      '#default_value' => (!empty($ecoMedia->sch_date_begin)) ? format_date($ecoMedia->sch_date_begin,'short'): $now,
      '#required' => TRUE,
    ), 
    'sch_date_end' => array(
      '#type' => 'date_popup',
      '#date_year_range' => '-6:+3',
      '#date_increment' => '5',
      '#title' => t('Date this ecoMedia is expected to end'),
      '#default_value' => (!empty($ecoMedia->sch_date_end)) ? format_date($ecoMedia->sch_date_end,'short') : $now,
    ), 
    'act_date_begin' => array(
      '#type' => 'date_popup',
      '#date_year_range' => '-6:+3',
      '#date_increment' => '5',
      '#title' => t('Date this ecoMedia is expected to begin'),
      '#default_value' => (!empty($ecoMedia->act_date_begin)) ? format_date($ecoMedia->act_date_begin,'short') : '',
    ), 
    'act_date_end' => array(
      '#type' => 'date_popup',
      '#date_year_range' => '-6:+3',
      '#date_increment' => '5',
      '#title' => t('Date this ecoMedia is expected to end'),
      '#default_value' => (!empty($ecoMedia->act_date_end)) ? format_date($ecoMedia->act_date_end,'short') : '',
    ), 
    'hour_plus' => array(
      '#type' => 'button',
      '#title' => t('+'),
//    '#default_value' => (isset($ecoMedia->attr['one_hour'])) ? $ecoMedia->attr['one_hour'] : $ecoMedia_type->attr['one_hour'],
    ), 
    'hour_minus' => array(
      '#type' => 'button',
      '#title' => t('-'),
//    '#default_value' => (isset($ecoMedia->attr['one_hour'])) ? $ecoMedia->attr['one_hour'] : $ecoMedia_type->attr['one_hour'],
    ), 
    'work_hours' => array(
      '#type' => 'button',
      '#title' => t('Work Hours?'),
      '#default_value' => (isset($ecoMedia->attr['work_hours'])) ? $ecoMedia->attr['work_hours'] : FALSE,
    ), 
    'all_day' => array(
      '#type' => 'checkbox',
      '#title' => t('Add Day'),
      '#default_value' => (isset($ecoMedia->attr['all_day'])) ? $ecoMedia->attr['all_day'] : FALSE,
    ), 
    'auto_activate' => array(
      '#type' => 'checkbox',
      '#title' => t('Automatically activate this event?'),
      '#default_value' => (isset($ecoMedia->attr['auto_activate'])) ? $ecoMedia->attr['auto_activate'] : $ecoMedia_type->attr['auto_activate'],
    ), 
  );
}

function _ecoMedia_add_desc($form, &$form_state, $ecoMedia, $ecoMedia_type, $args) {
  // Description
  return;
}

function _ecoMedia_add_comments($form, &$form_state, $ecoMedia, $ecoMedia_type, $args) {
  // Comments
  return;
}

function _ecoMedia_add_addl_fields($form, &$form_state, $ecoMedia, $ecoMedia_type, $args) {
  // Additional Fields
  return;
}

function _ecoMedia_add_actions($form, &$form_state, $ecoMedia, $ecoMedia_type, $args) {
  // Actions Top
  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $items = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save ecoMedia'),
      '#submit' => $submit + array('ecoMedia_edit_form_submit'),
    ),
  );
  
  if (!empty($ecoMedia->name)) {
    $items['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete ecoMedia'),
      '#suffix' => l(t('Cancel'), 'admin/content/ecoMedias'),
      '#submit' => $submit + array('ecoMedia_form_submit_delete'),
      '#weight' => 45,
    );
  }
  return $items;
}

/**
 * Form callback: create or edit a ecoMedia.
 *
 * @param $ecoMedia
 *   The ecoMedia object to edit or for a create form an empty ecoMedia object
 *     with only a ecoMedia type defined.
 */
function ecoMedia_edit_form($form, &$form_state, $ecoMedia) {
  // Add the default field elements.
  $path = drupal_get_path('module','ecoMedia');
//$js = drupal_add_js($path . '/jquery4u.datetime.js',array('group' => 99,
//                                                          'weight' => 100));
  $js = drupal_add_js($path . '/ecoMedia.js',array('group' => 100,
                                                 'weight' => 100));

  $args = _ecoMedia_get_arguments();
  $ecoMedia_type = ecoMedia_get_types($ecoMedia->type);

  // Add the field related form elements.
  $form_state['ecoMedia'] = $ecoMedia;
  field_attach_form('ecoMedia', $ecoMedia, $form, $form_state);

  // Attach CSS file
  $form['#attached']['css'][] = drupal_get_path('module','ecoMedia') . '/ecoMedia.form.css';

  // create form elements
  $form['name_fs']        = _ecoMedia_add_name($form,$form_state,$ecoMedia,$ecoMedia_type,$args);
  $form['owner_fs']       = _ecoMedia_add_owner($form,$form_state,$ecoMedia,$ecoMedia_type,$args);
  $form['department_fs']  = _ecoMedia_add_department($form,$form_state,$ecoMedia,$ecoMedia_type,$args);
  $form['personnel']      = _ecoMedia_add_personnel($form,$form_state,$ecoMedia,$ecoMedia_type,$args);
  $form['facility_fs']    = _ecoMedia_add_facility($form,$form_state,$ecoMedia,$ecoMedia_type,$args);
  $form['importance_fs']  = _ecoMedia_add_importance($form,$form_state,$ecoMedia,$ecoMedia_type,$args);
  $form['status_fs']      = _ecoMedia_add_status($form,$form_state,$ecoMedia,$ecoMedia_type,$args);
  $form['date_fs']        = _ecoMedia_add_date($form,$form_state,$ecoMedia,$ecoMedia_type,$args);
  $form['desc_fs']        = _ecoMedia_add_desc($form,$form_state,$ecoMedia,$ecoMedia_type,$args);
  $form['comments_fs']    = _ecoMedia_add_comments($form,$form_state,$ecoMedia,$ecoMedia_type,$args);
  $form['actions_top']    = _ecoMedia_add_actions($form,$form_state,$ecoMedia,$ecoMedia_type,$args);
  $form['actions_bottom'] = _ecoMedia_add_actions($form,$form_state,$ecoMedia,$ecoMedia_type,$args);

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'ecoMedia_edit_form_validate';
  return $form;
}


/**
 * Form API validate callback for the ecoMedia form
 */
function ecoMedia_edit_form_validate(&$form, &$form_state) {
  $ecoMedia = $form_state['ecoMedia'];
  $form_state['values']['ecoMedia_personnel']['und'] = array();
//foreach ($form_state['values']['ecoMedia_personnel']['und'] as $ind => $fld) {
//  if (isset($fld['target_id'])) {
//  }
//}
  $ind = 0;
  foreach ($form_state['values']['personnel'] as $fld) {
    if (empty($fld)) continue;
    //|| $fld == 0) continue;
    $form_state['values']['ecoMedia_personnel']['und'][$ind] = array('_weight' => $ind,
                                                                             'target_id' => $fld);     
    $ind++;
  }

  // Notify field widgets to validate their data.
//field_attach_form_validate('ecoMedia', $ecoMedia, $form, $form_state);
}


/**
 * Form API submit callback for the ecoMedia form.
 * 
 * @todo remove hard-coded link
 */
function ecoMedia_edit_form_submit(&$form, &$form_state) {
  
  $ecoMedia = entity_ui_controller('ecoMedia')->entityFormSubmitBuildEntity($form, $form_state);
  // Save the ecoMedia and go back to the list of ecoMedias
  
  // Add in created and changed times.
  if ($ecoMedia->is_new = isset($ecoMedia->is_new) ? $ecoMedia->is_new : 0){
    $ecoMedia->created = time();
  }

  $ecoMedia->changed = time();

  $ecoMedia->sch_date_begin = strtotime($ecoMedia->sch_date_begin);
  $ecoMedia->sch_date_end   = strtotime($ecoMedia->sch_date_end);
  $ecoMedia->act_date_begin = strtotime($ecoMedia->act_date_begin);
  $ecoMedia->act_date_end   = strtotime($ecoMedia->act_date_end);

  $ecoMedia->attr['auto_activate'] = $form_state['values']['auto_activate'];
  $ecoMedia->attr['one_hour']      = $form_state['values']['one_hour'];
  $ecoMedia->attr['all_day']       = $form_state['values']['all_day'];
  $ecoMedia->attr['work_day']      = $form_state['values']['work_day'];

  if (preg_match('|\((.*)\)|',$ecoMedia->facility,$matches)) {
    $ecoMedia->facility = $matches[1];
  } else {
    $ecoMedia->facility = _ecoMedia_facility_nid_by_name($ecoMedia->facility);
  }

  $ecoMedia->save();
  $form_state['redirect'] = 'admin/content/ecoMedias';
}

/**
 * Form API submit callback for the delete button.
 * 
 * @todo Remove hard-coded path
 */
function ecoMedia_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/ecoMedias/ecoMedia/' . $form_state['ecoMedia']->tckid . '/delete';
}


/**
 * Form callback: confirmation form for deleting a ecoMedia.
 *
 * @param $ecoMedia
 *   The ecoMedia to delete
 *
 * @see confirm_form()
 */
function ecoMedia_delete_form($form, &$form_state, $ecoMedia) {
  $form_state['ecoMedia'] = $ecoMedia;

  $form['#submit'][] = 'ecoMedia_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete ecoMedia %name?', array('%name' => $ecoMedia->name)),
    'admin/content/ecoMedias/ecoMedia',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );
  
  return $form;
}

/**
 * Submit callback for ecoMedia_delete_form
 */
function ecoMedia_delete_form_submit($form, &$form_state) {
  $ecoMedia = $form_state['ecoMedia'];

  ecoMedia_delete($ecoMedia);

  drupal_set_message(t('The ecoMedia %name has been deleted.', array('%name' => $ecoMedia->name)));
  watchdog('ecoMedia', 'Deleted ecoMedia %name.', array('%name' => $ecoMedia->name));

  $form_state['redirect'] = 'admin/content/ecoMedias';
}



/**
 * Page to add Ticket Entities.
 *
 * @todo Pass this through a proper theme function
 */
function ecoMedia_add_page() {
  $controller = entity_ui_controller('ecoMedia');
  return $controller->addPage();
}


/**
 * Displays the list of available ecoMedia types for ecoMedia creation.
 *
 * @ingroup themeable
 */
function theme_ecoMedia_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="ecoMedia-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer ecoMedia types')) {
      $output = '<p>' . t('Ticket Entities cannot be added because you have not created any ecoMedia types yet. Go to the <a href="@create-ecoMedia-type">ecoMedia type creation page</a> to add a new ecoMedia type.', array('@create-ecoMedia-type' => url('admin/structure/ecoMedia_types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No ecoMedia types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}


/**
 * Sets the breadcrumb for administrative ecoMedia pages.
 */
function ecoMedia_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Tickets'), 'admin/content/ecoMedias'),
  );

  drupal_set_breadcrumb($breadcrumb);
}
