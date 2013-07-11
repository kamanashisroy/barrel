<?php

function ci_form_new($name, $action) {
	$f = array();
	$f{'name'} = $name;
	$f{'action'} = $action;
	$f{'beautiflier'} = 'ci_default';
	return $f;
}
function ci_form_build_and_output($f) {
	$output = ci_form_build($f);
	echo $output;
}

function ci_form_build($f) {
	$i = 0;	
	$content = "";
	for($i = 0;$i < 100; $i++) {
		if(!isset($f[$i])) {
			break;
		}
		$content .= ci_form_item_build($f[$i], $f);
	}
	$output = "<form id=".$f{'name'}." name=".$f{'name'}." method=".$f{'name'}." action=".$f{'name'}.">".$content."</form>";
	return $output;
}

function ci_form_item_build($a, $f) {
	$output = "<input type=".$a{'type'}." name=".$a{'name'}." id=".$a{'name'}." />";
	$output = call_user_func($f{'beautiflier'}."_form_item_beautifier", $a, $f, $output);
	return $output;
}

function ci_default_form_item_beautifier($a, $f, $rendered_item) {
	$output = "<div align=\"left\">
<label>
<p align=\"center\"><span class=\"ci_form_input_label\">".$a{'title'}."</span>
".$rendered_item."
</p>
</label>
</div>
";
	return $output;
}

