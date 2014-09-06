<?php

function ci_form_submit($form_name, $data, $module = NULL, $arg = null) {
	if($module != NULL) {
		require_once(module_get_source($module.'/'.$module.".form.inc"));
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


