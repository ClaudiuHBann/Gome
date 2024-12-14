#pragma once

#ifdef _WIN32

#ifdef UNICODE
#undef UNICODE
#endif // !UNICODE

#ifdef _UNICODE
#undef _UNICODE
#endif // !_UNICODE

#define _WIN32_WINNT 0x0A00

#endif // _WIN32

#define ASIO_STANDALONE
#include "packages/asio-cppp-latest.1.24.0/build/native/include/asio.hpp"

using namespace asio;
using namespace ip;

#include <fstream>
#include <iostream>
#include <numeric>
#include <random>
#include <ranges>
#include <string>

using namespace std;

using bytes = vector<byte>;

#define THROW_INVALID_ARG_IF(cond)                                                                                     \
    if (cond)                                                                                                          \
    {                                                                                                                  \
        throw invalid_argument(#cond);                                                                                 \
    }
