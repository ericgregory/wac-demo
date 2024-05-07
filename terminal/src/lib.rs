#[allow(warnings)]
mod bindings;

use bindings::Guest;

struct Component;

impl Guest for Component {
    fn greet() -> String {
        String::new()
    }
}

bindings::export!(Component with_types_in bindings);
