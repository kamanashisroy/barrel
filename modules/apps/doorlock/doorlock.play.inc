<?php

function doorlock_play() {
	return array(
		'doorlock_open' => 'doorlock_job_open'
	);
}

function doorlock_job_open() {
	echo "It should open the door.\n";
	file_put_contents ('/sys/class/gpio/gpio'.DOORLOCK_PIN.'/value', 1);
}

