<?php

function ci_form_submit($form_name, $data) {
	$f = call_user_func($form_name, $data);
	// TODO check if the user input is correct
	return call_user_func($form_name.'_submit', $f);
}

function ci_form_set_value($f, $data) {
	foreach($data as $key=>$val) {
		if(isset($f[$key])) {
			$f[$key]['value'] = $val;
		}
	}
	return $f;
}


