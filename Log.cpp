#include "Log.h"
#include <boost/date_time/posix_time/posix_time.hpp>

Log * g_Log = nullptr;

static const char * g_LogLevelStr[eNumLogLevels] =
{
	"error", // eLogError
	"warn",  // eLogWarning
	"info",  // eLogInfo
	"debug"	 // eLogDebug 
};

void LogMsg::Process()
{
	output << boost::posix_time::second_clock::local_time().time_of_day () <<  
		"/" << g_LogLevelStr[level] << " - ";
	output << s.str();
}

void Log::Flush ()
{
#ifdef _WIN32	
	if (m_LogFile)
		m_LogFile->flush();
#endif
// TODO: find out what's wrong with flush for Windows	
}

void Log::SetLogFile (const std::string& fullFilePath)
{
	if (m_LogFile) delete m_LogFile;
	m_LogFile = new std::ofstream (fullFilePath, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
	if (m_LogFile->is_open ())
		LogPrint("Logging to file ",  fullFilePath, " enabled.");
	else
	{
		delete m_LogFile;
		m_LogFile = nullptr;
	}
}
