# WebAssembly Compositions (WAC) Demo

[WebAssembly Compositions (WAC)](https://github.com/bytecodealliance/wac) is a CLI tool and language for combining WebAssembly components created by [Peter Heune](https://github.com/peterhuene) and hosted by the [Bytecode Alliance](https://github.com/bytecodealliance). This is a hands-on demo for WAC based heavily (i.e., almost entirely) on a demo that Peter gave at the 2024 Bytecode Alliance Plumbers' Summit. 

The contents of this repo include:

* `/golang`: A directory containing a Go greeter project and compiled component
* `/cli`: A directory containing a Rust cli project and compiled component
* `/terminal`: A directory containing a Rust terminal project and compiled component
* `composition.wac`: The file defining how the components above should be combined ("composed")
* `/reference`: Purely for reference, a copy of the WIT used by the components and a copy of the final WebAssembly component after running through the demo

In this demo, we'll use the composition instructions defined in our `composition.wac` file to combine three components (a `greeter` written in Go and `terminal` and `cli` components written in Rust) into a single component that returns CLI output when we run it with the Wasmtime WebAssembly runtime. 

## Requirements

The only strict requirements for running this demo are [`cargo`](https://doc.rust-lang.org/cargo/getting-started/installation.html) and [WAC](https://github.com/bytecodealliance/wac) itself, since compiled Wasm components are provided. If you would like to compile the components on your own, you'll need tools to compile to a wasip2 target from Rust and Go. The components here were built with:

* [cargo component](https://github.com/bytecodealliance/cargo-component) v0.11.0 for Rust
* [wasmCloud shell (`wash`)](https://wasmcloud.com/docs/installation) v0.27.0 for Go

Additionally, [`wasm-tools`](https://github.com/bytecodealliance/wasm-tools) is a great utility for quickly checking out a component's WIT. 

## Instructions

Install WAC:

```shell
cargo install wac-cli
```

Clone or download this repository:

```shell
git clone https://github.com/ericgregory/wac-demo.git
```

At the root of the project directory, run WAC:

```shell
wac encode --dep demo:terminal=./terminal/target/wasm32-wasi/debug/terminal.wasm --dep demo:golang=./golang/build/greeter.wasm --dep demo:cli=./cli/target/wasm32-wasi/debug/cli.wasm -o composed.wasm composition.wac
```

This command **encodes** a new component called `composed.wasm` according to the definition in `composition.wac`. The `--dep` flags assign names (for example, `demo:terminal`) to the specified Wasm components that are bring composed together; these names are used in the `composition.wac` file. 

The `cli` component prints "Hello from" and the Go-based `greeter` component passes in the string "Golang". When we run our new composed component, we get...

```shell
wasmtime composed.wasm
Hello from Golang!
```