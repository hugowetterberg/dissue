<?php

/**
 * Implement this hook to be able to set default attribute values for a issue.
 *
 * @param array $issue
 *  A reference to a array of issue values
 * @param string $phase
 *  Either 'before' or 'after', this gives third party modules the chance to
 *  decide if they want to apply their defaults before or after internal
 *  defaults are applied. Don't apply the same defaults in both phases, that
 *  would only be a waste of cycles.
 * @return void
 */
function hook_dissue_defaults(&$issue, $phase) {
  switch ($phase) {
    case 'after':
      if (empty($issue['data']['my_custom_debug_message'])) {
        $issue['data']['my_custom_debug_message'] = 'It worked on my machine!';
      }
      break;
  }
}

/**
 * Implement this hook to the issue before or after a write (insert or update)
 * or simply to react to the write operation.
 *
 * @param object $issue
 * @param string $phase
 *  Either 'before' or 'after'. Only alterations made in the before-phase will
 *  be written to the database. The issue id will only be available in the
 *  after-phase if it is a insert.
 * @param bool $insert
 *  TRUE if the write operation is a insert, FALSE if it is a update.
 * @return void
 */
function hook_dissue_write(&$issue, $phase, $insert) {
  if ($insert && $phase==='after') {
    watchdog('dissue', 'The issue @title !id was created', array(
        '@title' => $issue->title,
        '!id' => $issue->liid,
      ));
  }
}

/**
 * Implement this hook to add custom issue types, or alter the existing ones.
 *
 * @param array $types
 *  A associative array containing type descriptions keyed by type name.
 * @return void
 */
function hook_dissue_types_alter(&$types) {
  $types['whining'] = t('Whining');
}

/**
 * Implement this hook to add custom issue statuses, or alter the existing 
 * ones.
 *
 * @param array $status
 *  A associative array containing status descriptions keyed by status name.
 * @return void
 */
function hook_dissue_statuses_alter(&$status) {
  $status['the-maintainer-doesnt-like-you'] = t('Postponed indefinitely');
}

/**
 * Implement this hook to add custom issue categories, or alter the existing 
 * ones.
 *
 * @param array $types
 *  A associative array containing category descriptions keyed by category 
 *  name.
 * @param string $project
 *  The project that is set for the issue.
 * @return void
 */
function hook_dissue_categories_alter(&$category, $project=NULL) {
  switch ($project) {
    case 'dissue':
      unset($category['documentation']);
      $category['praise'] = t('Praise');
      break;
  }
}

/**
 * Implement this hook to add, remove or alter the list of projects available
 * to DIssue.
 *
 * @param array $projects
 *  An associative array containing project information arrays keyed after 
 *  project name. The project information array should contain title and 
 *  version information.
 * @return void
 */
function hook_dissue_projects_alter(&$projects) {
  $projects['new_project'] = array(
    'title' => t('Ideas for new projects'),
    'version' => '',
  );
}