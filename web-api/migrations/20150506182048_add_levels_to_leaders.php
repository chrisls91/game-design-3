<?php

use Phinx\Migration\AbstractMigration;

class AddLevelsToLeaders extends AbstractMigration
{
    public function change()
    {
      $table = $this->table('leaders');
      $table->addColumn('level', 'string')
        ->save();
    }
}
