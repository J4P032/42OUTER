/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect3.rs                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:18:59 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/19 11:35:13 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Se necesita hacer Copy porque si no, al hacer:
let v1 = v2;
se produce un MOVE.*/
#[derive(Copy, Clone)]
pub struct	Vect3{ //x defecto struct es privado. Pub lo expone a publico
	x: f32,
	y: f32,
	z: f32,
}

use std::ops::{Add, AddAssign, Sub, SubAssign, Mul, MulAssign, Div, DivAssign};

//constructor
impl Vect3{
	pub fn new(x: f32, y: f32, z: f32) -> Self{
		Vect3{x, y, z}
	}
}

//getters
impl Vect3{
	pub fn x(&self) -> f32{
		self.x
	}
}

impl Vect3{
	pub fn y(&self) -> f32{
		self.y
	}
}

impl Vect3{
	pub fn z(&self) -> f32{
		self.z
	}
}


// +
impl Add for Vect3{
	type Output = Vect3;
	fn add(self, other: Vect3) -> Vect3{
		let aux = Vect3 {x: self.x + other.x, y: self.y + other.y, z: self.z + other.z};
		aux
	}		
}

// +=
impl AddAssign for Vect3{
	fn add_assign(&mut self, other: Vect3){
		self.x += other.x;
		self.y += other.y;
		self.z += other.z;
	}
}

// -
impl Sub for Vect3{
	type Output = Vect3;
	fn sub(self, other: Vect3) -> Vect3{
		Vect3 {x: self.x - other.x, y: self.y - other.y, z: self.z - other.z}
	}
}

// -=
impl SubAssign for Vect3{
	fn sub_assign(&mut self, other: Vect3){
		self.x -= other.x;
		self.y -= other.y;
		self.z -= other.z;
	}
}

//num * Vect3
/*el tipo va cruzado. Quiero decir que para poner num(f32) x Vect3, Vect3 debe ir
a la izquierda y f32 a la derecha como está aqui (for f32 a la derecha).
Ello (el for) es el que define que tipo es el "self" en este caso self es un f32 por 
lo que no lleva un .x ni ningun dato de la estructura de Vect3, pero en el de abajoç
(Vect3 * n) el Vect3 va en el "for" por lo que el self es un Vect3 y ha de accederse
a sus variables por el .x .y o .z*/
impl Mul<Vect3> for f32{
	type Output = Vect3;
	fn mul(self, other: Vect3) -> Vect3{
		return Vect3 {x: self * other.x, y: self * other.y, z: self * other.z}; 
	}
}

//Vect3 * n
impl Mul<f32> for Vect3{
	type Output = Vect3;
	fn mul(self, n: f32) -> Vect3{
		return Vect3 {x: self.x * n, y: self.y * n, z: self.z * n}; 
	}
}

//*=
impl MulAssign<f32> for Vect3{
	fn mul_assign(&mut self, n: f32){
		self.x *= n;
		self.y *= n;
		self.z *= n;
	}
}

// division
impl Div<f32> for Vect3{
	type Output = Vect3;
	fn div(self, n: f32) -> Vect3{
		if n == 0 as f32{ //casteo
			return self;
		}
		Vect3 {x: self.x / n, y: self.y / n, z: self.z / n}
	}
}

// /=
impl DivAssign<f32> for Vect3{
	fn div_assign(&mut self, n: f32){
		if n == 0 as f32{
			return;
		}
		self.x /= n;
		self.y /= n;
		self.z /= n;
	}
}



