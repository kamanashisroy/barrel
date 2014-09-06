<?php

function barrel_theme_build($arg) {
	global $project;
	include("themes/".$project['theme']."/theme.inc");
	render_theme($arg, $_REQUEST);
}
