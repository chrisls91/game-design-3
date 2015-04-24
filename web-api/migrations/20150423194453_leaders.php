<?php

use Phinx\Migration\AbstractMigration;

class Leaders extends AbstractMigration
{
    public function change()
    {
        $table = $this->table('leaders');
        $table->addColumn('name', 'string')
              ->addColumn('time', 'float')
              ->save();
    }
}
