<?php

function user_login($arg, $data) {
	require_once('modules/user/user/user.api.inc');
	$output = ci_header_build('User Login');
	if(isset($data) && is_array($data) && isset($data['user_login_form'])) {
		ci_form_submit('user_login_form', $data, 'user');
	}
	if(user_is_logged_in()) {
		$user = user_get();
		return user_view_page('user/view/'.$user['index']);
	} else {
		return ci_form_build('user_login_form', 'user');
	}
}

function user_view_page($arg = null) {
	$user = null;
	if(is_null($arg)) {
		$user = user_get();
	} else {
		$tmp = split('/', $arg);
		$index = isset($tmp[2])?$tmp[2]:-1;
		$user = user_get($index);
	}

	$view = array(
		'Login Name' => array(
			'value' => $user['username'],
		),
		'Full Name' => array(
			'value' => $user['fullname'],
		),
		'Created On' => array(
			'value' => date('Y-m-d', $user['created_on']),
		),
	);
	return theme_render_view($view);
	//return ci_form_build('user_view_form', 'user', $user);
}
