#include "Gome/pch.h"
#include "Utility.h"

namespace Shared {
	namespace Utility {
		bool IsConsolePresent() {
			return GetConsoleWindow();
		}
	}
}
