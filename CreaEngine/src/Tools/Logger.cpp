#include "stdafx.h"

#include "Tools\Logger.h"

namespace crea
{
	ILogger* ILogger::s_Instance = NULL;

	ILogger::~ILogger()
	{
		s_Instance = nullptr;
	}	

	void ILogger::SetLogger(ILogger* Logger)
	{
		if (s_Instance)
		{
			delete s_Instance;
		}
		s_Instance = Logger;
	}

	void ILogger::Log(const char* Format, ...)
	{
		// Formatage du message dans une chaîne de caractère
		char sBuffer[512];
		va_list Params;
		va_start(Params, Format);
		vsprintf_s(sBuffer, 512, Format, Params);
		va_end(Params);

		// Loggization
		s_Instance->Write(sBuffer);
	}

	template <class T> ILogger& ILogger::operator <<(const T& ToLog)
	{
		std::ostringstream Stream;
		Stream << ToLog;
		Write(Stream.str());

		// On n'oublie pas de toujours renvoyer notre instance, pour pouvoir chaîner les appels à <<
		return Log();
	}

	ILogger& ILogger::Log()
	{
		return *s_Instance;
	}
} // namespace crea