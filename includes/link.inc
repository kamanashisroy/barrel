<?php

function ci_link_build($data) {
	if(is_array($data)) {
		die('TODO: implement array argument in ci_link_build()');
	} else {
		return '?q='.$data;
	}
	return '';
}
