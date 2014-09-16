<?php

function theme_imagefull_form_beautifier($a, $f, $rendered_item) {
	$output = "<div class=\"barrel_form\" align=\"right\">".$rendered_item."</div>";
	return $output;
}

function theme_imagefull_form_item_beautifier($a, $f, $rendered_item) {
	$output = "<div class=\"barrel_form_input_div\" align=\"right\">";
	if($a['type'] == 'submit' || $a['type'] == 'reset') {
		$output .= $rendered_item;
	} else {
		$output .= "<label>
<span class=\"barrel_form_input_label\">".$a{'title'}."</span>
".$rendered_item."<br/>";
		if(isset($a{'tips'})) {
			$output .= "<span class=\"barrel_form_input_tips\">".$a{'tips'}."</span>";
		}
		$output .= "</label>";
	}
	$output .= "</div>";
	return $output;
}

