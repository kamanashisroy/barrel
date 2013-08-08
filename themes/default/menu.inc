<?php

function theme_default_menu_beautifier($menu) {
	$output = "<div class=\"ci_menu\" align=\"left\">";
	foreach($menu as $key=>$value) {
		if(!ci_page_access($value, 'null', NULL) || (isset($value['type']) && $value['type'] == 'hidden')) {
			continue;
		}
		$output .= "<a href=\"?q=".$key."\">".ci_menu_get_title($value)."</a>";
		//$output .= "<br/>";
	}
	$output .= "</div>";
	return $output;
}

