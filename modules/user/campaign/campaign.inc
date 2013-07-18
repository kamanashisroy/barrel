<?php

require_once("includes/headers/build.inc");

function campaign_module_register() {
	return array(
		'campaign/create' => array(
			'cb' => 'campaign_page_new',
			'title' => 'Add',
			'category' => 'Campaign',
		),
		'campaign/view' => array(
			'cb' => 'campaign_page_view',
			'category' => 'Campaign',
			'title' => 'View',
			'include' => 'campaign/campaign.page.inc',
		),
		'default_page' => 'campaign_page_new',
	);
}

function campaign_page_new($arg, $data = NULL) {
	$output = ci_header_build('Create Campaign');
	if(isset($data) && is_array($data) && isset($data['campaign_create_form'])) {
		$id = ci_form_submit('campaign_create_form', $data, 'campaign');
		return campaign_page_view('campaign/view/'.$id);
	} else {
		return ci_form_build('campaign_create_form', 'campaign');
	}
}

