/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Workshop.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 17:11:26 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/30 18:19:03 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORKSHOP_HPP
# define WORKSHOP_HPP

#include "Worker.hpp"
#include "Tool.hpp"


class Workshop {
private:
	std::vector<Worker*>	workers;	

public:

	void	signIn(const Worker& worker) {(void)worker;}
	void	leave(const Worker& worker) {(void)worker;}
};


#endif
