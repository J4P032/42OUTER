/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thuesdayDiscount.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 16:24:46 by jrollon-          #+#    #+#             */
/*   Updated: 2026/10/15 11:24:50 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THUESDAYDISCOUNT_HPP
# define THUESDAYDISCOUNT_HPP

# include "command.hpp"

class ThuesdayDiscountCommand : public Command {
	private:
		const Command&	command;

	public:
	ThuesdayDiscountCommand(const Command& c) : command(c) {}

	float	get_total_price() const{
		float total = command.get_total_price();
		total -= discount(total);
		return total;
	}

	float discount(float price) const { 
		return ( price / 10.0f );	
	}
};

#endif
