<?php namespace GameAPI;

use GameAPI\BaseAPI;

class Runs extends BaseAPI {

    protected $entity = 'Run';
    protected $fields = ['users_id', 'level', 'time', 'trophy', 'replay_data'];

    public function post($request_data)
    {
    }
}

