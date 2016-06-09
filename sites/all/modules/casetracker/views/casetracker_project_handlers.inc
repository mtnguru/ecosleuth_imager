<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying links to entities
 * as fields.
 */
class casetracker_project_handler_link_field extends views_handler_field {

  function construct() {
    parent::construct();

    $this->additional_fields['pid'] = 'pid';
    $this->additional_fields['type'] = 'type';
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['text'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $text = !empty($this->options['text']) ? $this->options['text'] : t('view');
    $pid = $values->{$this->aliases['pid']};

    return l($text, 'casetracker/project/' . $pid);
  }

}

/**
 * @file
 * Contains a Views field handler to take care of displaying edit links
 * as fields
 */
class casetracker_project_handler_edit_link_field extends casetracker_project_handler_link_field {

  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }

  function render($values) {
    $type = $values->{$this->aliases['type']};

    //Creating a dummy project to check access against
    $dummy_project = (object) array('type' => $type);
    if (!casetracker_project_access('edit', $dummy_project)) {
      return;
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
    $pid = $values->{$this->aliases['pid']};

    return l($text, 'casetracker/project/' . $pid . '/edit', array(
          'query' => drupal_get_destination()
        ));
  }

}

/**
 * @file
 * Contains a Views field handler to take care of displaying deletes links
 * as fields
 */
class casetracker_project_handler_delete_link_field extends casetracker_project_handler_link_field {

  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }

  function render($values) {
    $type = $values->{$this->aliases['type']};

    //Creating a dummy model to check access against
    $dummy_project = (object) array('type' => $type);
    if (!casetracker_project_access('edit', $dummy_project)) {
      return;
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    $pid = $values->{$this->aliases['pid']};

    return l($text, 'casetracker/project/' . $pid . '/delete', array(
          'query' => drupal_get_destination()
        ));
  }

}