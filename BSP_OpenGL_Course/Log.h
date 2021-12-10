#pragma once
#ifdef WIN32
	#include<boost/log/trivial.hpp>
	#define LOG_DEBUG BOOST_LOG_TRIVIAL(debug)
	#define LOG_INFO BOOST_LOG_TRIVIAL(info)
	#define LOG_ERROR BOOST_LOG_TRIVIAL(error)
	#include<iostream>
	//#define LOG_DEBUG std::out
	//#define LOG_INFO std::clog
	//#define LOG_ERROR std::cerr
	//#define LOG_END std::endl;
#else
#include<iostream>
	#define LOG_DEBUG std::out
	#define LOG_INFO std::clog
	#define LOG_ERROR std::cerr
	#define LOG_END std::endl;
#endif

void STDOUT();
