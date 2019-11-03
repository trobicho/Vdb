/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 02:02:24 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/03 08:30:40 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <cmath>

struct	s_vec3
{
	s_vec3(){};
	s_vec3(double sx, double sy, double sz): x(sx), y(sy), z(sz){};

	void	normalize();
	void	rotate(double angle);

	inline double	norme()
	{
		return (sqrt(x * x + y * y + z * z));
	}

	inline s_vec3	sub(s_vec3 v)
	{
		return (s_vec3){x - v.x, y - v.y, z - v.z};
	}

	inline s_vec3	add(s_vec3 v)
	{
		return (s_vec3){x + v.x, y + v.y, z + v.z};
	}

	inline double	dot(s_vec3 v)
	{
		return (x * v.x + y * v.y + z * v.z);
	}

	inline s_vec3	mul(s_vec3 v)
	{
		return (s_vec3){x * v.x, y * v.y, z * v.z};
	}

	inline s_vec3	scalar(double s)
	{
		return (s_vec3){x * s, y * s, z * s};
	}

	double	x;
	double	y;
	double	z;
};

struct	s_vec2
{
	s_vec2(double sx, double sy): x(sx), y(sy){};

	double	x;
	double	y;
};
