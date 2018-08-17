#pragma once

#include <memory>

namespace std
{
    namespace experimental
    {

        template<typename T, typename D>
        inline auto scope_guard(T* aValue, D aDeleter)
        {
            return std::unique_ptr<T, D>(aValue, aDeleter);
        }

    }
}
