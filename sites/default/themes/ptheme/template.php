<?php

/**
 * @file
 * Process theme data.
 *
 * Use this file to run your theme specific implimentations of theme functions,
 * such preprocess, process, alters, and theme function overrides.
 *
 * Preprocess and process functions are used to modify or create variables for
 * templates and theme functions. They are a common theming tool in Drupal, often
 * used as an alternative to directly editing or adding code to templates. Its
 * worth spending some time to learn more about these functions - they are a
 * powerful way to easily modify the output of any template variable.
 * 
 * Preprocess and Process Functions SEE: http://drupal.org/node/254940#variables-processor
 * 1. Rename each function and instance of "ps" to match
 *    your subthemes name, e.g. if your theme name is "footheme" then the function
 *    name will be "footheme_preprocess_hook". Tip - you can search/replace
 *    on "ptheme".
 * 2. Uncomment the required function to use.
 */


/**
 * Preprocess variables for the html template.
 */
/* -- Delete this line to enable.
function ptheme_preprocess_html(&$vars) {
  global $theme_key;

  // Two examples of adding custom classes to the body.
  
  // Add a body class for the active theme name.
  // $vars['classes_array'][] = drupal_html_class($theme_key);

  // Browser/platform sniff - adds body classes such as ipad, webkit, chrome etc.
  // $vars['classes_array'][] = css_browser_selector();

}
// */


/**
 * Process variables for the html template.
 */
/* -- Delete this line if you want to use this function
function ptheme_process_html(&$vars) {
}
// */


/**
 * Override or insert variables for the page templates.
 */
/* -- Delete this line if you want to use these functions
function ptheme_preprocess_page(&$vars) {
}
function ptheme_process_page(&$vars) {
}
// */


/**
 * Override or insert variables into the node templates.
 */
/* -- Delete this line if you want to use these functions
function ptheme_preprocess_node(&$vars) {
}
function ptheme_process_node(&$vars) {
}
// */


/**
 * Override or insert variables into the comment templates.
 */
/* -- Delete this line if you want to use these functions
function ptheme_preprocess_comment(&$vars) {
}
function ptheme_process_comment(&$vars) {
}
// */


/**
 * Override or insert variables into the block templates.
 */
/* -- Delete this line if you want to use these functions
function ptheme_preprocess_block(&$vars) {
}
function ptheme_process_block(&$vars) {
}
// */


function ptheme_preprocess_link(&$variables) {
  if (strstr($variables['text'],'BASE_PATH')) {
    $variables['text'] = str_replace('BASE_PATH',$GLOBALS['base_path'],$variables['text']);
  }
}


/**
 * Returns HTML for a menu item.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: Structured array data for a menu item.
 *   - properties: Various properties of a menu item.
 *
 * @ingroup themeable
 */
/*
function ptheme_superfish_menu_item($variables) {
  $element = $variables['element'];
  $properties = $variables['properties'];
  $sub_menu = '';

  if ($element['below']) {
    $sub_menu .= isset($variables['wrapper']['wul'][0]) ? $variables['wrapper']['wul'][0] : '';
    $sub_menu .= ($properties['megamenu']['megamenu_content']) ? '<ol>' : '<ul>';
    $sub_menu .= $element['below'];
    $sub_menu .= ($properties['megamenu']['megamenu_content']) ? '</ol>' : '</ul>';
    $sub_menu .= isset($variables['wrapper']['wul'][1]) ? $variables['wrapper']['wul'][1] : '';
  }

  $output = '<li' . drupal_attributes($element['attributes']) . '>';
  $output .= ($properties['megamenu']['megamenu_column']) ? '<div class="sf-megamenu-column">' : '';
  $output .= isset($properties['wrapper']['whl'][0]) ? $properties['wrapper']['whl'][0] : '';
  if ($properties['use_link_theme']) {
    $link_variables = array(
      'menu_item' => $element['item'],
      'link_options' => $element['localized_options']
    );
    $output .= theme('superfish_menu_item_link', $link_variables);
  }
  else {
    $output .= l($element['item']['link']['title'], $element['item']['link']['href'], $element['localized_options']);
  }
  $output .= isset($properties['wrapper']['whl'][1]) ? $properties['wrapper']['whl'][1] : '';
  $output .= ($properties['megamenu']['megamenu_wrapper']) ? '<ul class="sf-megamenu"><li class="sf-megamenu-wrapper ' . $element['attributes']['class'] . '">' : '';
  $output .= $sub_menu;
  $output .= ($properties['megamenu']['megamenu_wrapper']) ? '</li></ul>' : '';
  $output .= ($properties['megamenu']['megamenu_column']) ? '</div>' : '';
  $output .= '</li>';

  return $output;
} */



/** 
 * Used to change the term id's on the resources block to term names instead
 */
function ptheme_preprocess_views_view_summary(&$vars) {
//if($vars['view']->name == 'media_summary' && $vars['view']->current_display == '[CURRENT_DISPLAY_NAME]') {
    $items = array();
    foreach($vars['rows'] as $result){
      if(is_numeric($result->link)) {
        $term_object = taxonomy_term_load($result->link);
        $result->link = $term_object->name;
        $items[] = $result;
      }
      else {
        //used for the <no-value> item
        $items[] = $result;
      }
    }
    $vars['rows'] = $items;
//}
}



/*
 * Implements HOOK_preprocess_views_view
 */
//function ptheme_preprocess_views_view(&$vars) {
//  $view = $vars['view'];
//  // if the view has a class of ds-images
//  if ($view->display['default']->display_options['css_class'] == 'ds-images') {
//    $vars['header'] = '<div style="display: none; position: absolute; z-index: 110; left: 400; top: 100; width: 15; height: 15" id="preview_div"></div>';
//    // add needed javascript
//    drupal_add_js(drupal_get_path('theme', 'ptheme') . '/image-popup.js');
//    // add needed stylesheet
//    drupal_add_css(drupal_get_path('theme', 'ptheme') .'/image-popup.css');
//  }
//}
//

function ptheme_preprocess_views_view_field(&$vars) {
  $view = $vars['view'];
  // if the view has a class of ds-images

  $vars['output'] = $vars['field']->advanced_render($vars['row']);
  // if the field is 'field_media_status'
  if ($vars['field']->field == 'field_media_status') {
   $vars['field']->options[] = array('attributes' => array(
                               'class' => array($vars['output']),
                               ),
                             );
   $vars['classes_array'][] = $vars['output'];
  }

  if ($view->display['default']->display_options['css_class'] == 'ds-images') {
    /*
    if ($vars['field']->field == 'uri') {
      $width = $vars['row']->_field_data['fid']['entity']->metadata['width'];
      $height = $vars['row']->_field_data['fid']['entity']->metadata['height'];
      if ($width > 1024) {
        $width = 1024;
      }
      if ($height > 768) {
        $height = 768;
      }
      preg_match('/href="(.*?)"/',$vars['output'],$parts);
      $vars['output'] = preg_replace('/alt=/',
                   'onmouseenter="showtrail(\'' . $parts[1] . '\',\'Title of the Picture Goes Here\',' . $width . ',' . $height . ')" onmouseleave="hidetrail()" alt=',
                   $vars['output']);
//                 'onmouseenter="showtrail(\'' . $parts[1] . '\',\'Title of the Picture Goes Here\',' . $width . ',' . $height . ')" alt=',
//                 'onmouseenter="showtrail(\'' . $parts[1] . '\',\'Title of the Picture Goes Here\',' . $width . ',' . $height . ')" onmouseleave="hidetrail()" alt=',
//    var_dump($out);
    }
    */
  }
}


//function ptheme_fieldset(&$vars) {
//   return theme_fieldset($vars);
//}


/**
 * Returns HTML for a form element.
 *
 * Each form element is wrapped in a DIV container having the following CSS
 * classes:
 * - form-item: Generic for all form elements.
 * - form-type-#type: The internal element #type.
 * - form-item-#name: The internal form element #name (usually derived from the
 *   $form structure and set via form_builder()).
 * - form-disabled: Only set if the form element is #disabled.
 *
 * In addition to the element itself, the DIV contains a label for the element
 * based on the optional #title_display property, and an optional #description.
 *
 * The optional #title_display property can have these values:
 * - before: The label is output before the element. This is the default.
 *   The label includes the #title and the required marker, if #required.
 * - after: The label is output after the element. For example, this is used
 *   for radio and checkbox #type elements as set in system_element_info().
 *   If the #title is empty but the field is #required, the label will
 *   contain only the required marker.
 * - invisible: Labels are critical for screen readers to enable them to
 *   properly navigate through forms but can be visually distracting. This
 *   property hides the label for everyone except screen readers.
 * - attribute: Set the title attribute on the element to create a tooltip
 *   but output no label element. This is supported only for checkboxes
 *   and radios in form_pre_render_conditional_form_element(). It is used
 *   where a visual label is not needed, such as a table of checkboxes where
 *   the row and column provide the context. The tooltip will include the
 *   title and required marker.
 *
 * If the #title property is not set, then the label and any required marker
 * will not be output, regardless of the #title_display or #required values.
 * This can be useful in cases such as the password_confirm element, which
 * creates children elements that have their own labels and required markers,
 * but the parent element should have neither. Use this carefully because a
 * field without an associated label can cause accessibility challenges.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #title_display, #description, #id, #required,
 *     #children, #type, #name.
 *
 * @ingroup themeable
 */
function ptheme_form_element($variables) {
  $element = &$variables['element'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  if (isset($variables['classes_array'])) {
    $attributes['class'] = $variables['classes_array'];
  }
  $attributes['class'][] = 'form-item';
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }

      
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;

    case 'after':
      $output .= ' ' . $prefix . $element['#children'] . $suffix;
      $output .= ' ' . theme('form_element_label', $variables) . "\n";
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $prefix . $element['#children'] . $suffix . "\n";
      break;
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="description">' . $element['#description'] . "</div>\n";
  }

  $output .= "</div>\n";

  return $output;
} 


function ptheme_preprocess_form (&$vars) {
  return;
}

function ptheme_preprocess_fieldset (&$vars) {
  return;
}


function ptheme_preprocess_form_element (&$vars) {
  $element = $vars['element'];
  if (!empty($element['#name'])) {
    $name =preg_replace('/\[.*$/','',$element['#name']);
    if (($name == 'field_issue_status') ||
        ($name == 'field_department') ||
        ($name == 'field_system') ||
        ($name == 'field_importance')) {
//    $element['#attributes']['class'][] = 'ds-shadow';
//    $element['#attributes']['class'][] = strtr('ds-' . $element['#title'],array(' ' => '-',));
      $vars['classes_array'][] = 'ds-highlight ds-' . preg_replace('/-+/','-',preg_replace('/[^a-zA-Z0-9]/','-',$element['#title']));
      if (!isset($vars['element']['#options'])) {
//       $vars['classes_array'][] = 'ds-highlight';
      }
    }
  }
  return;
}
