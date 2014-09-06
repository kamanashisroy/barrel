<?php

function barrel_link_build($data) {
	if(is_array($data)) {
		die('TODO: implement array argument in barrel_link_build()');
	} else {
		return '?q='.$data;
	}
	return '';
}
