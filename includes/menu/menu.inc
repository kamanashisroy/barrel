<?php

function ci_menu_get_title($menu) {
	return is_array($menu)?(isset($menu['title'])?$menu['title']:ci_menu_get_cb($menu)):$menu;
}

function ci_menu_get_cb($menu) {
	return is_array($menu)?$menu['cb']:$menu;
}

function ci_menu_get_category($menu) {
	return is_array($menu)?(isset($menu['category'])?$menu['category']:NULL):NULL;
}
