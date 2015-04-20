<?php

use Phinx\Migration\AbstractMigration;

class MakeUsernameUnique extends AbstractMigration
{
    public function change()
    {
        $table = $this->table('users');
        $table->addIndex(['username'], ['unique' => true])
              ->save();
    }
}
