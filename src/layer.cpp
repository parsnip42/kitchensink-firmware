#include "layer.h"

// Layer::Layer(const KeyId list[5][20])
// {
//     for (auto& mappingRow : mMapping)
//     {
//         mappingRow.fill(KeyId::None);
//     }
    
//     for (size_t row(0); row < kRows; ++row)
//     {
//         for (size_t column(0); column < kColumns; ++column)
//         {
//             mMapping[row][column] = list[row][column];
//         }
//     }
// }

Layer::Layer(const std::initializer_list<std::initializer_list<KeyId>>& list)
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

