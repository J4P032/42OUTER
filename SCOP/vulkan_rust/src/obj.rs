/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.rs                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 11:39:29 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/23 14:06:53 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

pub use crate::vect3::Vect3; //pub to be included in main with obj
use std::collections::BTreeMap;

#[derive(Clone)] //copy not authorized in BTreeMap because it is in HEAP mem
pub struct Obj{
	_points: 			BTreeMap<usize, Vect3>,
	_polygon_indexes:	Vec<u32>,
	_center:			Vect3,
}

//constructors
impl Obj{
	pub fn empty() -> Self{
		Obj{ _points: BTreeMap::<usize, Vect3>::new(),
			_polygon_indexes: Vec::<u32>::new(),
			_center: Vect3::new(0.0, 0.0, 0.0),
		}
	}
}

impl Obj{
	pub fn new(points: BTreeMap<usize, Vect3>, polygon_indexes: Vec<u32>) -> Self{
		Obj{ _points: points, _polygon_indexes: polygon_indexes, _center: Vect3::new(0.0, 0.0, 0.0)}
	}
}

//getter
impl Obj{
	pub fn map_len(&self) -> usize{
		self._points.len() as usize
	}
}

impl Obj{
	pub fn get_points(&self) -> &BTreeMap<usize, Vect3> {
		&self._points
	}
}

impl Obj{
	pub fn get_polygon_indexes(&self) -> &Vec<u32> {
		&self._polygon_indexes
	}
}

impl Obj{
	pub fn mapa(&self) -> &BTreeMap<usize, Vect3>{
		&self._points
	}
}

impl Obj{
	pub fn vector(&self) -> &Vec<u32>{
		&self._polygon_indexes
	}
}

impl Obj{
	pub fn get_center(&self) -> &Vect3{
		&self._center
	}
}

//setter
impl Obj{
	pub fn map_insert(&mut self, i: usize, v: Vect3){
		self._points.insert(i, v);
	}
}

impl Obj{
	pub fn vec_insert(&mut self, i: u32){
		self._polygon_indexes.push(i);
	}
}


impl Obj{
	pub fn calculate_center(&mut self){
		if self._points.is_empty(){
			return;
		}
		let mut min_x = f32::MAX;
		let mut min_y = f32::MAX;
		let mut min_z = f32::MAX;
		let mut max_x = f32::MIN;
		let mut max_y = f32::MIN;
		let mut max_z = f32::MIN;

		for (_, num) in &self._points{
			let aux_x: f32 = (*num).x();
			let aux_y: f32 = (*num).y();
			let aux_z: f32 = (*num).z();
			
			if aux_x < min_x{
				min_x = aux_x;
			}
			if aux_y < min_y{
				min_y = aux_y;
			}
			if aux_z < min_z{
				min_z = aux_z;
			}
			if aux_x > max_x{
				max_x = aux_x;
			}
			if aux_y > max_y{
				max_y = aux_y;
			}
			if aux_z > max_z{
				max_z = aux_z;
			}
			
			self._center = Vect3::new(
				(max_x + min_x) / 2.0,
				(max_y + min_y) / 2.0,
				(max_z + min_z) / 2.0
			)
		} 
	}
}




impl Obj{
	pub fn write_me(&self){
		println!("POINTS:");
		for (_, punto) in &self._points{
			println!("x: {}, y: {}, z: {}", punto.x(), punto.y(), punto.z());
		}
		println!();
		println!("FACES:");
		
		for face in self._polygon_indexes.chunks(3) {
			println!("{} {} {}", face[0], face[1], face[2]);
		}
	}
}
