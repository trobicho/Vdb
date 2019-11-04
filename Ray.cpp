/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ray.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 01:58:54 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/04 08:58:18 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ray.h"

Ray::Ray(s_vec3 ro, s_vec3 rd): m_ro(ro), m_rd(rd)
{
	m_rd.normalize();
	m_delta_dist.x = abs(1.0 / m_rd.x);
	m_delta_dist.y = abs(1.0 / m_rd.y);
	m_delta_dist.z = abs(1.0 / m_rd.z);
	m_pos.x = (int)m_ro.x;
	m_pos.y = (int)m_ro.y;
	m_pos.z = (int)m_ro.z;
	m_step = s_vec3i(1, 1, 1);
	if (m_rd.x < 0)
	{
		m_step.x = -1.0;
		m_side_dist.x = (m_ro.x - m_pos.x) * m_delta_dist.x;
	}
	else
		m_side_dist.x = (m_pos.x + 1.0 - m_ro.x) * m_delta_dist.x;
	if (m_rd.y < 0)
	{
		m_step.y = -1.0;
		m_side_dist.y = (m_ro.y - m_pos.y) * m_delta_dist.y;
	}
	else
		m_side_dist.y = (m_pos.y + 1.0 - m_ro.y) * m_delta_dist.y;
	if (m_rd.z < 0)
	{
		m_step.z = -1.0;
		m_side_dist.z = (m_ro.z - m_pos.z) * m_delta_dist.z;
	}
	else
		m_side_dist.z = (m_pos.z + 1.0 - m_ro.z) * m_delta_dist.z;
}

int		Ray::launch(Vdb_test &vdb)
{
	int			s;
	uint32_t	found = 0;
	const Node_v		*node_ptr;

	for (int s = 0; s < MAX_STEP; s++)
	{
		node_ptr = vdb.get_interresting_node(m_pos, found);
		//node_ptr->get_log();
		if (found)
			return (found);
		else if (node_ptr == nullptr)
			return (0);
		if (calc_dist() > MAX_DIST)
			return (0);
		step();
	}
	return (0);
}

void	Ray::step()
{
	if (m_side_dist.x < m_side_dist.y && m_side_dist.x < m_side_dist.z)
	{
		m_side_dist.x += m_delta_dist.x;
		m_pos.x += m_step.x;
		m_side = 0;
	}
	else if (m_side_dist.y < m_side_dist.z)
	{
		m_side_dist.y += m_delta_dist.y;
		m_pos.y += m_step.y;
		m_side = 1;
	}
	else
	{
		m_side_dist.z += m_delta_dist.z;
		m_pos.z += m_step.z;
		m_side = 2;
	}
}

double	Ray::calc_dist()
{
	if (m_side == 0)
		m_d = (m_pos.x - m_ro.x + (1 - m_step.x) / 2.0) / m_rd.x;
	else if (m_side == 1)
		m_d = (m_pos.y - m_ro.y + (1 - m_step.y) / 2.0) / m_rd.y;
	else
		m_d = (m_pos.z - m_ro.z + (1 - m_step.z) / 2.0) / m_rd.z;
	return (m_d);
}
