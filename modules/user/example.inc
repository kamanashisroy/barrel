<?php

function example_module_register() {
	return array(
		'example/hello' => 'example_page_new',
	);
}

function example_page_new() {
	return 'Hello World';
}
