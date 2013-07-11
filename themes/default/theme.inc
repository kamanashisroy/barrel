<?php


function render_theme($arg) {
	global $project;
	include("themes/default/header.inc");
	echo(ci_page_build($arg));
	include("themes/default/footer.inc");
}

