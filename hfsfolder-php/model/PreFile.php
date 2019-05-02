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

    public function __construct($name, $size, $modified, $attributes, $formatSize, $formatModified) {
        $this->name = $name;
        $this->size = $size;
        $this->modified = $modified;
        $this->attributes = $attributes;
        $this->formatedSize = $formatSize;
        $this->formatedModified = $formatModified;
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

    public function limparDados() {
        $this->name = "";
        $this->size = 0;
        $this->modified = new DateTime();
        $this->attributes = "";
        $this->formatedSize = "";
        $this->formatedModified = "";
    }

    public function toString() {
        return "PreFile [name=" . $this->name . ", size=" . $this->size
            . ", modified=" . $this->modified . ", attributes=" . $this->attributes
            . ", formatSize=" . $this->formatedSize
            . ", formatModified=" . $this->formatedModified . "]";
    }

    public function toInsert() {
        return "'" . $this->getName() . "'," . $this->size
            . ",'" . $this->formatedModified . "','" . $this->attributes . "'";
    }

    public function toCVS() {
        return $this->getName() . ";" . $this->size . ";"
            . $this->formatedModified . ";" . $this->attributes;
    }

}