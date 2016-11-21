/***************************************************/
/* Nom:	ICore.h
/* Description: ICore
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _ICore_H
#define _ICore_H

namespace crea
{
	class CREAENGINE_API Vector2f
	{
		float m_fX;
		float m_fY;
	public:

		Vector2f()
		{
			m_fX = 0.f;
			m_fY = 0.f;
		}

		Vector2f(float _fX, float _fY)
		{
			m_fX = _fX;
			m_fY = _fY;
		}

		~Vector2f()
		{
		}

		inline void setX(float _fX) { m_fX += _fX; }
		inline void setY(float _fY) { m_fY += _fY; }
		inline float getX() { return m_fX; }
		inline float getY() { return m_fY; }
		inline void addX(float _fX) { m_fX += _fX; }
		inline void addY(float _fY) { m_fY += _fY; }

		inline Vector2f& operator+=(Vector2f& _v) { m_fX += _v.m_fX; m_fY += _v.m_fY; return *this; }
		inline Vector2f& operator*(float _f) { m_fX *= _f; m_fY *= _f; return *this; }

	};

	class CREAENGINE_API IntRect
	{
		int m_iX;
		int m_iY;
		int m_iW;
		int m_iH;

	public:

		IntRect()
		{
			m_iX = 0;
			m_iY = 0;
			m_iW = 0;
			m_iH = 0;
		}

		IntRect(int _x, int _y, int _w, int _h)
		{
			m_iX = _x;
			m_iY = _y;
			m_iW = _w;
			m_iH = _h;
		}

		~IntRect()
		{
		}

		int getLeft() { return m_iX; }
		int getTop() { return m_iY; }
		int getWidth() { return m_iW; }
		int getHeight() { return m_iH; }

	};

	class CREAENGINE_API FloatRect
	{
		float m_fX;
		float m_fY;
		float m_fW;
		float m_fH;
	public:

		FloatRect()
		{
		}

		FloatRect(float _x, float _y, float _w, float _h)
		{
			m_fX = _x;
			m_fY = _y;
			m_fW = _w;
			m_fH = _h;
		}

		~FloatRect()
		{
		}

	};
} // namespace crea

#endif // _ICore_H