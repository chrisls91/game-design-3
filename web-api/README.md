# Game Web API

### Requirements

* Composer
* PHP 5.3 or greater
* Apache ModRewrite Enabled
* MySQL

### Install

    composer install
    php vendor/bin/phinx migrate

### Usage

#### Get

    GET users           # returns all users
    GET users/{id}      # returns user with specified id
    GET users/runs/{id} # returns all runs associated with user id

#### Post

    POST users {"username": "foo", "password": "bar"} # creates user foo:bar

### Not Implemented

    POST users/run
