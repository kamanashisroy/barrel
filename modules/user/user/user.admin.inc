<?php

function user_admin_user_add_page($arg,$data) {
	//require_once('modules/user/user/user.api.inc');
	$output = ci_header_build('Add User');
	if(isset($data) && is_array($data) && isset($data['user_add_form'])) {
		$uid = ci_form_submit('user_add_form', $data, 'user');
		return ci_page_build('user/view/'.$uid);
	}
	return ci_form_build('user_add_form', 'user');
}

function user_admin_user_list($arg,$data) {
	require_once('modules/user/user/user.api.inc');
	$view = array();
	user_visit('user_admin_user_list_helper', $view);
	return theme_render_view($view);
}

function user_admin_user_list_helper(&$cb_argument, $content, $index) {
	$name = isset($content['fullname'])?$content['fullname']:$content['username'];
	$cb_argument[$content['username']] = array(
			'value' => theme_render_link(array('link' => ci_link_build('user/view/'.$index), 'title' => $name))
		);
	return 0;
}

