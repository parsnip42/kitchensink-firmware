#ifndef INCLUDED_CONFIG_H
#define INCLUDED_CONFIG_H

#include <cstdint>

namespace Config
{

constexpr std::size_t kTimerCount       = 20;

constexpr std::size_t kLayerNameLen     = 12;

constexpr std::size_t kMacroNameLen     = 12;
constexpr std::size_t kMacroShortcutLen = 12;
constexpr std::size_t kMacroCount       = 30;
constexpr std::size_t kMacroPoolSize    = 1024;

constexpr std::size_t kMultiKeyNameLen  = 12;
constexpr std::size_t kMultiKeyCount    = 5;
constexpr std::size_t kMultiKeyKeyCount = 4;

constexpr std::size_t kSmartKeyNameLen  = 12;
constexpr std::size_t kSmartKeyCount    = 10;

constexpr std::size_t kLayerColumns     = 16;
constexpr std::size_t kLayerRows        = 5;
constexpr std::size_t kLayerCount       = 10;

};

#endif

