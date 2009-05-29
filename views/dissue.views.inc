<?php
// $Id$

/**
 * @file
 *  Provide views data and handlers for dissue.module
 */

/**
 * Implementation of hook_views_data().
 */
function dissue_views_data() {
  $data = array();

  /* Tables */

  // Issues
  $data['dissue']['table']['group']  = t('Issue');
  $data['dissue']['table']['base'] = array(
    'field' => 'liid',
    'title' => t('Issue'),
    'help' => t("Issues."),
  );
  // Users
  $data['dissue_user']['table']['group']  = t('DIssue user info');

  // Convenient declaration to merge with for most fields
  $plain_string_field = array(
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array('handler' => 'views_handler_argument_string'),
    'filter' => array('handler' => 'views_handler_filter_string'),
    'sort' => array('handler' => 'views_handler_sort'),
  );
  $plain_num_field = array(
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'numeric' => TRUE,
    ),
    'filter' => array('handler' => 'views_handler_filter_numeric'),
    'sort' => array('handler' => 'views_handler_sort'),
  );

  /* Issue fields */
  $data['dissue']['liid'] = array_merge(array(
    'title' => t('Liid'),
    'help' => t('The local id of the issue.'),
  ), $plain_num_field);

  $data['dissue']['luid'] = array_merge(array(
    'title' => t('Reporter luid'),
    'help' => t('The luid of the user that reported the issue.'),
  ), $plain_num_field);

  $data['dissue']['luid'] = array_merge(array(
    'title' => t('Assignee luid'),
    'help' => t('The luid of the user that has been assigned to the issue.'),
  ), $plain_num_field);

  $data['dissue']['title'] = array_merge(array(
    'title' => t('Title'),
    'help' => t('Issue title'),
  ), $plain_string_field);

  $data['dissue']['description'] = array_merge(array(
    'title' => t('Description'),
    'help' => t('Issue description'),
  ), $plain_string_field);

  $data['dissue']['project'] = array_merge(array(
    'title' => t('Project'),
    'help' => t('The project the issue was reported on'),
  ), $plain_string_field);

  $data['dissue']['version'] = array_merge(array(
    'title' => t('Project version'),
    'help' => t('The version of the project the issue was reported on'),
  ), $plain_string_field);

  $data['dissue']['status'] = array_merge(array(
    'title' => t('Status'),
    'help' => t('Issue status'),
  ), $plain_string_field);

  $data['dissue']['type'] = array_merge(array(
    'title' => t('Type'),
    'help' => t('Issue type'),
  ), $plain_string_field);

  $data['dissue']['category'] = array_merge(array(
    'title' => t('Category'),
    'help' => t('Issue category'),
  ), $plain_string_field);

  /* Issue user fields */
  $data['dissue_user']['name'] = array_merge(array(
    'title' => t('Username'),
    'help' => t('The name of the dissue user'),
  ), $plain_string_field);

  /* Relationships */
  $data['dproject']['table']['join'] = array(
    'dissue_user' => array(
      'left_field' => 'luid',
      'field' => 'luid',
    ),
  );

  $data['dissue_user']['table']['join'] = array(
    'user' => array(
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );

  return $data;
}