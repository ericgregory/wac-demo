package main

import (
	greeter "demo/greeter/gen"
	"fmt"
)

func init() {
	a := Greeter{}
	greeter.SetGreeter(a)
}

type Greeter struct {
}

func (e Greeter) Greet() string {
	next := greeter.GreeterNext()
	if len(next) == 0 {
		return "Golang"
	}

	return fmt.Sprintf("Golang and %s", next)
}

//go:generate wit-bindgen tiny-go wit --out-dir=gen --gofmt
func main() {}
