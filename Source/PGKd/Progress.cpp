#include "stdafx.h"
#include "Progress.h"


namespace Sunstrider
{

    Progress::Progress(__in ExtExtension * aExt)
        : _Ext(aExt)
        , _Progress(0)
    { }

    Progress::~Progress()
    {
        _Ext->Out("\n");
    }

    Progress & Progress::operator++()
    {
        if (_Progress == 70)
        {
            _Progress = 0, _Ext->Out("\n");
        }
        ++_Progress, _Ext->Out(".");

        return *this;
    }


}
