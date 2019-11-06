/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vdb_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:06:37 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/06 17:28:21 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "libvdb.h"

using	Leaf = Leaf_node<uint32_t, 3>;
using	Internal_L2 = Internal_node<uint32_t, Leaf, 4>;
using	Internal_L1 = Internal_node<uint32_t, Internal_L2, 6>;
using	Node_v = Node<uint32_t>;

class	Vdb_test
{
	public:
		Vdb_test();
		~Vdb_test(){};

		void		set_vox(uint32_t value, s_vec3i v);
		uint32_t	get_vox(s_vec3i v);
		void		pruning();
		const Node_v
					*get_interresting_node(s_vec3i v, uint32_t &value);

	private:
		Internal_L1	m_root_static = Internal_L1(4096, 4096, 4096);
		s_vec3i		m_min;
		s_vec3i		m_max;
};
