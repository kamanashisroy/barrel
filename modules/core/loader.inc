<?php

$project['modules'] = array();
include("modules/core/modules.conf");
include("modules/user/modules.conf");

function loader_module_register() {
	global $project;
	$i = 0;
	$modules = $project['modules'];
	for($i = 0;isset($modules[$i]);$i++) {
		load_module("user", $modules[$i]);
	}
}
