<?php

function user_session_prefix() {
	return md5($_SESSION['username'].$_SESSION['userid']);
}

function user_is_logged_in() {
	$sessid = session_id();
	if($sessid != "") {
		return FALSE;
	}
	if(!isset($_SESSION) || !isset($_SESSION['username']) || !isset($_SESSION['userid']) || !is_string($_SESSION['username']) || !is_int($_SESSION['userid'])|| !$_SESSION['userid']) {
		return FALSE;
	}
	$prefix = user_session_prefix();
	if(strncmp($sessid, $prefix, strlen($prefix)) != 0) {
		return FALSE;
	}
	return TRUE;
}

