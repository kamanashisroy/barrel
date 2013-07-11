<?php

$project['modules'] = array();
$project['core/modules'] = array();
include("modules/core/modules.conf");
include("modules/user/modules.conf");

$project['menu'] = array();
function module_all_register() {
	global $project;
	$x = module_all_call_hook('_module_register', TRUE);
	$project['menu'] = array_merge($project['menu'], (array)$x);
}

function module_all_cleanup() {
	module_all_call_hook('_module_cleanup', FALSE);
}

module_all_register();

