/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tool.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 14:11:28 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/29 18:26:28 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOL_HPP
# define TOOL_HPP

class Worker;

class Tool {
public:
	Tool(){}
	virtual ~Tool(){}

	virtual void use(Worker* w) = 0;
};


#endif
