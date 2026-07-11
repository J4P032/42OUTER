// TODO: Define a new `SaturatingU16` type.
//   It should hold a `u16` value.
//   It should provide conversions from `u16`, `u8`, `&u16` and `&u8`.
//   It should support addition with a right-hand side of type
//   SaturatingU16, u16, &u16, and &SaturatingU16. Addition should saturate at the
//   maximum value for `u16`.
//   It should be possible to compare it with another `SaturatingU16` or a `u16`.
//   It should be possible to print its debug representation.
//
// Tests are located in the `tests` folder—pay attention to the visibility of your types and methods.

use std::ops::Add;
#[derive(Copy, Clone, Debug, PartialEq)]
pub struct SaturatingU16{
    value: u16,
}

impl From<u16> for SaturatingU16{
    fn from(num: u16) -> Self{
        Self{value: num}
    }
}

impl From<&u16> for SaturatingU16{
    fn from(num: &u16) -> Self{
        Self{value: *num}
    }
}

impl From<u8> for SaturatingU16{
    fn from(num: u8) -> Self{
        Self{value: num.into()}
    }
}

impl From<&u8> for SaturatingU16{
    fn from(num: &u8) -> Self{
        Self{value: (*num).into()}
    }
}

//S1 + S2
impl Add for SaturatingU16{
    type Output = SaturatingU16;
    fn add(self, num: Self) -> Self{
       Self { value: self.value.saturating_add(num.value) }
    }
}

//S1 + S1 == u16
impl PartialEq<u16> for SaturatingU16{
    fn eq(&self, other: &u16) -> bool{
        self.value == *other
    }
}


//S1 + nU16 -> u16
impl Add<u16> for SaturatingU16{
    type Output = u16;
    fn add(self, num: u16) -> u16{
        let aux = self.value + num;
        aux
    }
}

//s1 + &s2 -> s3
impl Add<&SaturatingU16> for SaturatingU16{
    type Output = SaturatingU16;
    fn add(self, other: &Self) -> Self{
        Self { value: self.value.saturating_add((*other).value)}
    }
}

