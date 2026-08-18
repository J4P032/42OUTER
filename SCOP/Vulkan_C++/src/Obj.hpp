/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obj.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 12:27:35 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/18 15:57:27 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_HPP
# define OBJ_HPP

# include "Interface.hpp"
# include "Vect3.hpp"
# include <map>
# include <vector>

using VMAP = std::map<size_t, Vect3>;
using VINDEX = std::vector<uint32_t>; //size_t not managed by vulkan. vector of face indexes

class Obj : public Interface{
	private:
		VMAP	_points;
		VINDEX	_polygon_indexes;
		
	public:
		Obj(void);
		Obj(VMAP points, VINDEX polygon_indexes);
		Obj(const Obj &other);
		Obj& operator=(const Obj &other);
		~Obj(void);

		void	stream_insert(std::ostream &out) const override;
};

#endif
