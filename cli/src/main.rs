#[allow(dead_code)]
mod bindings;

use bindings::greet;

fn main() {
    let msg: String = greet();
    if msg.is_empty() {
        println!("Hello!");
    } else {
        println!("Hello from {msg}!");
    }
}