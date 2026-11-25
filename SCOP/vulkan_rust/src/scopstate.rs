/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scopstate.rs                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/25 14:02:56 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/25 15:33:17 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

use std::f32::consts::PI;
use std::time::Instant;

pub struct ScopState{
	start_time: Instant,
	y_angle:	f32,
} 

//----------------------------------------------
//----------------------------------------------

impl ScopState{
	pub fn new() -> Self{
		Self{
			start_time: Instant::now(),
			y_angle: 0.0,
		}
	}
}

//getters
impl ScopState{
	pub fn get_start_time(&self) -> Instant{
		self.start_time
	}
	
	pub fn get_y_angle(&self) -> f32{
		self.y_angle
	}
}

//setters
impl ScopState{
	pub fn grab_time(&mut self){
		self.start_time = Instant::now();
	}

	pub fn set_y_angle(&mut self, seconds: std::time::Duration){
		self.y_angle += seconds.as_secs_f32() * PI;
		self.y_angle %= 2.0 * PI;
	}

}



