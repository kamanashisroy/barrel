<?php

// chown www-data:www-data -R .data
define('FILEDB_HOME', '.data');

function filedb_writefile($file, $x) {
	if(!($fd = @fopen($file, 'w'))) {
		return FALSE;
	}
	foreach($x as $key=>$val) {
		@fputs($fd, $key.' = '.$val."\r\n");
	}
	@fclose($fd);
	return TRUE;
}

function filedb_readfile($file) {
	if(($fd = @fopen($file, 'r')) == FALSE) {
		return FALSE;
	}
	$x = array();
	while(($str = @fgets($fd))) {
		$i = strpos($str, '=');
		if($i == 0 || $i == FALSE) {
			continue;
		}
		$key = substr($str, 0, $i);
		$key = trim($key);
		$val = substr($str, $i+1);
		$x[$key] = trim($val);
	}
	@fclose($fd);
	return $x;
}

function filedb_create_or_prepare_table($db, $tbl) {
	if(!@file_exists(FILEDB_HOME) && !@mkdir('.data', 0777)) {
		return;
	}
	$dbdir = FILEDB_HOME.'/'.make_it_txt($db);
	if(!@file_exists($dbdir) && !@mkdir($dbdir, 0777)) {
		return;
	}
	$tbldir = $dbdir.'/'.make_it_txt($tbl);
	if(!@file_exists($tbldir) && !@mkdir($tbldir, 0777)) {
		return;
	}
	return $tbldir;
}

function filedb_database_insert($db, $tbl, $more) {
	// mkdir .data
	// mkdir .data $db
	// mkdir .data $db/$tbl
	// echo $content > .data $db/$tbl/$index.data
	
	$tbldir = filedb_create_or_prepare_table($db, $tbl);
	if(!$tbldir) {
		error_report("Could not create table dir, please check file permission\n");
		return FALSE;
	}
	$index = 1;
	$infofile = $tbldir."/.info";
	$info = filedb_readfile($infofile);
	if(!isset($info) || !isset($info['index'])) {
		// new table
		$info = array('index' => $index);
	} else {
		$info['index'] = intval($info['index']);
		$info['index']++;
		$index = $info['index'];
	}
	// TODO write a function that locks and updates index file ..
	if(!filedb_writefile($infofile, $info) || !filedb_writefile($tbldir."/".$index, $more)) {
		return FALSE;
	}
	return $index;
}


function filedb_database_update($db, $tbl, $index, $more) {
	// mkdir .data
	// mkdir .data $db
	// mkdir .data $db/$tbl
	// echo $content > .data $db/$tbl/$index.data
	
	$tbldir = filedb_create_or_prepare_table($db, $tbl);
	if(!$tbldir) {
		error_report("Could not create table dir, please check file permission\n");
		return FALSE;
	}
	// TODO write a function that locks and updates index file ..
	if(!filedb_writefile($tbldir."/".$index, $more)) {
		return FALSE;
	}
	return $index;
}


function filedb_database_get($db, $tbl, $index) {
	$dbdir = FILEDB_HOME.'/'.make_it_txt($db);
	$tbldir = $dbdir.'/'.make_it_txt($tbl);
	$output = filedb_readfile($tbldir."/".$index);
	return $output;
}

/*function filedb_database_get_where($db, $tbl, $more) {
	$dbdir = FILEDB_HOME.'/'.make_it_txt($db);
	$tbldir = $dbdir.'/'.make_it_txt($tbl);
	$pattern = "";
	foreach($more as $key=>$val) {
		$pattern = "/^" . $key . " = " . $val . ".$/";
	}
	//echo "pattern:" . $pattern . "\n";
	$index = 1;
	$infofile = $tbldir."/.info";
	$info = filedb_readfile($infofile);
	// TODO use filedb_database_visit to get one.
	if(!isset($info) || !isset($info['index'])) {
	} else {
		$info['index'] = intval($info['index']);
		$index = $info['index'];
	}
	$i = 0;
	for($i = 1; $i <= $index; $i++) {
		$result = @preg_grep($pattern, file($tbldir."/".$i));
		if(!empty($result));
			return $i;
	}
	return -1;
}*/

function filedb_database_get_where_helper($referer, $content, $index) {
	$constraint = $referer[0]['where'];
	$matches = true;
	foreach($constraint as $key=>$val) {
		if(!isset($content[$key]) || $content[$key] != $val)	{
			$matches = false;		
		}
	}
	if($matches) {
		$referer[0]['index'] = $index;	
	}
}

function filedb_database_get_where($db, $tbl, $more) {
	$result = array();
	$result['where'] = $more;
	$result['index'] = -1;
	$refer = array(&$result);
	filedb_database_visit($db, $tbl, 'filedb_database_get_where_helper', $refer);	
	return $result['index'];
}


function filedb_database_visit($db, $tbl, $visitor, &$visitor_data) {
	$dbdir = FILEDB_HOME.'/'.make_it_txt($db);
	$tbldir = $dbdir.'/'.make_it_txt($tbl);
	$files = @scandir($tbldir);
	$i = 0;
	$count = 0;
	while(true) {
		$i++;
		if(!isset($files[$i]))
			break;
		if(!is_numeric($files[$i]))
			continue;
		$count++;
		$index = $files[$i];
		$content = filedb_readfile($tbldir . '/' . $index);
		if(call_user_func($visitor, $visitor_data, $content, $index)) {
			break;
		}
	}
	return $count;
}

function filedb_database_delete($db, $tbl, $index) {
	// TODO fill me 
}

function filedb_database_register() {
	return array(
		'insert' => 'filedb_database_insert',
		'delete' => 'filedb_database_delete',
		'get' => 'filedb_database_get',
		'update' => 'filedb_database_update',
		'visit' => 'filedb_database_visit',
		'get_where' => 'filedb_database_get_where',
	);
}


