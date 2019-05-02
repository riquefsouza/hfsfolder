<?php


namespace util;


class VisitFoldersUtil
{
    private $afolders = array();
    private $index = 0;

    public function getFoldersFromFiles($dir = '.'){
        $this->afolders[$this->index++] = $dir;
        $folders = $this->getArrayFromFiles($dir);
        return $folders;
    }

    public function getArrayFromFiles($dir = '.'){
        $prefix = $dir . '/';
        $dir = opendir($dir);

        while(($file = readdir($dir)) !== false) {

            if ($file === '.' || $file === '..')
                continue;

            $file = $prefix . $file;

            $this->afolders[$this->index++] = $file;

            if (is_dir($file)){
                $this->getArrayFromFiles($file);
            }
        }

        closedir($dir);

        return $this->afolders;
    }

}