namespace co
{
	Assets::Assets() { }
	template <typename T>
	std::map<std::string, std::unique_ptr<T>> Assets::m_Assets;

	template<typename T>
	void Assets::Add(std::string_view name, T& asset)
	{
		m_Assets<T>[std::string(name)] = asset;
	}
	template<typename T>
	T& Assets::Get(std::string_view name)
	{
		return *m_Assets<T>[std::string(name)];
	}
	template <typename T>
	bool Assets::Exists(std::string_view name)
	{
		return m_Assets<T>.find(std::string(name)) != m_Assets<T>.end();
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