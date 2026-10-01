/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hammer.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 18:26:52 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/01 14:14:18 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HAMMER_HPP
# define HAMMER_HPP

# include "Tool.hpp"
# include "Worker.hpp"

class Hammer : public Tool{
private:
	size_t			id;
	static size_t	id_counter;
	size_t			numberOfUses;
	Worker*			worker_assigned;

public:
	Hammer();
	Hammer(const Hammer& other);
	Hammer& operator=(const Hammer& other);
	~Hammer();

	void	liberateTool(void);
	void	use(Worker* w);
	size_t	getid() const;
	
	void stream_insert(std::ostream& out) const;
};

#endif
