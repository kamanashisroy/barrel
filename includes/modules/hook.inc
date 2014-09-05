<?php

function module_call_hook($grp, $m, $hook, $inc = FALSE, $suffix = NULL, $arg = NULL) {
	$x = array();
	if($inc) {
		$filename = "modules/".$grp."/".$m."/".$m.($suffix == NULL?"":".".$suffix).".inc";
		if($suffix == NULL || file_exists($filename)) {
			include($filename);
		}
	}
	$cb = $m.$hook;
	if(is_callable($cb)) {
		$x = call_user_func($cb, $arg);
	}
	return $x;
}

function module_all_call_hook($hook, $inc = FALSE, $suffix = NULL, $arg = NULL) {
	global $project;
	$x = array();
	$i = 0;
	// TODO write a common rule instead of modules/core,modules/extra,modules/apps
	$modules = $project['modules/core'];
	for($i = 0;isset($modules[$i]);$i++) {
		$y = module_call_hook("core", $modules[$i], $hook, $inc, $suffix, $arg);
		$x = array_merge( (array)$x, (array)$y);
	}
	$modules = $project['modules/extra'];
	for($i = 0;isset($modules[$i]);$i++) {
		$y = module_call_hook("extra", $modules[$i], $hook, $inc, $suffix, $arg);
		$x = array_merge( (array)$x, (array)$y);
	}
	$modules = $project['modules/apps'];
	for($i = 0;isset($modules[$i]);$i++) {
		$y = module_call_hook("apps", $modules[$i], $hook, $inc, $suffix, $arg);
		$x = array_merge( (array)$x, (array)$y);
	}
	return $x;
}

