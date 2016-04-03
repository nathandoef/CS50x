<?php 

//configuration 

require("../includes/config.php");

// if user reached page via GET (as by clicking a link or via redirect)
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
    // render register form 
    render("register_form.php", ["title" => "Register"]);
}

// else if user reached page via POST (as by submitting a form via POST)
else if ($_SERVER["REQUEST_METHOD"] == "POST")
{
    // make sure username field is filled 
    if ( empty($_POST["username"]) )
    {
        apologize("You must provide a username to register.");    
    }
    
    // make sure password field is filled 
    else if ( empty($_POST["password"]) )
    {
        apologize("You must provide a password to register.");  
    }
     
    // make sure passwords match 
    else if ( $_POST["password"] != $_POST["confirmation"] )
    {
        apologize("Your passwords do not match.");
    }
    
    // attempt to add a new user 
    $query_result = CS50::query("INSERT IGNORE INTO users (username, hash, cash) 
    VALUES(?, ?, 10000.00)", $_POST["username"], password_hash($_POST["password"], 
    PASSWORD_DEFAULT));
    
    // if the query return 0, the username exists 
    if ($query_result === false)
    {
        apologize("That username has already been taken.");
    }
    
    // if query has succeeded determine which row the user was added to 
    $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
    
    // since rows is an associative array, select the first row and "id" index
    $id = $rows[0]["id"];
    
    // store id in the superglobal variable $_SESSION 
    $_SESSION["id"] = $id;
    
    // redirect user to portfolio 
    redirect("/");
}

?>