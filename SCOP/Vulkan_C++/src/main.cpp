/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 13:18:17 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/18 15:57:44 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Obj.hpp"
#include "parser.hpp"
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
	VINDEX polygon_indexes; 
	while (std::getline(inputFile, line)){
		store_obj_data(line, objPoints, polygon_indexes);
	}
	Obj obj3D(objPoints, polygon_indexes);
	
	std::cout << obj3D << std::endl; //for testing good data.
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
