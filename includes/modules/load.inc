<?php

$project['menu'] = array();
function load_module($grp,$m) {
	global $project;
	include("modules/".$grp."/".$m.".inc");
	$x = call_user_func($m."_module_register");
	$project['menu'] = array_merge($project['menu'], (array)$x);
}

load_module("core","loader");

