<?php

function ci_page_build($arg) {
	global $project;
	if(!isset($arg) || $arg == "") {
		$arg = 'default_page';
	}
	$menu = $project['menu'];
	if(!isset($menu[$arg])) {
		if(!isset($menu['error/page_not_found'])) {
			return "Page not found";
		}
		$arg = 'error/page_not_found';
	}
	$func = $project['menu'][$arg];
	$output = call_user_func($func, $arg);
	return $output;
}
