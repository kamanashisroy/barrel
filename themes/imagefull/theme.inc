<?php

include('themes/imagefull/form.inc');
include('themes/imagefull/menu.inc');
include('themes/imagefull/view.inc');
include('themes/imagefull/link.inc');

function render_theme($arg, $data = NULL) {
	global $project;
	$output = barrel_page_build($arg, $data);
	include("themes/imagefull/header.inc");
	echo($output);
	include("themes/imagefull/footer.inc");
}

