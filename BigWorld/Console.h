#ifndef CONSOLE_H
#define CONSOLE_H

#include "Common.h"
#include "GameObject.h"
#include "VertexArray.h"
#include "Effect.h"

#include <sstream>
#include <vector>
#include <string>

class Console : public GameObject
{
public:
    Console(const std::string& name) : GameObject(name)
    {
        
    }
    
    
    Console() : Console("console.unknown")
    {
        
    }
    
	~Console()
    {
        
    }
    
    template<typename T>
    Console& operator<<(const T& value)
    {
        m_stream << value;
        
        if (value == std::endl)
        {
            /// temp debugging throw
            throw;
            m_strings.push_back(m_stream.str());
            m_stream.clear();
        }
        
        return *this;
    };
    
    
    void Clear()
    {
        m_stream.clear();
        m_strings.clear();
    }
    
    void OnLoad() override;
    
    void OnRender(const GameTime& time) override;
    
private:
    std::stringstream m_stream;
    std::vector<std::string> m_strings;
    
    Effect* m_consoleEffect = nullptr;
    VertexArray<char> m_vertexArray;
    
    
};

#endif

