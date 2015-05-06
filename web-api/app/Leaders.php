<?php namespace GameAPI;

use GameAPI\BaseAPI;

class Leaders extends BaseAPI {

    protected $entity = 'Leader';
    protected $fields = ['name', 'time', 'level'];

    public function post($request_data)
    {
        return $this->model->create($request_data);
    }

    public function index()
    {
        return $this->model->findByTime();
    }
}

