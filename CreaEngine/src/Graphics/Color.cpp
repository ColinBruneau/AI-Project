#include "stdafx.h"

#include "Graphics\Color.h"

namespace crea
{

	const Color Color::black(0, 0, 0, 255);
	const Color Color::white(255, 255, 255, 255);
	const Color Color::red(255, 0, 0, 255);
	const Color Color::green(0, 255, 0, 255);
	const Color Color::blue(0, 0, 255, 255);
	const Color Color::yellow(255, 255, 0, 255);
	const Color Color::magenta(255, 0, 255, 255);
	const Color Color::cyan(0, 255, 255, 255);
	const Color Color::transparent(0, 0, 0, 0);
	const Color Color::grey(51, 76, 76, 255);
	const Color Color::orange(255, 127, 51, 255);

	Color::Color()
		: m_r(255), m_g(255), m_b(255), m_a(255)
	{
	}

	Color::Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
		: m_r(_r), m_g(_g), m_b(_b), m_a(_a)
	{
	}

	void Color::setValues(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a)
	{
		m_r = _r;
		m_g = _g;
		m_b = _b;
		m_a = _a;
	}

	string Color::ToString() const
	{
		string toString("(");
		toString += to_string(m_r);
		toString += ", ";
		toString += to_string(m_g);
		toString += ", ";
		toString += to_string(m_b);
		toString += ", ";
		toString += to_string(m_a);
		toString += ")";
		return toString;
	}

	bool Color::operator== (const Color& _right) const
	{
		return ((m_r == _right.m_r)
			&& (m_g == _right.m_g)
			&& (m_b == _right.m_b)
			&& (m_a == _right.m_a));
	}

	bool Color::operator!= (const Color& _right) const
	{
		return ((m_r != _right.m_r)
			|| (m_g != _right.m_g)
			|| (m_b != _right.m_b)
			|| (m_a != _right.m_a));
	}

} // namespace crea
