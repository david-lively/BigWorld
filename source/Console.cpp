#include "Console.h"
#include "Effect.h"
#include "Log.h"


void Console::OnLoad()
{
    auto& effect = Create<Effect>("console");
    m_consoleEffect = &effect;
}

void Console::OnRender(const GameTime& time)
{
    Log::Info << "Console::OnRender\n";
}
