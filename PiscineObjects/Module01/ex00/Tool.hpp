/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tool.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 14:11:28 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/30 12:34:47 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOL_HPP
# define TOOL_HPP

# include <iostream>
# include <vector>
# include <algorithm>

#define RESET "\033[0m"
#define BLACK "\033[30m"
#define RED "\033[38;2;255;0;0m"
#define GREEN "\033[38;2;0;255;0m"
#define YELLOW "\033[38;5;226m"
#define BLUE "\033[38;2;0;100;255m"
#define MAGENTA "\033[38;2;100;50;255m"
#define CYAN "\033[38;2;0;200;255m"
#define WHITE "\033[37m"

class Worker;

class Tool {
public:
	Tool(){}
	virtual ~Tool(){}

	virtual void use(Worker* w) = 0;
	virtual void liberateTool(void) = 0;
};


#endif
