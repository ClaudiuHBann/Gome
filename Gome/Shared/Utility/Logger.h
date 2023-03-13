#pragma once

#include "String.h"
#include "Utility.h"

#define TRACE_LOCATION_PROCESS_THREAD_ID Shared::Utility::String(TEXT("PID: ") + Shared::Utility::ToString(::GetCurrentProcessId()) + TEXT("\tTID: ") + Shared::Utility::ToString(::GetCurrentThreadId()))
#define TRACE_LOCATION_FILE_LINE Shared::Utility::String(Shared::Utility::String(TEXT(__FILE__)) + TEXT(":") + Shared::Utility::ToString(__LINE__))
#define TRACE_LOCATION Shared::Utility::String(TRACE_LOCATION_PROCESS_THREAD_ID + TEXT("\t") + TRACE_LOCATION_FILE_LINE)
#define TRACE(strn) Shared::Utility::Print<const ::TCHAR*>((TRACE_LOCATION + TEXT("\t\t") + (Shared::Utility::StringStream() << strn).str()).c_str())

namespace Shared {
	namespace Utility {
		void OutputDebugStringForced(const ::TCHAR* str);

		template<typename Object, typename Iterable>
		void Print(
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
}
