<?php
	require_once('inc/functions.inc');
	$bruger = new Bruger;
	$bruger->logud();
	header('location: index.php');
?>