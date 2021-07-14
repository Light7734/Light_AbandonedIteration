#pragma once

#include "Base.h"

#include <ostream>
#include <fstream>

#include <chrono>

namespace Light {

	struct ScopeProfileResult
	{
		std::string name;
		long long start, duration;
		uint32_t threadID;
	};

	// #todo: add event categories
	// #todo: use ofstream in a separate thread
	class Instrumentor
	{
	private:
		static Instrumentor* s_Context;

		std::ofstream m_OutputFileStream;

		unsigned int m_CurrentSessionCount;

	public:
		static Instrumentor* Create();

		static inline void BeginSession(const std::string& outputPath) { s_Context->BeginSessionImpl(outputPath); }
		static inline void EndSession() { s_Context->EndSessionImpl(); }

		static inline void SubmitScopeProfile(const ScopeProfileResult& profileResult) { s_Context->SubmitScopeProfileImpl(profileResult); }

	private:
		Instrumentor();
		
		void BeginSessionImpl(const std::string& outputPath);
		void EndSessionImpl();

		void SubmitScopeProfileImpl(const ScopeProfileResult& profileResult);
	};

	class InstrumentorTimer
	{
	private:
		ScopeProfileResult m_Result;
		std::chrono::time_point<std::chrono::steady_clock> m_Start;

	public:
		InstrumentorTimer(const std::string& scopeName);
		~InstrumentorTimer();
	};

}

#define LT_PROFILE_SCOPE(name) InstrumentorTimer timer##__LINE__ (name)
#define LT_PROFILE_FUNCTION LT_PROFILE_SCOPE(__FUNCSIG__)
#define LT_PROFILE_BEGIN_SESSION(outputPath) ::Light::Instrumentor::BeginSession(outputPath)
#define LT_PROFILE_END_SESSION() ::Light::Instrumentor::EndSession()
