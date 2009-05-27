<?php
// $Id$

function _dissue_create() {
  return _dissue_form_get();
}

function _dissue_create_submit($form, $form_state) {
  
}

function _dissue_form_get($issue=NULL, $comment=FALSE) {
  $issue || $issue = (object)array();
  $form = array(
    'issue' => array('#type' => 'value', '#value' => $issue),
    'comment' => array('#type' => 'value', '#value' => $comment),
    '#attributes' => array(
      'class' => 'dissue-form',
    ),
    '#after_build' => array('_dissue_form_side_effects'),
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

  $form['issue_options']['category'] = array(
    '#type' => 'select',
    '#title' => t('Category'),
    '#default_value' => _dissue_form_default($issue, 'category'),
    '#options' => DIssue::issueCategories(),
  );

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