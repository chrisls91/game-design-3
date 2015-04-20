<?php require 'vendor/autoload.php';

use Luracast\Restler\Restler;

$r = new Restler();
$r->addAPIClass('GameAPI\Users');
$r->addAPIClass('GameAPI\Runs');
$r->handle();
