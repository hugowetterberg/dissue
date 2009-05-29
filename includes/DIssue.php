<?php
// $Id$

class DIssue {
  public static function issueDefaults($issue) {
    $issue = (array)$issue;
    $projects = DIssue::getProjects();
    if (!$issue['project']) {
      $issue['project'] = url('', array('absolute' => TRUE));
    }

    self::invokeByRef('dissue_defaults', $issue, 'before');
    $values = array_merge(array(
      'data' => array(),
      'luid' => DIssue::getLuid(),
      'version' => $projects[$issue['project']]['version'],
    ), $issue);
    self::invokeByRef('dissue_defaults', $issue, 'after');

    return (object)$values;
  }

  public function getLuid($account=NULL, $site=0) {
    // Load user if needed...
    if (is_int($account)) {
      $account = user_load(array('uid' => $account));
    }
    // ...use defaults if necessary.
    else if (!$account) {
      global $user;
      $account = $user;
    }

    // Set default value for site if necessary.
    if (!$site) {
      $site = variable_get('dissue_local_site', 1);
    }

    // Fetch the local user id for the account
    $luid = db_result(db_query("SELECT luid
      FROM {dissue_user}
      WHERE sid = %d
      AND uid = %d", array(
        ':sid' => $site,
        ':uid' => $account->uid,
    )));

    // Create a dissue entry for the user if it didn't have one
    if (!$luid) {
      $values = array(
        'name' => $account->name,
        'sid' => $site,
        'uid' => $account->uid,
      );
      drupal_write_record('dissue_user', $values);
      $luid = $values['luid'];
    }
    return $luid;
  }

  private static function invokeByRef($hook, &$obj) {
    // Construct our argument array
    $args = func_get_args();
    array_shift($args);
    $args[0] = &$obj;

    $modules = module_implements($hook);
    foreach ($modules as $module) {
      call_user_func_array($module . '_' . $hook, $args);
    }
  }

  public static function write(&$issue) {
    $update = isset($issue->liid)
      ? array('liid')
      : NULL;
    self::invokeByRef('dissue_write', $issue, 'before', !$update);
    drupal_write_record('dissue', $issue, $update);
    self::invokeByRef('dissue_write', $issue, 'after', !$update);
  }

  public static function issueTypes() {
    $types = array(
      'bug' => t('Bug'),
      'feature-request' => t('Feature request'),
      'support' => t('Support'),
    );
    drupal_alter('dissue_types', $types);
    return $types;
  }

  public static function issueStatuses() {
    $statuses = array(
      'open' => t('Open'),
      'active' => t('Active'),
      'fixed' => t('Fixed'),
      'wont-fix' => t('Won\'t fix'),
      'closed' => t('Closed'),
    );
    drupal_alter('dissue_statuses', $statuses);
    return $statuses;
  }

  public static function issueCategories($project=NULL) {
    $categories = array(
      'code' => t('Code'),
      'documentation' => t('Documentation'),
      'interface' => t('Interface'),
    );
    drupal_alter('dissue_categories', $categories, $project);
    return $categories;
  }

  public static function siteVersion() {
    $site_module = variable_get('dissue_site_project', 'system');
    $info = db_result(db_query("SELECT info
      FROM {system}
      WHERE name = '%s'", array(
        ':name' => $site_module,
    )));
    if ($info) {
      $info = unserialize($info);
      if (isset($info['version'])) {
        return $info['version'];
      }
    }
    return VERSION;
  }

  public static function getProjects($include_site=TRUE) {
    $cache_key = 'dissue:projects';

    if (($cache = cache_get($cache_key)) && isset($cache->data)) {
      $projects = $cache->data;
    }
    else {
      $res = db_query("SELECT name, info
        FROM {system}
        WHERE status = %d
        ORDER BY name", array(
          ':status' => TRUE,
      ));

      $projects = array();



      while ($p = db_fetch_object($res)) {
        $info = unserialize($p->info);
        $projects[$p->name] = array(
          'title' => $info['name'],
          'version' => $info['version'],
        );
      }

      drupal_alter('dissue_projects', $projects);
      cache_set($cache_key, $projects);
    }

    // Prepend the site project if required
    if ($include_site) {
      $projects = array_merge(array(url('', array('absolute' => TRUE)) => array(
        'title' => variable_get('site_name', t('This site')),
        'version' => self::siteVersion(),
      )), $projects);
    }

    return $projects;
  }
}