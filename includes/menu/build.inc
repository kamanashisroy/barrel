<?php

include("includes/menu/menu.inc");

function barrel_page_get($arg_array) {
	global $project;
	$i = count($arg_array);
	$menu = $project['menu'];
	for(;$i;$i--) {
		$tmp = implode("/", array_slice($arg_array,0,$i));
		if(isset($menu[$tmp])) {
			return array('arg' => $tmp, 'menu_info' => $menu[$tmp]);
		}
	}
	return FALSE;
}

function barrel_page_access($x, $arg, $data) {
	if(!isset($x['access']) || (is_bool($x['access']) && $x['access'] ) ) {
		return TRUE;
	}
	return call_user_func($x['access'], $arg, $data);
}

function barrel_page_build($arg, $data = NULL) {
	if(!isset($arg) || $arg == "") {
		$arg = 'default_page';
	}
	$arg_array = split('/',$arg);
	$func_data = barrel_page_get($arg_array);
	if(!$func_data) {
		if(!isset($menu['error/page_not_found'])) {
			return "Page not found";
		}
		$menu_info = $menu['error/page_not_found'];
	} else {
		$menu_info = $func_data['menu_info'];
		//$arg = $func_data['arg'];
	}

	$cb = barrel_menu_get_cb($menu_info);
	if(is_array($menu_info) && isset($menu_info['include'])) {
		require_once(module_get_source($menu_info['include']));
	}

	if(barrel_page_access($menu_info, $arg, $data) == FALSE) {
		return error_page_not_found();
	}

	$output = call_user_func($cb, $arg, $data);
	return $output;
}
