package main

import (
	"fmt"
	"os"
	"path/filepath"
)

const help = `Usage: %s [options] file...
Options:
  -h         Display this information.
  -e <input> Evaluate the input.
`

func parseArgs() (options, error) {
    opt := options{
        file: []*os.File{},
        help: false,
    }

    if len(os.Args) < 2 {
        return opt, noInputFile
    }

    for i := 1; i < len(os.Args); i++ {
        switch os.Args[i] {
        case "-h":
            opt.help = true
        default:
            file, err := os.Open(os.Args[i])
            if err != nil {
                return options{}, fileNotFound
            }
            opt.file = append(opt.file, file)
        }
    }
    return opt, nil
}

func bfEngine(input string) {

}

func main() {
	if len(os.Args) < 2 {
        fmt.Print(noInputFile)
		os.Exit(1)
	}

	opt, err := parseArgs()
	if err != nil {
		fmt.Print(err.Error())
		os.Exit(1)
	}

    if opt.help {
        fmt.Printf(
            help,
            filepath.Base(os.Args[0]),
        )
        os.Exit(0)
    }

    /*
    for _, _ := range opt.file {
        bfEngine()
    }
    */
}
