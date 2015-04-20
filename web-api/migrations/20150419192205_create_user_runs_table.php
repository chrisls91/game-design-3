<?php

use Phinx\Migration\AbstractMigration;

class CreateUserRunsTable extends AbstractMigration
{
    function change()
    {
        $table = $this->table('user_runs');
        $table->addColumn('users_id', 'integer')
              ->addColumn('level', 'integer')
              ->addColumn('time', 'string')
              ->addColumn('trophy', 'string')
              ->addColumn('replay_data', 'text')
              ->addForeignKey('users_id', 'users', 'id')
              ->create();
    }
}
