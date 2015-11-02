#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>
#include <ostream>
#include <ctime>

#include "Common.h"
#include "GameTime.h"

namespace Log
{

	std::string GetTimeStamp();

    extern bool StopOnErrors;
    
    
    
    const int NoHeader = 0x01;
    
    
    template<typename T, typename... Params>
    void Print(std::ostream& stream, T&& first, Params&&... values)
    {
        stream << " LOG-ERROR ";
        //		stream << first;
        //
        //		Print(stream, values);
    }

	struct Handler
	{
		std::ostream* Stream;
		std::string Label;
        bool PrintHeader=true;

		Handler(std::ostream& stream, const std::string& label)
		{
			Stream = &stream;
			Label = label;
		}

		template<typename T>
		std::ostream& operator<<(const T& value)
		{
            if (PrintHeader)
            {
                *Stream << GetTimeStamp() << Label << " ";
            }

            *Stream << value;

			return *Stream;
		};
        
        std::ostream& operator<<(const int& value)
        {
            if (value != NoHeader)
                *Stream << GetTimeStamp() << Label << " " << value;
            
            return *Stream;
        };
	};

    extern Handler Error;
    extern Handler Warning;
    extern Handler Info;

}

#endif