<?php
// $Id$

function _dissue_settings($form_state) {
  $projects = DIssue::getProjects(FALSE);
  $popt = array();
  foreach ($projects as $name => $info) {
    $popt[$name] = $info['title'];
  }

  $form = array();
  $form['dissue_site_project'] = array(
    '#type' => 'select',
    '#title' => t('Site project'),
    '#options' => $popt,
    '#default_value' => variable_get('dissue_site_project', 'system'),
    '#description' => t('Select the project that will be used to fetch version information when users file issues on the site.'),
  );
  return system_settings_form($form);
}