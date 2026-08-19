/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.rs                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 11:39:29 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/19 13:07:28 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

pub use crate::vect3::Vect3; //pub to be included in main with obj
use std::collections::BTreeMap;

#[derive(Clone)] //copy not authorized in BTreeMap because it is in HEAP mem
pub struct Obj{
	_points: BTreeMap<usize, Vect3>
}

impl Obj{
	pub fn empty() -> Self{
		Obj{ _points: BTreeMap::<usize, Vect3>::new() }
	}
}

impl Obj{
	pub fn new(points: BTreeMap<usize, Vect3>) -> Self{
		Obj{_points: points,}
	}
}

impl Obj{
	pub fn map_len(&self) -> usize{
		self._points.len() as usize
	}
}

impl Obj{
	pub fn map_insert(&mut self, i: usize, v: Vect3){
		self._points.insert(i, v);
	}
}

impl Obj{
	pub fn mapa(&self) -> &BTreeMap<usize, Vect3>{
		&self._points
	}
}
