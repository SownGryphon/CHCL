#include "Profiler.h"

#include "CHCL/Formatter.h"

class _ProfileScope
{
public:
	using time_type = std::chrono::microseconds;
	
private:
	bool m_running = false;
	std::string m_scopeName;

	std::chrono::steady_clock::time_point m_scopeBeginTime, m_pauseBegin;
	time_type m_duration, m_pauseDuration;

	_ProfileScope *m_parentScope = nullptr;
	std::map<std::string, _ProfileScope> m_childScopes;
	_ProfileScope* m_lastChildScopeCache = nullptr;

public:
	_ProfileScope() = default;
	_ProfileScope(const char *scopeName);

	void begin();
	void end();

	void pause();
	void unpause();

	const std::string& getName() const { return m_scopeName; }
	_ProfileScope* addChildScope(const char *name);
	_ProfileScope* getParent() const { return m_parentScope; }

	time_type getDuration() const { return m_duration; }

	void print(int depth = 0) const;
};

_ProfileScope g_topLevelScope = _ProfileScope(chcl::Profiler::TopLevelName);
_ProfileScope *g_currentTopScope = &g_topLevelScope;

#if 1
chcl::Profiler::Scope::Scope(const char *name)
{
	Profiler::Begin(name);
}

chcl::Profiler::Scope::~Scope()
{
	Profiler::End();
}
#endif

void chcl::Profiler::Begin(const char *scopeName)
{
	_ProfileScope *newScope = g_currentTopScope->addChildScope(scopeName);
	newScope->begin();

	g_currentTopScope = newScope;
}

void chcl::Profiler::End(const char *name)
{
	if (name && std::strcmp(g_currentTopScope->getName().c_str(), name))
	{
		std::cout << "BAD\n";
		return;
	}

	g_currentTopScope->end();

	g_currentTopScope = g_currentTopScope->getParent();
}

void chcl::Profiler::PrintAllTimes()
{
	g_topLevelScope.print();
}

void _ProfileScope::print(int depth) const
{
	std::cout << chcl::Formatter::Format("{0}- {1}: {2}\n", std::string(depth * 2, ' '), m_scopeName, m_duration);

	time_type child_cumulative = time_type(0);
	for (auto const &[name, scope] : m_childScopes)
	{
		scope.print(depth + 1);
		child_cumulative += scope.getDuration();
	}

	if (m_childScopes.size() > 0 && child_cumulative < m_duration)
		std::cout << chcl::Formatter::Format("  {0}- *other: {1}\n", std::string(depth * 2, ' '), m_duration - child_cumulative);
}

_ProfileScope::_ProfileScope(const char *scopeName) :
	m_scopeName(scopeName)
{}

void _ProfileScope::begin()
{
	m_running = true;
	m_scopeBeginTime = std::chrono::steady_clock::now();
}

void _ProfileScope::end()
{
	if (!m_running)
		return;
	
	for (auto &child : m_childScopes)
	{
		child.second.end();
	}

	m_running = false;

	time_type scopeDuration = std::chrono::duration_cast<time_type>(std::chrono::steady_clock::now() - m_scopeBeginTime);
	m_duration += scopeDuration;
}

void _ProfileScope::pause()
{}

void _ProfileScope::unpause()
{}

_ProfileScope* _ProfileScope::addChildScope(const char *name)
{
	if (m_lastChildScopeCache && !std::strcmp(m_lastChildScopeCache->getName().c_str(), name))
		return m_lastChildScopeCache;

	_ProfileScope *child = &m_childScopes[name];

	child->m_scopeName = name;
	child->m_parentScope = this;

	m_lastChildScopeCache = child;

	return child;
}