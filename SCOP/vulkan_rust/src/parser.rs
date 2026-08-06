/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.rs                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 17:27:18 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/06 22:27:48 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

use std::str::SplitWhitespace;
/*Aqui tenemos la linea de cada obj. para parsearlo, en
C++ usamos el istringstream, que separaba los espacios

como tokens. Aqui vamos a usar algo parecido:
std::str::SplitWhiteSpace siendo un iterador

let mut word = line.split_whitespace()
if let Some(vertex_type) = word.next(){
    if vertex_type != "v"
        return;
    else
        consumimos cada x y z como .next() y .parse::<f32>()
}
    NOTA: .parse::<f32>() es la forma de convertir de texto
    a numero como si fuera un atof. por ejemplo:
    let txt = "3.14";
    let num = txt.parse::<f32>(); que devuelve un Result
    OK(3.14) o Err si no era válido
*/
pub fn parser_line(line: String){
    let mut word = line.split_whitespace();
    if let Some(vertex_type) = word.next(){
        if vertex_type != "v"{
            return ;
        }
        else {
            println!("{}", line);           
        }
    }
    
}