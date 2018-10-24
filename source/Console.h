#ifndef CONSOLE_H
#define CONSOLE_H

#include "Common.h"
#include "GameObject.h"
#include "Mesh.h"
#include "VertexArray.h"
#include "Effect.h"

#include "SOIL2.h"

#include <sstream>
#include <vector>
#include <string>

class Console : public GameObject
{
public:
    /// number of lines to display in the console. Should adjust this dynamically based on display size, but whatever.
    int LinesToDisplay = 5;
    
    Console(const std::string& name) : GameObject(name)
    {
        
    }
    
    
    Console() : Console("console.unknown")
    {
        
    }
    
	~Console()
    {
        
    }
    
//    template<typename T>
//    std::ostream& operator<<(const T& value)
//    {
//        m_stream << value;
//        
//        return m_stream;
//    };
 
    
    template<typename T>
    Console& operator<<(const T& value)
    {
        m_stream << value;
        
        if (value == std::endl)
        {
            /// temp debugging throw
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
    Mesh<char,int> m_mesh;
    
    
};

#endif

