// TODO: Implement the `From` trait for the `WrappingU32` type to make `example` compile.

impl From<u32> for WrappingU32 {
    fn from (num: u32) -> Self{
        Self{value: num}
    }
}

pub struct WrappingU32 {
    value: u32,
}

fn example() {
    let wrapping: WrappingU32 = 42.into();
    let wrapping = WrappingU32::from(42);
}
