<?php
    
    // configurations 
    require("../includes/config.php");
    
    // if the user has not submitted a buy request
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render the buy form 
        render("buy_form.php",["title" => "Buy Form"]);
    }
    
    // if the user has submitted a buy request 
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // if the user does not specify a stock
        if (empty($_POST["symbol"]))
        {
            apologize("You must specify a stock to buy.");
        }
        
        // if the user does not enter the number of shares 
        if (empty($_POST["shares"]))
        {
            apologize("You must specify a number of shares.");
        }
        
        // if the number of shares is a non-negative integer 
        if (!preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("Invalid number of shares");
        }

        // make sure symbol is uppercase 
        $symbol = strtoupper($_POST["symbol"]);
        
        // make sure that the stock symbol is valid 
        $stock = lookup($_POST["symbol"]);
        
        // if the symbol cannot be found 
        if ($stock === "false")
        {
            apologize("Symbol not found.");
        }
        
        // get the users cash before transaction 
        $cash_before = get_cash();
        
        // since get_cash returns a formatted number, remove commas
        $cash_before = str_replace(",", "", $cash_before);
    
        // make sure the user has enough money to buy the stock 
        if (($stock["price"]*$_POST["shares"]) > $cash_before)
        {
            apologize("Insufficient funds.");
        }
        
        // update the number of stocks 
        CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?)
        ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",
        $_SESSION["id"], $symbol, $_POST["shares"]);
        
        // update the users cash 
        CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?",
        ($stock["price"] * $_POST["shares"]), $_SESSION["id"]);
        
        // update the history table * time zone is set in config *
        CS50::query("INSERT INTO history (user_id, transaction, date_time, symbol, shares, price)
        VALUES(?, 'BUY', DATE_ADD(NOW(), INTERVAL ? SECOND), ?, ?, ?)", $_SESSION["id"], date("Z"), $symbol,
        $_POST["shares"], ($stock["price"] * $_POST["shares"]));
       
        // update the users total cash 
        redirect("/");
    }

?>