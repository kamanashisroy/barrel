<?php

function ci_form_new($name, $action) {
	global $project;
	$f = array();
	$f{'form_name'} = $name;
	$f{'action'} = $action;
	$f{'beautiflier'} = $project['theme'];
	return $f;
}

function ci_form_build_and_output($f) {
	$output = ci_form_build($f);
	echo $output;
}

function ci_form_build($form_name, $module = NULL, $arg = NULL) {
	if($module != NULL) {
		require_once(module_get_source($module.'/'.$module.".form.inc"));
	}
	$f = call_user_func($form_name, null, $arg);
	$content = "";
	foreach($f as $key=>$val) {
		if(!is_array($val)) {
			continue;
		}
		$content .= ci_form_item_build($val, $f);
	}
	$output = "<form id=\"".$f{'form_name'}."\" name=\"".$form_name."[".$f{'form_name'}."]\" action=\"".ci_link_build($f{'action'})."\" method=\"POST\">".$content."</form>";
	$output = call_user_func('theme_'.$f{'beautiflier'}."_form_beautifier", $val, $f, $output);
	return $output;
}

function ci_form_item_build($a, $f) {
	$output = "";
	if($a['type'] == 'text' || $a['type'] == 'password' || $a['type'] == 'file') {
		$output = "<input type=\"".$a{'type'}."\" name=\"".$f['form_name']."[".$a{'name'}."]\" id=\"".$a{'name'}."\" />";
	} else if($a['type'] == 'submit') {
		$output = "<input type=\"submit\" name=\"".$f['form_name']."[".$a{'name'}."]\" id=\"".$a{'name'}."\" value=\"".$a['title']."\" ></input>";
	} else if($a['type'] == 'label') {
		$output = "</span><span class=\"list_item_value\">".$a['value']."</span>";
	}
	$output = call_user_func('theme_'.$f{'beautiflier'}."_form_item_beautifier", $a, $f, $output);
	return $output;
}

