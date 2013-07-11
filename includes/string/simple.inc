<?php

function make_it_simple($x) {
	$x = trim($x);
	$x = strtolower($x);
	return $x;
}

function make_it_txt($x) {
	$x = make_it_simple($x);
	$x = base64_encode($x);
	$x = str_replace('_', '__', $x);
	$x = str_replace('=', '_', $x);
	return $x;
}


