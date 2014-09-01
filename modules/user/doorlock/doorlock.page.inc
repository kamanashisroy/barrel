<?php

function doorlock_page_view($arg) {
	$index = 0;
	sscanf($arg, "doorlock/view/%d", $index);
	$data = db_get('doorlock', 'doorlock', $index);
	//return 'name:'.$data['name'].'index:'.$index;
	$view = array(
		'id' => array(
			'value' => $index,
		),
		'name' => array(
			'value' => $data['name'],
		),
	);
	return theme_render_view($view);
}
