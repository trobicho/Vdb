/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 06:04:11 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/05 08:05:22 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Renderer.h"

#define SAMPLING	4

Renderer::Renderer(Vdb_test &vdb, int w, int h):
	m_vdb(vdb), m_width(w), m_height(h)
	, m_cam(s_vec3(1100, 1100, 900), s_vec3(0, 0, 1), s_vec3(0, 1, 0), s_vec3(1, 0, 0))
{
	m_win = SDL_CreateWindow("Vdb dda"
		, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED
		, m_width, m_height, SDL_WINDOW_OPENGL);
	std::cout << m_width << " " << m_height << std::endl;
	if (m_win == NULL)
		throw "Unable to create win";
	m_renderer = SDL_CreateRenderer(m_win, -1, SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == NULL)
		throw "Unable to create renderer";
	m_texture = SDL_CreateTexture(m_renderer
		, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING
		, m_width, m_height);
	if (m_texture == NULL)
		throw "Unable to create texture";
	if ((m_pixels_buffer
		= (Uint32*)malloc(sizeof(Uint32) * m_width * m_height)) == NULL)
		throw "Unable to create pixels buffer";
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
	SDL_RenderPresent(m_renderer);
}

Renderer::~Renderer()
{
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_win);
	SDL_Quit();
	free(m_pixels_buffer);
}

void	Renderer::render_loop()
{
	while (!m_quit)
	{
		ray_launch_all();
		refresh();
		check_event();
	}
}

void	Renderer::ray_launch_all()
{
	s_vec3	color;

	for (int y = 0; y < m_height; y += SAMPLING)
	{
		for (int x = 0; x < m_width; x += SAMPLING)
		{
			Ray	ray(m_cam.pos, pixel_to_rd(x, y));
			color = get_color(ray);
			for (int ys = 0; ys < SAMPLING
				&& y + ys < m_height; ys++)
			{
				for (int xs = 0; xs < SAMPLING
					&& x + xs < m_width; xs++)
				{
					m_pixels_buffer[x + xs + (y + ys) * m_width] =
						(Uint32)(color.x * 255) << 16
						| (Uint32)(color.y * 255) << 8 
						| (Uint32)(color.z * 255);
				}
			}
		}
	}
}

s_vec3	Renderer::get_color(Ray &ray)
{
	s_vec3	color;
	double	dist;
	s_vec3	min(0, 0, 0);
	s_vec3	max(5, 5, 5);

	color = ray.get_dir();
	color.x = (color.x + 1.0) / 2.0;
	color.y = (color.y + 1.0) / 2.0;
	color.z = (color.z + 1.0) / 2.0;
	if (ray.launch(m_vdb))
	{
		color = s_vec3(1, 1, 1);
		color = color.scalar(1.0 / (sqrt(ray.calc_dist() / 3.14 + 1.0)));
	}
	else
		color = s_vec3(0, 0, 0);
	return (color);
}

void	Renderer::check_event()
{
	SDL_Event	event;

	SDL_WaitEvent(&event);
	if (event.type == SDL_QUIT)
		m_quit = 1;
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE
				&& event.key.repeat == 0)
			m_quit = 1;
		else if (event.key.keysym.scancode == SDL_SCANCODE_W)
			m_cam.translate(s_vec3(0.0, 0.0, 5));
		else if (event.key.keysym.scancode == SDL_SCANCODE_A)
			m_cam.translate(s_vec3(-5, 0.0, 0.0));
		else if (event.key.keysym.scancode == SDL_SCANCODE_S)
			m_cam.translate(s_vec3(0.0, 0.0, -5));
		else if (event.key.keysym.scancode == SDL_SCANCODE_D)
			m_cam.translate(s_vec3(5, 0.0, 0.0));
		else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
			m_cam.rotate(m_cam.up, 3.14 / 45);
		else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
			m_cam.rotate(m_cam.up, -3.14 / 45);
		else if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)
			m_cam.rotate(m_cam.right, -3.14 / 45);
		else if (event.key.keysym.scancode == SDL_SCANCODE_UP)
			m_cam.rotate(m_cam.right, 3.14 / 45);
	}
}

s_vec3	Renderer::pixel_to_rd(int x, int y)
{
	double	d_s;
	s_vec3	rd;
	double	lx;
	double	ly;

	d_s = 1.0;
	lx = ((double)x / m_width) - 0.5;
	ly = ((double)y / m_height) - 0.5;
	rd.x = m_cam.right.x * lx + m_cam.up.x * ly + m_cam.dir.x * d_s;
	rd.y = m_cam.right.y * lx + m_cam.up.y * ly + m_cam.dir.y * d_s;
	rd.z = m_cam.right.z * lx + m_cam.up.z * ly + m_cam.dir.z * d_s;
	return (rd);
}

void	Renderer::refresh()
{
	SDL_UpdateTexture(m_texture, NULL
			, m_pixels_buffer, m_width * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

void	Renderer::reset_pixels_buffer(Uint32 color)
{
	for (int p = 0; p < m_width * m_height; p++)
	{
		m_pixels_buffer[p] = color;
	}
}
