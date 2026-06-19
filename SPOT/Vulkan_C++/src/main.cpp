/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrollon- <jrollon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 13:18:17 by jrollon-          #+#    #+#             */
/*   Updated: 2026/06/19 13:27:19 by jrollon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vect3.hpp"

int main(void){
    Vect3   v1;
    Vect3   v2(1.0, 2.0, 3.0);
    Vect3   v3(v2);
    std::cout << "v1 = " << v1 << std::endl;
    std::cout << "v2 = " << v2 << std::endl;
    std::cout << "v3 = " << v3 << std::endl;
    v1 = v3;
    std::cout << "v1mod = " << v1 << std::endl;
    return (0);
}