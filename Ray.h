/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 01:57:17 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/05 07:53:14 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "vector.h"
#include "Vdb_test.h"
#define		MAX_DIST	500
#define		MAX_STEP	40

class	Ray
{
	public:
		Ray(s_vec3 ro, s_vec3 rd);
		~Ray(){};

		int				launch(Vdb_test &dvb);
		void			step();
		void			step(const Node_v *node);
		inline double	get_dist() const {return (m_d);};
		inline s_vec3i	get_pos() const {return (m_pos);};
		inline s_vec3	get_dir() const {return (m_rd);};
		double			calc_dist();

	private:
		s_vec3		m_ro;
		s_vec3		m_rd;
		s_vec3		m_delta_dist;
		s_vec3		m_side_dist;
		s_vec3i		m_pos;
		s_vec3i		m_step;
		double		m_d = 0.0;
		int			m_side;
};
