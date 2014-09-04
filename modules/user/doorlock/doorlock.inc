<?php

require_once("includes/headers/build.inc");

function doorlock_module_register() {
	return array(
		'default_page' => array(
			'cb' => 'doorlock_welcome',
			'category' => 'Door',
			'title' => 'Welcome',
			'access' => 'user_view_page_access',
			'include' => 'user/user.api.inc',
		),
		'doorlock/operations' => array(
			'cb' => 'doorlock_operations',
			'category' => 'Door',
			'title' => 'Operations',
			'access' => 'user_view_page_access',
			'include' => 'user/user.api.inc',
		),
		'doorlock/open' => array(
			'cb' => 'doorlock_open',
			'category' => 'Door',
			'title' => 'Open',
			'access' => 'user_view_page_access',
			'include' => 'user/user.api.inc',
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
	$output = ci_header_build('Welcome to doorlock open');
	return $output;
}

function doorlock_operations($arg, $data = NULL) {
	$output = ci_header_build('Welcome to doorlock operations');
	return $output;
}


