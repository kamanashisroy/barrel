<?php

function doorlock_play() {
	return array(
		'doorlock_open' => 'doorlock_job_open',
		'doorlock_cron' => 'doorlock_job_cron',
	);
}

function doorlock_job_open() {
	//echo "It should open the door.\n";
	file_put_contents ('/sys/class/gpio/gpio'.DOORLOCK_PIN.'/value', 1);
}

function doorlock_job_cron() {
	//echo "It should open the door.\n";
	global $project;
	$cron_job = db_get($project['db'], 'cron', 1);
	
	if(isset($cron_job) && isset($cron_job['cb']) && (!isset($cron_job['done']) || $cron_job['done']) == 0) {
		call_user_func($cron_job['cb']);
		$cron_job['done'] = 1;
		db_update($project['db'], 'cron', 1, $cron_job);
	}
}

