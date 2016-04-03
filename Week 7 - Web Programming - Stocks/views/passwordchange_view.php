<form action="passwordchange.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="old_pass" placeholder="Old Password" type="password"/>
        </div>
        <div class="form-group">
            <input autocomplete="off" class="form-control" name="new_pass" placeholder="New Password" type="password"/>
        </div>
        <div class="form-group">
            <input autocomplete="off" class="form-control" name="new_pass_conf" placeholder="Confirm New Password" type="password"/>
        </div>
        <div class="form-group">
            <button class=" btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Change Password
            </button>
        </div>
    </fieldset>
    
</form>