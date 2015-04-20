<?php namespace GameAPI\Entities;

abstract class BaseModel extends \Model {

    protected $model;

    public function __construct()
    {
        \ORM::configure('mysql:host=localhost;dbname=gameapi');
        \ORM::configure('username', 'dev');
        \ORM::configure('password', 'dev');

        $this->model = \Model::factory(get_called_class());
    }

    public function all()
    {
        return $this->model->find_many();
    }

    public function allAsArray()
    {
        return $this->model->find_array();
    }

    public function find($id)
    {
        return $this->model->find_one($id);
    }

    public function findAsArray($id)
    {
        return $this->model->where('id', $id)->find_array();
    }
}
