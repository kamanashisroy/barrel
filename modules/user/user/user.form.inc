<?php


function user_login_form($data = NULL) {
	$usrlgn = ci_form_new('user_login', 'user/create');
	$usrlgn['name'] = array(
		'name' => 'name',
		'title' => 'Name',
		'type' => 'text',
		//'db_simple' => TRUE,
	);
	$usrlgn['password'] = array(
		'name' => 'Password',
		'title' => 'Password',
		'type' => 'password',
		'tips' => 'Please check if the caps lock is ON or OFF.',
		//'db_simple' => TRUE,
	);
	$usrlgn[] = array(
		'name' => 'login',
		'title' => 'Login',
		'type' => 'submit',
	);
	if($data) {
		$usrlgn['db_name'] = 'user';
		$usrlgn['tbl_name'] = 'user';
		$usrlgn = ci_form_set_value($usrlgn, $data);
	}
	return $usrlgn;
}


