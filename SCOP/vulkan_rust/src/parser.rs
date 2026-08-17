/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.rs                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 17:27:18 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/17 15:28:05 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//use std::str::SplitWhitespace; no hace falta ya que en String esta incorporado
use std::collections::BTreeMap;
use crate::vect3::Vect3;
/*Aqui tenemos la linea de cada obj. para parsearlo, en
C++ usamos el istringstream, que separaba los espacios

como tokens. Aqui vamos a usar algo parecido:
std::str::SplitWhiteSpace siendo un iterador
NOTA: .parse::<f32>() es la forma de convertir de texto a numero como si fuera
un atof. por ejemplo:
    let txt = "3.14";
    let num = txt.parse::<f32>(); que devuelve un Result
    OK(3.14) o Err si no era válido*/
pub fn parser_line(line: String, obj_points: &mut BTreeMap<u16, Vect3>){
	let mut word = line.split_whitespace(); //iterador
	if let Some(vertex_type) = word.next(){ //es un Option.
		if vertex_type != "v"{
			return ;
		}
		else {
			/*puede fallar en linea x = 23.32e3 por ejemplo asi que usamos Some para next() y 
			Ok para .parse::<f32>() que es como hacer un atof().
			Si usasemos x: word.next().parse::<f32>().unwrap() podria hacer un panic, lo cual
			mal, por que solo queremos saltar dicha linea
			*/
			if let (Some(x_str), Some(y_str), Some(z_str)) = (word.next(), word.next(), word.next()){
				if let (Ok(x), Ok(y), Ok(z)) = (x_str.parse::<f32>(), y_str.parse::<f32>(), z_str.parse::<f32>()){
					let v = Vect3 { x, y, z };
					let i = obj_points.len() as u16;
					obj_points.insert(i, v);	
				}
			}
		}
	}
}
