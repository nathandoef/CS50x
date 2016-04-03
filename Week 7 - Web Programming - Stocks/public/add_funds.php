<?php
    
    // configuration
    require("../includes/config.php");
    
    // if the user has not submitted a request 
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("add_funds_view.php",["title" => "Add Funds"]);
    }
    
    // if the user has submitted a blank form 
    if (empty($_POST["amount"]))
    {
        apologize("You must specify an amount.");
    }
    
    // make sure the user has enter a currency value 
    // *** regex from Tim Pietzcker on stackoverflow.com ***
    if (!preg_match("/^\d{1,3}(?:,?\d{3})*(?:\.\d{2})?\$/", $_POST["amount"]))
    {
        apologize("Invalid amount");
    }
    
    // add cash into the users account 
    CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", 
    str_replace(",","",$_POST["amount"]), $_SESSION["id"]);
    
    //redirect to portfolio
    redirect("/");
?>