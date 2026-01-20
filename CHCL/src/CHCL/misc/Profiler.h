#pragma once

#include <chrono>
#include <map>
#include <unordered_map>
#include <string>

namespace chcl
{
	namespace Profiler
	{
		class ProfilerEntry
		{
		public:
			using time_type = std::chrono::microseconds;
			
		private:
			inline static unsigned int s_idIncrementer = 0;
			unsigned int m_numericID = 0;

			std::string m_scopeName;
			
			bool m_running = false;
			std::chrono::steady_clock::time_point m_scopeBeginTime; //, m_pauseBegin;
			time_type m_duration = time_type(0); //, m_pauseDuration = time_type(0);

			ProfilerEntry *m_parentEntry = nullptr;
			std::map<std::string, ProfilerEntry*> m_childEntries = {};

		public:
			ProfilerEntry() = delete;
			ProfilerEntry(const char *scopeName);
			// ProfilerEntry(const ProfilerEntry&);
			// ProfilerEntry(ProfilerEntry&&);
			~ProfilerEntry();

			void begin();
			void end();

			// void pause();
			// void unpause();

			inline unsigned int getNumericID() const { return m_numericID; }
			inline const std::string& getName() const { return m_scopeName; }
			ProfilerEntry* getChildEntry(const char *name);
			ProfilerEntry* addChildEntry(const char *name);
			inline ProfilerEntry* getParentEntry() const { return m_parentEntry; }

			inline time_type getDuration() const { return m_duration; }
			// inline time_type getPauseDuration() const { return m_pauseDuration; }

			void print(int depth = 0) const;

			// ProfilerEntry& operator =(const ProfilerEntry&);
			// ProfilerEntry& operator =(ProfilerEntry&&);
		};

		class EntryCache
		{
		private:
			std::unordered_map<unsigned int, ProfilerEntry*> m_entryMap;
			std::string m_name;
		public:
			EntryCache(const char *name);

			ProfilerEntry* get();
		};

		class ScopeAutoProfiler
		{
		private:
			ProfilerEntry *m_entry;
		public:
			ScopeAutoProfiler(EntryCache *cache);
			~ScopeAutoProfiler();
		};

		constexpr char TopLevelName[] = "all";

		void Begin(ProfilerEntry *entry);
		void End(ProfilerEntry *entry);

		void PrintTree();
	}
}

#ifdef CHCL_ENABLE_PROFILING
	#define ProfileBegin(name) static chcl::Profiler::EntryCache _chclProfilerCache_##name{ #name }; \
		chcl::Profiler::ProfilerEntry *_chclProfilerCacheEntry_##name = _chclProfilerCache_##name.get();\
		chcl::Profiler::Begin(_chclProfilerCacheEntry_##name);
	#define ProfileEnd(name) chcl::Profiler::End(_chclProfilerCacheEntry_##name);
	#define ProfileScope(name) static chcl::Profiler::EntryCache _chclProfilerCache_##name{ #name }; \
		chcl::Profiler::ScopeAutoProfiler _profileScope_##name{ &_chclProfilerCache_##name };
#else
	#define ProfileBegin(name)
	#define ProfileEnd(name)
	#define ProfileScope(name)
#endif