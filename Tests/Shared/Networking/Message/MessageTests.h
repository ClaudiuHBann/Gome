#pragma once

namespace Shared {
	namespace Networking {
		namespace Message {
			CLASS_TEST_START(MessageTests);
				private:
					bool TestMessages() const;
					bool TestMessageConverter() const;
					bool TestMessageManager() const;
			CLASS_TEST_END;
		}
	}
}
