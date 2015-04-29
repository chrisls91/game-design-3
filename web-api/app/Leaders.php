<?php namespace GameAPI;

use GameAPI\BaseAPI;

class Leaders extends BaseAPI {

    protected $entity = 'Leader';
    protected $fields = ['name', 'score'];

    public function post($request_data)
    {
        return $this->model->create($request_data);
    }
}

