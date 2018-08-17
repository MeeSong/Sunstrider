#include "stdafx.h"
#include "ProcessorExecute.h"


extern"C"
{
    VOID NTAPI KeGenericCallDpc(
        __in PKDEFERRED_ROUTINE Routine,
        __in_opt PVOID Context);

    LOGICAL KeSignalCallDpcSynchronize(
        __in PVOID SystemArgument2);

    VOID KeSignalCallDpcDone(
        __in PVOID SystemArgument1);

}

auto ProcessorExecute($ProcessorrExecuteRoutine aRoutine, void * aContext)
-> void
{
    struct DpcContext
    {
        $ProcessorrExecuteRoutine   Routine;
        PVOID                       Context;
    };

    auto vContext = DpcContext{ aRoutine, aContext };

    KeGenericCallDpc([](
        PKDPC /*aDpc*/, PVOID aContext, PVOID aBarrier, PVOID aReverseBarrier) -> void
    {
        auto vContext = static_cast<DpcContext*>(aContext);
        vContext->Routine(KeGetCurrentProcessorNumber(), vContext->Context);

        KeSignalCallDpcSynchronize(aReverseBarrier);
        KeSignalCallDpcDone(aBarrier);
    }, &vContext);
}
