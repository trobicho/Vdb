/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 20:39:09 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/05 07:52:00 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Renderer.h"
#include "Vdb_test.h"
#include "my_lib.h"

int	main(int ac, char **av)
{
	Vdb_test	my_vdb;
	Renderer	renderer(my_vdb, 800, 600);
	auto&		mt = trl::req_mt_ref();
	std::uniform_int_distribution<int>
			dis(0, 1000);

	for (int z = 0; z < 300; z++)
	{
		for (int y = 0; y < 300; y++)
		{
			for (int x = 0; x < 300; x++)
			{
				int d = trl::rand_uniform_int(0, 100);
				if (d == 1)
					my_vdb.set_vox(1, s_vec3i(x + 1000, y + 1000, z + 1000));
			}
		}
	}
	/*
	for (int n = 0; n < 1000000; n++)
	{
		my_vdb.set_vox(1, s_vec3i(dis(mt), dis(mt), dis(mt)));
	}
	*/
	renderer.render_loop();

	return (0);
}
