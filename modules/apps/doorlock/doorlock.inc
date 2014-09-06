<?php

require_once("includes/headers/build.inc");

function doorlock_module_register() {
	return array(
		'default_page' => array(
			'cb' => 'doorlock_open',
			'category' => 'Door',
			'title' => 'Welcome',
			'access' => 'user_view_page_access',
			'include' => 'user/user.api.inc',
			'dir' => module_get_dir(__FILE__),
		),
		'doorlock/test' => array(
			'cb' => 'doorlock_test',
			'category' => 'Door',
			'title' => 'Testing',
			'access' => 'user_admin_view_page_access',
			'include' => 'user/user.api.inc',
			'dir' => module_get_dir(__FILE__),
		),
		'doorlock/open' => array(
			'cb' => 'doorlock_open',
			'category' => 'Door',
			'title' => 'Open',
			'access' => 'user_view_page_access',
			'include' => 'user/user.api.inc',
			'dir' => module_get_dir(__FILE__),
		),
		'doorlock/log' => array(
			'cb' => 'doorlock_logs',
			'category' => 'Door',
			'title' => 'Logs',
			'access' => 'user_admin_view_page_access',
			'include' => 'user/user.api.inc',
			'dir' => module_get_dir(__FILE__),
		),
	);
}

function doorlock_welcome($arg, $data = NULL) {
	$output = ci_header_build('Welcome to doorlock');
/*
	if(isset($data) && is_array($data) && isset($data['campaign_create_form'])) {
		$id = ci_form_submit('campaign_create_form', $data, 'campaign');
		return campaign_page_view('campaign/view/'.$id);
	} else {
		return ci_form_build('campaign_create_form', 'campaign');
	}
*/
	return $output;
}

function doorlock_open($arg, $data = NULL) {
	$output = ci_header_build('Opening');
	// TODO do open task
	return $output;
}

function doorlock_test($arg, $data = NULL) {
	$output = ci_header_build('Testing');
	// TODO write test script
	return $output;
}

function doorlock_logs($arg,$data) {
	$output = ci_header_build('Logs');
	$view = array();
	global $project;
	db_visit($project['db'], 'doorlock', 'doorlock_logs_helper', $view);
	if(empty($view)) {
		return "No logs";
	}
	return $output + theme_render_view($view);
}

function doorlock_logs_helper(&$cb_argument, $content, $index) {
	$uid = $content['userid'];
	$user = user_load($uid);
	$name = isset($user)?(isset($user['fullname'])?$user['fullname']:$user['username']):'deleted';
	$cb_argument[] = array(
			'value' => theme_render_link(array('link' => ci_link_build('user/view/'.$uid), 'title' => $name)) . $content['tm']
		);
	return 0;
}
