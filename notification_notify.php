<?php
$GLOBALS['DATAFILE']=__FILE__.".dat";


if( isset($_GET["mode"]) ){
	if( htmlspecialchars($_GET["mode"]) == "set0" ){ set_status0(); }
	if( htmlspecialchars($_GET["mode"]) == "set1" ){ set_status1(); }
}

print( get_status() );

exit(0);






function get_status(){
	if(!file_exists($GLOBALS['DATAFILE'])){
		set_status0();
		return( 0 );
	}else{
		$fp = fopen($GLOBALS['DATAFILE'] , 'r');
		rewind($fp);
		$val = fread( $fp , 1 );
		fclose($fp);
		return( $val );
	}
	return( 0 );
}

function set_status0(){
	if(!file_exists($GLOBALS['DATAFILE'])){
		touch($GLOBALS['DATAFILE']);
	}
	$fp = fopen($GLOBALS['DATAFILE'] , 'w');
	rewind( $fp );
	fwrite( $fp , '0' , 1 );
	fclose( $fp );
}

function set_status1(){
	if(!file_exists($GLOBALS['DATAFILE'])){
		touch($GLOBALS['DATAFILE']);
	}
	$fp = fopen($GLOBALS['DATAFILE'] , 'w');
	rewind( $fp );
	fwrite( $fp , '1' , 1 );
	fclose( $fp );
}


?>
