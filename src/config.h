#ifndef INCLUDED_CONFIG_H
#define INCLUDED_CONFIG_H

#include <cstdint>

namespace Config
{

constexpr std::size_t kTimerCount = 20;

constexpr std::size_t kHomeLedCount = 12;

constexpr std::size_t kLayerNameLen = 24;

constexpr std::size_t kMacroNameLen     = 24;
constexpr std::size_t kMacroShortcutLen = 24;
constexpr std::size_t kMacroMaxSize     = 200;
constexpr std::size_t kMacroCount       = 30;
constexpr std::size_t kMacroPoolSize    = 1024;
constexpr std::size_t kSMacroCount      = 30;
constexpr std::size_t kSMacroPoolSize   = 1024;

constexpr std::size_t kMultiKeyNameLen  = 24;
constexpr std::size_t kMultiKeyCount    = 12;
constexpr std::size_t kMultiKeyTapCount = 4;

constexpr std::size_t kSmartKeyNameLen = 24;
constexpr std::size_t kSmartKeyCount   = 12;

constexpr std::size_t kLayerColumns = 16;
constexpr std::size_t kLayerRows    = 5;
constexpr std::size_t kLayerCount   = 10;

constexpr int         kEntropySourceFactor = 1;
constexpr std::size_t kEntropyPoolSize     = 200;
constexpr std::size_t kPasswordMin         = 8;
constexpr std::size_t kPasswordMax         = 100;
};

#endif

