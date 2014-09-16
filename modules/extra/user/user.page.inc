<?php

function user_login($arg, $data = null) {
	require_once('modules/extra/user/user.api.inc');
	$output = barrel_header_build('User Login');
	if(isset($data) && is_array($data) && isset($data['user_login_form'])) {
		barrel_form_submit('user_login_form', $data, 'user');
	}
	if(user_is_logged_in()) {
		//$user = user_get();
		//return user_view_page('user/view/'.$user['index']);
		return user_view_page('user/view/');
	} else {
		return barrel_form_build('user_login_form', 'user');
	}
}


function user_view_page($arg = null) {
	$user = null;
	$edit_link = 'user/edit';
	if(is_null($arg)) {
		$user = user_get();
	} else {
		$tmp = split('/', $arg);
		$index = isset($tmp[2])?$tmp[2]:-1;
		$user = user_get($index);
		if($index == $user['index'])
			$edit_link = 'user/edit/'.$user['index'];
	}

	if(!isset($user['username'])) {
		$user = user_get();
	}

	$view = array(
		'Picture' => array(
			'value' => theme_render_image(array('src' => user_picture($user['index']))),
		),
		'Login Name' => array(
			'value' => $user['username'],
		),
		'Full Name' => array(
			'value' => isset($user['fullname'])?$user['fullname']:"",
		),
		'Created On' => array(
			'value' => isset($user['created_on'])?date('Y-m-d', $user['created_on']):"",
		),
		'Edit' => array(
			'value' => theme_render_link(
				array(
					'link' => barrel_link_build($edit_link),
					'title' => ((isset($user['fullname']) && $user['fullname'] != "")?$user['fullname']:$user['username'])
				)
			)
		),
	);
	return theme_render_view($view);
	//return barrel_form_build('user_view_form', 'user', $user);
}

function user_edit_page($arg,$data) {
	//require_once('modules/extra/user/user.api.inc');
	//$output = barrel_header_build('Personal Settings');
	if(isset($data) && is_array($data) && isset($data['user_edit_form'])) {
		$uid = barrel_form_submit('user_edit_form', $data, 'user', $arg);
		return barrel_page_build('user/view/'.$uid);
	}
	return barrel_form_build('user_edit_form', 'user', $arg);
}


