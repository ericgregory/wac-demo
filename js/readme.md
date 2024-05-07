# Greeter component in JavaScript

This directory contains a greeter component in JavaScript. For this demo, it was compiled to a WebAssembly component using `jco` v1.2.1.

The component is already built in this directory, but if you would like to compile yourself, you can [install `jco`](https://github.com/bytecodealliance/jco) and run:

```shell
jco componentize greeter.js --wit ./wit/greeter.wit -o greeter.wasm
```
