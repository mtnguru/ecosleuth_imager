<?php

/**
 * @file
 * Ticket editing UI.
 *
 * We make very little use of the EntityAPI interface for this - preferring instead to use
 * views. That offers more flexibility to change a UI that will, more often than not,
 * be end-user facing.
 */

include_once('pijs.utils.inc');

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
      'description' => 'Add edit and update pijs.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
    );
    
    // Change the overview menu type for the list of pijss.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    
    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a pijs',
      'description' => 'Add a new pijs',
      'page callback'  => 'pijs_add_page',
      'access callback'  => 'pijs_access',
      'access arguments' => array('edit'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'pijs.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])

    );
    
    // Add menu items to add each different type of entity.
    foreach (pijs_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'pijs_form_wrapper',
        'page arguments' => array(pijs_create(array('type' => $type->type))),
        'access callback' => 'pijs_access',
        'access arguments' => array('edit', 'edit ' . $type->type),
        'file' => 'pijs.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
      );
    }

    // Loading and editing pijs entities
    $items[$this->path . '/pijs/' . $wildcard] = array(
      'page callback' => 'pijs_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'pijs_access',
      'access arguments' => array('edit', $id_count + 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'pijs.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    $items[$this->path . '/pijs/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );
    
    $items[$this->path . '/pijs/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'pijs_delete_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'pijs_access',
      'access arguments' => array('edit', $id_count + 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'pijs.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    
    // Menu item for viewing pijss
    $items['pijs/' . $wildcard] = array(
      //'title' => 'Title',
      'title callback' => 'pijs_page_title',
      'title arguments' => array(1),
      'page callback' => 'pijs_page_view',
      'page arguments' => array(1),
      'access callback' => 'pijs_access',
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
        
    return theme('pijs_add_list', array('content' => $content));
  }
  
}


/**
 * Form callback wrapper: create or edit a pijs.
 *
 * @param $pijs
 *   The pijs object being edited by this form.
 *
 * @see pijs_edit_form()
 */
function pijs_form_wrapper($pijs) {
  // Add the breadcrumb for the form's location.
  pijs_set_breadcrumb();
  return drupal_get_form('pijs_edit_form', $pijs);
}


/**
 * Form callback wrapper: delete a pijs.
 *
 * @param $pijs
 *   The pijs object being edited by this form.
 *
 * @see pijs_edit_form()
 */
function pijs_delete_form_wrapper($pijs) {
  // Add the breadcrumb for the form's location.
  //pijs_set_breadcrumb();
  return drupal_get_form('pijs_delete_form', $pijs);
}

function _pijs_get_arguments () {
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

function _pijs_add_name($form, &$form_state, $pijs, $pijs_type, $args) {
  // Ticket Name
  $items =  array(
    '#type' => 'fieldset',
    '#title' => 'Ticket Name',
    '#tree' => FALSE,
    'name' => array(
      '#type' => 'textfield',
      '#default_value' => (!empty($pijs->name)) ? $pijs->name : '',
//    'length' => 60,
      '#maxlength' => 255,
      '#required' => TRUE,
    ),
  );
  return $items;
}

function _pijs_add_owner($form, &$form_state, $pijs, $pijs_type, $args) {
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

function _pijs_add_department($form, &$form_state, $pijs, $pijs_type, $args) {
  // Department
  return array(
    '#type' => 'fieldset',
    '#title' => 'Department',
    '#tree' => FALSE,
    'department' => array(
      '#type' => 'radios',
      '#default_value' => !empty($pijs->department) ? $pijs->department : $pijs_type->attr['department_default'],
      '#options' => _pijs_get_taxonomy_terms('departments'),
      '#required' => TRUE,
    ),
  );
  return $items;
}

function _pijs_add_personnel($form, &$form_state, $pijs, $pijs_type, $args) {
  // List Personnel here - show some links
  // Add Personnel by department fieldsets - arrange by department
  $departments = _pijs_get_departments();
  $personnel   = _pijs_get_personnel_by_dept();
  if ($pijs_type->attr['kind'] == 'full') {
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
  //    '#default_value' => !empty($pijs_type->attr['status']['collect']),
      );
      unset($defs);
      $defs = array();
      foreach ($form['pijs_personnel']['und'] as $ind => $fld) {
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

function _pijs_add_facility($form, &$form_state, $pijs, $pijs_type, $args) {
  // Facility
  if (!empty($pijs->facility)) {
    $fac = entity_load('node',array($pijs->facility));
    $facility = $fac[$pijs->facility]->title . ' (' . $pijs->facility . ')';
  } else {
    $facility = $pijs_type->attr['facility_default'];
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

function _pijs_add_importance($form, &$form_state, $pijs, $pijs_type, $args) {
  // Importance
  return array(
    '#type' => 'fieldset',
    '#title' => 'Importance',
    '#tree' => FALSE,
    'importance' => array(
      '#type' => 'radios',
      '#default_value' => !empty($pijs->importance) ? $pijs->importance : $pijs_type->attr['importance_default'],
      '#options' => _pijs_get_taxonomy_terms('importance'),
      '#required' => TRUE,
    ),
  );
}

function _pijs_add_status($form, &$form_state, $pijs, $pijs_type, $args) {
  // Status
  return array(
    '#type' => 'fieldset',
    '#title' => 'Status',
    '#tree' => FALSE,
    'status' => array(
      '#type' => 'select',
      '#default_value' => !empty($pijs->status) ? $pijs->status : $pijs_type->attr['status_default'],
      '#options' => _pijs_get_taxonomy_terms('pijs_status'),
      '#required' => TRUE,
    ),
  ); 
}

function _pijs_add_date($form, &$form_state, $pijs, $pijs_type, $args) {
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
      '#title' => t('Date this pijs is expected to begin'),
      '#default_value' => (!empty($pijs->sch_date_begin)) ? format_date($pijs->sch_date_begin,'short'): $now,
      '#required' => TRUE,
    ), 
    'sch_date_end' => array(
      '#type' => 'date_popup',
      '#date_year_range' => '-6:+3',
      '#date_increment' => '5',
      '#title' => t('Date this pijs is expected to end'),
      '#default_value' => (!empty($pijs->sch_date_end)) ? format_date($pijs->sch_date_end,'short') : $now,
    ), 
    'act_date_begin' => array(
      '#type' => 'date_popup',
      '#date_year_range' => '-6:+3',
      '#date_increment' => '5',
      '#title' => t('Date this pijs is expected to begin'),
      '#default_value' => (!empty($pijs->act_date_begin)) ? format_date($pijs->act_date_begin,'short') : '',
    ), 
    'act_date_end' => array(
      '#type' => 'date_popup',
      '#date_year_range' => '-6:+3',
      '#date_increment' => '5',
      '#title' => t('Date this pijs is expected to end'),
      '#default_value' => (!empty($pijs->act_date_end)) ? format_date($pijs->act_date_end,'short') : '',
    ), 
    'hour_plus' => array(
      '#type' => 'button',
      '#title' => t('+'),
//    '#default_value' => (isset($pijs->attr['one_hour'])) ? $pijs->attr['one_hour'] : $pijs_type->attr['one_hour'],
    ), 
    'hour_minus' => array(
      '#type' => 'button',
      '#title' => t('-'),
//    '#default_value' => (isset($pijs->attr['one_hour'])) ? $pijs->attr['one_hour'] : $pijs_type->attr['one_hour'],
    ), 
    'work_hours' => array(
      '#type' => 'button',
      '#title' => t('Work Hours?'),
      '#default_value' => (isset($pijs->attr['work_hours'])) ? $pijs->attr['work_hours'] : FALSE,
    ), 
    'all_day' => array(
      '#type' => 'checkbox',
      '#title' => t('Add Day'),
      '#default_value' => (isset($pijs->attr['all_day'])) ? $pijs->attr['all_day'] : FALSE,
    ), 
    'auto_activate' => array(
      '#type' => 'checkbox',
      '#title' => t('Automatically activate this event?'),
      '#default_value' => (isset($pijs->attr['auto_activate'])) ? $pijs->attr['auto_activate'] : $pijs_type->attr['auto_activate'],
    ), 
  );
}

function _pijs_add_desc($form, &$form_state, $pijs, $pijs_type, $args) {
  // Description
  return;
}

function _pijs_add_comments($form, &$form_state, $pijs, $pijs_type, $args) {
  // Comments
  return;
}

function _pijs_add_addl_fields($form, &$form_state, $pijs, $pijs_type, $args) {
  // Additional Fields
  return;
}

function _pijs_add_actions($form, &$form_state, $pijs, $pijs_type, $args) {
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
      '#value' => t('Save pijs'),
      '#submit' => $submit + array('pijs_edit_form_submit'),
    ),
  );
  
  if (!empty($pijs->name)) {
    $items['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete pijs'),
      '#suffix' => l(t('Cancel'), 'admin/content/pijss'),
      '#submit' => $submit + array('pijs_form_submit_delete'),
      '#weight' => 45,
    );
  }
  return $items;
}

/**
 * Form callback: create or edit a pijs.
 *
 * @param $pijs
 *   The pijs object to edit or for a create form an empty pijs object
 *     with only a pijs type defined.
 */
function pijs_edit_form($form, &$form_state, $pijs) {
  // Add the default field elements.
  $path = drupal_get_path('module','pijs');
//$js = drupal_add_js($path . '/jquery4u.datetime.js',array('group' => 99,
//                                                          'weight' => 100));
  $js = drupal_add_js($path . '/pijs.js',array('group' => 100,
                                                 'weight' => 100));

  $args = _pijs_get_arguments();
  $pijs_type = pijs_get_types($pijs->type);

  // Add the field related form elements.
  $form_state['pijs'] = $pijs;
  field_attach_form('pijs', $pijs, $form, $form_state);

  // Attach CSS file
  $form['#attached']['css'][] = drupal_get_path('module','pijs') . '/pijs.form.css';

  // create form elements
  $form['name_fs']        = _pijs_add_name($form,$form_state,$pijs,$pijs_type,$args);
  $form['owner_fs']       = _pijs_add_owner($form,$form_state,$pijs,$pijs_type,$args);
  $form['department_fs']  = _pijs_add_department($form,$form_state,$pijs,$pijs_type,$args);
  $form['personnel']      = _pijs_add_personnel($form,$form_state,$pijs,$pijs_type,$args);
  $form['facility_fs']    = _pijs_add_facility($form,$form_state,$pijs,$pijs_type,$args);
  $form['importance_fs']  = _pijs_add_importance($form,$form_state,$pijs,$pijs_type,$args);
  $form['status_fs']      = _pijs_add_status($form,$form_state,$pijs,$pijs_type,$args);
  $form['date_fs']        = _pijs_add_date($form,$form_state,$pijs,$pijs_type,$args);
  $form['desc_fs']        = _pijs_add_desc($form,$form_state,$pijs,$pijs_type,$args);
  $form['comments_fs']    = _pijs_add_comments($form,$form_state,$pijs,$pijs_type,$args);
  $form['actions_top']    = _pijs_add_actions($form,$form_state,$pijs,$pijs_type,$args);
  $form['actions_bottom'] = _pijs_add_actions($form,$form_state,$pijs,$pijs_type,$args);

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'pijs_edit_form_validate';
  return $form;
}


/**
 * Form API validate callback for the pijs form
 */
function pijs_edit_form_validate(&$form, &$form_state) {
  $pijs = $form_state['pijs'];
  $form_state['values']['pijs_personnel']['und'] = array();
//foreach ($form_state['values']['pijs_personnel']['und'] as $ind => $fld) {
//  if (isset($fld['target_id'])) {
//  }
//}
  $ind = 0;
  foreach ($form_state['values']['personnel'] as $fld) {
    if (empty($fld)) continue;
    //|| $fld == 0) continue;
    $form_state['values']['pijs_personnel']['und'][$ind] = array('_weight' => $ind,
                                                                             'target_id' => $fld);     
    $ind++;
  }

  // Notify field widgets to validate their data.
//field_attach_form_validate('pijs', $pijs, $form, $form_state);
}


/**
 * Form API submit callback for the pijs form.
 * 
 * @todo remove hard-coded link
 */
function pijs_edit_form_submit(&$form, &$form_state) {
  
  $pijs = entity_ui_controller('pijs')->entityFormSubmitBuildEntity($form, $form_state);
  // Save the pijs and go back to the list of pijss
  
  // Add in created and changed times.
  if ($pijs->is_new = isset($pijs->is_new) ? $pijs->is_new : 0){
    $pijs->created = time();
  }

  $pijs->changed = time();

  $pijs->sch_date_begin = strtotime($pijs->sch_date_begin);
  $pijs->sch_date_end   = strtotime($pijs->sch_date_end);
  $pijs->act_date_begin = strtotime($pijs->act_date_begin);
  $pijs->act_date_end   = strtotime($pijs->act_date_end);

  $pijs->attr['auto_activate'] = $form_state['values']['auto_activate'];
  $pijs->attr['one_hour']      = $form_state['values']['one_hour'];
  $pijs->attr['all_day']       = $form_state['values']['all_day'];
  $pijs->attr['work_day']      = $form_state['values']['work_day'];

  if (preg_match('|\((.*)\)|',$pijs->facility,$matches)) {
    $pijs->facility = $matches[1];
  } else {
    $pijs->facility = _pijs_facility_nid_by_name($pijs->facility);
  }

  $pijs->save();
  $form_state['redirect'] = 'admin/content/pijss';
}

/**
 * Form API submit callback for the delete button.
 * 
 * @todo Remove hard-coded path
 */
function pijs_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/pijss/pijs/' . $form_state['pijs']->tckid . '/delete';
}


/**
 * Form callback: confirmation form for deleting a pijs.
 *
 * @param $pijs
 *   The pijs to delete
 *
 * @see confirm_form()
 */
function pijs_delete_form($form, &$form_state, $pijs) {
  $form_state['pijs'] = $pijs;

  $form['#submit'][] = 'pijs_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete pijs %name?', array('%name' => $pijs->name)),
    'admin/content/pijss/pijs',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );
  
  return $form;
}

/**
 * Submit callback for pijs_delete_form
 */
function pijs_delete_form_submit($form, &$form_state) {
  $pijs = $form_state['pijs'];

  pijs_delete($pijs);

  drupal_set_message(t('The pijs %name has been deleted.', array('%name' => $pijs->name)));
  watchdog('pijs', 'Deleted pijs %name.', array('%name' => $pijs->name));

  $form_state['redirect'] = 'admin/content/pijss';
}



/**
 * Page to add Ticket Entities.
 *
 * @todo Pass this through a proper theme function
 */
function pijs_add_page() {
  $controller = entity_ui_controller('pijs');
  return $controller->addPage();
}


/**
 * Displays the list of available pijs types for pijs creation.
 *
 * @ingroup themeable
 */
function theme_pijs_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="pijs-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer pijs types')) {
      $output = '<p>' . t('Ticket Entities cannot be added because you have not created any pijs types yet. Go to the <a href="@create-pijs-type">pijs type creation page</a> to add a new pijs type.', array('@create-pijs-type' => url('admin/structure/pijs_types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No pijs types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}


/**
 * Sets the breadcrumb for administrative pijs pages.
 */
function pijs_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Tickets'), 'admin/content/pijss'),
  );

  drupal_set_breadcrumb($breadcrumb);
}
