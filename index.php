<?php
include("includes/config.inc");
include("includes/string/simple.inc");
include("includes/forms/build.inc");
include("includes/forms/submit.inc");
include("includes/modules/hook.inc");
include("includes/modules/load.inc");
include("includes/menu/build.inc");
include("includes/theme/build.inc");

$project['debug'] = 1;
ci_theme_build(isset($_REQUEST['q'])?$_REQUEST['q']:"");
module_all_cleanup();

