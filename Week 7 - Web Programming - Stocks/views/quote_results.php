<!-- $stock was sent in as an associative array via render --->
<div>
    <!-- Make sure stock price is formatted corrently --->
    <?= "A share of " . $stock["name"] . "(" . $stock["symbol"] . ")" . 
    " costs " . "<strong>\${$stock_price}</strong>". "."; ?>
</div>