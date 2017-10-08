#ifndef INCLUDED_MCP23017_H
#define INCLUDED_MCP23017_H

#include <cstdint>

namespace MCP23017
{
constexpr uint8_t IODIRA = 0x00;
constexpr uint8_t IODIRB = 0x01;
constexpr uint8_t GPPUA  = 0x0c;
constexpr uint8_t GPPUB  = 0x0d;
constexpr uint8_t GPIOA  = 0x12;
constexpr uint8_t GPIOB  = 0x13;
};

#endif
