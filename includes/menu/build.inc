<?php

function ci_page_build($arg) {
	global $project;
	$menu = $project['menu'];
	if(!isset($menu[$arg])) {
		echo "Page not found";
	}
	$func = $project['menu'][$arg];
	$output = call_user_func($func, $arg);
	return $output;
}
