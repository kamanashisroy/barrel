<?php

function ci_theme_build($arg) {
	global $project;
	include("themes/".$project['theme']."/theme.inc");
	render_theme($arg);
}
