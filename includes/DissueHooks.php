<?php
// $Id$

/**
 * Convenience wrapper for all hook implementations to allow lazy-loading and
 * get the hook-code organized.
 */
class DIssueHooks {
  /**
   * Implementation of hook_perm().
   */
  public static function perm() {
    return array('dissue create issue', 'administer dissue');
  }

  /**
   * Implementation of hook_menu().
   */
  public static function menu() {
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

  /**
   * Implementation of hook_theme().
   */
  public static function theme() {
    $tpl_dir = drupal_get_path('module', 'dissue') . '/templates';
    return array(
      'dissue_log_item' => array(
        'path' => $tpl_dir,
        'template' => 'log_item',
        'arguments' => array(
          'item' => NULL,
        )
      )
    );
  }
}