/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 06:02:59 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/07 16:01:30 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <thread>
#include <SDL2/SDL.h>
#include "Vdb_test.h"
#include "camera.h"
#include "Ray.h"

#define SAMPLING	5
#define NB_THREAD	8

class	Renderer
{
	public:
		Renderer(Vdb_test &vdb, int w, int h);
		~Renderer();

		void	render_loop();
		void	ray_launch_all();
		void	ray_launch_thread(int tid);
		s_vec3	get_color(Ray &ray);
		void	check_event();
		void	refresh();
		s_vec3	pixel_to_rd(int x, int y);
		void	reset_pixels_buffer(Uint32 color = 0x0);

	private:
		int				m_width;
		int				m_height;
		SDL_Window		*m_win;
		SDL_Renderer	*m_renderer;
		SDL_Texture		*m_texture;
		Uint32			*m_pixels_buffer;

		Vdb_test		&m_vdb;
		bool			m_quit = false;
		Camera			m_cam;
		bool			m_render_tree = false;
		std::thread		m_thread[NB_THREAD];
};
