<?php


namespace model;


class Folder extends PreFile
{
    private $code = 0;
    private $order = 0;
    private $parentCodFolder = 0;
    private $folderType = '';
    private $path = "";
    private $parentName = "";
    private $parentPath = "";
    private $originalPath = "";

    public function __construct($preFile) {
        $this->setName($preFile->getName());
        $this->setSize($preFile->getSize());
        $this->setModified($preFile->getModified());
        $this->setAttributes($preFile->getAttributes());
        $this->setFormatedSize($preFile->getFormatedSize());
        $this->setFormatedModified($preFile->getFormatedModified());
    }

    /**
     * @param int $code
     */
    public function setCode($code)
    {
        $this->code = $code;
    }

    /**
     * @return int
     */
    public function getCode()
    {
        return $this->code;
    }

    /**
     * @param int $order
     */
    public function setOrder($order)
    {
        $this->order = $order;
    }

    /**
     * @return int
     */
    public function getOrder()
    {
        return $this->order;
    }

    /**
     * @return int
     */
    public function getParentCodFolder()
    {
        return $this->parentCodFolder;
    }

    /**
     * @param int $parentCodFolder
     */
    public function setParentCodFolder($parentCodFolder)
    {
        $this->parentCodFolder = $parentCodFolder;
    }

    /**
     * @return string
     */
    public function getFolderType()
    {
        return $this->folderType;
    }

    /**
     * @param string $folderType
     */
    public function setFolderType($folderType)
    {
        $this->folderType = $folderType;
    }

    /**
     * @return string
     */
    public function getPath()
    {
        return $this->path;
    }

    /**
     * @param string $path
     */
    public function setPath($path)
    {
        $this->path = $path;
    }

    /**
     * @return string
     */
    public function getParentName()
    {
        return $this->parentName;
    }

    /**
     * @param string $parentName
     */
    public function setParentName($parentName)
    {
        $this->parentName = $parentName;
    }

    /**
     * @return string
     */
    public function getParentPath()
    {
        return $this->parentPath;
    }

    /**
     * @param string $parentPath
     */
    public function setParentPath($parentPath)
    {
        $this->parentPath = $parentPath;
    }

    /**
     * @return string
     */
    public function getOriginalPath()
    {
        return $this->originalPath;
    }

    /**
     * @param string $originalPath
     */
    public function setOriginalPath($originalPath)
    {
        $this->originalPath = $originalPath;
    }

    public function limparDados() {
        parent::limparDados();
        $this->code = 0;
        $this->order = 0;
        $this->parentCodFolder = 0;
        $this->folderType = 'A';
        $this->path = "";
        $this->parentName = "";
        $this->parentPath = "";
        $this->originalPath = "";
    }

    public function __toString() {
        return "Folder [codigo=" . $this->code . ", ordem=" . $this->order
            . ", codDirPai=" . $this->parentCodFolder . ", tipo=" . $this->folderType
            . ", caminho=" . $this->path . ", nomePai=" . $this->parentName
            . ", caminhoPai=" . $this->parentPath . "]";
    }

    public function toInsert($naba) {
        return "INSERT INTO Diretorios(aba, cod, ordem, nome, tam, tipo, modificado, atributos, coddirpai, caminho) VALUES("
            . $naba . "," . $this->code . "," . $this->order . ",'" . $this->getName() . "',"
            . $this->getSize() . ",'" . $this->folderType . "','" . $this->getFormatedModified()
            . "','" . $this->getAttributes() . "'," . $this->parentCodFolder . ",'" . $this->getPath()
            . "');";
    }

    public function toCVS() {
        return $this->code . ";" . $this->order . ";" . $this->getName()
            . ";" . $this->getSize() . ";" . $this->folderType . ";"
            . $this->getFormatedModified() . ";" . $this->getAttributes() . ";"
            . $this->parentCodFolder . ";" . $this->getPath();
    }

}