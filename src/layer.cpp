#include "layer.h"

Layer::Layer()
{
    for (auto& mappingRow : mMapping)
    {
        mappingRow.fill(KeyId::None);
    }
}

Layer::Layer(const char*                                                name,
             const std::initializer_list<std::initializer_list<KeyId>>& list)
    : mName(name)
{
    for (auto& mappingRow : mMapping)
    {
        mappingRow.fill(KeyId::None);
    }
    
    size_t row(0);
    
    for (const auto& rowEntry : list)
    {
        size_t column(0);
        
        for (const auto& keyId : rowEntry)
        {
            mMapping[row][column] = keyId;
            
            if (++column >= kColumns)
            {
                break;
            };
        }

        if (++row >= kRows)
        {
            break;
        }
    }
}

