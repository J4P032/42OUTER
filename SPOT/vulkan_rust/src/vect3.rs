/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect3.rs                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/22 11:18:59 by jrollon-          #+#    #+#             */
/*   Updated: 2026/06/23 13:08:21 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Se necesita hacer Copy porque si no, al hacer:

let v1 = v2;

se produce un MOVE.

Eso significa que la propiedad del valor pasa de v2 a v1,
y v2 deja de ser válido.

Con Copy, en vez de mover, se copia el valor, y ambos
pueden seguir usándose independientemente. */
#[derive(Copy, Clone)]
pub struct	Vect3{ //x defecto struct es privado. Pub lo expone a publico
	pub x: f32, //f32 o f64 32 o 64 bits float.
	pub y: f32,
	pub z: f32,
}


