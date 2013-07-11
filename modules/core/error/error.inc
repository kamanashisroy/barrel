<?php


function error_module_register() {
	return array(
		'error/page_not_found' => 'error_page_not_found',
		'error/whoami' => 'error_whoami',
	);
}

function error_whoami() {
	die(`whoami`);
}

function error_page_not_found() {
	return 'We are sorry that the asked page is not found';
}

function error_report($log) {
	global $project;
	if($project['debug']) {
		if($project['debug'] == 2) {
			echo $log;
		} else {
			error_log($log, 3, '/tmp/website_'.$project['name'].'.log');
		}
	}
}

