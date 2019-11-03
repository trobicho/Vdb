/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 20:39:09 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/03 06:58:31 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Renderer.h"
#include "Vdb_test.h"

int	main(int ac, char **av)
{
	Vdb_test	my_vdb;
	Renderer	renderer(my_vdb, 800, 600);

	my_vdb.set_vox(1, (s_vec3i){0, 0, 0});
	my_vdb.set_vox(2, (s_vec3i){0, 1, 1});
	my_vdb.set_vox(3, (s_vec3i){0, 2, 2});
	my_vdb.set_vox(9, (s_vec3i){5, 9, 3});
	my_vdb.set_vox(9, (s_vec3i){5, 8, 3});
	for (int z = 0; z < 4; z++)
	{
		for (int y = 0; y < 10; y++)
		{
			for (int x = 0; x < 10; x++)
				std::cout << my_vdb.get_vox((s_vec3i){x, y, z}) << " ";
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	renderer.render_loop();

	return (0);
}
