/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vdb_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:06:27 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/03 03:10:22 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vdb_test.h"

Vdb_test::Vdb_test()
{
}

void		Vdb_test::set_vox(uint32_t value, s_vec3i v)
{
	if (v.x >= m_min.x && v.y >= m_min.y && v.z >= m_min.z
		&& v.x < m_max.x && v.y < m_max.y && v.z < m_max.z)
	{
		m_root_static.set_vox(value, v.x, v.y, v.z);
	}
}

uint32_t	Vdb_test::get_vox(s_vec3i v)
{
	if (v.x >= m_min.x && v.y >= m_min.y && v.z >= m_min.z
		&& v.x < m_max.x && v.y < m_max.y && v.z < m_max.z)
	{
		return (m_root_static.get_vox(v.x, v.y, v.z));
	}
	return (0);
}
