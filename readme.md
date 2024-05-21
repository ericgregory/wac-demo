# WebAssembly Compositions (WAC) Demo

[WebAssembly Compositions (WAC)](https://github.com/bytecodealliance/wac) is a CLI tool and language for combining WebAssembly components created by [Peter Heune](https://github.com/peterhuene) and hosted by the [Bytecode Alliance](https://github.com/bytecodealliance). This is a hands-on demo for WAC based heavily (i.e., almost entirely) on a demo that Peter gave at the 2024 Bytecode Alliance Plumbers' Summit. 

The contents of this repo include:

* `/golang`: A directory containing a Go greeter project and compiled component
* `/js`: A directory containing a JavaScript greeter project and compiled component
* `/rust`: A directory containing a Rust greeter project and compiled component
* `/cli`: A directory containing a Rust CLI project and compiled component
* `/terminal`: A directory containing a Rust project and compiled component
* `composition.wac`: The file defining how components should be combined ("composed")
* `/reference`: Copies of the greeter WIT, final components, and the final `composition.wac`

In this demo, we'll explore how you can encode more complex compositions using the WAC language. We'll use the instructions defined in our `composition.wac` file to combine multiple components into a single component that returns CLI output when we run it with the Wasmtime WebAssembly runtime.

## Requirements

The only strict requirements for running this demo are [Wasmtime](https://github.com/bytecodealliance/wasmtime) (or another Wasm runtime that supports components), [`cargo`](https://doc.rust-lang.org/cargo/getting-started/installation.html), and [WAC](https://github.com/bytecodealliance/wac) itself, since compiled Wasm components are provided. If you would like to compile the components on your own, you'll need tools to compile to a wasip2 target from Rust and Go. The components here were built with:

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

This command **encodes** a new component called `composed.wasm` according to the definition in `composition.wac`. The `--dep` flags assign names (for example, `demo:terminal`) to the specified Wasm components that are being composed together; these names are used in the `composition.wac` file. 

The `cli` component prints "Hello from" and the Go-based `greeter` component passes in the string "Golang". When we run our new composed component, we get...

```shell
wasmtime composed.wasm
Hello from Golang!
```

This example is built to be extended via the `next` function. If we like, we can extend it indefinitely with a chain of additional greetings. 

We haven't used the `js` and `rust` greeter components so far. Let's add them to `composition.wac` (you can find a copy of the updated file in `reference`):

```
package demo:service;

let terminal = new demo:terminal {
    ...
};

let rust = new demo:rust {
    next: terminal.greet,
    ...
};

let js = new demo:js {
    next: rust.greet,
    ...
};

let golang = new demo:golang {
    next: js.greet,
    ...
};

let cli = new demo:cli {
    greet: golang.greet,
    ...
};

export cli ... ;
```
Now run `wac encode` again, adding the component dependencies for the JavaScript and Rust greeters:

```shell
wac encode --dep demo:terminal=./terminal/target/wasm32-wasi/debug/terminal.wasm --dep demo:golang=./golang/build/greeter.wasm --dep demo:cli=./cli/target/wasm32-wasi/debug/cli.wasm --dep demo:rust=./rust/target/wasm32-wasi/debug/rust.wasm --dep demo:js=./js/greeter.wasm -o composed.wasm composition.wac
```

When we run `composed.wasm` again:

```shell
wasmtime composed.wasm
Hello from Golang and JavaScript and Rust!
```
