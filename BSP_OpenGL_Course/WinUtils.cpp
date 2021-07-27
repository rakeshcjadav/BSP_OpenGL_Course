#include "WinUtils.h"
#include <stdlib.h>
#include "Log.h"
#include <string>
#include <format>

char * GetEnvPrivate(const char* varName)
{
    char* libvar;
    size_t requiredSize;

    getenv_s(&requiredSize, nullptr, 0, varName);
    if (requiredSize == 0)
    {
        LogMessage(std::format("Environment variable {0} doesn't exist!", varName).c_str());
        return nullptr;
    }

    libvar = (char*)malloc(requiredSize * sizeof(char));
    if (!libvar)
    {
        LogMessage(std::format("Failed to allocate memory {0} bytes!", requiredSize).c_str());
        return nullptr;
    }

    // Get the value of the LIB environment variable.
    getenv_s(&requiredSize, libvar, requiredSize, varName);

    return libvar;
}

std::string GetEnv(std::string varName)
{
    return GetEnvPrivate("MYMEDIA_PATH");
}

std::string GetMediaPath()
{
    return GetEnv("MYMEDIA_PATH").append("\\");
}

std::string GetTexturesPath()
{
    return GetMediaPath().append("textures\\");
}