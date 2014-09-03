<?php

function user_session_prefix($name = null, $userid = null) {
	if(is_null($name)) {
		$name = $_SESSION['username'];
	}
	if(is_null($userid)) {
		$userid = $_SESSION['userid'];
	}
	return md5($name.$userid);
}

function user_is_logged_in() {	
	$sessid = session_id();
	if($sessid == "") {	
		return FALSE;
	}
	if(!isset($_SESSION) || !isset($_SESSION['username']) 
		|| !isset($_SESSION['userid']) /*|| !is_string($_SESSION['username'])*/ 
		|| /*!is_int($_SESSION['userid'])||*/ !$_SESSION['userid']) {
		//echo "problem here \n" . $_SESSION['userid'] ;		
		return FALSE;
	}
	$prefix = user_session_prefix($_SESSION['username'], $_SESSION['userid']);//user_session_prefix();
	if(strncmp($sessid, $prefix, strlen($prefix)) != 0) {
		//echo "problem here \n" . $prefix . "!=" . $sessid;		
		return FALSE;
	}
	return TRUE;
}

function user_is_admin() {
	return user_is_logged_in() && ($_SESSION["userid"] == 1);
}

