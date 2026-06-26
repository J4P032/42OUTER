/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.rs                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:36:12 by jrollon-          #+#    #+#             */
/*   Updated: 2026/06/26 17:40:16 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

use std::process::ExitCode; //codigo de salida en main
use std::fs::File; //abrir archivo
use std::io::BufReader; //leer archivo abierto.
use std::io::BufRead;


mod	vect3; //debe ser en minuscula y el file en minuscula.. ya la variable mayuscula si se quiere
//use crate::vect3::Vect3; //para no usar los vect3::Vect3 y solo Vect3.

fn _print_vector(a: &vect3::Vect3){
	//{} es como % en printf. Para imprimir las llaves seria {{}} -> {}
	println!("x: {}, y: {}, z: {}", a.x, a.y, a.z); //si le pongo {2} un numero imprimira ese indice saltandose el orden.
}

fn process_file(str: &str) -> Result<(), &'static str>{
	if let Ok(input_file) = File::open(str){ // tras el open es un Result<File, std::io::error>
		let _reader = BufReader::new(input_file); //el _ para si no la uso no warning compilador
		for line in _reader.lines(){
			/* _reader.lines() devuelve un ITERADOR line y cada uno de ellos devuelve un
			 Result<String, error> para averiguarlo podemos usar:
			
			let line = match line {
				Ok(value) => value,
				Err(e) => return Err("Error: Error Reading the file\n"),
			};
			HAY UNA FORMA MAS SENCILLA DE HACERLO EN RUST CON UNA LINEA (la siguiente):
				let line = line?;
			que esto pregunta con el '?' si es Ok suelta el line y si no un Err pero ese
			Err seria de tipo std::io::error y no &'static str como es y fallaria compilar
			para ello mapeamos el error con map_err pero este método necesita una funcion
			recibe el error std::io::error y devuelve un &str. yo le digo me da igual loque
			recibo, solo devuelveme y string: |e| uso el error. |_| ignoro el error.
			|_| es una closure que se puede ver en los apuntes de Rust y que en si son los
			parametros. Una funcion Closure es como : |parametros| implementacion.
			*/
			let line = line.map_err(|_| "Error: Error Reading the file\n")?;
		}
		return Ok(());
	} else {
		return Err("Error: Couldn't open the OBJ file\n");
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
fn scop(args: Vec<String>) -> Result<(), &'static str>{
	if args.len() != 2{
		return Err("Error: Not enough parameters. Use: spot file.obj\n");
	}
	if let Err(e) = process_file(&args[1]){
		return Err(e);
	}


	Ok(())
}

fn main() -> ExitCode {
	/*let args = std::env::args(); //argc y argv. Es un iterador.
	pero con el iterador no podemos saber el numero de elementos que tiene
	para imitar el argc, obtenemos el iterador y lo metemos en un vector dinámico:
	argc == args.len() 
	argv[0] (nombre del programa) = args[0] */
	let args: Vec<String> = std::env::args().collect();
	if let Err(err) = scop(args){
		println!("{}", err);
		return ExitCode::from(1); //hace drop (llama destructores)
		//std::process::exit(1); //no hace drop
	}
	ExitCode::from(0)
	/*
	let mut v1 = vect3::Vect3 { x: 0.0, y: 0.0, z: 0.0 }; //let = deja, asigna a la variable. Siempre se le da valor
	let v2 = vect3::Vect3 { x: 1.0, y: 2.0, z: 3.0 };
	let v3 = vect3::Vect3 { x: 1.0, y: 2.0, z: 3.0 };
	print_vector(&v1);
	print_vector(&v2);
	print_vector(&v3);
	v1 = v3;
	v1 *= 4.0;
	print_vector(&v1);
	v1 /= 2.0;
	print_vector(&v1);
	*/
}
