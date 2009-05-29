<?php
// $Id$

function _dissue_create() {
  return _dissue_form_get();
}

function _dissue_create_submit($form, $form_state) {
  $values = $form_state['values'];
  $issue = array(
    'project' => $values['issue_project'],
    'title' => $values['title'],
    'description' => $values['description'],
    'type' => $values['issue_options']['type'],
    'category' => $values['issue_options']['category'],
    'status' => $values['issue_options']['status'],
  );

  $log_ids = array();
  foreach ($values['issue_watchdog'] as $wid => $checked) {
    $log_ids[] = $wid;
  }
  if (!empty($log_ids)) {
    $issue['data']['log'] = DIssue::getLogItems($log_ids);
  }

  $issue = DIssue::issueDefaults($issue);
  DIssue::write($issue);
}

function _dissue_form_get($issue=NULL, $comment=FALSE) {
  $issue || $issue = (object)array();
  $form = array(
    'issue' => array('#type' => 'value', '#value' => $issue),
    'comment' => array('#type' => 'value', '#value' => $comment),
    '#attributes' => array(
      'class' => 'dissue-form',
    ),
  );

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => _dissue_form_default($issue, 'title'),
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => _dissue_form_default($issue, 'description'),
  );

  _dissue_form_extend($form, $issue, $comment);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
}

function _dissue_form_side_effects($form) {
  drupal_add_css(drupal_get_path('module', 'dissue') . '/css/dissue.css');
  drupal_add_js(drupal_get_path('module', 'dissue') . '/script/issue_form.js');
  return $form;
}

function _dissue_form_default($issue, $attr, $default='') {
  if (isset($issue->$attr)) {
    return $issue->$attr;
  }
  else {
    return $default;
  }
}

function _dissue_form_extend(&$form, $issue, $comment=FALSE) {
  global $user;

  $form['#after_build'][] = '_dissue_form_side_effects';

  $form['issue_options'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#title' => t('Options'),
    '#tree' => TRUE,
    '#prefix' => '<div class="dissue-options">',
    '#suffix' => '</div>',
    '#weight' => -1,
  );

  $form['issue_options']['type'] = array(
    '#type' => 'select',
    '#title' => t('Issue type'),
    '#default_value' => _dissue_form_default($issue, 'status'),
    '#options' => DIssue::issueTypes(),
  );

  $form['issue_options']['status'] = array(
    '#type' => 'select',
    '#title' => t('Status'),
    '#default_value' => _dissue_form_default($issue, 'status'),
    '#options' => DIssue::issueStatuses(),
  );

  // TODO: We need some ahah-stuff here to update the categories
  //       based on what project the user has selected.
  $form['issue_options']['category'] = array(
    '#type' => 'select',
    '#title' => t('Category'),
    '#default_value' => _dissue_form_default($issue, 'category'),
    '#options' => DIssue::issueCategories(),
  );

  if (module_exists('dblog')) {
    $form['issue_watchdog'] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('Included log items'),
      '#tree' => TRUE,
      '#attributes' => array(
        'class' => 'watchdog-items',
      ),
    );

    $res = db_query_range("SELECT wid, message, variables, timestamp FROM {watchdog}
      WHERE uid=%d
      ORDER BY timestamp DESC", array(
        ':uid' => $user->uid,
    ), 0, 10);
    while ($item = db_fetch_object($res)) {
      $form['issue_watchdog'][$item->wid] = array(
        '#type' => 'checkbox',
        '#title' => theme('dissue_log_item', $item),
        '#default_value' => variable_get('dissue_include_watchdog_by_default', TRUE),
      );
    }
  }

  if (!variable_get('dissue_only_site_issues', FALSE)) {
    $projects = DIssue::getProjects();
    $p_opts = array();
    foreach ($projects as $name => $info) {
      $p_opts[$name] = $info['title'] . ($info['version'] ? ' v.' . $info['version'] : '');
    }

    $form['issue_project'] = array(
      '#type' => 'select',
      '#title' => t('Project'),
      '#default_value' => _dissue_form_default($issue, 'project'),
      '#options' => $p_opts,
    );
  }
  else {
    $form['issue_project'] = array(
      '#type' => 'value',
      '#value' => url('', array('absolute' => TRUE)),
    );
  }

}

function _dissue_handle_webhook($hook, $id, $nonce=NULL) {
  switch ($hook) {
    case 'issue-updated':
  }

  if ($nonce) {
    print md5($nonce);
    die;
  }
  else {
    printf('%s/%s', $hook, $id);
    die;
  }
}