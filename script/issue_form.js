// $Id$
jQuery(document).ready(function(select_mode) {
  jQuery('<div class="bulk-ops"></div>').prependTo('.dissue-form .watchdog-items')
    .append('<a id="watchdog-select-all" href="#">' + Drupal.t('Select all') +  '</a>')
    .append('<a id="watchdog-select-none" href="#">' + Drupal.t('Select none') +  '</a>');
  jQuery('#watchdog-select-all').click(function() {
    jQuery('.dissue-form .watchdog-items input').attr('checked', 'checked');
  });
  jQuery('#watchdog-select-none').click(function() {
    jQuery('.dissue-form .watchdog-items input').val([]);
  });
});