#include "layer.h"

Layer::Layer(const std::initializer_list<std::initializer_list<KeyId>>& list)
{
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

