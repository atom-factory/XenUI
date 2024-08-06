// Author: Jake Rieger
// Created: 8/3/2024.
//

#pragma once

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <limits>
#include <filesystem>
#include <exception>

#define CAST static_cast
#define RCAST reinterpret_cast
#define CCAST const_cast
#define DCAST dynamic_cast

using u8   = uint8_t;
using u16  = uint16_t;
using u32  = uint32_t;
using u64  = uint64_t;
using i8   = int8_t;
using i16  = int16_t;
using i32  = int32_t;
using i64  = int64_t;
using f32  = float;
using f64  = double;
using wstr = std::wstring;
using str  = std::string;

using Exception    = std::exception;
using RuntimeError = std::runtime_error;

namespace FileSystem = std::filesystem;
using Path           = std::filesystem::path;

template<class T>
using Option = std::optional<T>;

static constexpr std::nullopt_t kNone = std::nullopt;

template<class T>
using Shared = std::shared_ptr<T>;

template<class T>
using Unique = std::unique_ptr<T>;

template<class T>
using Vector = std::vector<T>;

constexpr auto kInf32 = std::numeric_limits<f32>::infinity();
constexpr auto kInf64 = std::numeric_limits<f64>::infinity();
