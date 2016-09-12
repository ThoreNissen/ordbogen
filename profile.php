<?php
require_once('inc/functions.inc');
$bruger = new Bruger;
if (!$bruger->loggetInd) {
	die(header('location: index.php'));
}
?><!DOCTYPE html>
<head>
<title>Hej <?=$bruger->email; ?></title>
<link rel="stylesheet" href="css/styles.css" />
</head>
<body>
	<p>
		Hej <?php echo $bruger->email;?>. Dit unikke id er <?php echo $bruger->id; ?>.<br><br><a href="logud.php">Klik her for at logge ud</a>
	</p>
</body> 
</html> 