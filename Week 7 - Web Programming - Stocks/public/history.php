<?php

    // configuration 
    require("../includes/config.php");
    
    
    /* perform a query on the history table for all fields and store in an array
    of associative arrays*/
    $history = CS50::query("SELECT * FROM history WHERE user_id = ?", $_SESSION["id"]);
    
    // make sure the user has made at least one transaction 
    if (empty($history[0]))
    {
        render("history_blank.php", ["title" => "Transaction History"]);
    }
    
    // format time and price
    foreach($history as $event=>$value)
    {
        $history[$event]["price"] = number_format($value["price"], 2, ".", ",");
        $history[$event]["date_time"] = date("M j Y g:ia ", (strtotime($value["date_time"])));
    }

    // the query has succeeded and a transaction history can be displayed 
    render("history_view.php", ["title" => "Transaction History", "history" => $history]);
?>