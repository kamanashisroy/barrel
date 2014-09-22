<?php

define ("DOORLOCK_PIN", "4");
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
		'doorlock/close' => array(
			'cb' => 'doorlock_close',
			'category' => 'Door',
			'title' => 'Close',
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
	$output = barrel_header_build('Welcome to doorlock');
/*
	if(isset($data) && is_array($data) && isset($data['campaign_create_form'])) {
		$id = barrel_form_submit('campaign_create_form', $data, 'campaign');
		return campaign_page_view('campaign/view/'.$id);
	} else {
		return barrel_form_build('campaign_create_form', 'campaign');
	}
*/
	return $output;
}

function doorlock_open_cronjob() {
	file_put_contents ('/sys/class/gpio/gpio'.DOORLOCK_PIN.'/value', 1);
}

function doorlock_open($arg, $data = NULL) {
	global $project;
	$output = barrel_header_build('Opening');
	$cron_job = db_get($project['db'], 'cron', 1);
	$newcron = false;
	if(!isset($cron_job) || !isset($cron_job['index'])) {
		$newcron = true;
		$cron_job = array();
	}
	$cron_job['cb'] = 'doorlock_open_cronjob';
	$cron_job['done'] = 0;
	if($newcron) {
		db_insert($project['db'], 'cron', $cron_job);
	} else {
		db_update($project['db'], 'cron', 1, $cron_job);
	}
	// log the opening event
	$user = user_get();
	$log = array();
        $log['tm'] = time();
        $log['userid'] = $user['index'];
        db_insert($project['db'], 'doorlock', $log);
	return $output;
}

function doorlock_close($arg, $data = NULL) {
	$output = barrel_header_build('Closing');
	file_put_contents ('/sys/class/gpio/gpio'.DOORLOCK_PIN.'/value', 0);
	return $output;
}

function doorlock_logs($arg,$data) {
	$output = barrel_header_build('Logs');
	$view = array();
	$refer = array('view' => &$view);
	global $project;
	db_visit($project['db'], 'doorlock', 'doorlock_logs_helper', $refer);
	if(empty($view)) {
		return "No logs";
	}
	return $output + theme_render_view($view);
}

function doorlock_logs_helper(&$cb_argument, $content, $index) {
	$uid = $content['userid'];
	$user = user_get($uid);
	$name = isset($user)?(isset($user['fullname'])?$user['fullname']:$user['username']):'deleted';
	$cb_argument['view'][$name] = array(
			'value' => theme_render_link(array('link' => barrel_link_build('user/view/'.$uid), 'title' => $name)) . date('Y-m-d', $content['tm'])
		);
	return 0;
}

