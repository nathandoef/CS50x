<?php

    // configuration
    require("../includes/config.php"); 
    
    // call created get_assets function in helpers 
    $assets = get_assets();
    
    // call created get_cash function in helpers 
    $cash = get_cash();
    
    // render portfolio and pass in assets and cash
    render("portfolio.php", ["title" => "Portfolio","assets" => $assets, 
    "cash" => $cash]);
?>
