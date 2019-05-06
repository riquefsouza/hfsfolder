<?php

namespace util;

require_once(__ROOT__.'/model/PreFile.php');

use model\PreFile as PreFile;

class VisitFoldersUtil
{
    private $afolders = array();
    private $index = 0;

    public function getFoldersFromFiles($dir = '.'){
        $filename = basename($dir);
        $prefile = $this->attributesToPreFile($dir, $filename);

        $this->afolders[$this->index++] = $prefile;
        $folders = $this->getArrayFromFiles($dir);
        return $folders;
    }

    private function getArrayFromFiles($dir = '.'){
        $prefix = $dir . '/';
        $dir = opendir($dir);

        while(($file = readdir($dir)) !== false) {

            if ($file === '.' || $file === '..')
                continue;

            $file = $prefix . $file;

            $filename = basename($file);
            $prefile = $this->attributesToPreFile($file, $filename);
            $this->afolders[$this->index++] = $prefile;

            if (is_dir($file)){
                $this->getArrayFromFiles($file);
            }
        }
        closedir($dir);

        return $this->afolders;
    }

    public function getFoldersFromFilesByPattern($dir = '.', $pattern = '/./'){
        $this->afolders[$this->index++] = $dir;
        $folders = $this->getArrayFromFilesByPattern($dir, $pattern);
        return $folders;
    }

    private function getArrayFromFilesByPattern($dir = '.', $pattern = '/./'){
        $prefix = $dir . '/';
        $dir = opendir($dir);

        while(($file = readdir($dir)) !== false) {

            if ($file === '.' || $file === '..')
                continue;

            $file = $prefix . $file;

            if (preg_match($pattern, $file)) {
                $this->afolders[$this->index++] = $file;
            }

            if (is_dir($file)){
                $this->getArrayFromFilesByPattern($file, $pattern);
            }
        }
        closedir($dir);

        return $this->afolders;
    }

    private function formatDecimal($valor){
        return number_format($valor, 2, ',', '.');
    }

    private function mountBigSize($nTam) {
        $nUmKilo = 1024;
        $nUmMega = $nUmKilo * 1024;
        $nUmGiga = $nUmMega * 1024;
        $nUmTera = $nUmGiga * 1024;
        $nUmPeta = $nUmTera * 1024;

        if ($nTam < $nUmKilo) {
            $nTamLocal = floatval($nTam);
            return $this->formatDecimal($nTamLocal) . " Byte(s)";
        } elseif ($nTam > $nUmKilo and $nTam < $nUmMega) {
            $nTamLocal = floatval($nTam) / $nUmKilo;
            return $this->formatDecimal($nTamLocal) . " KByte(s)";
        } elseif ($nTam > $nUmMega and $nTam < $nUmGiga) {
            $nTamLocal = floatval($nTam) / $nUmMega;
            return $this->formatDecimal($nTamLocal) . " MByte(s)";
        } elseif ($nTam < $nUmGiga and $nTam > $nUmTera) {
            $nTamLocal = floatval($nTam) / $nUmGiga;
            return $this->formatDecimal($nTamLocal) . " GByte(s)";
        } elseif ($nTam < $nUmTera and $nTam > $nUmPeta) {
            $nTamLocal = floatval($nTam) / $nUmTera;
            return $this->formatDecimal($nTamLocal) . " TByte(s)";
        } else {
            $nTamLocal = floatval($nTam) / $nUmPeta;
            return $this->formatDecimal($nTamLocal) . " PByte(s)";
        }
    }

    private function attributesToPreFile($sfile, $filename) {
        $pf = new PreFile();
        $sAtributos = "";
        $sName = str_replace("'", "''", $filename);
        $pf->setName($sName);
        $pf->setSize(filesize($sfile));
        $pf->setModified(filemtime($sfile));

        if (is_dir($sfile)) {
            $sAtributos .= "[DIR]";
            $pf->setDirectory(true);
        } else {
            $sAtributos .= "[ARQ]";
            $pf->setDirectory(false);
        }

        $pf->setAttributes($sAtributos);
        $pf->setOriginalPath($sfile);
        $pf->setFormatedSize($this->mountBigSize($pf->getSize()));
        $pf->setFormatedModified(date("d/m/Y H:i:s", $pf->getModified()));
        return $pf;
    }
}