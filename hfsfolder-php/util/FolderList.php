<?php


namespace util;


class FolderList
{
    private $afolders = array();

    public function add($obj, $key = null) {
        if ($key == null) {
            $this->afolders[] = $obj;
        }
        else {
            if (isset($this->afolders[$key])) {
                throw new exception("Key $key already in use.");
            }
            else {
                $this->afolders[$key] = $obj;
            }
        }
    }

    public function delete($key) {
        if (isset($this->afolders[$key])) {
            unset($this->afolders[$key]);
    }
        else {
            throw new exception("Wrong key $key.");
        }
    }

    public function get($key) {
        if (isset($this->afolders[$key])) {
            return $this->afolders[$key];
        }
        else {
            throw new exception("Wrong key $key.");
        }
    }

    public function keys() {
        return array_keys($this->afolders);
    }

    public function size() {
        return count($this->afolders);
    }

    public function existKey($key) {
        return isset($this->afolders[$key]);
    }
}