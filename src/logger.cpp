//
// Created by Denis Afendikov on 03.03.2021.
//
#include <string>
#include <iostream>
#include <fstream>
#include "logger.h"

#ifdef _DEBUG
std::ostream& log( const std::string& prefix ) {
	return std::cout << prefix;
}
#else
std::ostream& log( const std::string& prefix ) {
	static std::fstream tmp{ "tmp", std::fstream::in };
	return tmp << prefix;
}
#endif
