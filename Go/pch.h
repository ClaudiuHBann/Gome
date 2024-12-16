#pragma once

#include <queue>

// TODO: remove this Gome/pch.h dependency
#include "Gome/pch.h"
//
#include "Gome/Utility/Logger.h"

#include "Go/json.hpp"
using namespace nlohmann;

#ifdef _DEBUG
inline constexpr auto SERVER_IP = "127.0.0.1";
#else
inline constexpr auto SERVER_IP = "162.55.32.18";
#endif

inline constexpr auto SERVER_PORT = 741;
