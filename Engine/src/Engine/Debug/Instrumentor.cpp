#include "ltpch.h"
#include "Instrumentor.h"

namespace Light {

	Instrumentor* Instrumentor::s_Context = nullptr;

	Instrumentor* Instrumentor::Create()
	{
		return new Instrumentor;
	}
	
	Instrumentor::Instrumentor()
	{
		// #todo: maintenance
		LT_ENGINE_ASSERT(!s_Context, "Instrumentor::Instrumentor: an instance of 'Instrumentor' already exists, do not construct this class!");
		s_Context = this;
	}

	void Instrumentor::BeginSessionImpl(const std::string& outputPath)
	{
		m_OutputFileStream.open(outputPath);
		m_OutputFileStream << "{\"traceEvents\":[";
	}

	void Instrumentor::EndSessionImpl()
	{
		m_OutputFileStream << "]}";
		m_OutputFileStream.flush();
		m_OutputFileStream.close();
	}

	void Instrumentor::SubmitScopeProfileImpl(const ScopeProfileResult& profileResult)
	{
		static bool test = true;

		if (test)
		{
			test = false;
			m_OutputFileStream << "{";
		}
		else 
			m_OutputFileStream << ",{";

		m_OutputFileStream << "\"name\":\"" << profileResult.name << "\",";
		m_OutputFileStream << "\"cat\": \"scope\",";
		m_OutputFileStream << "\"ph\": \"X\",";
		m_OutputFileStream << "\"ts\":" << profileResult.start << ",";
		m_OutputFileStream << "\"dur\":" << profileResult.duration << ",";
		m_OutputFileStream << "\"pid\":0,";
		m_OutputFileStream << "\"tid\":" << profileResult.threadID<< "";
		m_OutputFileStream << "}";
	}

	InstrumentorTimer::InstrumentorTimer(const std::string& scopeName)
		: m_Result( { scopeName, 0, 0, 0 } ), m_Start(std::chrono::steady_clock::now())
	{
	}

	InstrumentorTimer::~InstrumentorTimer()
	{
		auto end = std::chrono::steady_clock::now();

		m_Result.start = std::chrono::time_point_cast<std::chrono::microseconds>(m_Start).time_since_epoch().count();
		m_Result.duration = std::chrono::time_point_cast<std::chrono::microseconds>(end).time_since_epoch().count() - m_Result.start;

		Instrumentor::SubmitScopeProfile(m_Result);
	}

}