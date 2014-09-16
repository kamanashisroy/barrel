<?php

function theme_render_view($view) {
	$output = "<div class=\"barrel_view\">";
	foreach($view as $name=>$desc) {
		$output .= "<div class=\"barrel_view_item\">";
		$output .= $name . ":" . $desc['value'];
		$output .= "</div>";
	}
	$output .= "</div>";
	return $output;
}
