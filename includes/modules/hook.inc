<?php

function module_get_group($filename) {
	return basename(dirname(dirname($filename)));
}

function module_get_current($filename) {
	return basename((dirname($filename)));
}

function module_get_dir($filename) {
	return array(module_get_group($filename),module_get_current($filename));
}

function module_get_source($target_file) {
	$target_module = dirname($target_file);
	global $project;
	foreach($project as $space => $modules) {
		if(!strstr($space, 'modules/'))
			continue;
		if(in_array($target_module, $modules)) {
			return $space.'/'.$target_file;
		}
	}
	return null;
}


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
	foreach($project as $key => $modules) {
		if(!stristr($key,'modules/')) {
			continue;
		}
		$grp = basename($key);
		for($i = 0;isset($modules[$i]);$i++) {
			$y = module_call_hook( $grp, $modules[$i], $hook, $inc, $suffix, $arg);
			$x = array_merge( (array)$x, (array)$y);
		}
	}
	return $x;
}

