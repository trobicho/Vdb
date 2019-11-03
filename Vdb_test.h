/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vdb_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:06:37 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/03 03:10:26 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libvdb.h"

struct	s_vec3i
{
	int32_t	x, y, z;
};

using	Leaf = Leaf_node<uint32_t, 3>;
using	Internal_L2 = Internal_node<uint32_t, Leaf, 4>;
using	Internal_L1 = Internal_node<uint32_t, Internal_L2, 6>;

class	Vdb_test
{
	public:
		Vdb_test();
		~Vdb_test(){};

		void		set_vox(uint32_t value, s_vec3i v);
		uint32_t	get_vox(s_vec3i v);

	private:
		Internal_L1	m_root_static = Internal_L1(4096, 4096, 4096);
		s_vec3i		m_min = (s_vec3i){0, 0, 0};
		s_vec3i		m_max = (s_vec3i){8192, 8192, 8192};
};
