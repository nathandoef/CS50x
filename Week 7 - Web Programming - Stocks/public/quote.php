<?php

//configuration
require("../includes/config.php");

// if user reached page via GET (clicking a link or was redirected)
if ( $_SERVER["REQUEST_METHOD"] == "GET" )
{
    // render the quote form 
    render("quote_form.php", ["title" => "Quote Form"]);
}

// else if the user reached the page via POST (by submitting a quote form via post)
else if ( $_SERVER["REQUEST_METHOD"] == "POST" )
{
    // lookup the symbol that was typed 
    $stock = lookup($_POST["symbol"]);

    // if lookup does not succeed, the symbol does not exist 
    if ( $stock == false )
    {
        apologize("Symbol not found.");
    }

    // if the symbol is valid and lookup was successful 
    else 
    {
        //format the stock price 
        $stock_price = number_format($stock["price"], 2, ".", ",");
        
        // render the quote results page with appropriate results 
        render("quote_results.php", ["title" => "Quote Results", "stock" => $stock,
        "stock_price" => $stock_price]);
    }
}

?>