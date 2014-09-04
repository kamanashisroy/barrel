<?php

$db = array();
function db_module_register() {
	global $db;
	$x = module_all_call_hook('_database_register', TRUE, 'db');
	$db = array_merge((array)$db, (array)$x);
	return array();
}

function db_insert($db_name, $tbl, $more) {
	global $db;
	return call_user_func($db['insert'], $db_name, $tbl, $more);
}

function db_delete($db_name, $tbl, $index) {
	global $db;
	return call_user_func($db['delete'], $db_name, $tbl, $index);
}

function db_get($db_name, $tbl, $index) {
	global $db;
	return call_user_func($db['get'], $db_name, $tbl, $index);
}

function db_visit($db_name, $tbl, $visitor, &$visitor_data) {
	global $db;
	return call_user_func($db['visit'], $db_name, $tbl, $visitor, &$visitor_data);
}

function db_get_where($db_name, $tbl, $more) {
	global $db;
	return call_user_func($db['get_where'], $db_name, $tbl, $more);
}

function db_play() {
	global $db;
	return array(
		'insert' => 'db_insert',
		'delete' => 'db_delete',
		'get' => 'db_get',
		'get_where' => 'db_get_where',
	);
}

function db_simple_form_insert($f) {
	if(!isset($f['db_name']) || !isset($f['tbl_name'])) {
		return FALSE;
	}
	$info = array();
	foreach($f as $key => $val) {
		if(!is_array($val)) {
			break;
		}
		if(!is_array($val)) {
			continue;
		}
		if(!$val['db_simple']) {
			continue;
		}
		if(!isset($val['db_key'])) {
			$val['db_key'] = $key;
		}
		$info[$val['db_key']] = $val['value'];
	}
	return db_insert($f['db_name'], $f['tbl_name'], $info);
}

