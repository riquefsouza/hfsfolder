#!/usr/bin/php
<?php
define('__ROOT__', dirname(__FILE__));
require_once(__ROOT__.'/model/FolderOrder.php');
require_once(__ROOT__.'/util/VisitFoldersUtil.php');
require_once(__ROOT__.'/util/FolderList.php');

use util\FolderList as FolderList;
use model\FolderOrder as FolderOrder;

/*
$c = new FolderList();

$c->add(new FolderOrder(1, 4), 0);
$c->add(new FolderOrder(2, 5), 1);
$c->add(new FolderOrder(3, 6), 2);

//foreach ($c->items as $item) {
for ($x = 0; $x < $c->size(); $x++) {
    echo $c->get($x)->getOrder() . "\n";
}

$c->delete(1);

try {
    echo $c->get(1);
}
catch (exception $e) {
    print "The collection doesn't contain Steve.";
}

*/
use util\VisitFoldersUtil as VisitFoldersUtil;

$visitFoldersUtil = new VisitFoldersUtil();
$folders = $visitFoldersUtil->getFoldersFromFiles("c:/Fabricante");

for ($x = 0; $x < count($folders); $x++) {
    echo "outro: " . $folders[$x] . "\n";
}


/*
foreach($argv as $value)
{
    echo "$value\n";
}


//$d=strtotime("now");
//echo date("d/m/Y H:i:s");
//print_r(getdate());
date_default_timezone_set("America/Recife");
echo date(DATE_W3C);
printf("\n");
echo date("d/m/Y H:i:s");
*/
