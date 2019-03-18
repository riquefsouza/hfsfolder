package main

import (
	"fmt"
	"go/build"
	"io"
	"os"
	"path/filepath"
	"strings"
)

func main() {
	fmt.Println("Olá Mundo")

	comando := leComando()

	switch comando {
	case 1:
		fmt.Println("Monitorando... ")
		find()
		break
	case 2:
		fmt.Println("Exibindo logs...")
		break
	case 0:
		fmt.Println("Saindo do programa")
		os.Exit(0)
	default:
		fmt.Println("Não conheço esse comando")
		break
	}
}

func leComando() int {
	var comandoLido int
	fmt.Scan(&comandoLido)
	fmt.Println("O comando escolhido foi", comandoLido)
	return comandoLido
}

func visit(path string, f os.FileInfo, err error) error {
	if !f.IsDir() {
		return nil
	}

	if f.Name() == "vendor" {
		return filepath.SkipDir
	}

	dirName := strings.ToLower(f.Name())

	//if pkgName == dirName {
	fmt.Println(dirName)
	fmt.Println(path)
	return io.EOF
	//}

	//return nil
}

func find() (err error) {
	root := build.Default.GOPATH + "/src"

	err = filepath.Walk(root, visit)
	if err == nil || err == io.EOF {
		return
	}
	return
}
