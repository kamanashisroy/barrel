<?php

function campaign_play() {
	return array(
		'campaign_job' => 'campaign_job'
	);
}

define('CALLFILE_SANDBOX', '/tmp');
define('CALLFILE_SPOOLDIR', '/var/lib/asterisk/spool');

function campaign_writecallfile($file, $x) {
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

function campaign_job() {
	$info = array(
		'dial' => 'sometrunk/somenumber',
		'exten' => 'campaign_exten',
		'context' => 'campaign_context',
		'retry' => 'campaign_retry',
	);
	campaign_writecallfile('callfile', $info);
}

