package main

import (
	"fmt"
	"os"
	"path/filepath"
)

/*
const (
	defaultCellSize  = 8
	defaultArraySize = 30000
)
*/

type options struct {
	file []*os.File
    help bool
}

type optionError int

const (
	noInputFile optionError = iota + 1
	fileNotFound
)

func (opt optionError) Error() string {
	baseExecutable := filepath.Base(os.Args[0])

	var err string

	switch opt {
	case noInputFile:
		err = fmt.Sprintf(
			"%s: fatal error: no input file\n",
			baseExecutable,
		)
	case fileNotFound:
		err = fmt.Sprintf(
			"%s: fatal error: file not found\n",
			baseExecutable,
		)
	default:
		err = "undefined error"
	}
	err += fmt.Sprintf(
        "try \"%s -h\" for help.\n",
        baseExecutable,
    )
	return err
}
