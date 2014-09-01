<?php

function doorlock_create_form($data = NULL) {
	$cpn = ci_form_new('new_doorlock', 'doorlock/create');
	$cpn['name'] = array(
		'name' => 'name',
		'title' => 'Name',
		'type' => 'text',
		'db_simple' => TRUE,
	);
	$cpn['start'] = array(
		'name' => 'start',
		'title' => 'Start on date',
		'type' => 'text',
		'tips' => 'date:month:year, for example, 12:12:2013',
		'db_simple' => TRUE,
	);
	$cpn['end'] = array(
		'name' => 'end',
		'title' => 'To the date',
		'type' => 'text',
		'tips' => 'date:month:year, for example, 12:12:2013',
		'db_simple' => TRUE,
	);
	$cpn['skip_days_of_week'] = array(
		'name' => 'skip_days_of_week',
		'title' => 'Days to skip doorlock',
		'type' => 'text',
		'tips' => 'for example, sun,mon',
		'db_simple' => TRUE,
	);
	$cpn['skip_hours_of_days'] = array(
		'name' => 'skip_hours_of_days',
		'title' => 'Hours to skip doorlock',
		'type' => 'text',
		'tips' => 'for example, 8,9',
		'db_simple' => TRUE,
	);
	$cpn['number_file'] = array(
		'name' => 'number_file',
		'title' => 'Number',
		'type' => 'file',
		'tips' => 'CSV file containing number',
		'db_simple' => TRUE,
	);
	$cpn['speech_file'] = array(
		'name' => 'speech_file',
		'title' => 'Speech',
		'type' => 'file',
		'tips' => 'Speech file (PCM format)',
		'db_simple' => TRUE,
	);
	$cpn[] = array(
		'name' => 'create',
		'title' => 'Create',
		'type' => 'submit',
	);
	if($data) {
		$cpn['db_name'] = 'doorlock';
		$cpn['tbl_name'] = 'doorlock';
		$cpn = ci_form_set_value($cpn, $data);
	}
	return $cpn;
}

function doorlock_create_form_submit($f) {
	return db_simple_form_insert($f);
}

