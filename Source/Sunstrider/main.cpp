#include "stdafx.h"

#include "main.tmh" // Windows software trace preprocessor

extern"C"
{
    DRIVER_INITIALIZE DriverEntry;
}

static auto DriverUnload(PDRIVER_OBJECT aDriverObject)
-> void
{
    WPP_CLEANUP(aDriverObject);
}

auto DriverEntry(PDRIVER_OBJECT aDriverObject, PUNICODE_STRING aRegistryPath)
-> NTSTATUS
{
    NTSTATUS vStatus = STATUS_UNSUCCESSFUL;

    for (;;)
    {
        WPP_INIT_TRACING(aDriverObject, aRegistryPath);



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
