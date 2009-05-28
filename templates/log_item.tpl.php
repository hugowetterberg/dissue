<?php
// $Id$
?>
<span class="timestamp"><?php print format_date($item->timestamp) ?>
</span><div class="message"><?php print t($item->message, unserialize($item->variables)) ?></div>