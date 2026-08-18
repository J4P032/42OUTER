/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 11:13:35 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/18 16:11:42 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"

/*El istrinstream parsea al tipo que se le dice saltandose
los espacios por tokens. si hay fallo dara el iss(words) como falso pero puede
haber basura por ejemplo:
v 1 2 3 8
en ese caso words >> extra seria true y nos salimos por que es linea no valida*/
void	store_obj_data(const std::string& line, VMAP& objPoints, VINDEX& polygon_indexes){
	std::string			type;
	std::istringstream	words(line); //conecta el line con el iss words
	float				x, y, z;
	std::string			something;

	words >> type;
	if (!words)
		return;
	
	//POINTS	
	if (type == "v"){
		words >> x >> y >> z;
		if (words >> something) //not necesary data
			return;
		Vect3	aux(x,y,z);
		size_t	num = objPoints.size();
		objPoints.emplace(num + 1, aux);
	}

	//FACES only not lines supported (2 vertex only conected)
	if (type == "f"){
		std::string	token; //for groups as 1/1/2. tokens = 1, 1, 2
		size_t		num_token = 0;
		size_t		num_vertex = 0;
		while (words >> something){
			std::istringstream stoken(something);
			while (std::getline(stoken, token, '/')){ //case f 1/1/2 -> vertex/texture/normal
				if (num_token == 0){ //vertex
					polygon_indexes.push_back(std::stoi(token));
					num_token++;
				}
				if (num_token == 1){ //texture coordinates
					
					num_token++;
				}
				if (num_token == 2){ //normal
					
					num_token++;
				}
				//num_tocken > 2 will be ignored
			}
			num_vertex++;
		}
		
	}
	
}
