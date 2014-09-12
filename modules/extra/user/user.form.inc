<?php


function user_login_form($data = NULL, $arg = null) {
	$usrlgn = barrel_form_new('user_login_form', 'user/login');
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
		$usrlgn = barrel_form_set_value($usrlgn, $data['user_login_form']);
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

function user_login_form_submit($f, $arg = null) {
	if(!isset($f) || !isset($f['username']) || !isset($f['username']['value'])) {
		return 0;
	}

	$username = $f['username']['value'];
	require_once('modules/extra/user/user.api.inc');
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

function user_edit_form($data = NULL, $arg = null) {
	$usrlgn = barrel_form_new('user_edit_form', 'user/edit');
	$user = user_get();
	$usrlgn['fullname'] = array(
		'name' => 'fullname',
		'title' => 'Full Name',
		'type' => 'text',
		'value' => isset($user['fullname'])?$user['fullname']:$user['username'],
	);
	$usrlgn['old_password'] = array(
		'name' => 'old_password',
		'title' => 'Old Password',
		'type' => 'password',
		'tips' => 'Put your old password here.',	
	);
	$usrlgn['password'] = array(
		'name' => 'password',
		'title' => 'New Password',
		'type' => 'password',
	);
	$usrlgn['retype_password'] = array(
		'name' => 'retype_password',
		'title' => 'Retype new password',
		'type' => 'password',
		'tips' => 'Please check if the caps lock is ON or OFF.',
	);
	$usrlgn[] = array(
		'name' => 'save',
		'title' => 'Save',
		'type' => 'submit',
	);
	$usrlgn[] = array(
		'name' => 'cancel',
		'title' => 'Cancel',
		'type' => 'reset',
	);
	if(!is_null($data) && isset($data['user_edit_form'])) {
		$usrlgn['db_name'] = 'user';
		$usrlgn['tbl_name'] = 'user';
		$usrlgn = barrel_form_set_value($usrlgn, $data['user_edit_form']);
	}
	return $usrlgn;
}

function user_edit_form_submit($f, $arg = null) {
	if(!isset($f)) {
		return 0;
	}

	$user = user_get();
	// set password
	if(isset($f['password']) && isset($f['password']['value']) && $f['password']['value'] != "") {
		$pass = $f['password']['value'];
		$retype_pass = $f['retype_password']['value'];
		if($pass != $retype_pass 
			|| !isset($f['old_password']) || !isset($f['old_password']['value']) 
			|| $f['old_password']['value'] != $user['password']) {
			// set message("Your password entries did not match");
			return 0;
		}
		$user['password'] =$pass; 
	}

	$username = $f['username']['value'];
	require_once('modules/extra/user/user.api.inc');
	
	$user['fullname'] = $f['fullname']['value'];
	$index = user_save($user);
	return $index;
}

function user_add_form($data = NULL, $arg = null) {
	$usrlgn = barrel_form_new('user_add_form', 'user/admin/add');
	$usrlgn['fullname'] = array(
		'name' => 'fullname',
		'title' => 'Full Name',
		'type' => 'text',
		//'db_simple' => TRUE,
	);
	$usrlgn['username'] = array(
		'name' => 'username',
		'title' => 'Login Name',
		'type' => 'text',
		//'db_simple' => TRUE,
	);
	$usrlgn['password'] = array(
		'name' => 'password',
		'title' => 'Password',
		'type' => 'password',
		//'db_simple' => TRUE,
	);
	$usrlgn['retype_password'] = array(
		'name' => 'retype_password',
		'title' => 'Retype password',
		'type' => 'password',
		'tips' => 'Please check if the caps lock is ON or OFF.',
		//'db_simple' => TRUE,
	);
	$usrlgn[] = array(
		'name' => 'save',
		'title' => 'Save',
		'type' => 'submit',
	);
	$usrlgn[] = array(
		'name' => 'cancel',
		'title' => 'Cancel',
		'type' => 'reset',
	);
	if(!is_null($data) && isset($data['user_add_form'])) {
		$usrlgn['db_name'] = 'user';
		$usrlgn['tbl_name'] = 'user';
		$usrlgn = barrel_form_set_value($usrlgn, $data['user_add_form']);
	}
	return $usrlgn;
}

function user_add_form_submit($f, $arg = null) {
	if(!isset($f) || !isset($f['username']) || !isset($f['username']['value']) || !isset($f['password']) || !isset($f['password']['value'])) {
		return 0;
	}

	$pass = $f['password']['value'];
	$retype_pass = $f['retype_password']['value'];
	if($pass != $retype_pass) {
		// set message("Your password entries did not match");
		return 0;
	}

	$username = $f['username']['value'];
	require_once('modules/extra/user/user.api.inc');
	$user = array();
	$user['username'] = $f['username']['value'];
	$user['fullname'] = $f['fullname']['value'];
	$user['password'] = $f['password']['value'];
	$index = user_add($user);
	return $index;
}


/*
function user_view_form($data = NULL, $arg = null) {
	if($arg == null)
		return array();//user_all_view_form($data, $arg);
	$user = $arg;
	$usrlgn = barrel_form_new('user_view_form', 'user/view/' . $user['index']);
	$usrlgn['username'] = array(
		'title' => 'Login Name',
		'type' => 'label',
		'value' => $user['username'],
	);
	$usrlgn['fullname'] = array(
		'title' => 'Full Name',
		'type' => 'label',
		'value' => $user['fullname'],
	);
	$usrlgn['created_on'] = array(
		'title' => 'Created On',
		'type' => 'label',
		'value' => date('Y-m-d', $user['created_on']),
	);
	return $usrlgn;
}*/

