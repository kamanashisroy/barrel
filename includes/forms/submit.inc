<?php

function ci_form_submit($form_name, $data, $module = NULL, $arg = null) {
	if($module != NULL) {
		$filename = $module.'/'.$module.".form.inc";
		$user_filename = 'modules/extra/'.$filename;
		$apps_filename = 'modules/apps/'.$filename;
		$core_filename = 'modules/core/'.$filename;
		$target_filename = file_exists($user_filename)?$user_filename:(file_exists($core_filename)?$core_filename:$apps_filename);
		require_once($target_filename);
	}
	$f = call_user_func($form_name, $data, $arg);
	// TODO check if the user input is correct
	return call_user_func($form_name.'_submit', $f, $arg);
/*
	if($val) {
		// cleanup data
		foreach($f as $key=>$val) {
			if(!is_array($key) || !isset($key['name']) ) {
				continue;
			}
			unset($_REQUEST[$key]);
		}
	}
*/
}

function ci_form_set_value($f, $data) {
	foreach($data as $key=>$val) {
		if(isset($f[$key])) {
			$f[$key]['value'] = $val;
		}
	}
	return $f;
}


