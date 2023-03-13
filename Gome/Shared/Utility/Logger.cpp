#include "Gome/pch.h"
#include "Logger.h"

namespace Shared {
	namespace Utility {
		void OutputDebugStringForced(const ::TCHAR* str) {
			if (::IsDebuggerPresent()) {
				::OutputDebugString(str);
			}

			if (IsConsolePresent()) {
#if defined(_UNICODE) || defined(UNICODE)
				wcout << str;
#else
				cout << str;
#endif // defined(_UNICODE) || defined(UNICODE)
			}

			// TO DO: add a log file
		}
	}
}
