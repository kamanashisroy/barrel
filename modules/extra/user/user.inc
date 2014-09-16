<?php

define("MEGHMALA","KUNDALI");


$_user = NULL;
$_users = array();
function user_get($userid = -1) {
	if($userid == -1) {
		global $_user;
		return $_user;
	}
	global $_users;
	if(isset($_users[$userid]))
		return $_users[$userid];
	global $project;
	$user = db_get($project['db'], 'user', $userid);
	$user['index'] = $userid;
	$_users[$userid] = $user;
	return $user;
}

function user_set($userid) {
	global $project;
	$user = db_get($project['db'], 'user', $userid);
	if(is_null($user) || !isset($user['username']))
		return;
	$user['index'] = $userid;
	global $_user;
	$_user = $user;
}

// load user from session.
function user_load($session_id = null) {
	session_name(MEGHMALA);	

	if(is_null($session_id) && !empty($_COOKIE[MEGHMALA])) {
		$session_id = $_COOKIE[MEGHMALA];
	}

	if(!is_null($session_id)) {
		session_id($session_id);
		session_start($session_id);	
		user_set($_SESSION['userid']);
	}
}

function user_module_register() {		
	user_load();	
	return array(
		'user/admin/list' => array(
			'cb' => 'user_admin_user_list',
			'access' => 'user_admin_view_page_access',
			'category' => 'User Administration',
			'title' => 'Users',
			'include' => 'user/user.admin.inc',
			'dir' => module_get_dir(__FILE__),
		),
		'user/admin/add' => array(
			'cb' => 'user_admin_user_add_page',
			'access' => 'user_admin_view_page_access',
			'category' => 'User Administration',
			'title' => 'Add User',
			'include' => 'user/user.admin.inc',
			'dir' => module_get_dir(__FILE__),
		),
		'user/view' => array(
			'cb' => 'user_view_page',
			'access' => 'user_view_page_access',
			'category' => 'User',
			'title' => 'My Account',
			'include' => 'user/user.page.inc',
			'dir' => module_get_dir(__FILE__),
		),
		'user/edit' => array(
			'cb' => 'user_edit_page',
			'access' => 'user_view_page_access',
			'category' => 'User',
			'title' => 'Update Account',
			'include' => 'user/user.page.inc',
			'dir' => module_get_dir(__FILE__),
			'type' => 'hidden',
		),
		'user/login' => array(
			'cb' => 'user_login',
			'category' => 'User',
			'title' => 'Login',
			'type' => 'hidden',
			'include' => 'user/user.page.inc',
			'dir' => module_get_dir(__FILE__),
		),
		'user/logout' => array(
			'cb' => 'user_logout',
			'category' => 'User',
			'access' => 'user_view_page_access',
			'title' => 'Log Out',
			'dir' => module_get_dir(__FILE__),
		),
	);
}

function user_menu_alter($menu) {
	require_once('modules/extra/user/user.api.inc');
	if(user_is_logged_in()) {
		unset($menu['user/login']);
	} else {
		unset($menu['default_page']);
		$menu['default_page'] = $menu['user/login'];
	}
	return $menu;
}

function user_view_page_access($arg, $data) {
	require_once('modules/extra/user/user.api.inc');
	return user_is_logged_in();
}

function user_admin_view_page_access($arg, $data) {
	require_once('modules/extra/user/user.api.inc');
	return user_is_admin();
}


function user_logout($arg) {
	user_load();
	session_destroy();
	//return 'User Logout';
	return barrel_page_build($arg);
}
