#include "stdafx.h"
#include <intrin.h>
#include "ProcessorExecute.h"

#include "main.tmh" // Windows software trace preprocessor

//////////////////////////////////////////////////////////////////////////

#pragma pack(push, 1)
typedef struct _KDESCRIPTOR
{
    UINT16  Limit;
    PVOID   Base;
}KDESCRIPTOR, *PKDESCRIPTOR;
#pragma pack(pop)

extern"C"
{
    DRIVER_INITIALIZE DriverEntry;
}

static auto AdjustIDTLimit(UINT16 aDiff)
-> NTSTATUS
{
    NTSTATUS vStatus = STATUS_SUCCESS;

    TraceEntry();
    for (;;)
    {
        static UINT16 sOldLimit = 0;
        if (0 == aDiff)
        {
            if (0 == sOldLimit)
            {
                break;
            }
            aDiff = sOldLimit;
        }

        ProcessorExecute([](UINT32 aProcessorNumber, void* aContext) -> void
        {
            auto vLimitDiff = (INT16)(SIZE_T)aContext;
            auto vIdt       = KDESCRIPTOR{};

            __sidt(&vIdt);

            if (0 == sOldLimit)
            {
                sOldLimit = vIdt.Limit;
            }
            vIdt.Limit = vLimitDiff;

            __lidt(&vIdt);

            TraceInfo("Cpu[%d] idt base: 0x%p, limit: 0x%04X to 0x%04X", aProcessorNumber, vIdt.Base, sOldLimit, vIdt.Limit);

        }, (void*)(SIZE_T)aDiff);
        
        break;
    }
    TraceExit(vStatus);

    return vStatus;
}

static auto DriverUnload(PDRIVER_OBJECT aDriverObject)
-> void
{
    AdjustIDTLimit(static_cast<UINT16>(0u));

    WPP_CLEANUP(aDriverObject);
}

auto DriverEntry(PDRIVER_OBJECT aDriverObject, PUNICODE_STRING aRegistryPath)
-> NTSTATUS
{
    NTSTATUS vStatus = STATUS_UNSUCCESSFUL;

    for (;;)
    {
        WPP_INIT_TRACING(aDriverObject, aRegistryPath);

        vStatus = AdjustIDTLimit(static_cast<UINT16>(-1));
        if (!NT_SUCCESS(vStatus))
        {
            break;
        }
        
        aDriverObject->DriverUnload = DriverUnload;
        break;
    }
    TraceReturn(vStatus);

    if (!NT_SUCCESS(vStatus))
    {
        DriverUnload(aDriverObject);
    }

    return vStatus;
}
