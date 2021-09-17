#include "WinUtils.h"
#include <stdlib.h>
#include "Log.h"
#include <string>
#include<iostream>

char * GetEnvPrivate(const char* varName)
{
#ifndef _WIN32
    char * value = getenv(varName);
    return value;
#elif _WIN32
    char* libvar;
    size_t requiredSize;
    getenv_s(&requiredSize, nullptr, 0, varName);
    if (requiredSize == 0)
    {
     //   LogMessage(fmt::format("Environment variable {0} doesn't exist!", varName).c_str());
        return nullptr;
    }

    libvar = (char*)malloc(requiredSize * sizeof(char));
    if (!libvar)
    {
     //   LogMessage(fmt::format("Failed to allocate memory {0} bytes!", requiredSize).c_str());
        return nullptr;
    }

    // Get the value of the LIB environment variable.
    getenv_s(&requiredSize, libvar, requiredSize, varName);

    return libvar;
#endif
}

std::string GetEnv(std::string varName)
{
    std::string mediaPath;
    char * path = GetEnvPrivate(varName.c_str());
    if(path)
    {
        mediaPath = path;
    }
    else 
    {
        LOG_ERROR << varName << " env variable is not defined.";
    }
    return mediaPath;
}

std::string GetMediaPath()
{
#ifdef _WIN32
    return GetEnv("MYMEDIA_PATH").append("\\");
#else
    return GetEnv("MYMEDIA_PATH").append("/");
#endif
}

std::string GetTexturesPath()
{
#ifdef _WIN32
    return GetMediaPath().append("textures\\");
#else
    return GetMediaPath().append("textures/");
#endif
}

std::string GetShaderPath()
{
#ifdef _WIN32
    return GetMediaPath().append("shaders\\");
#else
    return GetMediaPath().append("shaders/");
#endif
}