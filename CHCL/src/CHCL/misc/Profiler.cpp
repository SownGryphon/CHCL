#include "Profiler.h"

#include "CHCL/Formatter.h"

static chcl::Profiler::ProfilerEntry * const g_topLevelEntry = new chcl::Profiler::ProfilerEntry(chcl::Profiler::TopLevelName);
// static std::vector<chcl::Profiler::ProfilerEntry*> g_entries = { g_topLevelEntry};
static chcl::Profiler::ProfilerEntry *g_currentEntry = g_topLevelEntry;
static bool g_profilerBad = false;

void chcl::Profiler::Begin(ProfilerEntry *entry)
{
	if (g_profilerBad) return;
	entry->begin();

	g_currentEntry = entry;
}

void chcl::Profiler::End(ProfilerEntry *entry)
{
	if (g_profilerBad) return;

	if (g_currentEntry != entry)
	{
		std::cout << Formatter::Format("Profiler BAD: got {}, expected {}\n", entry->getName(), g_currentEntry->getName());
		while (g_currentEntry != g_topLevelEntry)
		{
			g_currentEntry->end();
			g_currentEntry = g_currentEntry->getParentEntry();
		}
		g_profilerBad = true;
		return;
	}

	g_currentEntry->end();
	g_currentEntry = g_currentEntry->getParentEntry();
}

void chcl::Profiler::PrintTree()
{
	g_topLevelEntry->print();
}

void chcl::Profiler::ProfilerEntry::print(int depth) const
{
	std::cout << chcl::Formatter::Format("{}- {}: {}\n", std::string(depth * 2, ' '), m_scopeName, m_duration);

	time_type child_cumulative = time_type(0);
	for (auto const &[name, entry] : m_childEntries)
	{
		entry->print(depth + 1);
		child_cumulative += entry->getDuration();
	}

	if (m_childEntries.size() > 0 && child_cumulative < m_duration)
		std::cout << chcl::Formatter::Format("  {}- *other: {}\n", std::string(depth * 2, ' '), m_duration - child_cumulative);
}

chcl::Profiler::ProfilerEntry::ProfilerEntry(const char *scopeName) :
	m_scopeName(scopeName),
	m_numericID(++s_idIncrementer)
{}

#if 0
#if 0
chcl::Profiler::ProfilerEntry::ProfilerEntry(const ProfilerEntry &other) :
	m_numericID(other.m_numericID),
	m_scopeName(other.m_scopeName),
	m_running(other.m_running),
	m_scopeBeginTime(other.m_scopeBeginTime),
	m_duration(other.m_duration),
	m_parentScopeIndex(other.m_parentScopeIndex),
	m_childEntryIndices(other.m_childEntryIndices)
{
	std::cout << Formatter::Format("Copy ctor size: {}, parent size: {}\n", m_childEntryIndices.size(), other.m_childEntryIndices.size());
}

chcl::Profiler::ProfilerEntry::ProfilerEntry(ProfilerEntry &&other) :
	m_numericID(other.m_numericID),
	m_scopeName(other.m_scopeName),
	m_running(other.m_running),
	m_scopeBeginTime(other.m_scopeBeginTime),
	m_duration(other.m_duration),
	m_parentScopeIndex(other.m_parentScopeIndex),
	m_childEntryIndices(std::move(other.m_childEntryIndices))
{
	other.m_numericID = 0;
	other.m_parentScopeIndex = 0;
	std::cout << Formatter::Format("Move ctor size: {}, parent size: {}\n", m_childEntryIndices.size(), other.m_childEntryIndices.size());
}
#else
chcl::Profiler::ProfilerEntry::ProfilerEntry(const ProfilerEntry &other)
{
	*this = other;
}

chcl::Profiler::ProfilerEntry::ProfilerEntry(ProfilerEntry &&other)
{
	*this = std::move(other);
}
#endif
#endif

chcl::Profiler::ProfilerEntry::~ProfilerEntry()
{
	// TODO: Actually implement well
	// for (auto &[name, childIndex] : m_childEntryIndices)
	// {
	// 	g_entries.erase(g_entries.begin() + childIndex);
	// }
}

void chcl::Profiler::ProfilerEntry::begin()
{
	m_running = true;
	m_scopeBeginTime = std::chrono::steady_clock::now();
}

void chcl::Profiler::ProfilerEntry::end()
{
	if (!m_running)
		return;

	m_running = false;

	time_type scopeDuration = std::chrono::duration_cast<time_type>(std::chrono::steady_clock::now() - m_scopeBeginTime);

	// if (m_parentScope)
	// 	m_parentScope->m_pauseDuration += m_pauseDuration;

	m_duration += scopeDuration;
	// m_pauseDuration = time_type(0);
}

#if 0
void chcl::Profiler::ProfilerEntry::pause()
{
	m_pauseBegin = std::chrono::steady_clock::now();
}

void chcl::Profiler::ProfilerEntry::unpause()
{
	time_type pauseDuration = std::chrono::duration_cast<time_type>(std::chrono::steady_clock::now() - m_pauseBegin);
	m_pauseDuration += pauseDuration;
	// std::cout << "Paused for " << pauseDuration << '\n';
}
#endif

chcl::Profiler::ProfilerEntry* chcl::Profiler::ProfilerEntry::getChildEntry(const char *name)
{
	ProfilerEntry *res = m_childEntries[name];

	if (res == nullptr)
		res = addChildEntry(name);

	return res;
}

chcl::Profiler::ProfilerEntry* chcl::Profiler::ProfilerEntry::addChildEntry(const char *name)
{
	ProfilerEntry *child = new ProfilerEntry(name);

	// g_entries.push_back(child);
	m_childEntries[name] = child;
	child->m_parentEntry = this;

	return child;
}

#if 0
chcl::Profiler::ProfilerEntry& chcl::Profiler::ProfilerEntry::operator =(const ProfilerEntry &other)
{
	m_numericID = other.m_numericID;
	m_scopeName = other.m_scopeName;
	m_running = other.m_running;
	m_scopeBeginTime = other.m_scopeBeginTime;
	m_duration = other.m_duration;
	m_parentScopeIndex = other.m_parentScopeIndex;
	m_childEntryIndices = other.m_childEntryIndices;

	return *this;
}

chcl::Profiler::ProfilerEntry& chcl::Profiler::ProfilerEntry::operator =(ProfilerEntry &&other)
{
	m_numericID = other.m_numericID;
	m_scopeName = other.m_scopeName;
	m_running = other.m_running;
	m_scopeBeginTime = other.m_scopeBeginTime;
	m_duration = other.m_duration;
	m_parentScopeIndex = other.m_parentScopeIndex;
	m_childEntryIndices = std::move(other.m_childEntryIndices);

	return *this;
}
#endif

chcl::Profiler::EntryCache::EntryCache(const char *name) :
	m_name(name)
{}

#if 0
unsigned int chcl::Profiler::EntryCache::getIndex()
{
	unsigned int res = m_entryMap[GetCurrentEntry()->getNumericID()];
	std::cout << "Cache initial get success\n";

	if (res == 0)
	{
		std::cout << "Cache needs new entry\n";
		res = GetCurrentEntry()->getChildEntryIndex(m_name.c_str());
	}

	return res;
}
#endif

chcl::Profiler::ProfilerEntry* chcl::Profiler::EntryCache::get()
{
	ProfilerEntry *res = m_entryMap[g_currentEntry->getNumericID()];

	if (res != nullptr)
		return res;

	m_entryMap[g_currentEntry->getNumericID()] = g_currentEntry->getChildEntry(m_name.c_str());

	return m_entryMap[g_currentEntry->getNumericID()];
}

chcl::Profiler::ScopeAutoProfiler::ScopeAutoProfiler(EntryCache *cache) :
	m_entry(cache->get())
{
	Profiler::Begin(m_entry);
}

chcl::Profiler::ScopeAutoProfiler::~ScopeAutoProfiler()
{
	Profiler::End(m_entry);
}