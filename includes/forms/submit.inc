<?php

function ci_form_submit($form_name, $data, $module = NULL) {
	if($module != NULL) {
		$filename = $module.'/'.$module.".form.inc";
		$user_filename = "modules/user/".$filename;
		$core_filename = "modules/core/".$filename;
		$target_filename = file_exists($user_filename)?$user_filename:$core_filename;
		require_once($target_filename);
	}
	$f = call_user_func($form_name, $data);
	// TODO check if the user input is correct
	return call_user_func($form_name.'_submit', $f);
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


