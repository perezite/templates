#pragma once 

namespace sb 
{
	class AndroidAudio
	{
	public:
		static void init();

		inline static bool isInit() { return m_isInit; }

		inline static bool isValid() { return m_isValid; }
	private: 
		static bool m_isInit;

		static bool m_isValid;

	};
}