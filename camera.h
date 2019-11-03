/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 02:00:32 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/03 06:56:06 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"

class	Camera
{
	public:
		Camera(s_vec3 cpos, s_vec3 cdir, s_vec3 cup, s_vec3 cright):
			pos(cpos), dir(cdir), up(cup), right(cright){};
		void	rotate(s_vec3 v, double angle);
		void	translate(s_vec3 v);

		s_vec3	dir;
		s_vec3	up;
		s_vec3	right;
		s_vec3	pos;
};

#endif
