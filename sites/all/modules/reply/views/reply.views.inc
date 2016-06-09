<?php
/**
 * @file
 * Provide views data and handlers for reply.module
 */

/**
 * @defgroup views_reply_module reply.module handlers
 *
 * Includes the 'reply' table.
 * @{
 */

/**
 * Implements hook_views_data_alter().
 */
function reply_views_data_alter(&$data) {
  // ----------------------------------------------------------------
  // reply table -- basic table information.

  // Define some fields based upon views_handler_field_entity in the entity
  // table so they can be re-used with other query backends.
  // @see views_handler_field_entity

  $data['views_entity_reply']['edit_reply'] = array(
    'field' => array(
      'title' => t('Edit link'),
      'help' => t('Provide a simple link to edit the reply, if this is possible.'),
      'handler' => 'views_handler_field_reply_link_edit',
      'real field' => 'url',
      'type' => 'uri',
    ),
  );

  $data['views_entity_reply']['delete_reply'] = array(
    'field' => array(
      'title' => t('Delete link'),
      'help' => t('Provide a simple link to delete the reply, if this is possible.'),
      'handler' => 'views_handler_field_reply_link_delete',
      'real field' => 'url',
      'type' => 'uri',
    ),
  );

  $data['views_entity_reply']['reply_reply'] = array(
    'field' => array(
      'title' => t('Reply to reply link'),
      'help' => t('Provide a simple link to reply to the reply, if this is possible.'),
      'handler' => 'views_handler_field_reply_link_reply',
      'real field' => 'url',
      'type' => 'uri',
    ),
  );
}

/**
 * @}
 */
