#pragma once

// TODO: remove this Gome/pch.h dependency
#include "Gome/pch.h"
#include "Gome/Shared/Utility/Logger.h"

#define CLASS_TEST_START(className, ...) \
class className { \
	public: \
		bool Test(__VA_ARGS__);

#define CLASS_TEST_END }

#define TEST_CLASS(className, ...) \
TRACE(TEXT("---------------------------------------------------------------------")); \
TRACE(TEXT(#className) << TEXT("\t\t\t...")); \
if (className().Test(__VA_ARGS__)) { \
	TRACE(TEXT(#className) << TEXT("\t\t\tSUCCEEDED")); \
} else { \
	TRACE(TEXT(#className) << TEXT("\t\t\tFAILED")); \
} \
TRACE(TEXT("---------------------------------------------------------------------\n"));

#define TEST_CLASS_METHOD(methodName, ...) \
if (methodName(__VA_ARGS__)) { \
	TRACE(TEXT(#methodName) << TEXT("\t\t\tSUCCEEDED")); \
} else { \
	TRACE(TEXT(#methodName) << TEXT("\t\t\tFAILED")); \
}

#define TEST_CLASS_METHOD_AND_SET_SUCCEEDED(methodName, succeeded, ...) \
if (methodName(__VA_ARGS__)) { \
	TRACE(TEXT(#methodName) << TEXT("\t\t\tSUCCEEDED")); \
} else { \
	TRACE(TEXT(#methodName) << TEXT("\t\t\tFAILED")); \
	succeeded = false; \
}

#define CHECK_EX(condition, ...) \
if (!(condition)) { \
	TRACE(#condition); \
	return { __VA_ARGS__ }; \
}

#define CHECK_TRUE_RETURN_FALSE(condition) CHECK_EX(condition, false)
