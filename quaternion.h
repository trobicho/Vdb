/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 07:40:38 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/03 08:20:11 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "vector.h"

typedef struct	s_quaternion
{
	s_quaternion(){};
	s_quaternion(s_vec3 v, double sw = 0.0):
		s_quaternion(v.x, v.y, v.z, sw){};
	s_quaternion(double sx, double sy, double sz, double sw = 0.0):
		x(sx), y(sy), z(sz), w(sw){};

	void					normalize();
	void					rotate(s_vec3 v, double angle);
	s_quaternion			conjug();
	s_quaternion			mul(s_quaternion q);

	static s_quaternion		mul(s_quaternion q1, s_quaternion q2);
	static s_quaternion		rotate(s_quaternion q, s_vec3 v, double angle);
	static s_quaternion		conjug(s_quaternion q);

	inline double	length()
	{
		return (sqrt(x * x + y * y + z * z + w * w));
	}

	double	x;
	double	y;
	double	z;
	double	w;
}				s_quaternion;
