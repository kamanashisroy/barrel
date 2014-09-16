<?php

function theme_imagefull_menu_beautifier_helper_for_category($current_page, $cat, $menu) {
	$output = "<ul class=\"barrel_menu\" align=\"left\" onClick=\"unwrap(this);\">";
	if($cat != NULL) {
		$output .= "<a href=\"javascript:noaction()\">".$cat."</a>";
	}
	foreach($menu as $key=>$value) {
		if(barrel_menu_get_category($value) != $cat || !barrel_page_access($value, 'null', NULL) || (isset($value['type']) && $value['type'] == 'hidden')) {
			continue;
		}
		if($key == $current_page)
			$output .= "<li class=\"barrel_current_page\">";
		else
			$output .= "<li>";
		$output .= "<a href=\"?q=".$key."\">".barrel_menu_get_title($value)."</a></li>";
	}
	$output .= "</ul>";
	return $output;
}

function theme_imagefull_menu_beautifier($current_page, $menu) {

	$categories = array();

	foreach($menu as $key=>$value) {
		$cat = barrel_menu_get_category($value);
		if($cat === NULL || !barrel_page_access($value, 'null', NULL) || (isset($value['type']) && $value['type'] == 'hidden') || in_array($cat, $categories)) {
			continue;
		}
		$categories[] = $cat;
	}

	$output = "<div id=\"barrel_menu_tree\">";
	foreach($categories as $index=>$cat) {
		$output .= theme_imagefull_menu_beautifier_helper_for_category($current_page, $cat, $menu);
	}
	$output .= "</div>";
	return $output;
}

