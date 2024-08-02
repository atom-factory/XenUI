// Author: Jake Rieger
// Created: 8/2/2024.
//

#pragma once

#pragma warning(disable : 4996)

#include <Windows.h>
#include <codecvt>
#include <windowsx.h>
#include <wrl/client.h>
#include <d2d1.h>
#include <dwrite.h>
#include <locale>
#include <stdexcept>
#include <string>

using Microsoft::WRL::ComPtr;

namespace XenUI {
    inline std::string GetHResultErrorMessage(HRESULT hr) {
        char* errorMsg = nullptr;
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                         FORMAT_MESSAGE_IGNORE_INSERTS,
                       nullptr,
                       hr,
                       MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                       (LPSTR)&errorMsg,
                       0,
                       nullptr);

        std::string errorString;
        if (errorMsg) {
            errorString = errorMsg;
            LocalFree(errorMsg);
        } else {
            errorString = "Unknown error";
        }

        return errorString;
    }

    class com_exception final : public std::exception {
    public:
        explicit com_exception(HRESULT hr) noexcept : result(hr) {}

        const char* what() const noexcept override {
            static char s_str[256] = {};
            sprintf_s(s_str,
                      "Failure with HRESULT of %08X.\nError: %s\n",
                      static_cast<unsigned int>(result),
                      GetHResultErrorMessage(result).c_str());
            return s_str;
        }

    private:
        HRESULT result;
    };

    inline void ThrowIfFailed(HRESULT hr) {
        if (FAILED(hr)) {
            throw com_exception(hr);
        }
    }

    inline void WideToANSI(const std::wstring& value, std::string& converted) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        converted = converter.to_bytes(value);
    }

    inline void ANSIToWide(const std::string& value, std::wstring& converted) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        converted = converter.from_bytes(value);
    }
}  // namespace XenUI