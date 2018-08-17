#pragma once

#include <string>

namespace Sunstrider
{

    class PoolTagNote
    {
        PGET_POOL_TAG_DESCRIPTION   _GetPoolTagDescription = nullptr;

    public:
        PoolTagNote(__in ExtExtension* aExt);
        
        auto get(__in ULONG aTag) const 
            -> std::string;
    };

}
