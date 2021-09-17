#pragma once
#ifndef WIN32
    #include<boost/log/trivial.hpp>
#else
#include<iostream>
#define BOOST_LOG_TRIVIAL(level) std::cout;
#endif
