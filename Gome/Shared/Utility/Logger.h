#pragma once

#include "String.h"

#define TRACE_LOCATION_PROCESS_THREAD_ID Shared::Utility::String(TEXT("PID: ") + Shared::Utility::ToString(::GetCurrentProcessId()) + TEXT(" TID: ") + Shared::Utility::ToString(::GetCurrentThreadId()))
#define TRACE_LOCATION_FILE_LINE Shared::Utility::ClampFileNameLength(TEXT(__FILE__), Shared::Utility::ToString(__LINE__), 50)
#define TRACE_LOCATION Shared::Utility::String(TRACE_LOCATION_PROCESS_THREAD_ID + TEXT(" ") + TRACE_LOCATION_FILE_LINE + TEXT("\t"))
#define TRACE(strn) Shared::Utility::Print<const ::TCHAR*>((TRACE_LOCATION + (Shared::Utility::StringStream() << strn).str()).c_str())

namespace Shared::Utility {
	static inline String ClampFileNameLength(
		String file,
		String line,
		const size_t lengthMaxFileName = 69,
		const size_t lengthMaxLine = 4,
		const String& padding = TEXT("...")
	) {
		line += String(lengthMaxLine - line.length(), TEXT(' '));
		String lineStr(TEXT(":") + line);

		auto fileLength = file.length();
		if (fileLength <= lengthMaxFileName) {
			file += lineStr;
			file += String(lengthMaxFileName - fileLength, TEXT(' '));
		} else {
			auto start = fileLength - lengthMaxFileName + padding.length();
			file = padding + file.substr(start);
			file += lineStr;
		}

		return file;
	}

	static inline void OutputDebugStringForced(const ::TCHAR* str) {
		if (::IsDebuggerPresent()) {
			::OutputDebugString(str);
		}

		if (::GetConsoleWindow()) {
#if defined(_UNICODE) || defined(UNICODE)
			wcout << str;
#else
			cout << str;
#endif // defined(_UNICODE) || defined(UNICODE)
		}

		// TO DO: add a log file
	}

	template<typename Object, typename Iterable>
	static void Print(
		const Iterable& iterable,
		const String& separatorDimensions = TEXT("\n"),
		const function<void(const Object&)>& funcPrintElem = [] (const auto& obj) {
			if constexpr (is_arithmetic_v<decay_t<Object>>) {
				OutputDebugStringForced(ToString(obj).c_str());
			} else if constexpr (is_same_v<remove_const_t<remove_reference_t<decay_t<Object>>>, String>) {
				OutputDebugStringForced(obj.c_str());
			} else if constexpr (is_same_v<remove_const_t<remove_pointer_t<decay_t<Object>>>, ::TCHAR>) {
				OutputDebugStringForced(obj);
			} else {
				static_assert(false, R"(The object from the innermost range is not a built-in/(c)string type, please provide a valid print element function.)");
			}

			OutputDebugStringForced(TEXT(" "));
		}
	) {
		if constexpr (ranges::range<Iterable>) {
			OutputDebugStringForced(separatorDimensions.c_str());
			ranges::for_each(iterable, [&] (const auto& it) { Print(it, separatorDimensions, funcPrintElem); });
		} else {
			funcPrintElem(iterable);
			OutputDebugStringForced(separatorDimensions.c_str());
		}
	}
}
