<?php

    // configuration
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render password change form 
        render("passwordchange_view.php", ["title"=>"Password Change Form"]);
    }
    
    // make sure the old password field is filled out 
    if (empty($_POST["old_pass"]))
    {
        apologize("You must enter your old password.");
    }
    
    // make sure the new password field is filled out 
    if (empty($_POST["new_pass"]))
    {
        apologize("You must enter your new password.");
    }
    
    // make sure the new password confirm field is filled out 
    if (empty($_POST["new_pass_conf"]))
    {
        apologize("You must confirm your new password.");
    }
    
    // make sure passwords match
    if ($_POST["new_pass"] !== $_POST["new_pass_conf"])
    {
        apologize("Your new passwords do not match.");
    }

    // find out the user's old password
    $old = CS50::query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);

    // make sure the old password matches current password 
    if(password_verify($_POST["old_pass"], $old[0]["hash"]) === false)
    {
        apologize("You entered an incorrect old password.");
    }
    
    // update the users passowrd 
    $change = CS50::query("UPDATE users SET hash = ? WHERE id = ?", 
    password_hash($_POST["new_pass"], PASSWORD_DEFAULT), $_SESSION["id"]);
    
    // make sure the password change was successful
    if ($change === false)
    {
        apologize("Your password could not be changed.");
    }
    
    //redirect to portfolio
    redirect("/");
?>