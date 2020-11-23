/***************************************************/
/* Nom:	Color.h
/* Description: Color
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _Color_H
#define _Color_H

namespace crea
{

	class CREAENGINE_API Color
	{
	public:
		unsigned char m_r;
		unsigned char m_g;
		unsigned char m_b;
		unsigned char m_a;

		// constants
		const static Color black;
		const static Color white;
		const static Color red;
		const static Color green;
		const static Color blue;
		const static Color yellow;
		const static Color magenta;
		const static Color cyan;
		const static Color transparent;
		const static Color grey;
		const static Color orange;

		Color();
		Color(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a);
		virtual ~Color() {};

		// public methods
		void setValues(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a);

		string ToString() const;

		float getR() { return m_r * ONEOVER255; }
		float getG() { return m_g * ONEOVER255; }
		float getB() { return m_b * ONEOVER255; }
		float getA() { return m_a * ONEOVER255; }

		// comparison operators
		bool operator== (const Color& _right) const;
		bool operator!= (const Color& _right) const;
	};

} // namespace crea

#endif // _Color_H