#include "stdafx.h"
#include "PoolTagNote.h"



namespace Sunstrider
{
    
    PoolTagNote::PoolTagNote(__in ExtExtension* aExt)
    {
        aExt->m_Control->GetExtensionFunction(0,
            "GetPoolTagDescription",
            reinterpret_cast<FARPROC*>(&_GetPoolTagDescription));
    }

    auto PoolTagNote::get(__in ULONG aTag) const 
        -> std::string
    {
        auto vResult = std::string();

        for (;;)
        {
            if (!_GetPoolTagDescription)
            {
                break;
            }

            DEBUG_POOLTAG_DESCRIPTION vTagInfo = { sizeof(vTagInfo) };
            auto hr = _GetPoolTagDescription(aTag, &vTagInfo);
            if (FAILED(hr))
            {
                break;
            }

            char vDesc[400] = {};
            if (vTagInfo.Description[0])
            {
                hr = StringCbPrintfA(vDesc, sizeof(vDesc),
                    "  Pooltag %4.4s : %s", (char*)&aTag, vTagInfo.Description);
            }
            else
            {
                hr = StringCbPrintfA(vDesc, sizeof(vDesc),
                    "  Pooltag %4.4s : Unknown", (char*)&aTag);
            }

            char vBinary[100] = {};
            if (vTagInfo.Binary[0])
            {
                hr = StringCbPrintfA(vBinary, sizeof(vBinary),
                    ", Binary : %s", vTagInfo.Binary);
            }

            char vOwner[100] = {};
            if (vTagInfo.Owner[0])
            {
                hr = StringCbPrintfA(vOwner, sizeof(vOwner),
                    ", Owner : %s", vTagInfo.Owner);
            }

            vResult = vDesc + std::string(vBinary) + vOwner;
            break;
        }

        return std::move(vResult);
    }

}
