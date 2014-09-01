<?php

function doorlock_play() {
	return array(
		'doorlock_job' => 'doorlock_job'
	);
}

define('CALLFILE_SANDBOX', '/tmp');
define('CALLFILE_SPOOLDIR', '/var/lib/asterisk/spool');

function doorlock_writecallfile($file, $x) {
	if(!($fd = @fopen(CALLFILE_SANDBOX.'/'.$file, 'w'))) {
		return FALSE;
	}
	foreach($x as $key=>$val) {
		@fputs($fd, $key.' : '.$val."\r\n");
	}
	@fclose($fd);
	fmove(CALLFILE_SANDBOX.'/'.$file, CALLFILE_SPOOLDIR.'/'.$file);
	return TRUE;
}

function doorlock_job() {
	$info = array(
		'dial' => 'sometrunk/somenumber',
		'exten' => 'doorlock_exten',
		'context' => 'doorlock_context',
		'retry' => 'doorlock_retry',
	);
	doorlock_writecallfile('callfile', $info);
}

