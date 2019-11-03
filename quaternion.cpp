/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 07:34:35 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/03 08:18:41 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cmath>
#include "vector.h"
#include "quaternion.h"

void			s_quaternion::normalize()
{
	double	len;

	len = length();
	x /= len;
	y /= len;
	z /= len;
	w /= len;
}

s_quaternion	s_quaternion::conjug()
{
	s_quaternion q;

	q.x = -x;
	q.y = -y;
	q.z = -z;
	return (q);
}

s_quaternion	s_quaternion::conjug(s_quaternion q)
{
	q.x = -q.x;
	q.y = -q.y;
	q.z = -q.z;
	return (q);
}

s_quaternion	s_quaternion::mul(s_quaternion q)
{
	s_quaternion	qr;

	qr.x = w * q.x + x * q.w + y * q.z - z * q.y;
	qr.y = w * q.y - x * q.z + y * q.w + z * q.x;
	qr.z = w * q.z + x * q.y - y * q.x + z * q.w;
	qr.w = w * q.w - x * q.x - y * q.y - z * q.z;
	return (qr);
}

s_quaternion	s_quaternion::mul(s_quaternion q1, s_quaternion q2)
{
	s_quaternion	qr;

	qr.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	qr.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	qr.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	qr.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	return (qr);
}

void			s_quaternion::rotate(s_vec3 v, double angle)
{
	s_quaternion	tmp;

	tmp.x = v.x * sin(angle / 2.0);
	tmp.y = v.y * sin(angle / 2.0);
	tmp.z = v.z * sin(angle / 2.0);
	tmp.w = cos(angle / 2.0);
	//q = quat_mul(quat_mul(tmp, q), quat_conjug(tmp));
	*this = (tmp.mul(*this));
	*this = mul(tmp.conjug());
}

s_quaternion	s_quaternion::rotate(s_quaternion q, s_vec3 v, double angle)
{
	s_quaternion	tmp;

	tmp.x = v.x * sin(angle / 2.0);
	tmp.y = v.y * sin(angle / 2.0);
	tmp.z = v.z * sin(angle / 2.0);
	tmp.w = cos(angle / 2.0);
	q = s_quaternion::mul(s_quaternion::mul(tmp, q), s_quaternion::conjug(tmp));
	return (q);
}
