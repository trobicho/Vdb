/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Leaf_node.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trobicho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 20:38:57 by trobicho          #+#    #+#             */
/*   Updated: 2019/11/03 03:38:05 by trobicho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdint>
#include <bitset>

template <class Value, int Log2X, int Log2Y = Log2X, int Log2Z = Log2Y>
class Leaf_node
{
	public:
		Leaf_node(int32_t x, int32_t y, int32_t z);
		~Leaf_node(){};


		void	set_vox(Value value, int32_t x, int32_t y, int32_t z);
		Value	get_vox(int32_t x, int32_t y, int32_t z);

		static const int sSize = 1 << (Log2X + Log2Y + Log2Z);
		static const int sLog2X = Log2X, sLog2Y = Log2Y, sLog2Z = Log2Z;

	private:
		Value				m_leaf_data[sSize];	//direct access table

		std::bitset<sSize>	m_value_mask;		//active states
		//[BitMask<sSize>	mInsideMask];		//optional for LS
		//uint64_t			mFlags;				//64 bit flags
		int32_t				m_x, m_y, m_z;	//origin of node
};

template <class Value, int Log2X, int Log2Y, int Log2Z>
Leaf_node<Value, Log2X, Log2Y, Log2Z>
	::Leaf_node(int32_t x, int32_t y, int32_t z): m_x(x), m_y(y), m_z(z)
{
	m_value_mask.reset();
}

template <class Value, int Log2X, int Log2Y, int Log2Z>
void	Leaf_node<Value, Log2X, Log2Y, Log2Z>
		::set_vox(Value value, int32_t x, int32_t y, int32_t z)
{
	unsigned int	leaf_offset = ((x & (1 << sLog2X)-1) << (Log2Y + Log2Z))
		+ ((y & (1 << sLog2Y)-1) << Log2Z) + (z & (1 << sLog2Z) - 1);

	m_leaf_data[leaf_offset] = value;
	m_value_mask.set(leaf_offset);
}

template <class Value, int Log2X, int Log2Y, int Log2Z>
Value	Leaf_node<Value, Log2X, Log2Y, Log2Z>
		::get_vox(int32_t x, int32_t y, int32_t z)
{
	unsigned int	leaf_offset = ((x & (1 << sLog2X)-1) << (Log2Y + Log2Z))
		+ ((y & (1 << sLog2Y)-1) << Log2Z) + (z & (1 << sLog2Z) - 1);

	if (m_value_mask[leaf_offset])
		return (m_leaf_data[leaf_offset]);
	return (0);
}
