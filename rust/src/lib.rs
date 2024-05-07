#[allow(dead_code)]
mod bindings;

use bindings::{next, Guest};

struct Component;

impl Guest for Component {
    fn greet() -> String {
        let next = next();
        if next.is_empty() {
            return "Rust".to_string();
        }

        format!("Rust and {next}")
    }
}

bindings::export!(Component with_types_in bindings);
