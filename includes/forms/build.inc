<?php

function barrel_form_new($name, $action) {
	global $project;
	$f = array();
	$f{'form_name'} = $name;
	$f{'action'} = $action;
	$f{'beautiflier'} = $project['theme'];
	return $f;
}

function barrel_form_build_and_output($f) {
	$output = barrel_form_build($f);
	echo $output;
}

function barrel_form_build($form_name, $module = NULL, $arg = NULL) {
	if($module != NULL) {
		require_once(module_get_source($module.'/'.$module.".form.inc"));
	}
	$f = call_user_func($form_name, null, $arg);
	$content = "";
	foreach($f as $key=>$val) {
		if(!is_array($val)) {
			continue;
		}
		$content .= barrel_form_item_build($val, $f);
	}
	$output = "<form id=\"".$f{'form_name'}."\" name=\"".$form_name."[".$f{'form_name'}."]\" action=\"".barrel_link_build($f{'action'})."\" method=\"POST\"  enctype=\"multipart/form-data\">".$content."</form>";
	$output = call_user_func('theme_'.$f{'beautiflier'}."_form_beautifier", $val, $f, $output);
	return $output;
}

function barrel_form_item_build($a, $f) {
	$output = "";
	if($a['type'] == 'text' || $a['type'] == 'password') {
		$output = "<input type=\"".$a{'type'}."\" name=\"".$f['form_name']."[".$a{'name'}."]\" id=\"".$a{'name'}."\" ";
		if(isset($a['value']))
			$output .= " value=\"".$a['value']."\"";
		$output .= " />";
	} else if($a['type'] == 'submit' || $a['type'] == 'disabled' || $a['type'] == 'reset') {
		$output = "<input type=\"".$a['type']."\" name=\"".$f['form_name']."[".$a{'name'}."]\" id=\"".$a{'name'}."\" value=\"".(isset($a['value'])?$a['value']:$a['title'])."\" ></input>";
	} else if($a['type'] == 'label') {
		$output = "</span><span class=\"list_item_value\">".$a['value']."</span>";
	} else if($a['type'] == 'file') {
		$output = "<input type=\"".$a['type']."\" name=\"".$a{'name'}."\" id=\"".$a{'name'}."\"/>";
	}
	$output = call_user_func('theme_'.$f{'beautiflier'}."_form_item_beautifier", $a, $f, $output);
	return $output;
}

