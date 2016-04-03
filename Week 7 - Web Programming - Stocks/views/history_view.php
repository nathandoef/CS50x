<table class="table table-striped" style="text-align:left">
    <thead>
        <tr>
            <th>Transaction Type</th>
            <th>Date/Time</th>
            <th>Symbol</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    </thead>
    
    <tbody>
        
        <?php foreach($history as $event): ?>
        
            <tr>
                <td><?= $event["transaction"] ?></td>
                <td><?= $event["date_time"] ?></td>
                <td><?= $event["symbol"] ?></td>
                <td><?= $event["shares"] ?></td>
                <td><?= "\$" . $event["price"] ?></td>
            </tr>
        
        <?php endforeach ?>
        
    </tbody>
</table>
   