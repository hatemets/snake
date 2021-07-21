#ifndef AUXILIARY_HPP
#define AUXILIARY_HPP

struct Direction
{
	bool m_up, m_down, m_left, m_right;

	Direction() : m_up(false), m_down(false), m_left(false), m_right(false) {}

	bool operator==(const Direction& m_direction)
	{
		return (m_up == m_direction.m_up && m_down == m_direction.m_down && m_left == m_direction.m_left && m_right == m_direction.m_right);
	}
};

#endif
