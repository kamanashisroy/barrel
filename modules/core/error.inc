<?php


function error_module_register() {
	return array(
		'error/page_not_found' => 'error_page_not_found',
	);
}

function error_page_not_found() {
	return 'We are sorry that the asked page is not found';
}
