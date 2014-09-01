<?php

define("MEGHMALA","KUNDALI");

function user_load() {
	session_name(MEGHMALA);	
	if(!empty($_COOKIE[MEGHMALA])) {
		session_start($_COOKIE[MEGHMALA]);
	}
	//print_r($SID);
	//print_r($_COOKIE);
	//print_r(session_id());
	//print_r($_SESSION);
}

function user_module_register() {		
	user_load();	
	return array(
		'user/logout' => 'user_logout',
		'user/view' => array(
			'cb' => 'user_view_page',
			'access' => 'user_view_page_access',
			'category' => 'User',
			'title' => 'Hi',
		),
		'user/login' => array(
			'cb' => 'user_login',
			'category' => 'User',
			'title' => 'Login',
			'type' => 'hidden',
			'include' => 'user/user.page.inc',
		),
	);
}

function user_menu_alter($menu) {
	require_once('modules/user/user/user.api.inc');
	if(user_is_logged_in()) {
		unset($menu['user/login']);
	} else {
		unset($menu['default_page']);
		$menu['default_page'] = $menu['user/login'];
	}
	return $menu;
}

function user_view_page_access($arg, $data) {
	require_once('modules/user/user/user.api.inc');
	return user_is_logged_in();
}

function user_view_page() {
	//session_start();
	return 'Hi you .. Mr.'.$_SESSION['name'];
}

function user_logout() {
	if(!empty($_COOKIE[MEGHMALA])) {
		session_start($_COOKIE[MEGHMALA]);
	}
	session_destroy();
	return 'User Logout';
}
