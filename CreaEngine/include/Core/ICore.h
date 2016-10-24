/***************************************************/
/* Nom:	ICore.h
/* Description: ICore
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _ICore_H
#define _ICore_H
#include <Windows.h>

namespace crea
{
	class CREAENGINE_API Time
	{
		float m_fTime;
	public:

		Time()
		{
			m_fTime = 0;
		}

		Time(float _fTime)
		{
			m_fTime = _fTime;
		}

		~Time()
		{
		}

		virtual Time& operator=(float _fTime) { m_fTime = _fTime; return *this; }
		virtual Time& operator+=(Time& _Time) { m_fTime += _Time.m_fTime; return *this; }
		virtual bool operator>=(Time& _Time) { return m_fTime >= _Time.m_fTime; }

		int asMicroseconds() { return (int) (m_fTime * 1000); }
		int asMilliseconds() { return (int) m_fTime; }
		float asSeconds() { return (float) m_fTime * 0.001f; }

	};

	class CREAENGINE_API Clock
	{
		DWORD m_dwFirstTime;
	public:

		Clock()
		{
			m_dwFirstTime = timeGetTime(); // milliseconds since Windows was started
		}
		
		~Clock()
		{
		}
		
		Time getElapsedTime() { return Time((float)(timeGetTime() - m_dwFirstTime)); }
		Time restart() { Time dt = getElapsedTime();  m_dwFirstTime = timeGetTime(); return (dt.asMilliseconds() > 0 ? dt : Time(1)); }
	};

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