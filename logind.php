<?php
require_once('inc/functions.inc');

if ($_POST['create'] || $_POST['login']){
	// Tjekker om email feltet er udfyldt
	if(!$_POST['email']){
		$_SESSION['msg'] = "Du skal skrive din email i feltet";
		die(header('location: index.php'));	
	}elseif(!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)){
		// Tjekker om emailen er valid
		$_SESSION['msg'] = "Din email er ikke en rigtig email, prøv igen";
		die(header('location: index.php'));	
	
	}else{
		// Hvis email feltet er udfyldt med en valid email gemmes den som en variabel
		$email = $_POST['email'];
	}
	
	// Tjekker om adgangskode feltet er udfyldt		
	if (!$_POST['adgangskode']){
		$_SESSION['msg'] = "Angiv venligst adgangskode";
		die(header('location: index.php'));
		
	}else{
		// Gemmer adgangskode som variabel
		$adgangskode = $_POST['adgangskode'];
	}

	// Kalder de to forskellige klasser alt efter hvilken knap der er blevet trykket på
	$bruger = new Bruger;
	if($_POST['login']){
		$bruger->Login($email,$adgangskode);
	}elseif($_POST['create']){	
		$bruger->Create($email,$adgangskode);
	}
	header('location:profile.php');
}else{
	header('location: index.php');
}	
	
?>