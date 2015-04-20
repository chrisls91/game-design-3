<?php namespace GameAPI\Entities;

class User extends BaseModel {
    public static $_table = 'users';

    public function create($data)
    {
        $username = $data['username'];
        $passwordHash = password_hash($data['password'], PASSWORD_BCRYPT);

        $user = $this->model->create();
        $user->username = $username;
        $user->password = $passwordHash;
        $user->save();

        return $user;
    }

    public function runs()
    {
        return $this->has_many('GameAPI\Entities\Run');
    }
}
