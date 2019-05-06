#!/usr/bin/php
<?php
define('__ROOT__', dirname(__FILE__));
require_once(__ROOT__.'/ProcessFolders.php');

function input($text){
    print($text);
    $handle = fopen ("php://stdin","r");
    $line = fgets($handle);
    if(strlen(trim($line))> 0){
        return intval($line);
    }
    return 0;
}

function main($argv) {
    $processFolders = new ProcessFolders();
    $folder = "";
    $tojson = false;
    $tofile = false;
    $toinsert = false;
    $tocvs = false;
    if (count($argv) > 1) {
        for ($i = 1; $i < count($argv); $i++) {
            $opt = $argv[$i];

            if (strlen(strstr($opt,"--")) == 0) {
                $folder = $opt;
            }
            if ($opt === "--version") {
                print("hfsfolder 1.0\n");
            }
            if ($opt === "--tojson") {
                $tojson = true;
            }
            if ($opt === "--tofile") {
                $tofile = true;
            }
            if ($opt === "--toinsert") {
                $toinsert = true;
            }
            if ($opt === "--tocvs") {
                $tocvs = true;
            }
        }

        if (strlen($folder) > 0) {
            $data = "";
            $outFile = "hfsfolder";
            if ($tojson) {
                $outFile .= ".json";
                $data = $processFolders->processFoldersToJson($folder);
            }
            if ($toinsert) {
                $naba = input("Inform tab number: ");
                $outFile .= "-insert.sql";
                $data = $processFolders->processFoldersToInsert($folder, $naba);
            }
            if ($tocvs) {
                $outFile .= ".csv";
                $data = $processFolders->processFoldersToCSV($folder);
			}
            if ($tofile and strlen($data) > 0) {
                $processFolders->processFoldersToFile($data, $outFile);
                print("Finish process folders!\n");
            } elseif (strlen($data) > 0) {
                print($data . "\n");
            }
            if (!$tojson and !$toinsert and !$tocvs and !$tofile) {
                print("Inform option!\n");
            }
        } else {
            if ($tojson or $toinsert or $tocvs or $tofile) {
                print("Inform folder!\n");
            }
        }

    } else {
        print("HFSFolder \n"
        . "Usage:\n"
        . "    php hfsfolder-php.php /folder\n\n"
        . "Options:\n"
        . "    --version\n"
        . "    --tojson\n"
        . "    --toinsert\n"
        . "    --tocvs\n"
        . "    --tofile\n\n"
        . "Example:\n"
        . "    php hfsfolder-php.php /folder --tojson --tofile --version\n");
    }
}

main($argv);

