<?php namespace GameAPI\Entities;

class Leader extends BaseModel {
    public static $_table = 'leaders';

    public function create($data)
    {
        $leader = $this->model->create();
        $leader->name = $data['name'];
        $leader->time = $data['time'];
        $leader->level = $data['level'];
        $leader->save();

        return $leader;
    }

    public function findByTime()
    {
        return \ORM::for_table('leaders')->order_by_asc('time')->find_array();
    }
}
