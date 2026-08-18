/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 11:10:42 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/18 14:12:10 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include "Obj.hpp"
# include <map>

using VMAP = std::map<size_t, Vect3>;

void	store_obj_data(const std::string& line, VMAP& objPoints);

#endif
