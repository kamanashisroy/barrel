<?php

function ci_form_new($name, $action) {
	global $project;
	$f = array();
	$f{'name'} = $name;
	$f{'action'} = $action;
	$f{'beautiflier'} = $project['theme'];
	return $f;
}

function ci_form_build_and_output($f) {
	$output = ci_form_build($f);
	echo $output;
}

function ci_form_build($form_name) {
	$f = call_user_func($form_name);
	$content = "";
	foreach($f as $key=>$val) {
		if(!is_array($val)) {
			continue;
		}
		$content .= ci_form_item_build($val, $f);
	}
	$output = "<form id=\"".$f{'name'}."\" name=\"".$f{'name'}."\" method=\"".$f{'name'}."\" action=\"?q=".$f{'action'}."\">".$content."</form>";
	$output = call_user_func('theme_'.$f{'beautiflier'}."_form_beautifier", $val, $f, $output);
	return $output;
}

function ci_form_item_build($a, $f) {
	$output = "";
	if($a['type'] == 'text' || $a['type'] == 'password') {
		$output = "<input type=\"".$a{'type'}."\" name=\"".$a{'name'}."\" id=\"".$a{'name'}."\" />";
	} else if($a['type'] == 'submit') {
		$output = "<input type=\"submit\" name=\"".$a{'name'}."\" id=\"".$a{'name'}."\" value=\"".$a['title']."\" ></input>";
	}
	$output = call_user_func('theme_'.$f{'beautiflier'}."_form_item_beautifier", $a, $f, $output);
	return $output;
}

