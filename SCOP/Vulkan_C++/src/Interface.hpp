/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Interface.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 19:03:53 by jrollon-          #+#    #+#             */
/*   Updated: 2026/07/11 19:30:58 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<sstream>

#ifndef INTERFACE_HPP
# define INTERFACE_HPP

class	Interface{
	public:
		virtual void	stream_insert(std::ostream &out) const = 0;
		virtual ~Interface(void) = default;	
	
	friend std::ostream &operator<<(std::ostream &out, const Interface &operand){
		operand.stream_insert(out);
		return (out);
	}
};

#endif