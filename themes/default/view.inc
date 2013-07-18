<?php

function theme_render_view($view) {
	$output = "<div class=\"ci_view\">";
	foreach($view as $name=>$desc) {
		$output .= "<div class=\"ci_view_item\">";
		$output .= $name . ":" . $desc['value'];
		$output .= "</div>";
	}
	$output .= "</div>";
	return $output;
}
