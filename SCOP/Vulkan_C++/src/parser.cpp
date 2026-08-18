/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 11:13:35 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/18 14:12:19 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"

/*El istrinstream parsea al tipo que se le dice saltandose
los espacios por tokens. si hay fallo dara el iss(words) como falso pero puede
haber basura por ejemplo:
v 1 2 3 8
en ese caso words >> extra seria true y nos salimos por que es linea no valida*/
void	store_obj_data(const std::string& line, VMAP& objPoints){
	std::string			type;
	std::istringstream	words(line); //conecta el line con el iss words
	float				x, y, z;
	std::string			extra;

	words >> type;
	if (!words)
		return;
	
	//POINTS	
	if (type == "v"){
		words >> x >> y >> z;
		if (words >> extra) //not necesary data
			return;
		Vect3	aux(x,y,z);
		size_t	num = objPoints.size();
		objPoints.emplace(num + 1, aux);
	}

	//FACES
	if (type == "f"){

		
	}
	
}
