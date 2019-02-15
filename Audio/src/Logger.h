#pragma once
#include <sstream>
#include <iostream>
#include <assert.h>
#include <SDL2/SDL.h>

#define NO_ERROR_AS_WARNING_IN_DEBUG_MODE

namespace sb
{
	class NullBuffer : public std::streambuf
	{
	public:
		int overflow(int c) { return c; }
	};

	static NullBuffer NullBuf;
	static std::ostream NullStream(&NullBuf);
}

#define SB_ERROR() sb::Logger().error()

#define SB_ERROR_IF(condition) (condition ? sb::Logger().error() : sb::NullStream)

#define SB_WARNING() sb::Logger().warning()

#define SB_WARNING_IF(condition) (condition ? sb::Logger().warning() : sb::NullStream)

#define SB_WARNING_IF2(condition, errorInDebugMode) (condition ? sb::Logger().warning(errorInDebugMode) : sb::NullStream)

namespace sb
{
	class Logger
	{
	private:
		enum class LoggerType {
			None, Error, Warning
		};

	public:
		Logger() : m_hasError(true), m_hasWarning(true), m_isDebugMode(false), m_type(LoggerType::None) {
			#ifdef _DEBUG
				m_isDebugMode = true;
			#endif
		}

		std::ostream& error() { 
			m_type = LoggerType::Error;
			return m_stream; 
		}
		
		std::ostream& errorIf(bool condition) { 
			m_type = LoggerType::Error;
			m_hasError = condition;
			return m_stream; 
		}

		std::ostream& warning(bool errorInDebugMode = false) {
			m_type = errorInDebugMode && m_isDebugMode ? LoggerType::Error : LoggerType::Warning;
			return m_stream;
		}

		std::ostream& warningIf(bool condition, bool errorInDebugMode = false) {
			m_type = errorInDebugMode && m_isDebugMode ? LoggerType::Error : LoggerType::Warning;
			m_hasWarning = condition;
			return m_stream;
		}

		~Logger() { 
			if (m_type == LoggerType::Error && m_hasError) {
				SDL_Log("ERROR: %s", m_stream.str().c_str());
				#ifdef WIN32
					__debugbreak();
				#else	
					exit(0);
				#endif		
			}
			else if (m_type == LoggerType::Warning && m_hasWarning) {
				SDL_Log("WARNING: %s", m_stream.str().c_str());
			}
		}

	private:
		std::ostringstream m_stream;

		bool m_hasError;

		bool m_hasWarning;

		bool m_isDebugMode;

		LoggerType m_type;

	};
}