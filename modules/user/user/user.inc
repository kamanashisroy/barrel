<?php

define("MEGHMALA","KUNDALI");

function user_load($session_id = null) {
	session_name(MEGHMALA);	

	if(is_null($session_id) && !empty($_COOKIE[MEGHMALA])) {
		$session_id = $_COOKIE[MEGHMALA];
	}

	if(!is_null($session_id)) {
		session_id($session_id);
		session_start($session_id);	
		db_get($project['db'], 'user', $_SESSION['userid']);
	}

	//print_r($SID);
	//print_r($_COOKIE);
	//print_r(session_id());
	//print_r($_SESSION);
}

function user_module_register() {		
	user_load();	
	return array(
		'user/logout' => array(
			'cb' => 'user_logout',
			'category' => 'User',
			'access' => 'user_view_page_access',
			'title' => 'Log Out',
		),
		'user/admin' => array(
			'cb' => 'user_admin_page',
			'access' => 'user_admin_view_page_access',
			'category' => 'User',
			'title' => 'User Administration',
			'include' => 'user/user.admin.inc',
		),
		'user/view' => array(
			'cb' => 'user_view_page',
			'access' => 'user_view_page_access',
			'category' => 'User',
			'title' => 'Hi',
			'include' => 'user/user.page.inc',
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

function user_admin_view_page_access($arg, $data) {
	require_once('modules/user/user/user.api.inc');
	return user_is_admin();
}


function user_logout($arg) {
	user_load();
	session_destroy();
	//return 'User Logout';
	return ci_page_build($arg);
}
