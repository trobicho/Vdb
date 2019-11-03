/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Internal_node.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 20:38:22 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/03 03:56:03 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>
#include <bitset>
#include <iostream>

template <class Value, class Child
	, int Log2X, int Log2Y = Log2X, int Log2Z = Log2Y>
class Internal_node
{
	public:
		Internal_node(int32_t x, int32_t y, int32_t z);
		~Internal_node();

		void	set_vox(Value v, int32_t x, int32_t y, int32_t z);
		Value	get_vox(int32_t x, int32_t y, int32_t z);

		static const int sLog2X = Log2X + Child::sLog2X,
			sLog2Y = Log2Y + Child::sLog2Y,
			sLog2Z = Log2Z + Child::sLog2Z,
			sSize = 1 << (Log2X + Log2Y + Log2Z);
	private:
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
		delete m_internal_data[i].child;
		m_internal_data[i].child = nullptr;
	}
}

template <class Value, class Child, int Log2X, int Log2Y, int Log2Z>
void	Internal_node<Value, Child, Log2X, Log2Y, Log2Z>
		::set_vox(Value value, int32_t x, int32_t y, int32_t z)
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
	::get_vox(int32_t x, int32_t y, int32_t z)
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
