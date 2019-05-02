package model

import "time"

type PreFile struct {
	name string
	size int64
	modified time.Time
	attributes string
	formatedSize string
	formatedModified string
	originalPath string
	directory bool
	separatorChar string
}

func PreFile_limparDados(preFile PreFile) {
	preFile.name = ""
	preFile.size = 0
	preFile.modified = time.Now()
	preFile.attributes = ""
	preFile.formatedSize = ""
	preFile.formatedModified = ""
	preFile.originalPath = ""
	preFile.directory = false
}


