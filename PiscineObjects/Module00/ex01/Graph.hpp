/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Graph.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 17:49:46 by jrollon-          #+#    #+#             */
/*   Updated: 2026/09/29 10:38:52 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPH_HPP
# define GRAPH_HPP

# include <vector>
# include "Vect2.hpp"


class Graph {
private:
	Vect2				size;
	std::vector<Vect2>	list;

public:
	Graph(void);
	Graph(float width, float height);
	Graph(const Graph& other);
	Graph& operator=(const Graph& other);
	~Graph();

	void	add_point(const Vect2& point);
	void	print_graph() const;
};

#endif
