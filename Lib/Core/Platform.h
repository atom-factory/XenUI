// Author: Jake Rieger
// Created: 8/2/2024.
//

#pragma once

#pragma warning(disable : 4996)

#define WIN32_LEAN_AND_MEAN
#ifdef min
    #undef min
#endif

#ifdef max
    #undef max
#endif

#include <Windows.h>
#include <windowsx.h>
#include <wrl/client.h>

#include <d2d1.h>
#include <dwrite.h>

#include <locale>
#include <string>
#include <codecvt>

#include "Types.h"

using Microsoft::WRL::ComPtr;

namespace XenUI {
    inline str GetHResultErrorMessage(HRESULT hr) {
        char* errorMsg = nullptr;
        FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
                         FORMAT_MESSAGE_IGNORE_INSERTS,
                       nullptr,
                       hr,
                       MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                       (LPSTR)&errorMsg,
                       0,
                       nullptr);

        str errorString;
        if (errorMsg) {
            errorString = errorMsg;
            LocalFree(errorMsg);
        } else {
            errorString = "Unknown error";
        }

        return errorString;
    }

    class ComError final : public Exception {
    public:
        explicit ComError(HRESULT hr) noexcept : result(hr) {}

        const char* what() const noexcept override {
            static char msg[256] = {};
            sprintf_s(msg,
                      "Failure with HRESULT of %08X.\nError: %s\n",
                      static_cast<unsigned int>(result),
                      GetHResultErrorMessage(result).c_str());
            return msg;
        }

    private:
        HRESULT result;
    };

    inline void ThrowIfFailed(HRESULT hr) {
        if (FAILED(hr)) {
            throw ComError(hr);
        }
    }

    inline void WideToANSI(const wstr& value, str& converted) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        converted = converter.to_bytes(value);
    }

    inline void ANSIToWide(const str& value, wstr& converted) {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        converted = converter.from_bytes(value);
    }
}  // namespace XenUI