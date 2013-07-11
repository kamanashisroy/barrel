<?php

function module_call_hook($grp, $m, $hook, $inc = FALSE) {
	$x = array();
	if($inc) {
		include("modules/".$grp."/".$m.".inc");
	}
	$cb = $m.$hook;
	if(is_callable($cb)) {
		$x = call_user_func($cb);
	}
	return $x;
}

function module_all_call_hook($hook, $inc = FALSE) {
	global $project;
	$x = array();
	$i = 0;
	$modules = $project['modules'];
	for($i = 0;isset($modules[$i]);$i++) {
		$y = module_call_hook("user", $modules[$i], $hook, $inc);
		$x = array_merge( (array)$x, (array)$y);
		
	}
	$modules = $project['core/modules'];
	for($i = 0;isset($modules[$i]);$i++) {
		$y = module_call_hook("core", $modules[$i], $hook, $inc);
		$x = array_merge( (array)$x, (array)$y);
	}
	return $x;
}

