/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.rs                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:36:12 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/20 15:13:18 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

use std::process::ExitCode; //exit code in main, as return (1 or 0)
use std::fs::File; //open file
use std::io::BufReader; //read opened file
use std::io::BufRead;

use vulkan_rust::obj::{Obj, Vect3}; //allow "let a: vulkan_rust::obj::Obj;" -> "let a: Obj;"
use vulkan_rust::parser::store_obj_data;

fn _print_vector(a: &Vect3){
	println!("x: {}, y: {}, z: {}", a.x(), a.y(), a.z());
}

/* _reader.lines() devuelve un ITERADOR line y cada uno de ellos devuelve un
Result<String, error> para averiguarlo podemos usar:
			
let line = match line {
	Ok(value) => value,
	Err(e) => return Err("Error: Error Reading the file"),
};
HAY UNA FORMA MAS SENCILLA DE HACERLO EN RUST CON UNA LINEA (la siguiente):
	let line = line?;
que esto pregunta con el '?' si es Ok suelta el line y si no un Err pero ese
Err seria de tipo std::io::error y no &'static str como es y fallaria compilar
para ello mapeamos el error con map_err pero este método propio de Rust necesita
una funcion recibe el error std::io::error y devuelve un &str. yo le digo me da
igual lo que recibo, solo devuelveme y string: |e| uso el error. |_| ignoro el error.
|_| es una closure que se puede ver en los apuntes de Rust y que en si son los
parametros. Una funcion Closure es como : |parametros| implementacion.
*/
fn process_file(str: &str, obj3d: &mut Obj) -> Result<(), &'static str>{
	if let Ok(input_file) = File::open(str){ // open is a Result<File, std::io::error>
		let _reader = BufReader::new(input_file); //'_' no warning in compiler if not used
		for line in _reader.lines(){
			let line = line.map_err(|_| "Error: Error Reading the file")?; //if Err stops for
			store_obj_data(line, obj3d); //obj3d is already & as is &mut in function
		}
		return Ok(());
	} else {
		return Err("Error: Couldn't open the OBJ file");
	}
}

/* Result <T, K> donde T y K son tipos de variables (int, float, etc..)
	es 'algo' hecho en Rust que devuelve dos tipos de elementos:
	Ok(T) -> que está bien bajo devolviendo ese tipo T.
	Err(K) -> que está mal devolviendo ese tipo K
	Antes tenía:
	
	Result<(), String> 
	
	De tal forma que Ok devuelve void [Ok(())]
	y Err devuelve un String. Asi cuando devolviamos en Err era:
	
	Err("Error: Not enough...file.obj\n".to_string());

	Tenia que aplicarle el método .to_string() que lo que hace
	es copiar todo a un contenedor string. Por que ese mensaje
	entre comillas vive en el scope de la funcion y muere al 
	salir de ella. Se necesita reservar en el Heap para que viva
	y de ahi el .to_string() que lo mete en el contenedor.
	Pero eso reserva memoria. Se puede hacer que como en C:
	char* str = "hola"; que vive siempre en el programa en rust es:
	&'static str. donde el "'" indica "el tiempo de vida".
	En Rust 'static = para siempre dentro del programa.

	NOTA2: si hacemos

	process_file(args[1]); en C dejaría ya que es copia.. PERO
	EN RUST NO!!! por que es un MOVE. y no puede dejar al vector
	sin elementos. Asi que el compilador NO DEJA. para ello
	usamos una referencia. O hacemos 

	process_file(args[1].to_string())
 */
fn scop(args: &Vec<String>) -> Result<(), &'static str>{
	if args.len() != 2{
		return Err("Error: Not enough parameters. Use: spot file.obj");
	}
	let mut obj3d = Obj::empty();
	if let Err(e) = process_file(&args[1], &mut obj3d){
		return Err(e);
	}
	
	obj3d.write_me();
	
	Ok(())
}

fn main() -> ExitCode {
	/*let args = std::env::args(); //argc y argv. Es un iterador.
	pero con el iterador no podemos saber el numero de elementos que tiene
	para imitar el argc, obtenemos el iterador y lo metemos en un vector dinámico:
	argc == args.len() 
	argv[0] (nombre del programa) = args[0] */
	let args: Vec<String> = std::env::args().collect();
	if let Err(err) = scop(&args){
		println!("{}", err);
		return ExitCode::from(1); //do drop (call destructors)
		//std::process::exit(1); //no drop
	}
	ExitCode::from(0)
}
