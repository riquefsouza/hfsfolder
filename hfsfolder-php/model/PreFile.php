<?php


namespace model;


class PreFile
{
    private $name = "";
    private $size = 0;
    private $modified;
    private $attributes = "";
    private $formatedSize = "";
    private $formatedModified = "";
    private $originalPath = "";
    private $directory = false;

    public function __construct() {
        $this->limparDados();
    }

    /**
     * @return string
     */
    public function getName()
    {
        return $this->name;
    }

    /**
     * @param string $name
     */
    public function setName($name)
    {
        $this->name = $name;
    }

    /**
     * @return int
     */
    public function getSize()
    {
        return $this->size;
    }

    /**
     * @param int $size
     */
    public function setSize($size)
    {
        $this->size = $size;
    }

    /**
     * @return mixed
     */
    public function getModified()
    {
        return $this->modified;
    }

    /**
     * @param mixed $modified
     */
    public function setModified($modified)
    {
        $this->modified = $modified;
    }

    /**
     * @return string
     */
    public function getAttributes()
    {
        return $this->attributes;
    }

    /**
     * @param string $attributes
     */
    public function setAttributes($attributes)
    {
        $this->attributes = $attributes;
    }

    /**
     * @return string
     */
    public function getFormatedSize()
    {
        return $this->formatedSize;
    }

    /**
     * @param string $formatedSize
     */
    public function setFormatedSize($formatedSize)
    {
        $this->formatedSize = $formatedSize;
    }

    /**
     * @return string
     */
    public function getFormatedModified()
    {
        return $this->formatedModified;
    }

    /**
     * @param string $formatedModified
     */
    public function setFormatedModified($formatedModified)
    {
        $this->formatedModified = $formatedModified;
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

    /**
     * @return bool
     */
    public function isDirectory()
    {
        return $this->directory;
    }

    /**
     * @param bool $directory
     */
    public function setDirectory($directory)
    {
        $this->directory = $directory;
    }

    public function limparDados() {
        $this->name = "";
        $this->size = 0;
        $this->modified = date("d/m/Y H:i:s");
        $this->attributes = "";
        $this->formatedSize = "";
        $this->formatedModified = "";
        $this->originalPath = "";
        $this->directory = false;
    }

    public function __toString() {
        return "PreFile [name=" . $this->name . ", size=" . $this->size
            . ", modified=" . $this->modified . ", attributes=" . $this->attributes
            . ", formatSize=" . $this->formatedSize
            . ", formatModified=" . $this->formatedModified . "]";
    }

    public function toCVS() {
        return $this->getName() . ";" . $this->size . ";"
            . $this->formatedModified . ";" . $this->attributes;
    }

}