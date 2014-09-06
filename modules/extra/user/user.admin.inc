<?php

function user_admin_user_add_page($arg,$data) {
	//require_once('modules/extra/user/user.api.inc');
	$output = barrel_header_build('Add User');
	if(isset($data) && is_array($data) && isset($data['user_add_form'])) {
		$uid = barrel_form_submit('user_add_form', $data, 'user');
		return barrel_page_build('user/view/'.$uid);
	}
	return barrel_form_build('user_add_form', 'user');
}

function user_admin_user_list($arg,$data) {
	require_once('modules/extra/user/user.api.inc');
	$view = array();
	$refer = array(&$view);
	user_visit('user_admin_user_list_helper', $refer);
	return theme_render_view($view);
}

function user_admin_user_list_helper(&$cb_argument, $content, $index) {
	$name = isset($content['fullname'])?$content['fullname']:$content['username'];
	$cb_argument[0][$content['username']] = array(
			'value' => theme_render_link(array('link' => barrel_link_build('user/view/'.$index), 'title' => $name))
		);
	return 0;
}

