<?php


namespace model;


class FolderOrder
{
    private $codFolder = 0;
    private $order = 0;

    public function __construct($codFolder, $order) {
        $this->codFolder = $codFolder;
        $this->order = $order;
    }

    public function FolderOrder($folderOrder) {
        $this->codFolder = $folderOrder->codFolder;
        $this->order = $folderOrder->order;
    }

    /**
     * @return int
     */
    public function getCodFolder()
    {
        return $this->codFolder;
    }

    /**
     * @param int $codFolder
     */
    public function setCodFolder($codFolder)
    {
        $this->codFolder = $codFolder;
    }

    /**
     * @return int
     */
    public function getOrder()
    {
        return $this->order;
    }

    /**
     * @param int $order
     */
    public function setOrder($order)
    {
        $this->order = $order;
    }

}