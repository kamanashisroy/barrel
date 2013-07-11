<?php
include("includes/config.inc");
include("includes/forms/build.inc");
include("includes/modules/load.inc");
include("includes/menu/build.inc");
include("includes/theme/build.inc");

ci_theme_build($_REQUEST['q']);
