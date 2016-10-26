/***************************************************/
/* Nom:	Time.h
/* Description: ITime
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _Time_H
#define _Time_H
#include <chrono>

using namespace std::chrono;

namespace crea
{
	class CREAENGINE_API Time
	{
		double m_dTime;
	public:

		Time();

		Time(double _dTime);

		~Time();

		Time& operator=(double _dTime);
		Time& operator+=(Time& _Time);
		bool operator>=(Time& _Time);

		int asMicroseconds();
		int asMilliseconds();
		double asSeconds();

		void setAsMicroSeconds(int _iTime);
		void setAsMilliSeconds(int _iTime);
		void setAsSeconds(double _dTime);
	};

	class CREAENGINE_API Clock
	{
		high_resolution_clock::time_point m_t1;
		Time m_elapsedTime;
	public:

		Clock();
		
		~Clock();
		
		Time getElapsedTime();
		Time restart();
	};

} // namespace crea

#endif // _Time_H