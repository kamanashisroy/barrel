<?php


function play_module_register() {
	return array(
		'play/commands' => 'play_commands_page',
	);
}

function play_commands_page() {
	return 'Executes commands';
}

function play_command_show_usage() {
	echo "Please type a command, (q to quit)\n";
}

$playtool = array();
$playtool['cmds'] = array();
function play_command_load_commands() {
	global $playtool;
	$x = module_all_call_hook("_play");
	$playtool['cmds'] = array_merge((array)$playtool['cmds'], (array)$x);
}

function play_string_to_assoc_array($artoks) {
	$i = 0;
	$ar = array();
	$key = NULL;
	$x = $artoks[0];
	assert($x == '(');
	$keyval = FALSE;
	for($i = 1; isset($artoks[$i]); $i++) {
		$x = trim($artoks[$i]);
		if($x == ')') {
			break;
		}
		if($x == '=>') {
			$keyval = TRUE;
			assert($key != NULL);
			continue;
		}
		if($key == NULL) {
			$key = $x;
			continue;
		}
		$val = $x;
		if($keyval) {
			$ar[$key] = $val;
			$keyval = FALSE;
		} else {
			$ar[] = $key;
			$ar[] = $val;
		}
		$key = NULL;
	}
	if($key != NULL) {
		$ar[] = $key;
	}
	assert($x == ')');
	return $ar;
}

function play_command_execute($cmd) {
	global $playtool;
	$exc = strtok($cmd, " \t\n");
	$args = array();
	$x = TRUE;
	$artoks = NULL;
	//echo "You provided [".$cmd."]\n";
	while(($x = strtok(" \t\n")) !== FALSE) {
		$x = trim($x);
		//echo "token:".$x."\n";
		if($x == '(' && $artoks == NULL) {
			// then it is an array
			$artoks = array();
			$artoks[] = '(';
			//echo "You provided an array in the argument.\n";
		} else if ($x == ')' && $artoks != NULL) {
			$artoks[] = ")";
			$args[] = play_string_to_assoc_array($artoks);
			$artoks = NULL;
		} else if($artoks == NULL){
			$args[] = $x;
		} else {
			$artoks[] = $x;
		}
	}
	//print_r($args);
	if(!isset($playtool['cmds'][$exc])) {
		echo "Command not found\n";
		return;
	}
	$cb = $playtool['cmds'][$exc];
	if(is_callable($cb)) {
		$ret = call_user_func_array($cb, $args);
		print_r($ret);
	} else {
		echo "Command is not executable\n";
	}
}

function play_command() {
	play_command_load_commands();
	play_command_show_usage();
	while(true) {
		$cmd = fgets(STDIN);
		if($cmd == null) {
			// stdin closed
			return;
		}
		$cmd = rtrim($cmd);
		if($cmd == 'q') {
			return;
		}
		play_command_execute($cmd);
	}
}

function play_command_show_full_help() {
	global $playtool;
	foreach($playtool['cmds'] as $c=>$cb) {
		echo $c." => ".$cb."\n";
	}
}

function play_play() {
	return array(
		'help' => 'play_command_show_full_help'
	);
}

