/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obj.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 12:27:35 by jrollon-          #+#    #+#             */
/*   Updated: 2026/08/18 14:05:06 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_HPP
# define OBJ_HPP

# include "Interface.hpp"
# include "Vect3.hpp"
# include <map>

using VMAP = std::map<size_t, Vect3>;

class Obj : public Interface{
	private:
		VMAP	_points;

	public:
		Obj(void);
		Obj(VMAP points);
		Obj(const Obj &other);
		Obj& operator=(const Obj &other);
		~Obj(void);

		const VMAP&	get_points(void) const;

		void	stream_insert(std::ostream &out) const override;
};

#endif
