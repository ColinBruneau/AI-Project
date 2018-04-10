/***************************************************/
/* Nom:	ILogger.h
/* Description: ILogger
/* Auteur: BRUNEAU Colin
/***************************************************/
#ifndef _ILogger_H
#define _ILogger_H

#include <fstream>

namespace crea
{
	class CREAENGINE_API ILogger
	{
	public:

		virtual ~ILogger();

		static void SetLogger(ILogger* Logger);

		static void Log(const char* Format, ...);

		static ILogger& Log();
		template <class T> ILogger& operator <<(const T& ToLog);

	private:

		virtual void Write(const std::string& Message) = 0;

		static ILogger* s_Instance; 
	};

	// Logger in console
	class CREAENGINE_API LoggerDebug : public ILogger
	{
		virtual void Write(const std::string& Message)
		{
			OutputDebugString((Message + '\n').c_str());
		}
	};

	// Logger in MsgBox
	class CREAENGINE_API LoggerMsgBox : public ILogger
	{
		virtual void Write(const std::string& Message)
		{
			MessageBox(NULL, Message.c_str(), "CreaEngine", MB_OK);
		}
	};

	// Logger in a file
	class CREAENGINE_API LoggerFile : public ILogger
	{
	public:

		LoggerFile(const std::string& Filename = "Output.log") : m_File(Filename)
		{
			if (m_File.fail())
			{
				cerr << "Can't open "<< Filename << endl;
			}
		}

		virtual LoggerFile::~LoggerFile()
		{
			m_File.close();
		}

	private:

		virtual void Write(const std::string& Message)
		{
			m_File << Message;
		}

		std::ofstream m_File;
	};

} // namespace crea

#endif // _ILogger_H