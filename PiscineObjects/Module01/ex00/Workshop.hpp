/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Workshop.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 17:11:26 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/02 12:47:02 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORKSHOP_HPP
# define WORKSHOP_HPP

#include "Worker.hpp"
#include "Tool.hpp"


class Workshop {
private:
	size_t					id;
	static size_t			id_counter;
	std::vector<Worker*>	workers;	

public:
	Workshop(void);
	Workshop(const Workshop& other);
	Workshop& operator=(const Workshop& other);
	


	void	signIn(const Worker& worker);
	void	leave(const Worker& worker);
};


#endif
