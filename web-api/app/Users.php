<?php namespace GameAPI;

use GameAPI\BaseAPI;

class Users extends BaseAPI {

    protected $entity = 'User';
    protected $fields = ['username', 'password'];

    public function post($request_data)
    {
        return $this->model->create($request_data);
    }

    public function runs($id)
    {
        return $this->model->find($id)->runs()->find_array();
    }
}

