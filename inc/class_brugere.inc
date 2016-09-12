<?php
class Bruger {
	public $id;
	public $email;
	public $loggetInd = false;
	
	function __construct(){
		if (session_id() == ""){
			session_start();
		}
		if (isset($_SESSION['loggetInd']) && $_SESSION['loggetInd'] == true) {
			$this->_initUser();
        }
    }
	
	public function Create($email,$pass){
		$mysqli = new mysqli(DBHOST,DBUSER,DBPASS,DB);
		if ($mysqli->connect_errno) {
			$_SESSION['msg'] = "Kunne ikke oprette forbindelse til databasen: " . $mysqli->connect_error;
			return false;
		}
		
		$safeEmail = $mysqli->real_escape_string($email);
		$safePass = crypt($mysqli->real_escape_string($pass));
		
		// Tjek om emailen eksisterer
		$query = "SELECT * FROM users WHERE email = '$safeEmail'";
		$result = $mysqli->query($query);
		
		// Hvis e-mailen allerede findes sendes brugeren videre med en fejlmeddelelse
			if ($result->num_rows >= 1){
			$_SESSION['msg'] = "Der eksisterer allerede en bruger med samme e-mail";
			die(header('location:index.php'));
		}
		
		// Brugeren eksisterer ikke - så den oprettes
		$query = "INSERT INTO users (email, password) VALUES ('$safeEmail', '$safePass')";
		$result = $mysqli->query($query);
		
		// Log ind
		$query = "SELECT * FROM users WHERE email = '$safeEmail'";
		$result = $mysqli->query($query);
		$row = $result->fetch_array();
		$this->id = $row['id'];
		$this->email = $row['email'];
		$this->loggetInd = true;
       
		// Sæt sessions
        $this->_setSession();
		
		return true;
	}
	
	public function Login($email,$pass){
		$mysqli = new mysqli(DBHOST,DBUSER,DBPASS,DB);
		if ($mysqli->connect_errno) {
			$_SESSION['msg'] = "Kunne ikke oprette forbindelse til databasen: " . $mysqli->connect_error;
			die(header('location:index.php'));
		}
		
		$safeEmail = $mysqli->real_escape_string($email);
		$safePass = $mysqli->real_escape_string($pass);
		
		// Tjek om emailen eksisterer
		$query = "SELECT * FROM users WHERE email = '$safeEmail'";
		$result = $mysqli->query($query);
		if ($result->num_rows == 0){
			// Emailen findes ikke
			$_SESSION['msg'] = "Der blev ikke fundet en bruger med den indtastede e-mail";
			die(header('location:index.php'));
		}
		$row = $result->fetch_assoc();
		if (crypt($safePass,$row['password']) != $row['password']){
			$_SESSION['msg'] = "Adgangskoden matcher ikke";
			die(header('location:index.php'));	
		}
		
		
		// Logger ind
		$this->id = $row['id'];
		$this->email = $row['email'];
		$this->loggetInd = true;
		
		// Sæt sessions
        $this->_setSession();
		
		
	}
	
	
	public function logud() {
        $this->loggetInd = false;
		if (session_id() == '') {
			session_start();
		}
		$_SESSION['loggetInd'] = false;
		foreach ($_SESSION as $key => $value) {
			$_SESSION[$key] = '';
			unset($_SESSION[$key]);
		}
		$_SESSION = array();
		if (ini_get("session.use_cookies")) {
		    $cookieParameters = session_get_cookie_params();
		    setcookie(session_name(), '', time() - 28800, $cookieParameters['path'],$cookieParameters['domain'], $cookieParameters['secure'],$cookieParameters['httponly']);
		} 
        session_destroy();
    }

	
	private function _initUser() {
        if (session_id() == '') {
            session_start();
		}
        $this->id = $_SESSION['id'];
        $this->email = $_SESSION['email'];
        $this->loggetInd = $_SESSION['loggetInd'];
    } 
    
    
	private function _setSession() {
        if (session_id() == '') {
            session_start();
		}
        $_SESSION['id'] = $this->id;
        $_SESSION['email'] = $this->email;
        $_SESSION['loggetInd'] = $this->loggetInd;
    }
}	
?>