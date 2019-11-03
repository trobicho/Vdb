/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 04:25:18 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/03 08:21:07 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "quaternion.h"
#include <iostream>

void	Camera::translate(s_vec3 v)
{
	pos.x += v.x * right.x + v.y * up.x + v.z * dir.x;
	pos.y += v.x * right.y + v.y * up.y + v.z * dir.y;
	pos.z += v.x * right.z + v.y * up.z + v.z * dir.z;
}

void	Camera::rotate(s_vec3 v, double angle)
{
	s_quaternion	view_tmp;

	view_tmp = s_quaternion(dir);
	view_tmp = s_quaternion::rotate(view_tmp, v, angle);
	dir = (s_vec3){view_tmp.x, view_tmp.y, view_tmp.z};

	view_tmp = s_quaternion(up);
	view_tmp = s_quaternion::rotate(view_tmp, v, angle);
	up = (s_vec3){view_tmp.x, view_tmp.y, view_tmp.z};

	view_tmp = s_quaternion(right);
	view_tmp = s_quaternion::rotate(view_tmp, v, angle);
	right = (s_vec3){view_tmp.x, view_tmp.y, view_tmp.z};
}
