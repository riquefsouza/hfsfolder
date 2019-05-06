<?php

require_once(__ROOT__.'/model/FolderOrder.php');
require_once(__ROOT__.'/model/Folder.php');
require_once(__ROOT__.'/util/VisitFoldersUtil.php');

use model\FolderOrder as FolderOrder;
use model\Folder as Folder;
use util\VisitFoldersUtil as VisitFoldersUtil;

class ProcessFolders
{
    private function startsWith($haystack, $needle) {
        if (substr_compare($haystack, $needle, 0, strlen($needle)) === 0)
            return true;
        else
            return false;
    }

    private function createFolder($pf, $folderOrder) {
        $folder = new Folder($pf);

        if ($pf->isDirectory()) {
            $folder->setFolderType('D');
        } else {
            $folder->setFolderType('A');
        }

        $sPath = $pf->getOriginalPath();
        $regex = '/[a-zA-Z]:\\\\/';
        if (preg_match($regex, $sPath)) {
            $sPath = substr($sPath, 3);
            $folder->separatorChar = '\\';
        }
        $regex = '/[a-zA-Z]:\//';
        if (preg_match($regex, $sPath)) {
            $sPath = substr($sPath, 3);
            $folder->separatorChar = '/';
        }
        if ($this->startsWith($sPath, "/")) {
            $sPath = substr($sPath, 1);
            $folder->separatorChar = '/';
        }

        $sPart = str_replace("'", "''", $sPath);
        $sPart = str_replace("\\", "/", $sPart);

        $folder->setPath($sPart);
        $folder->setOriginalPath($pf->getOriginalPath());

        if (strlen(strstr($folder->getPath(),"/")) == 0) {
            $folderOrder->setCodFolder($folderOrder->getCodFolder() + 1);
            $folderOrder->setOrder(1);
        } else {
            $folderOrder->setOrder($folderOrder->getOrder() + 1);
        }

        $folder->setCode($folderOrder->getCodFolder());
        $folder->setOrder($folderOrder->getOrder());

        return $folder;
    }

    private function filterFindFirst($listFolders, $sfolder) {

        for ($i = 0; $i < count($listFolders); $i++) {
            $folder = $listFolders[$i];

            if ($sfolder == $folder->getOriginalPath()) {
                return $folder;
            }
        }

        return null;
    }

    private function process($folder) {
        $listaFolders = array();
        $folderOrder = new FolderOrder(-1, 0);
        echo "Processing folders!\n";
        $vfu = new VisitFoldersUtil();
        $listaPrefiles = $vfu->getFoldersFromFiles($folder);

        for ($i = 0; $i < count($listaPrefiles); $i++) {
            $pf = $listaPrefiles[$i];

            $dir = $this->createFolder($pf, $folderOrder);
            $listaFolders[$i] = $dir;
        }

        for ($i = 0; $i < count($listaFolders); $i++) {
            $item = $listaFolders[$i];

            $lastIndex = strrpos($item->getOriginalPath(), $item->separatorChar);
            $pathChild = substr($item->getOriginalPath(), 0, $lastIndex);

            $pathFather = $this->filterFindFirst($listaFolders, $pathChild);

            if ($pathFather != null) {
                $item->setParentCodFolder($pathFather->getOrder());
                $item->setParentName($pathFather->getName());
                $item->setParentPath($pathFather->getPath());
            } else {
                $item->setParentCodFolder(0);
                $item->setParentName("");
                $item->setParentPath("");
            }

        }

        //sort($listaFolders);

        return $listaFolders;
    }

    public function processFoldersToJson($folder) {
        $lista = $this->process($folder);
        $result = "[ ";

        for ($i = 0; $i < count($lista); $i++) {
            $item = $lista[$i];

            if ($i == 0) {
                $result .= $item->toJSON();
            } else {
                $result .= ", " . $item->toJSON();
            }
        }

        return $result . " ]";
    }

    public function processFoldersToFile($data, $sfile) {
        $file = fopen($sfile, "w");
        if ($file) {
            fwrite($file,$data);
        } else {
            echo "Unable to open file!\n";
        }
        fclose($file);
    }

    public function processFoldersToInsert($folder, $naba) {
        $lista = $this->process($folder);
        $result = "";

        for ($i = 0; $i < count($lista); $i++) {
            $item = $lista[$i];
            $result .= $item->toInsert($naba) . "\n";
        }

        return $result;
    }

    public function processFoldersToCSV($folder) {
        $lista = $this->process($folder);
        $result = 'Code;Order;Name;Size;"Folder Type";"Formated Modified";Attributes;"Parent Code Folder";Path\n';

        for ($i = 0; $i < count($lista); $i++) {
            $item = $lista[$i];
            $result .= $item->toCVS() . "\n";
        }

        return $result;
    }


}