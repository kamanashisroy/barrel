<?php


function user_login_form($data = NULL) {
	$usrlgn = ci_form_new('user_login_form', 'user/login');
	$usrlgn['username'] = array(
		'name' => 'username',
		'title' => 'Name',
		'type' => 'text',
		//'db_simple' => TRUE,
	);
	$usrlgn['password'] = array(
		'name' => 'password',
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
	if(!is_null($data) && isset($data['user_login_form'])) {
		$usrlgn['db_name'] = 'user';
		$usrlgn['tbl_name'] = 'user';
		$usrlgn = ci_form_set_value($usrlgn, $data['user_login_form']);
	}
	return $usrlgn;
}

function user_login_helper($user) {
	$session_id = user_session_prefix($user['username'], $user['index']).rand(0,100);
	user_load($session_id);
	$_SESSION['name'] = $user['username'];
	$_SESSION['username'] = $user['username'];
	$_SESSION['userid'] = $user['index'];
	setcookie(MEGHMALA, $session_id);
}

function user_login_form_submit($f) {
	if(!isset($f) || !isset($f['username']) || !isset($f['username']['value'])) {
		return 0;
	}

	$username = $f['username']['value'];
	require_once('modules/user/user/user.api.inc');
	$user = user_get_by_username($username);
	if(is_null($user))
		return 0;

	$upass = trim($user['password']);
	$gpass = trim($f['password']['value']);
	if($upass != $gpass) {
		return 0;
	}

	user_login_helper($user);
	return $index;
}

