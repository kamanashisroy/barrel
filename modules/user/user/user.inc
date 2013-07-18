<?php

function user_module_register() {
	return array(
		'user/logout' => 'user_logout',
		'user/login' => array(
			'cb' => 'user_login',
			'category' => 'User',
			'title' => 'Login',
			'include' => 'user/user.page.inc',
		),
	);
}

function user_logout() {
	session_destroy();
	return 'User Logout';
}
