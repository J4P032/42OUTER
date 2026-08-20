/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 11:13:35 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/20 14:01:17 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"


void	store_triangle_points(Obj& obj3D, std::string& sub_token, size_t num_tokens,
	size_t vertex_number, uint32_t& first, uint32_t& third){
	
	/*4 vertex polygon (5 num_tokens)
		we will need to make triangulation as Vulkan only accept that.
		if we have "f 1 2 3 4" will be 2 triangles -> 1 2 3, 1 3 4
		So in the 4th vertex we previous to that, store the 1st and 3rd first of previous triangle
		so we need to save those numbers.
		*/
	if (num_tokens == 5){
		if (vertex_number == 1)
			first = std::stoi(sub_token);
		if (vertex_number == 3)
			third = std::stoi(sub_token);		
	}
	
	//store triangles points
	//1. first 3 vertex
	if (vertex_number < 4)
		obj3D.insert_findex(std::stoi(sub_token));	
	//2. when there is a 4th vertex: store 1st, 3rd, 4th
	else { 
		obj3D.insert_findex(first);
		obj3D.insert_findex(third);
		obj3D.insert_findex(std::stoi(sub_token));
	}
}


void	store_faces(Obj& obj3D, std::istringstream& words, size_t num_tokens, std::string& something){
		std::string	sub_token; //for groups as 1/1/2. tokens = 1, 1, 2
		size_t		vertex_number = 1;
		uint32_t	first = 0;
		uint32_t	third = 0;
		
		while (words >> something){
			std::istringstream	stream_token(something);
			size_t				num_sub_token = 0;
			
			while (std::getline(stream_token, sub_token, '/')){ //case f 1/1/2 -> vertex/texture/normal. Separator is '/'
				
				//vertex
				if (num_sub_token == 0){
					store_triangle_points(obj3D, sub_token, num_tokens, vertex_number, first, third);
					num_sub_token++;
				}

				//texture coordinates
				if (num_sub_token == 1){
					
					num_sub_token++;
				}

				//normals
				if (num_sub_token == 2){
					
					num_sub_token++;
				}
				//num_sub_tocken > 2 will be ignored
			}
			vertex_number++;
		}
}

void	store_vertex(Obj& obj3D, std::istringstream& words, std::string& something){
	float		x, y, z;
	
	words >> x >> y >> z;
		if (words >> something) //not necesary data
			return;
		Vect3	aux(x,y,z);
		size_t	num = obj3D.get_map_size();
		obj3D.insert_vert3(num + 1, aux);
}

/*El istrinstream parsea al tipo que se le dice saltandose
los espacios por tokens. si hay fallo dara el iss(words) como falso pero puede
haber basura por ejemplo:
v 1 2 3 8
en ese caso words >> extra seria true y nos salimos por que es linea no valida*/
void	store_obj_data(const std::string& line, Obj& obj3D){
	std::string			type;
	std::istringstream	words(line); //conecta el line con el iss words
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
	if (type == "v")
		store_vertex(obj3D, words, something);

	//FACES
	if (type == "f")
		store_faces(obj3D, words, num_tokens, something);
}
