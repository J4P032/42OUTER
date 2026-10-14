/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thuesdayDiscount.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 16:24:46 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/14 18:26:26 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THUESDAYDISCOUNT_HPP
# define THUESDAYDISCOUNT_HPP

# include "command.hpp"


class ThuesdayDiscount : public Command {
public:
	ThuesdayDiscount(std::string name, std::string d) {
		client = name;
		date = d;
	}

	float discount(float price) const { 
		return ( price / 10.0f );		
	}
};

#endif
