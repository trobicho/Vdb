/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Internal_node.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 20:38:22 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/06 17:52:00 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>
#include <bitset>
#include <iostream>
#include "Node.h"

template <class Value, class Child
	, int Log2X, int Log2Y = Log2X, int Log2Z = Log2Y>
class Internal_node: public Node<Value>
{
	public:
		Internal_node(int32_t x, int32_t y, int32_t z);
		~Internal_node();

		void		do_set_vox(Value v, int32_t x, int32_t y, int32_t z);
		Value		do_get_vox(int32_t x, int32_t y, int32_t z) const;
		Value		pruning();
		const Node<Value>
					*do_get_interresting_node(s_vec3i v, Value &value) const;

		static const int sLog2X = Log2X + Child::sLog2X,
			sLog2Y = Log2Y + Child::sLog2Y,
			sLog2Z = Log2Z + Child::sLog2Z,
			sSize = 1 << (Log2X + Log2Y + Log2Z);
	private:
		inline bool			do_is_leaf() const {
			return (false);
		}
		inline s_vec3i		do_get_log() const {
			return s_vec3i(Log2X, Log2Y, Log2Z);
		}
		inline s_vec3i		do_get_slog() const {
			return s_vec3i(sLog2X, sLog2Y, sLog2Z);
		}
		inline s_vec3i		do_get_child_slog() const {
			return s_vec3i(Child::sLog2X, Child::sLog2Y, Child::sLog2Z);
		}

		union u_internal_data 
		{
			Child*	child;					//child node pointer
			Value	value;					//tile value
		} m_internal_data[sSize];

		std::bitset<sSize>	m_value_mask;	//active states
		std::bitset<sSize>	m_child_mask;	//node topology
		int32_t				m_x, m_y, m_z;	//origin of node
};

template <class Value, class Child, int Log2X, int Log2Y, int Log2Z>
Internal_node<Value, Child, Log2X, Log2Y, Log2Z>
	::Internal_node(int32_t x, int32_t y, int32_t z): m_x(x), m_y(y), m_z(z)
{
	m_value_mask.reset();
	m_child_mask.reset();
	for (int i = 0; i < sSize; ++i)
	{
		m_internal_data[i].child = nullptr;
	}
}

template <class Value, class Child, int Log2X, int Log2Y, int Log2Z>
Internal_node<Value, Child, Log2X, Log2Y, Log2Z>::~Internal_node()
{
	for (int i = 0; i < sSize; ++i)
	{
		if (m_child_mask[i])
			delete m_internal_data[i].child;
		m_internal_data[i].child = nullptr;
	}
}

template <class Value, class Child, int Log2X, int Log2Y, int Log2Z>
void	Internal_node<Value, Child, Log2X, Log2Y, Log2Z>
		::do_set_vox(Value value, int32_t x, int32_t y, int32_t z)
{
	unsigned int	internal_offset =
		(((x & (1 << sLog2X) - 1) >> Child::sLog2X) << (Log2Y + Log2Z))
		+ (((y & (1 << sLog2Y) - 1) >> Child::sLog2Y) << Log2Z)
		+ ((z & (1 << sLog2Z) - 1) >> Child::sLog2Z);

	if (m_child_mask[internal_offset])
		m_internal_data[internal_offset].child->set_vox(value, x, y, z);
	else
	{
		m_internal_data[internal_offset].child = new Child(
			x % Child::sLog2X, y % Child::sLog2Y, z % Child::sLog2Z);
		m_internal_data[internal_offset].child->set_vox(value, x, y, z);
		m_child_mask.set(internal_offset);
	}
}

template <class Value, class Child, int Log2X, int Log2Y, int Log2Z>
Value	Internal_node<Value, Child, Log2X, Log2Y, Log2Z>
	::do_get_vox(int32_t x, int32_t y, int32_t z) const
{
	unsigned int	internal_offset =
		(((x & (1 << sLog2X) - 1) >> Child::sLog2X) << (Log2Y + Log2Z))
		+ (((y & (1 << sLog2Y) - 1) >> Child::sLog2Y) << Log2Z)
		+ ((z & (1 << sLog2Z) - 1) >> Child::sLog2Z);
	if (m_value_mask[internal_offset])
		return (m_internal_data[internal_offset].value);
	else if (m_child_mask[internal_offset])
		return (m_internal_data[internal_offset].child->get_vox(x, y, z));
	return (0);
}

template <class Value, class Child, int Log2X, int Log2Y, int Log2Z>
const Node<Value>	*Internal_node<Value, Child, Log2X, Log2Y, Log2Z>
	::do_get_interresting_node(s_vec3i v, Value &value) const
{
	unsigned int	internal_offset =
		(((v.x & (1 << sLog2X) - 1) >> Child::sLog2X) << (Log2Y + Log2Z))
		+ (((v.y & (1 << sLog2Y) - 1) >> Child::sLog2Y) << Log2Z)
		+ ((v.z & (1 << sLog2Z) - 1) >> Child::sLog2Z);
	if (m_value_mask[internal_offset])
	{
		value = m_internal_data[internal_offset].value;
		return (this);
	}
	else if (m_child_mask[internal_offset])
		return (m_internal_data[internal_offset].child
			->get_interresting_node(v, value));
	return (this);
}
template <class Value, class Child, int Log2X, int Log2Y, int Log2Z>
Value	Internal_node<Value, Child, Log2X, Log2Y, Log2Z>
	::pruning()
{
	Value	val;

	for (int i = 0; i < sSize; i++)
	{
		if (m_child_mask[i])
		{
			if ((val = m_internal_data[i].child->pruning()) != 0)
			{
				m_child_mask.set(i, false);
				m_value_mask.set(i, true);
				delete(m_internal_data[i].child);
				m_internal_data[i].value = val;
			}
		}
	}
	if (m_value_mask.all())
	{
		return (m_internal_data[0].value);
	}
	return (0);
}
