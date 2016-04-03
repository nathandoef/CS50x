<?php

    /**
     * helpers.php
     *
     * Computer Science 50
     * Problem Set 7
     *
     * Helper functions.
     */

    require_once("config.php");

    /**
     * Apologizes to user with message.
     */
    function apologize($message)
    {
        render("apology.php", ["message" => $message]);
    }

    /**
     * Facilitates debugging by dumping contents of argument(s)
     * to browser.
     */
    function dump()
    {
        $arguments = func_get_args();
        require("../views/dump.php");
        exit;
    }

    /**
     * Logs out current user, if any.  Based on Example #1 at
     * http://us.php.net/manual/en/function.session-destroy.php.
     */
    function logout()
    {
        // unset any session variables
        $_SESSION = [];

        // expire cookie
        if (!empty($_COOKIE[session_name()]))
        {
            setcookie(session_name(), "", time() - 42000);
        }

        // destroy session
        session_destroy();
    }

    /**
     * Returns a stock by symbol (case-insensitively) else false if not found.
     */
    function lookup($symbol)
    {
        // reject symbols that start with ^
        if (preg_match("/^\^/", $symbol))
        {
            return false;
        }

        // reject symbols that contain commas
        if (preg_match("/,/", $symbol))
        {
            return false;
        }

        // headers for proxy servers
        $headers = [
            "Accept" => "*/*",
            "Connection" => "Keep-Alive",
            "User-Agent" => sprintf("curl/%s", curl_version()["version"])
        ];

        // open connection to Yahoo
        $context = stream_context_create([
            "http" => [
                "header" => implode(array_map(function($value, $key) { return sprintf("%s: %s\r\n", $key, $value); }, $headers, array_keys($headers))),
                "method" => "GET"
            ]
        ]);
        $handle = @fopen("http://download.finance.yahoo.com/d/quotes.csv?f=snl1&s={$symbol}", "r", false, $context);
        if ($handle === false)
        {
            // trigger (big, orange) error
            trigger_error("Could not connect to Yahoo!", E_USER_ERROR);
            exit;
        }
 
        // download first line of CSV file
        $data = fgetcsv($handle);
        if ($data === false || count($data) == 1)
        {
            return false;
        }

        // close connection to Yahoo
        fclose($handle);

        // ensure symbol was found
        if ($data[2] === "N/A" || $data[2] === "0.00")
        {
            return false;
        }

        // return stock as an associative array
        return [
            "symbol" => strtoupper($data[0]),
            "name" => $data[1],
            "price" => floatval($data[2])
        ];
    }

    /**
     * Redirects user to location, which can be a URL or
     * a relative path on the local host.
     *
     * http://stackoverflow.com/a/25643550/5156190
     *
     * Because this function outputs an HTTP header, it
     * must be called before caller outputs any HTML.
     */
    function redirect($location)
    {
        if (headers_sent($file, $line))
        {
            trigger_error("HTTP headers already sent at {$file}:{$line}", E_USER_ERROR);
        }
        header("Location: {$location}");
        exit;
    }

    /**
     * Renders view, passing in values.
     */
    function render($view, $values = [])
    {
        // if view exists, render it
        if (file_exists("../views/{$view}"))
        {
            // extract variables into local scope
            extract($values);

            // render view (between header and footer)
            require("../views/header.php");
            require("../views/{$view}");
            require("../views/footer.php");
            exit;
        }

        // else err
        else
        {
            trigger_error("Invalid view: {$view}", E_USER_ERROR);
        }
    }

    /**
     * does a query for all of the user's stocks and returns an array of 
     * associate arrays of the users stocks along with the stocks properties 
     **/
    function get_assets()
    {
        /* query returns an array of rows that contain all the stock symbols 
        and shares for a particular user */
        $rows = CS50::query("SELECT symbol, shares FROM portfolios WHERE user_id = ?",
        $_SESSION["id"]);
        
        /*declare an array called assets which will contain an associate array 
        of stocks with indexes that consist their properies*/
        $assets = [];
        
        // iterates through each of the stocks that are owned 
        foreach($rows as $row)
        {
            // lookup stock properties and make sure the stock exists 
            $stock = lookup($row["symbol"]);
            if ($stock !== false)
            {
                $assets[]= [
                    "name" => $stock["name"],
                    "price" => number_format($stock["price"], 2, ".", ","),
                    "shares" => $row["shares"],
                    "symbol" => $row["symbol"],
                    "total price" => number_format($stock["price"] * $row["shares"], 2, ".", ",")
                ];
            }
        }
        return $assets;
    }
    
    /**
     * performs a query to find the user's total cash
     **/
    function get_cash()
    {
        //query to obtain the users total cash 
        $cash = CS50::query("SELECT cash FROM users where id = ?", $_SESSION["id"]);
    
        //format total_cash obtained from the query 
        $cash = number_format($cash[0]["cash"], 2, ".", ","); 
        
        return $cash;
    
    }
?>
