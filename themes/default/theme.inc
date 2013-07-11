<?php

include('themes/default/form.inc');

function render_theme($arg, $data = NULL) {
	global $project;
	$output = ci_page_build($arg, $data);
	include("themes/default/header.inc");
	echo($output);
	include("themes/default/footer.inc");
}

