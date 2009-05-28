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

  $form['dissue_only_site_issues'] = array(
    '#type' => 'checkbox',
    '#title' => t('Only allow site issues'),
    '#default_value' => variable_get('dissue_only_site_issues', FALSE),
    '#descriptions' => t('Activate this option to only allow issues to be filed on the site itself, and not on themes and modules'),
  );

  $form['dissue_include_watchdog_by_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include log items by default'),
    '#default_value' => variable_get('dissue_include_watchdog_by_default', TRUE),
  );

  return system_settings_form($form);
}