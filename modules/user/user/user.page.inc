<?php

function user_login() {
	$output = ci_header_build('User Login');
	if(isset($data) && is_array($data) && isset($data['user_login_form'])) {
		$id = ci_form_submit('user_login_form', $data, 'user');
		return campaign_page_view('user/view/'.$id);
	} else {
		return ci_form_build('user_login_form', 'user');
	}
	//session_start();
	//return 'User Login';
}
