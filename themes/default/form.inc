<?php

function theme_default_form_beautifier($a, $f, $rendered_item) {
	$output = "<div class=\"ci_form\" align=\"right\">".$rendered_item."</div>";
	return $output;
}

function theme_default_form_item_beautifier($a, $f, $rendered_item) {
	$output = "<div class=\"ci_form_input_div\" align=\"right\">";
	if($a['type'] == 'submit') {
		$output .= $rendered_item;
	} else {
		$output .= "<label>
<span class=\"ci_form_input_label\">".$a{'title'}."</span>
".$rendered_item."<br/>";
		if(isset($a{'tips'})) {
			$output .= "<span class=\"ci_form_input_tips\">".$a{'tips'}."</span>";
		}
		$output .= "</label>";
	}
	$output .= "</div>";
	return $output;
}

