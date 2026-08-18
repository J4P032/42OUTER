/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obj.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 12:27:35 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/18 17:04:44 by jrollon-         ###   ########.fr       */
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

/*Vulkan solo admite triangulos. Por lo que un poligono tipo:
	f 1 2 3 4
Tiene que ser estructurado como dos triangulos:
	triangulo1: 1 2 3
	triangulo2: 1 3 4
Yo pensaba que deberia hacer un vector de vectores de indices, por que querria ver cada poligono
con sus indices formados. PERO VULKAN no lo trata asi:
Vulkan si recibe un vector como: 1 2 3 1 3 4 que seria los dos poligonos de arriba divididos
en triangulos, pillaria de 3 en 3 y compondria cada triangulo. 
Es importantisimo para buen rendimiento que los datos esten en memoria conjunta, y por eso se
debe usar un vector con todos los indices juntos. Eso si metiendolos por orden. 
eso sera el VINDEX	_polygon_indexes (std::vector<uint32_t> _polygon_indexes)*/
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

		size_t	get_map_size(void);
		void	insert_vert3(size_t, Vect3);
		
		void		insert_findex(uint32_t);
		uint32_t	show_last_findex(void);
		void		remove_findex(size_t);

		void	stream_insert(std::ostream &out) const override;
};

#endif
