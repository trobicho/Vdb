/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 04:25:34 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/03 07:33:45 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "quaternion.h"

void	s_vec3::normalize()
{
	double	len;

	len = sqrt(x * x + y * y + z * z);
	x /= len;
	y /= len;
	z /= len;
}

void	s_vec3::rotate(double angle)
{
	s_quaternion	view_tmp(*this);

	view_tmp.rotate(*this, angle);
	*this = (s_vec3){view_tmp.x, view_tmp.y, view_tmp.z};
}
