#pragma once
#include <cstdint>


namespace Sunstrider
{

    class Progress
    {
        ExtExtension*   _Ext        = nullptr;
        std::uint64_t   _Progress   = 0;

    public:
        Progress(__in ExtExtension* aExt);

        ~Progress();

        Progress& operator++();
    };

}
