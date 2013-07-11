<?php

require_once("includes/headers/build.inc");

function campaign_module_register() {
	return array(
		'campaign/create' => 'campaign_page_new',
		'campaign/view' => 'campaign_page_view',
		'default_page' => 'campaign_page_new',
	);
}

function campaign_page_new($arg, $data = NULL) {
	$output = ci_header_build('Create Campaign');
	if(isset($data) && $data != NULL) {
		$id = ci_form_submit('campaign_create_form', $data);
		return campaign_page_view('campaign/view/'.$id);
	} else {
		return ci_form_build('campaign_create_form');
	}
}


function campaign_create_form($data = NULL) {
	$cpn = ci_form_new('new_campaign', 'campaign/create');
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
		'title' => 'Days to skip campaign',
		'type' => 'text',
		'tips' => 'for example, sun,mon',
		'db_simple' => TRUE,
	);
	$cpn['skip_hours_of_days'] = array(
		'name' => 'skip_hours_of_days',
		'title' => 'Hours to skip campaign',
		'type' => 'text',
		'tips' => 'for example, 8,9',
		'db_simple' => TRUE,
	);
	$cpn[] = array(
		'name' => 'create',
		'title' => 'Create',
		'type' => 'submit',
	);
	if($data) {
		$cpn['db_name'] = 'campaign';
		$cpn['tbl_name'] = 'campaign';
		$cpn = ci_form_set_value($cpn, $data);
	}
	return $cpn;
}

function campaign_create_form_submit($f) {
	return db_simple_form_insert($f);
}

function campaign_page_view($arg) {
	$index = 0;
	sscanf($arg, "campaign/view/%d", $index);
	$data = db_get('campaign', 'campaign', $index);
	return 'name:'.$data['name'].'index:'.$index;
}

