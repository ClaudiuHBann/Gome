#pragma once

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif // _WIN32
#define ASIO_STANDALONE
#include "packages/asio-cppp-latest.1.24.0/build/native/include/asio.hpp"

#include <Rpc.h>
#pragma comment(lib, "Rpcrt4.lib")

#include <iostream>
#include <string>

using namespace std;
