<?php

function ci_page_get($arg_array) {
	global $project;
	$i = count($arg_array);
	$menu = $project['menu'];
	for(;$i;$i--) {
		$tmp = implode("/", array_slice($arg_array,0,$i));
		if(isset($menu[$tmp])) {
			return array('arg' => $tmp, 'func' => $menu[$tmp]);
		}
	}
	return FALSE;
}

function ci_page_build($arg, $data = NULL) {
	if(!isset($arg) || $arg == "") {
		$arg = 'default_page';
	}
	$arg_array = split('/',$arg);
	$func_data = ci_page_get($arg_array);
	if(!$func_data) {
		if(!isset($menu['error/page_not_found'])) {
			return "Page not found";
		}
		$func = $menu['error/page_not_found'];
	} else {
		$func = $func_data['func'];
		//$arg = $func_data['arg'];
	}
	$output = call_user_func($func, $arg, $data);
	return $output;
}
