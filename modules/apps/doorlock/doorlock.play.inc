<?php

function doorlock_play() {
	return array(
		'doorlock_testing' => 'doorlock_job_testing',
		'doorlock_open' => 'doorlock_job_open'
	);
}

function doorlock_job_testing() {
	echo "It will try different combinations of gpio pins.\n";
}

function doorlock_job_open() {
	echo "It should open the door.\n";
	file_put_contents ('/sys/class/gpio/gpio'.DOORLOCK_PIN.'/value', 1);
}

