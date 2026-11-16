/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.rs                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 12:09:35 by jrollon-          #+#    #+#             */
/*   Updated: 2026/11/16 15:24:41 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#![allow(warnings)] //remove warning msg.
/*This is the files of the project to be included to find the .rs files.
It does not to be included (mod) in any main file. Cargo pick up itself when is created.*/
pub mod	vect3; 
pub mod parser;
pub mod obj;
pub mod matrix;
