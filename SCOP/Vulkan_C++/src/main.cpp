/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 13:18:17 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/26 17:26:11 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Obj.hpp"
#include "parser.hpp"
#include "vulkan_init.hpp"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include <fstream>
#include <map>

Obj	process_file(char* str){
	std::ifstream	inputFile(str);
	if (!inputFile.is_open())
		throw std::runtime_error("Error: Couldn't open the OBJ file\n");
	std::string	line;
	Obj obj3D;

	while (std::getline(inputFile, line)){
		store_obj_data(line, obj3D);
	}
	
	//std::cout << obj3D << std::endl; //for testing good data.
	return obj3D;
}

void	scop(int ac, char** av){
	if (ac != 2)
		throw std::runtime_error("Error: Not enough parameters. Use: spot file.obj\n");
	Obj obj3D = process_file(av[1]);

	VulkanInit scop;
	if (scop.initialize(obj3D)) {
		scop.run();
	}
	scop.shutdown();
}

int	main(int ac, char** av){
	try{scop(ac, av);}
	catch (const std::runtime_error& err){
		std::cerr.write(err.what(), std::strlen(err.what()));
		return 1;
	}
	return 0;
}
