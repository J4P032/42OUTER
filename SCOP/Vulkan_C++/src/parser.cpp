/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 11:13:35 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/18 18:34:24 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"

/*El istrinstream parsea al tipo que se le dice saltandose
los espacios por tokens. si hay fallo dara el iss(words) como falso pero puede
haber basura por ejemplo:
v 1 2 3 8
en ese caso words >> extra seria true y nos salimos por que es linea no valida*/
void	store_obj_data(const std::string& line, Obj& obj3D){
	std::string			type;
	std::istringstream	words(line); //conecta el line con el iss words
	float				x, y, z;
	std::string			something;
	size_t				num_tokens = 0;
	
	while(words >> something)
		num_tokens++;
	if (num_tokens < 4 || num_tokens > 5) //only 3-4 vertex polygons consider
		return;
	//reset to come back to beginning
	words.clear(); //clean EOF
	words.seekg(0); //move cursor to beginning
	
	words >> type;
		
	//POINTS	
	if (type == "v"){
		words >> x >> y >> z;
		if (words >> something) //not necesary data
			return;
		Vect3	aux(x,y,z);
		size_t	num = obj3D.get_map_size();
		obj3D.insert_vert3(num + 1, aux);
	}

	//FACES
	if (type == "f"){
		std::string	sub_token; //for groups as 1/1/2. tokens = 1, 1, 2
		 
		size_t		num_vertex = 1;
		uint32_t	first = 0;
		uint32_t	third = 0;
		
		while (words >> something){
			std::istringstream stream_token(something);
			size_t		num_sub_token = 0;
			while (std::getline(stream_token, sub_token, '/')){ //case f 1/1/2 -> vertex/texture/normal
				if (num_sub_token == 0){ //vertex
					if (num_tokens == 5 && num_vertex == 1) //4 vertex
						first = std::stoi(sub_token);
					if (num_tokens == 5 && num_vertex == 3)
						third = std::stoi(sub_token);
					if (num_vertex < 4) //the 4th has to be introduced after previous first and third
						obj3D.insert_findex(std::stoi(sub_token));
					else{ //subdivide of 4 vertex to 2 triangles. This is 2nd triangle
						obj3D.insert_findex(first);
						obj3D.insert_findex(third);
						obj3D.insert_findex(std::stoi(sub_token));
					}
					num_sub_token++;
				}
				if (num_sub_token == 1){ //texture coordinates
					
					num_sub_token++;
				}
				if (num_sub_token == 2){ //normal
					
					num_sub_token++;
				}
				//num_sub_tocken > 2 will be ignored
			}
			num_vertex++;
		}
	}
	
}
