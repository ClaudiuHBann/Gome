#pragma once

#include "String.h"

#define TRACE_LOCATION_PROCESS_THREAD_ID                                                                               \
    Utility::String(TEXT("PID: ") + Utility::ToString(::GetCurrentProcessId()) + TEXT(" TID: ") +                      \
                    Utility::ToString(::GetCurrentThreadId()))
#define TRACE_LOCATION_FILE_LINE Utility::ClampFileNameLength(TEXT(__FILE__), Utility::ToString(__LINE__), 50)
#define TRACE_LOCATION                                                                                                 \
    Utility::String(TRACE_LOCATION_PROCESS_THREAD_ID + TEXT(" ") + TRACE_LOCATION_FILE_LINE + TEXT("\t"))
#define TRACE(strn) Utility::Print<const ::TCHAR *>((TRACE_LOCATION + (Utility::StringStream() << strn).str()).c_str())

namespace Utility
{
/**
 * @brief Cuts the beginning the file name if it's length is bigger than the clamp value
 * @param file the file name
 * @param line the line number
 * @param lengthMaxFileName clamp value for the file name
 * @param lengthMaxLine clamp value for the line number
 * @param padding the front padding if the file name was cut
 * @return the new file name
 */
static inline String ClampFileNameLength(String file, String line, const size_t lengthMaxFileName = 69,
                                         const size_t lengthMaxLine = 4, const String &padding = TEXT("..."))
{
    line += String(lengthMaxLine - line.length(), TEXT(' '));
    String lineStr(TEXT(":") + line);

    auto fileLength = file.length();
    if (fileLength <= lengthMaxFileName)
    {
        file += lineStr;
        file += String(lengthMaxFileName - fileLength, TEXT(' '));
    }
    else
    {
        auto start = fileLength - lengthMaxFileName + padding.length();
        file = padding + file.substr(start);
        file += lineStr;
    }

    return file;
}

/**
 * @brief Prints a string in the windows's console and VS' debug console and a file with the name of current DateTime
 * @param str the string to be printed
 */
static inline void OutputDebugStringForced(const ::TCHAR *str)
{
    if (::IsDebuggerPresent())
    {
        ::OutputDebugString(str);
    }

    if (::GetConsoleWindow())
    {
#if defined(_UNICODE) || defined(UNICODE)
        wcout << str;
#else
        cout << str;
#endif // defined(_UNICODE) || defined(UNICODE)
    }

    static auto &&currentZoneTime = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());
    static String fileName(format(TEXT("{:%Y-%m-%d--%H-%M-%OS}.log"), currentZoneTime));
    static FileOutStream file(fileName);
    file << str << flush;
}

/**
 * @brief Prints any object or n dimensions containers of built-in types and (c style) strings by default but can print
 * any object if a callback is passed for that object
 * @tparam Object the object type
 * @tparam Iterable the iterable type
 * @param iterable the iterable object to print
 * @param separatorDimensions char for separating dimensions between the iterable
 * @param funcPrintElem the callback for printing an object
 */
template <typename Object, typename Iterable>
static void Print(
    const Iterable &iterable, const String &separatorDimensions = TEXT("\n"),
    const function<void(const Object &)> &funcPrintElem = [](const auto &obj) {
        if constexpr (is_arithmetic_v<decay_t<Object>>)
        {
            OutputDebugStringForced(ToString(obj).c_str());
        }
        else if constexpr (is_same_v<remove_const_t<remove_reference_t<decay_t<Object>>>, String>)
        {
            OutputDebugStringForced(obj.c_str());
        }
        else if constexpr (is_same_v<remove_const_t<remove_pointer_t<decay_t<Object>>>, ::TCHAR>)
        {
            OutputDebugStringForced(obj);
        }
        else
        {
            static_assert(
                false,
                R"(The object from the innermost range is not a built-in/(c)string type, please provide a valid print element function.)");
        }

        OutputDebugStringForced(TEXT(" "));
    })
{
    if constexpr (ranges::range<Iterable>)
    {
        OutputDebugStringForced(separatorDimensions.c_str());
        ranges::for_each(iterable, [&](const auto &it) { Print(it, separatorDimensions, funcPrintElem); });
    }
    else
    {
        funcPrintElem(iterable);
        OutputDebugStringForced(separatorDimensions.c_str());
    }
}
} // namespace Utility
