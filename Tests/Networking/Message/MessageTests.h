#pragma once

namespace Networking::Message
{
/**
 * @brief The tests for the parsing module
 */
CLASS_TEST_START(MessageTests);

private:
/**
 * @brief Tests the converter module of parsing
 */
bool TestMessageConverter() const;

/**
 * @brief Tests the manager module of parsing
 */
bool TestMessageManager() const;
CLASS_TEST_END;
} // namespace Networking::Message
