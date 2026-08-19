/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.rs                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 11:39:29 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/19 19:34:50 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

pub use crate::vect3::Vect3; //pub to be included in main with obj
use std::collections::BTreeMap;

#[derive(Clone)] //copy not authorized in BTreeMap because it is in HEAP mem
pub struct Obj{
	_points: 			BTreeMap<usize, Vect3>,
	_polygon_indexes:	Vec<u32>,
}

//constructors
impl Obj{
	pub fn empty() -> Self{
		Obj{ _points: BTreeMap::<usize, Vect3>::new(),
			_polygon_indexes: Vec::<u32>::new(),
		}
	}
}

impl Obj{
	pub fn new(points: BTreeMap<usize, Vect3>, polygon_indexes: Vec<u32>) -> Self{
		Obj{ _points: points, _polygon_indexes: polygon_indexes }
	}
}

//getter
impl Obj{
	pub fn map_len(&self) -> usize{
		self._points.len() as usize
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
