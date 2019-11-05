/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 06:38:12 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/05 07:44:12 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

struct	s_vec3i
{
	s_vec3i(){};
	s_vec3i(int32_t sx, int32_t sy, int32_t sz): x(sx), y(sy), z(sz){};
	int32_t	x, y, z;
};

template <class Value>
class	Node
{
	public:
		Node(){};
		inline bool			is_leaf() const {return (do_is_leaf());}
		inline s_vec3i		get_log() const {return (do_get_log());}
		inline s_vec3i		get_slog() const {return (do_get_slog());}
		inline s_vec3i		get_child_slog() const {return (do_get_child_slog());}
		inline void			set_vox(Value value, int32_t x, int32_t y, int32_t z)
		{
			return (do_set_vox(value, x, y, z));
		}
		inline Value		get_vox(int32_t x, int32_t y, int32_t z)
		{
			return (do_get_vox(x, y, z));
		}
		inline const Node<Value>
							*get_interresting_node(s_vec3i v, Value &value)
		{
			return (do_get_interresting_node(v, value));
		}

	private:
		virtual bool		do_is_leaf() const = 0;
		virtual s_vec3i		do_get_log() const = 0;
		virtual s_vec3i		do_get_slog() const = 0;
		virtual s_vec3i		do_get_child_slog() const = 0;
		virtual void		do_set_vox(Value value, int32_t x, int32_t y, int32_t z) = 0;
		virtual Value		do_get_vox(int32_t x, int32_t y, int32_t z) const = 0;
		virtual const Node<Value>
							*do_get_interresting_node(s_vec3i v, Value &value) const = 0;
};
