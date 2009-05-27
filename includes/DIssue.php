<?php
// $Id$

class DIssue {
  /**
   * Implementation of hook_perm().
   */
  public static function hook_perm() {
    return array('dissue create issue', 'administer dissue');
  }

  /**
   * Implementation of hook_menu().
   */
  public static function hook_menu() {
    $menu = array();

    $menu['dissue/create'] = array(
      'title' => 'Create issue',
      'file' => 'dissue.inc',
      'page callback' => 'drupal_get_form',
      'page arguments' => array('_dissue_create'),
      'access arguments' => array('dissue create issue'),
      'type' => MENU_NORMAL_ITEM,
    );

    $menu['dissue/webhooks/%'] = array(
      'file' => 'dissue.inc',
      'page callback' => '_dissue_handle_webhook',
      'page arguments' => array(2, 3, 4),
      'type' => MENU_CALLBACK,
      'access arguments' => array('access content'),
    );

    $menu['admin/settings/dissue'] = array(
      'title' => 'Dissue settings',
      'file' => 'dissue.admin.inc',
      'page callback' => 'drupal_get_form',
      'page arguments' => array('_dissue_settings'),
      'access arguments' => array('administer dissue'),
      'description' => t('Settings for the distributed issue tracker.'),
    );

    return $menu;
  }

  public static function issueTypes() {
    return array(
      'bug' => t('Bug'),
      'feature-request' => t('Feature request'),
      'support' => t('Support'),
    );
  }

  public static function issueStatuses() {
    return array(
      'open' => t('Open'),
      'fixed' => t('Fixed'),
      'wont-fix' => t('Won\'t fix'),
      'closed' => t('Closed'),
    );
  }

  public static function issueCategories($project=NULL) {
    return array(
      'code' => t('Code'),
      'documentation' => t('Documentation'),
      'interface' => t('Interface'),
    );
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
    $res = db_query("SELECT name, info
      FROM {system}
      WHERE status = %d
      ORDER BY name", array(
        ':status' => TRUE,
    ));

    $projects = array();

    if ($include_site) {
      $projects[url('', array('absolute' => TRUE))] = array(
        'title' => variable_get('site_name', t('This site')),
        'version' => self::siteVersion(),
      );
    }

    while ($p = db_fetch_object($res)) {
      $info = unserialize($p->info);
      $projects[$p->name] = array(
        'title' => $info['name'],
        'version' => $info['version'],
      );
    }

    return $projects;
  }
}