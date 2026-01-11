#pragma once

#include <chrono>
#include <map>
#include <string>

namespace chcl
{
	namespace Profiler
	{
		class Scope
		{
		public:
			Scope(const char *name);
			~Scope();
		};

		constexpr char TopLevelName[] = "all";

		void Begin(const char *layerName);
		void End(const char *name = nullptr);

		void PrintAllTimes();
	}
}

#ifdef CHCL_ENABLE_PROFILING
	#define ProfileBegin(name) chcl::Profiler::Begin(#name);
	#define ProfileEnd(name) chcl::Profiler::End(#name);
	#define ProfileScope(name) chcl::Profiler::Scope _profileScope_##name{ #name };
#else
	#define ProfileBegin(name)
	#define ProfileEnd(name)
	#define ProfileScope(name)
#endif