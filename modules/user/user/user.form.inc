<?php


function user_login_form($data = NULL) {
	$usrlgn = ci_form_new('user_login_form', 'user/login');
	$usrlgn['name'] = array(
		'name' => 'name',
		'title' => 'Name',
		'type' => 'text',
		//'db_simple' => TRUE,
	);
	$usrlgn['password'] = array(
		'name' => 'Password',
		'title' => 'Password',
		'type' => 'password',
		'tips' => 'Please check if the caps lock is ON or OFF.',
		//'db_simple' => TRUE,
	);
	$usrlgn[] = array(
		'name' => 'login',
		'title' => 'Login',
		'type' => 'submit',
	);
	if($data) {
		$usrlgn['db_name'] = 'user';
		$usrlgn['tbl_name'] = 'user';
		$usrlgn = ci_form_set_value($usrlgn, $data);
	}
	return $usrlgn;
}

function user_login_helper() {
	require_once('modules/user/user/user.api.inc');
	//session_destroy();
	global $_COOKIE;
	$_COOKIE = array();
	$name = 'Aparajita';
	$userid = 10;
	$_COOKIE[MEGHMALA] = user_session_prefix($name, $userid).rand(0,100);
	user_load();
	$_SESSION['name'] = $name;
	$_SESSION['username'] = $userid;
	$_SESSION['userid'] = '10';
	//session_close();
	setcookie(MEGHMALA, $_COOKIE[MEGHMALA]);
}

function user_login_form_submit($f) {
	user_login_helper();	
	return 1;
}

