<?php namespace GameAPI;

abstract class BaseAPI {

    protected $model;

    public function __construct()
    {
        $entity = 'GameAPI\Entities\\' . $this->entity;
        $this->model = new $entity();
    }

    public function index()
    {
        return $this->model->allAsArray();
    }

    public function get($id)
    {
        return $this->model->findAsArray($id);
    }

}
