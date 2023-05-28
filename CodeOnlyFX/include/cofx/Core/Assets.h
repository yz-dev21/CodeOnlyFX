#pragma once

#include <map>
#include <string>
#include <memory>

namespace co
{
	class Assets
	{
	private:
		template <typename T>
		static std::map<std::string, std::unique_ptr<T>> m_Assets;
	public:
		static void Load(std::string_view assetsPath);
		template <typename T>
		static T& Get(std::string_view name);
		template <typename T>
		static bool Exists(std::string_view name);
		template <typename T>
		static void Clear();
	};
}
#include "Assets.inl"