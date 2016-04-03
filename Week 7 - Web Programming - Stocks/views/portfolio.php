<table class="table table-striped" style="text-align:left">
    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>TOTAL</th>
        </tr>
    </thead>
    <!-- *$assets represent an array of associative arrays of each stock owned
         *asset is an associative array of each of the stocks properties  
         *(i.e asset["price"], $asset["symbol"], $asset["name"] -->
    <tbody>
       
        <?php foreach($assets as $asset): ?>
                
                
            <tr>
                <td><?= $asset["symbol"] ?></td>
                <td><?= $asset["name"] ?></td>
                <td><?= $asset["shares"] ?></td>
                <td><?= "\$" . $asset["price"] ?></td>
                <td><?= "\$" . $asset["total price"] ?></td> 
            </tr>
    
        <?php endforeach ?>
        
        <tr>
            <td colspan="4">CASH</td>
            <td><?= "\$" . $cash ?></td>
        </tr>
    </tbody>
</table>
