/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 20:39:09 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/11 01:43:48 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Renderer.h"
#include "Vdb_test.h"
#include "my_lib.h"
#include <SDL2/SDL_image.h>

static uint64_t	nb_vox = 0;

struct	s_vbox
{
	s_vec3i	origin;
	s_vec3i	len;
};

double	get_noise_value_from_img(SDL_Surface *surface, double x, double y)
{
	double	v;
	int ix = x * surface->w;
	int iy = y * surface->h;

	v = ((Uint8*)surface->pixels)[ix + iy * surface->w] / 255.0;
	return (v);
}

int		add_voxel_from_img(Vdb_test &vdb, const char *file_name, s_vbox box)
{
	SDL_Surface *img = IMG_Load(file_name);
	if (!img)
	{
		std::cout << SDL_GetError() << std::endl;
		return (1);
	}
	std::cout << "Bpp: " << img->format->BitsPerPixel << std::endl;
	for (int z = 0; z < box.len.z; ++z)
	{
		for (int x = 0; x < box.len.x; ++x)
		{
			double	d = get_noise_value_from_img(img, (double)x / box.len.x
				, (double)z / box.len.z);
			for (int y = 0; y < box.len.y * d + 1; ++y)
			{
				s_vec3i	vox(x, y, z);
				vox.x += box.origin.x;
				vox.y = (box.origin.y + box.len.y) - y;
				vox.z += box.origin.z;
				vdb.set_vox(1, vox);
				nb_vox++;
				if (nb_vox > 0 && nb_vox % 200000000 == 0)
				{
					vdb.pruning();
					std::cout << "prunning" << std::endl;
					std::cout << (z / (double)box.len.x) * 100.0 << "%"  << std::endl;
					std::cout << "total of " << nb_vox << " voxels." << std::endl;
				}
			}
		}
	}
	SDL_FreeSurface(img);
	return (0);
}

int		main(int ac, char **av)
{
	Vdb_test	my_vdb;
	Renderer	renderer(my_vdb, 700, 700);
	auto&		mt = trl::req_mt_ref();
	std::uniform_int_distribution<int>
			dis(0, 1000);
	s_vbox		box;

	IMG_Init(IMG_INIT_PNG);
	box.origin = s_vec3i(1000, 1000, 1000);
	box.len = s_vec3i(1000, 128, 1000);
	if (add_voxel_from_img(my_vdb, "./map_img/noise3d.png", box))
		return (1);
	IMG_Quit();
	my_vdb.pruning();
	std::cout << "total of " << nb_vox << " voxels." << std::endl;
	/*
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
	*/
	/*
	for (int n = 0; n < 1000000; n++)
	{
		my_vdb.set_vox(1, s_vec3i(dis(mt), dis(mt), dis(mt)));
	}
	*/
	renderer.render_loop();

	return (0);
}
