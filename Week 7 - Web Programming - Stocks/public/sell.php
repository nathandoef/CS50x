<?php 
    
    // configuration
    require("../includes/config.php");
    
    // get users assets 
    $assets = get_assets();

    // if the user has not yet made a sell request
    if($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render the sell form
        render("sell_form_blank.php", ["title" => "Sell Form", "assets" => $assets]);
    }
    
    // if a requested has been submitted
    elseif ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // if the user has not selected a stock  
        if (empty($_POST["symbol"]))
        {
            apologize("You must select a stock symbol.");
        }
        
        // make sure the user has entered a non-negative integer 
        if (!preg_match("/^\d+$/", $_POST["shares"]))
        {
            apologize("Invalid number of shares.");
        }
        
        // find out how many shares the user has 
        $shares = CS50::query("SELECT shares FROM portfolios WHERE 
        user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        
        // make sure the user has the number of shares requested 
        if ($shares[0]["shares"] < $_POST["shares"])
        {
            apologize("You do not own that many shares.");
        }
        
        // look up the price of the stock 
        $stock = lookup($_POST["symbol"]);
        
        // add the value of all the shares to the users account 
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", 
        ($_POST["shares"] * $stock["price"]), $_SESSION["id"]);
        
        // update the history table *** time zone is set in config***
        CS50::query("INSERT INTO history (user_id, transaction, date_time, symbol, shares, price)
        VALUES(?, 'SELL', DATE_ADD(NOW(), INTERVAL ? SECOND), ?, ?, ?)", $_SESSION["id"], date("Z"),
        strtoupper($_POST["symbol"]), $_POST["shares"], ($_POST["shares"] * $stock["price"]));
    
        // if the user has the same amount of shares delete the database entry
        if ($_POST["shares"] == $shares[0]["shares"])
        {
             // delete the stock from the users portfolio 
            CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?",
            $_SESSION["id"], $_POST["symbol"]);
        }
        
        //else, update the portfolios table 
        else
        {
            CS50::query("UPDATE portfolios SET shares = shares - ? WHERE user_id = ?
            AND symbol = ?", $_POST["shares"], $_SESSION["id"], strtoupper($_POST["symbol"]));
        }
        
        // redirect to index
        redirect("/");
    }
?>
    