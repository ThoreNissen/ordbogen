<?php
require_once('inc/functions.inc');

// Sender brugeren videre til profile.php hvis de er logget ind
$bruger = new Bruger;
if ($bruger->loggetInd) {
	die(header('location: profile.php'));
}
?><!DOCTYPE html>
<head>
	<meta charset='utf-8'>
	<title>Kode test</title>
	<link rel="stylesheet" href="css/styles.css" />
</head>
<body>
	
<form action="logind.php" method="POST" name="form">
	<p style="margin:0;margin-bottom:15px;">
		<?php
		// fejlmeddelelse
		if ($_SESSION['msg']){
			echo $_SESSION['msg'];
			unset($_SESSION['msg']);
		} 
		?>
	</p>
	<input type="text" placeholder="E-mail" name="email" />
	<input type="password" placeholder="Adgangskode" name="adgangskode" />
	<input type="submit" name="create" value="Opret bruger" />
	<input type="submit" name="login" value="Log ind" />
</form>
</body> 
</html> 