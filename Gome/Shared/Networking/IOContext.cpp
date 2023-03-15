#include "Gome/pch.h"
#include "IOContext.h"

namespace Shared::Networking {
	IOContext::IOContext()
		: mIOContext(make_shared<io_context>()) {
	}

	shared_ptr<io_context> IOContext::Get() {
		return mIOContext;
	}
}