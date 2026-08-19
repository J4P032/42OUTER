/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.rs                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 17:27:18 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/19 19:03:36 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//use std::str::SplitWhitespace; no hace falta ya que en String esta incorporado
use crate::obj::{Obj, Vect3};
/*Aqui tenemos la linea de cada obj. para parsearlo, en
C++ usamos el istringstream, que separaba los espacios

como tokens. Aqui vamos a usar algo parecido:
std::str::SplitWhiteSpace siendo un iterador
NOTA: .parse::<f32>() es la forma de convertir de texto a numero como si fuera
un atof. por ejemplo:
    let txt = "3.14";
    let num = txt.parse::<f32>(); que devuelve un Result
    OK(3.14) o Err si no era válido*/
pub fn parser_line(line: String, obj3d: &mut Obj){
	let num_tokens = line.split_whitespace().count(); //runs all the iterator
	
	if num_tokens < 4 || num_tokens > 5{ //only 3-4 vertex polygons considered
		return;
	}
	
	let mut word = line.split_whitespace(); //iterator. Separate tokens by spaces or tabs
	if let Some(label) = word.next(){ //is an Option.
		
		//POINTS
		/*puede fallar en linea x = 23.32e3 por ejemplo asi que usamos Some para next() y 
		Ok para .parse::<f32>() que es como hacer un atof().
		Si usasemos x: word.next().parse::<f32>().unwrap() podria hacer un panic, lo cual
		mal, por que solo queremos saltar dicha linea */
		if label == "v"{
			if let (Some(x_str), Some(y_str), Some(z_str)) = (word.next(), word.next(), word.next()){
				if let (Ok(x), Ok(y), Ok(z)) = (x_str.parse::<f32>(), y_str.parse::<f32>(), z_str.parse::<f32>()){
					let v = Vect3::new(x, y, z);
					let i = obj3d.map_len();
					obj3d.map_insert(i, v);	
				}
			}
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
						//4 vertex
						if num_tokens == 5{
							if let Ok(valor) = sub_token.parse::<u32>(){
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
							}
						} 
						num_sub_token += 1;
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

