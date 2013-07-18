<?php

function user_play() {
	return array(
		'user_create' => 'user_play_create'
	);
}


function user_play_create($more) {
	global $project;
	db_insert($project['db'], 'user', $more);
}

