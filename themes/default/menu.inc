<?php

function theme_default_menu_beautifier_helper_for_category($cat, $menu) {
	$output = "<div class=\"ci_menu\" align=\"left\">";
	if($cat != NULL) {
		$output .= "<div>".$cat."</div>";
	}
	foreach($menu as $key=>$value) {
		if(ci_menu_get_category($value) != $cat || !ci_page_access($value, 'null', NULL) || (isset($value['type']) && $value['type'] == 'hidden')) {
			continue;
		}
		$output .= "<a href=\"?q=".$key."\">".ci_menu_get_title($value)."</a>";
		//$output .= "<br/>";
	}
	$output .= "</div>";
	return $output;
}

function theme_default_menu_beautifier($menu) {

	$categories = array();

	foreach($menu as $key=>$value) {
		$cat = ci_menu_get_category($value);
		if($cat === NULL || !ci_page_access($value, 'null', NULL) || (isset($value['type']) && $value['type'] == 'hidden')) {
			continue;
		}
		$categories[] = $cat;
	}

	$output = "";
	foreach($categories as $index=>$cat) {
		$output .= theme_default_menu_beautifier_helper_for_category($cat, $menu);
	}
	return $output;
}

