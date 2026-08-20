/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.rs                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 17:27:18 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/20 15:13:27 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

use crate::obj::{Obj, Vect3};
use std::str::SplitWhitespace; //to be accepted as parameter in functions.

/*4 vertex polygon (5 num_tokens)
		we will need to make triangulation as Vulkan only accept that.
		if we have "f 1 2 3 4" will be 2 triangles -> 1 2 3, 1 3 4
		So in the 4th vertex we previous to that, store the 1st and 3rd first of previous triangle
		so we need to save those numbers.*/
fn	store_triangle_points(
	obj3d: &mut Obj,
	valor: u32,
	num_tokens: usize,
	vertex_number: usize,
	first: &mut u32,
	third: &mut u32
){
	//4 vertex
	if num_tokens == 5{
		if vertex_number == 1{
			*first = valor;
		} else if vertex_number == 3{
			*third = valor;
		}
						
		//store triangles points
		//1. first 3 vertex
		if vertex_number < 4{
			obj3d.vec_insert(valor);											
		} else { //2. when there is a 4th vertex: store 1st, 3rd, 4th
			obj3d.vec_insert(*first);
			obj3d.vec_insert(*third);
			obj3d.vec_insert(valor);
		}
	} else { //3 vertex only
		obj3d.vec_insert(valor);
	}
}


fn	store_faces(obj3d: &mut Obj, word: &mut SplitWhitespace, num_tokens: usize){
	let mut vertex_number: usize = 1;
	let mut first: u32 = 0;
	let mut third: u32 = 0;
		
	while let Some(something) = word.next(){
		let mut num_sub_token: usize = 0;
		let mut sub_token = something.split('/'); //case f 1/1/2 -> vertex/texture/normal
		while let Some(sub_token) = sub_token.next(){ 
			
			//vertex
			if num_sub_token == 0{
				if let Ok(valor) = sub_token.parse::<u32>(){
					store_triangle_points(obj3d, valor, num_tokens, vertex_number, &mut first, &mut third);
					num_sub_token += 1;
				}
			}
			
			//texture coordinates
			if num_sub_token == 1{
				num_sub_token += 1;
			}
			
			//normals
			if num_sub_token == 2{
				num_sub_token += 1;
			}
			//num_sub_tocken > 2 will be ignored					
		}
		vertex_number += 1;
	}
}



/*NOTE:
.parse::<f32>() is like atof o stof. example:
    let txt = "3.14";
    let num = txt.parse::<f32>(); returns a Result
    OK(3.14) or Err if it wasn't valid.
	If we used x: word.next().parse::<f32>().unwrap() could panic, but we want
	to only to ignore that line	*/
fn	store_vertex(obj3d: &mut Obj, word: &mut SplitWhitespace){

	let parse = |s: &str| s.parse::<f32>(); //closure function!! :) to make it short & clean

	if let (Some(x_str), Some(y_str), Some(z_str)) = (word.next(), word.next(), word.next()){
		if let (Ok(x), Ok(y), Ok(z)) = (parse(x_str), parse(y_str), parse(z_str)){
			let v = Vect3::new(x, y, z);
			let i = obj3d.map_len();
			obj3d.map_insert(i, v);	
		}
	}
}


/*Here we have the line of each obj. To parser it in C++ we use istringstream.
here we are going to use std::str::SplitWhiteSpace that is an iterator*/
pub fn store_obj_data(line: String, obj3d: &mut Obj){
	let num_tokens = line.split_whitespace().count(); //runs all the iterator
	
	//only 3-4 vertex polygons considered
	if num_tokens < 4 || num_tokens > 5{ 
		return;
	}
	
	let mut word = line.split_whitespace();
	
	if let Some(label) = word.next(){ // .next() is an Option.
		
		//POINTS
		if label == "v"{
			store_vertex(obj3d, &mut word);
		}

		//FACES
		if label == "f"{
			store_faces(obj3d, &mut word, num_tokens);
		}
	}
}






