// TODO: Define a new `Order` type.
//   It should keep track of three pieces of information: `product_name`, `quantity`, and `unit_price`.
//   The product name can't be empty and it can't be longer than 300 bytes.
//   The quantity must be strictly greater than zero.
//   The unit price is in cents and must be strictly greater than zero.
//   Order must include a method named `total` that returns the total price of the order.
//   Order must provide setters and getters for each field.
//
// Tests are located in a different place this time—in the `tests` folder.
// The `tests` folder is a special location for `cargo`. It's where it looks for **integration tests**.
// Integration here has a very specific meaning: they test **the public API** of your project.
// You'll need to pay attention to the visibility of your types and methods; integration
// tests can't access private or `pub(crate)` items.

pub struct Order{
    product_name:   String,
    quantity:       u32,
    unit_price:     u32,    
}

impl Order {
    pub fn new(name: String, q: u32, p: u32) -> Order {
        if name.is_empty(){panic!();}
        if name.len() > 300 {panic!();}
        if q == 0 {panic!();}
        if p < 1 {panic!();}

        let aux = Order {
            product_name : name,
            quantity : q,
            unit_price : p,
        };
        aux
    }
    
    pub fn total(&self) -> u32{
        self.quantity * self.unit_price
    }

    pub fn set_product_name(&mut self, new_name: String) {
        if new_name.is_empty(){panic!();}
        if new_name.len() > 300 {panic!();}
        self.product_name = new_name
        
    }

    pub fn set_quantity(&mut self, n_q: u32){
        if n_q == 0 {panic!();}
        self.quantity = n_q
    }

    pub fn set_unit_price(&mut self, n_p: u32){
        if n_p < 1 {panic!();}
        self.unit_price = n_p
    }

    pub fn product_name(&self) -> &String{
        &self.product_name
    }

    pub fn quantity(&self) -> &u32{
        &self.quantity
    }

    pub fn unit_price(&self) -> &u32{
        &self.unit_price
    }
}