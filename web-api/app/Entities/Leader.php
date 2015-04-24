<?php namespace GameAPI\Entities;

class Leader extends BaseModel {
    public static $_table = 'leaders';

    public function create($data)
    {
        $leader = $this->model->create();
        $leader->name = $data['name'];
        $leader->score = $data['score'];
        $leader->save();

        return $leader;
    }

}
