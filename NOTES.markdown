Distributed bug reporting
-------------------------

Clients wouldn't have to leave their site to report issues.
Can be used to collect Drupal and module version information from clients.
It should be _optional_ to create nodes for issues

Projects
============

* The site itself is a project
  * Allow the selection of a site-specific module
* Modules are projects
* Themes are projects
* User defined projects

Issues
===============

* Attributes
  * Title
  * Description
  * Priority - use the SCRUM idea for priority? Never allow the same priority to be set for two issues.
  * Project
  * Version
  * Milestone
  * Status - open, closed
  * Component
  * Type - bug, feature request, support and so on
  * Category - Code, Documentation, UI
  * Tags - Arbitrary tags
  * Environment info - Browser version, page uri, page source, headers?, PHP info
  * Site
  * Reporter (site,user)
  * Assigned to (site,user)
* In-site issue creation
* Use version information where available
  * Fill in versions of modules and themes
* Collect watchdog information from modules
  * Check for log entries where category == [component name]
  * Allow manual category override on component level

Issue comments
===============

Drupal.org style where comments are used to update the properties of the issue.

Components
===============

* Global and project-specific

Categories & Tags
==================

* Global
* Uses taxonomy
