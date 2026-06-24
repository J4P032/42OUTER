/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.rs                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:36:12 by jrollon-          #+#    #+#             */
/*   Updated: 2026/06/24 12:41:53 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

mod	vect3; //debe ser en minuscula y el file en minuscula.. ya la variable mayuscula si se quiere
//use crate::vect3::Vect3; //para no usar los vect3::Vect3 y solo Vect3.

fn print_vector(a: &vect3::Vect3){
	//{} es como % en printf. Para imprimir las llaves seria {{}} -> {}
	println!("x: {}, y: {}, z: {}", a.x, a.y, a.z); //si le pongo {2} un numero imprimira ese indice saltandose el orden.
}

fn main(){
	//let args = std::env::args(); es el argc y argv Es un iterador
	let mut v1 = vect3::Vect3 { x: 0.0, y: 0.0, z: 0.0 }; //let = deja, asigna a la variable. Siempre se le da valor
	let v2 = vect3::Vect3 { x: 1.0, y: 2.0, z: 3.0 };
	let v3 = vect3::Vect3 { x: 1.0, y: 2.0, z: 3.0 };
	print_vector(&v1);
	print_vector(&v2);
	print_vector(&v3);
	v1 = v3;
	print_vector(&v1);
	v1 = v2 + v3;
	print_vector(&v1);
	v1 = v1 - v1;
	print_vector(&v1);
}
