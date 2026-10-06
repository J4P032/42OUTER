/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Shovel.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 13:59:03 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/06 18:10:12 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHOVEL_HPP
# define SHOVEL_HPP

# include "Tool.hpp"
# include "Worker.hpp"


class Shovel : public Tool {
private:
	size_t			id;
	static size_t	id_counter;
	size_t			numberOfUses;
	Worker*			worker_assigned;
	friend struct	Garbage;
	

public:
	Shovel();
	Shovel(const Shovel& other);
	Shovel& operator=(const Shovel& other);
	~Shovel();

	void	liberateTool(void);
	void	use(Worker* w);
	size_t	getid() const;

	void	stream_insert(std::ostream& out) const;
};

#endif
