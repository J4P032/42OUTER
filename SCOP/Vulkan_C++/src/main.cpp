/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 13:18:17 by jrollon-          #+#    #+#             */
/*   Updated: 2026/06/25 17:02:23 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vect3.hpp"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <fstream>
#include <map>

void	process_file(char* str){
	std::ifstream	inputFile(str);
	if (!inputFile.is_open())
		throw std::runtime_error("Error: Couldn't open the OBJ file\n");
	std::string	line;
	VMAP objPoints; 
	while (std::getline(inputFile, line)){
		store_vertex(line, objPoints);
	}
	test_data(objPoints);

	
}


void	scop(int ac, char** av){
	if (ac != 2)
		throw std::runtime_error("Error: Not enough parameters. Use: spot file.obj\n");
	process_file(av[1]);
	
	
	
		
}

int	main(int ac, char** av){
	try{scop(ac, av);}
	catch (const std::runtime_error& err){
		std::cerr.write(err.what(), std::strlen(err.what()));
		return 1;
	}
	return 0;
}
