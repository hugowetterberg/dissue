<?php
// $Id$

function _dissue_create() {
  
}

function _dissue_form_get($issue) {
  $form = array();

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => _dissue_form_default($issue, 'title'),
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => _dissue_form_default($issue, 'title'),
  );

  _dissue_form_extend($form, $issue);

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

function _dissue_form_extend(&$form, $issue) {
  
}