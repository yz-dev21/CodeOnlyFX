#include "Debug.h"

namespace co
{
	inline Assets::Assets() { }
	template <typename T>
	std::map<std::string, std::unique_ptr<T>> Assets::m_Assets;

	template <typename T>
	bool Assets::Exists(std::string_view name)
	{
		return m_Assets<T>.find(std::string(name)) != m_Assets<T>.end();
	}
	template<typename T>
	void Assets::Add(std::string_view name, T& asset)
	{
		if (Exists<T>(name))
		{
			CO_WARN("cofx::Core::Assets; Such asset already exists, so overwrited: {} `{}`.", typeid(T).name(), name);
			return;
		}
		m_Assets<T>[std::string(name)] = asset;
	}
	template<typename T>
	T& Assets::Get(std::string_view name)
	{
		if (!Exists<T>(name))
			CO_WARN("cofx::Core::Assets; There is no such asset: {} `{}`.", typeid(T).name(), name);

		return *m_Assets<T>[std::string(name)];
	}
	template <typename T>
	void Assets::Clear()
	{
		m_Assets<T>.clear();
	}
	/*
	* assets file
	* type
	* 1: image
	* 2: sound
	*/
}