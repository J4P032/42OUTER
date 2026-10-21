/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/21 14:05:05 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/21 14:07:51 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "utils.hpp"

#ifdef USING_SDL2
	#include <SDL2/SDL.h> //para SDL2 instalado en 42.
#else
	#include <SDL3/SDL.h>
#endif


#include <fstream>
#include <sstream>

void showError(SDL_Window *window, const std::string &errorMessasge)
{
}

std::string readTextFile(const std::string &filePath)
{
	std::ifstream infile(filePath);
	if (infile.is_open())
	{
		std::stringstream buffer;
		buffer << infile.rdbuf();
		const std::string output = buffer.str();
		infile.close();
		return output;
	}
	return std::string();
}
