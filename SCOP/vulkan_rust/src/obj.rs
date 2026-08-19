/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.rs                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 11:39:29 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/19 12:07:21 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

pub use crate::vect3::Vect3; //pub to be included in main with obj
use std::collections::BTreeMap;

#[derive(Clone)] //copy not authorized in BTreeMap because it is in HEAP mem
pub struct Obj{
	_points: BTreeMap<usize, Vect3>
}

impl Obj{
	pub fn new(points: BTreeMap<usize, Vect3>) -> Self{
		Obj{_points: points,}
	}
}
