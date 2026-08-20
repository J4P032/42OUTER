/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.rs                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 17:27:18 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/20 14:26:04 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

use crate::obj::{Obj, Vect3};
use std::str::SplitWhitespace; //to be accepted as parameter in functions.

/*NOTE:
.parse::<f32>() is like atof o stof. example:
    let txt = "3.14";
    let num = txt.parse::<f32>(); returns a Result
    OK(3.14) or Err if it wasn't valid.
	If we used x: word.next().parse::<f32>().unwrap() could panic, but we want
	to only to ignore that line	*/
fn	store_vertex(obj3d: &mut Obj, word: &mut SplitWhitespace){
	if let (Some(x_str), Some(y_str), Some(z_str)) = (word.next(), word.next(), word.next()){
		if let (Ok(x), Ok(y), Ok(z)) = (x_str.parse::<f32>(), y_str.parse::<f32>(), z_str.parse::<f32>()){
			let v = Vect3::new(x, y, z);
			let i = obj3d.map_len();
			obj3d.map_insert(i, v);	
		}
	}
}


/*Aqui tenemos la linea de cada obj. para parsearlo, en
C++ usamos el istringstream, que separaba los espacios
como tokens. Aqui vamos a usar algo parecido:
std::str::SplitWhiteSpace siendo un iterador
*/
pub fn parser_line(line: String, obj3d: &mut Obj){
	let num_tokens = line.split_whitespace().count(); //runs all the iterator
	
	if num_tokens < 4 || num_tokens > 5{ //only 3-4 vertex polygons considered
		return;
	}
	
	let mut word = line.split_whitespace(); //iterator. Separate tokens by spaces or tabs
	if let Some(label) = word.next(){ //is an Option.
		
		//POINTS
		if label == "v"{
			store_vertex(obj3d, &mut word);
		}

		//FACES
		if label == "f"{
			let mut num_vertex: usize = 1;
			let mut first: u32 = 0;
			let mut third: u32 = 0;
		
			while let Some(something) = word.next(){
				let mut num_sub_token: usize = 0;
				let mut sub_token = something.split('/'); //case f 1/1/2 -> vertex/texture/normal
				while let Some(sub_token) = sub_token.next(){ 
					//vertex
					if num_sub_token == 0{
						if let Ok(valor) = sub_token.parse::<u32>(){

							//4 vertex
							if num_tokens == 5{
							
								if num_vertex == 1{
									first = valor;
								} else if num_vertex == 3{
									third = valor;
								}
								
								//the 4th has to be introduced ONLY after previous first and third
								if num_vertex < 4{
										obj3d.vec_insert(valor);											
								} else { //subdivide of 4 vertex to 2 triangles. This is 2nd triangle
									obj3d.vec_insert(first);
									obj3d.vec_insert(third);
									obj3d.vec_insert(valor);
								}
							
							} else { //3 vertex
								obj3d.vec_insert(valor);
							}
						num_sub_token += 1;
						}
					}
					
					//texture coordinates
					if num_sub_token == 1{
						num_sub_token += 1;
					}
					//normal
					if num_sub_token == 2{
						num_sub_token += 1;
					}
					//num_sub_tocken > 2 will be ignored					
				}
				num_vertex += 1;
			}
		}
	}
}






