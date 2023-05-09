#pragma once

namespace impl
{
template <typename T> constexpr bool is_basic_string_v = false;

template <typename... T> constexpr bool is_basic_string_v<basic_string<T...>> = true;
} // namespace impl

template <typename T> constexpr bool is_basic_string_v = impl::is_basic_string_v<T>;

namespace Utility
{
#if defined(_UNICODE) || defined(UNICODE)
using String = wstring;
using StringStream = wstringstream;
using FileOutStream = wofstream;
#else
using String = string;
using StringStream = stringstream;
using FileOutStream = ofstream;
#endif // defined(_UNICODE) || defined(UNICODE)

/**
 * @brief Converts built-in types and c style strings to the c++ strings
 * @tparam T the type of the object to be converted to string
 * @param t the object to be converted to string
 * @return the object as a string
 */
template <typename T> static inline String ToString(const T &t)
{
    if constexpr (is_same_v<remove_const_t<remove_pointer_t<decay_t<T>>>, ::TCHAR> ||
                  is_same_v<remove_const_t<remove_reference_t<decay_t<T>>>, String>)
    {
        return t;
    }
    else
    {
#if defined(_UNICODE) || defined(UNICODE)
        return to_wstring(t);
#else
        return to_string(t);
#endif // defined(_UNICODE) || defined(UNICODE)
    }
}

/**
 * @brief Converts a string of units to another string of units
 * @note Suppresses narrowing conversion
 * @tparam StringType the string's unit to be converted to
 * @tparam StringFrom the string's unit to be converted from
 * @param strTo the string
 * @return the converted string
 */
template <typename StringType, typename StringFrom> static inline auto ToStringType(const StringFrom &strTo)
{
    static_assert(is_basic_string_v<StringFrom>, "The StringFrom is not a basic_string!");
    static_assert(is_arithmetic_v<StringType>, "The StringType is not a built-in type!");

    if constexpr (is_same_v<typename StringFrom::value_type, StringType>)
    {
        return strTo;
    }
    else
    {
#pragma warning(suppress : 4244)
        return basic_string<StringType, char_traits<StringType>, allocator<StringType>>(strTo.begin(), strTo.end());
    }
}
} // namespace Utility
