<?php

require_once("includes/headers/build.inc");

function campaign_module_register() {
	return array(
		'campaign/create' => 'campaign_page_new',
	);
}

function campaign_page_new($arg) {
	$output = ci_header_build('Create Campaign');
	$cpn = ci_form_new('new_campaign', 'new_campaign.php');
	$cpn[] = array(
		'name' => 'name',
		'title' => 'Name',
		'type' => 'text',
	);
	return ci_form_build($cpn);
}
