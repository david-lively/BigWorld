#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include <map>

//#include "Resource.h"
#include "Identity.h"
#include "Log.h"

class Window;

class ResourceManager
{
public:
	ResourceManager()
	{
		if (nullptr != Instance)
			Log::Error << "Only one instance of ResourceManager is allowed\n";

		Instance = this;
	}

	~ResourceManager()
	{

	}

	template<typename T>
	T& Create(const std::string& name)
	{
		if (m_resources.find(name) != end(m_resources))
        {
			Log::Error << "Can't create duplicate resource named \"" << name << "\"\n";
            throw;
        }

		auto item = std::make_shared<T>(name);

		m_resources[name] = item;

		return *item;
	}

	template<typename T>
	T& Get(const std::string& name)
	{
		auto resource = m_resources[name];

		if (nullptr == resource)
			Log::Error << "Can't find resources \"" << name << "\"\n";

		return *resource;
	}

	static ResourceManager* Instance;


private:
	std::map<std::string, std::shared_ptr<Identity>> m_resources;

};


#endif