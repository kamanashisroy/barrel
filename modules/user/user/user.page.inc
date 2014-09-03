<?php

function user_login($arg, $data) {
	$output = ci_header_build('User Login');
	if(isset($data) && is_array($data) && isset($data['user_login_form'])) {
		$id = ci_form_submit('user_login_form', $data, 'user');
		return user_view_page('user/view/'.$id);
	} else {
		return ci_form_build('user_login_form', 'user');
	}
	//return 'User Login';
}

function user_view_page() {
	return 'Hi you .. Mr.'.$_SESSION['name'] . ' session: ' . $_SESSION['userid'];
}
