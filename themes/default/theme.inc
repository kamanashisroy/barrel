<?php

include('themes/default/form.inc');
include('themes/default/menu.inc');
include('themes/default/view.inc');
include('themes/default/link.inc');

function render_theme($arg, $data = NULL) {
	global $project;
	$output = ci_page_build($arg, $data);
	include("themes/default/header.inc");
	echo($output);
	include("themes/default/footer.inc");
}

