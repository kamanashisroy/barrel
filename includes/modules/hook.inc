<?php

function module_call_hook($grp, $m, $hook, $inc = FALSE, $suffix = NULL) {
	$x = array();
	if($inc) {
		$filename = "modules/".$grp."/".$m."/".$m.($suffix == NULL?"":".".$suffix).".inc";
		if($suffix == NULL || file_exists($filename)) {
			include($filename);
		}
	}
	$cb = $m.$hook;
	if(is_callable($cb)) {
		$x = call_user_func($cb);
	}
	return $x;
}

function module_all_call_hook($hook, $inc = FALSE, $suffix = NULL) {
	global $project;
	$x = array();
	$i = 0;
	$modules = $project['modules'];
	for($i = 0;isset($modules[$i]);$i++) {
		$y = module_call_hook("user", $modules[$i], $hook, $inc, $suffix);
		$x = array_merge( (array)$x, (array)$y);
		
	}
	$modules = $project['core/modules'];
	for($i = 0;isset($modules[$i]);$i++) {
		$y = module_call_hook("core", $modules[$i], $hook, $inc, $suffix);
		$x = array_merge( (array)$x, (array)$y);
	}
	return $x;
}

