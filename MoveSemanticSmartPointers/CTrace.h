#pragma once
#include <ostream>

class CTrace {
public:
	CTrace(int i_a) : m_a(i_a)
	{
		std::cout << "ctor " << m_a << std::endl;
	}
	~CTrace()
	{
		std::cout << "dtor " << m_a << std::endl;
	}
	CTrace(const CTrace& i_other) : m_a(i_other.m_a)
	{
		std::cout << "copytor " << m_a << std::endl;
	}
	CTrace(CTrace&& i_other) : m_a(i_other.m_a)
	{
		std::cout << "movetor " << m_a << std::endl;
	}

	CTrace& operator=(const CTrace& i_other)
	{
		std::cout << "assignment operator " << m_a << std::endl;
		if (this == &i_other) return *this;
		m_a = i_other.m_a;
		return *this;
	}
	CTrace& operator=(CTrace&& i_other)
	{
		std::cout << "move operator " << m_a << std::endl;
		if (this == &i_other) return *this;
		m_a = i_other.m_a;
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& os, CTrace& sp)
	{
		os << sp.m_a;
		return os;
	}

	int m_a;
};