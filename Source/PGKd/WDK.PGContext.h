#pragma once
#include <winternl.h>

#pragma warning(push)
#pragma warning(disable: 4201)
namespace wdk
{

#define __Append$(x, y) x##y
#define Append$(x, y)   __Append$(x, y)
#define AutoInc$(x)     Append$(x, __COUNTER__)
#define Unkonwn$        AutoInc$(_Unknown)


    struct PGProtectCode
    {
        UINT64  Routine;
        UINT64  RoutineBytes;
    };

    struct PGProtectValue
    {
        UINT64  Address;
        UINT64  Value;
    };

    struct PGProtectCode2
    {
        UINT64  Unkonwn$;
        UINT64  Routine;
        UINT32  RoutineBytes;
        UINT32  Unkonwn$;
        UINT64  Unkonwn$;
        UINT64  Reserved[2];
    };

    struct PGHashValidationBlock
    {
        UINT64  Unkonwn$;
        UINT64  Address;
        UINT32  Bytes;
        UINT32  Hash;
        UINT64  Unkonwn$;
        UINT64  Unkonwn$;
        UINT64  Unkonwn$;
    };

    template<UINT64 _NumberOfStrs>
    struct PGProtectString
    {
        UINT64  Bytes;          // UINT64 * (2 + Count)
        UINT64  Flags;
        UINT64  Strings[_NumberOfStrs];
    };

    namespace build_7600
    {
        struct PGContextHeader
        {
            enum : UINT32 
            {
                VerificationFunctionBytes = 0xC4 
            };

            UINT8   PatchGuardVerification[VerificationFunctionBytes];
            UINT32  ContextSizeInQWord;
        };

        struct PGContext : public PGContextHeader
        {
            UINT64  ExAcquireResourceSharedLite;
            UINT64  ExAllocatePoolWithTag;
            UINT64  ExFreePool;
            UINT64  ExMapHandleToPointer;
            UINT64  ExQueueWorkItem;
            UINT64  ExReleaseResourceLite;
            UINT64  ExUnlockHandleTableEntry;
            UINT64  ExfAcquirePushLockExclusive;
            UINT64  ExfReleasePushLockExclusive;
            UINT64  KeAcquireInStackQueuedSpinLockAtDpcLevel;
            UINT64  ExAcquireSpinLockShared;
            UINT64  KeBugCheckEx;
            UINT64  KeDelayExecutionThread;
            UINT64  KeEnterCriticalRegionThread;
            UINT64  KeLeaveCriticalRegion;
            UINT64  KeEnterGuardedRegion;
            UINT64  KeLeaveGuardedRegion;
            UINT64  KeReleaseInStackQueuedSpinLockFromDpcLevel;
            UINT64  ExReleaseSpinLockShared;
            UINT64  KeRevertToUserAffinityThread;
            UINT64  KeProcessorGroupAffinity;
            UINT64  KeSetSystemGroupAffinityThread;
            UINT64  KeSetTimer;
            UINT64  LdrResFindResource;
            UINT64  MmDbgCopyMemory;
            UINT64  ObfDereferenceObject;
            UINT64  ObReferenceObjectByName;
            UINT64  RtlAssert;
            UINT64  RtlImageDirectoryEntryToData;
            UINT64  RtlImageNtHeader;
            UINT64  RtlLookupFunctionTable;
            UINT64  RtlSectionTableFromVirtualAddress;
            UINT64  DbgPrint;
            UINT64  DbgPrintEx;
            UINT64  KiProcessListHead;
            UINT64  KiProcessListLock;
            UINT64  ObpTypeObjectType;
            UINT64  PsActiveProcessHead;
            UINT64  PsInvertedFunctionTable;
            UINT64  PsLoadedModuleList;
            UINT64  PsLoadedModuleResource;
            UINT64  PsLoadedModuleSpinLock;
            UINT64  PspActiveProcessLock;
            UINT64  PspCidTable;
            UINT64  SwapContext;
            UINT64  EnlightenedSwapContext;
            UINT64  Unkonwn0;
            UINT64  Unkonwn1;
            UINT64  Unkonwn2;
            UINT64  WorkerRoutine;
            UINT64  WorkerRoutineContext;
            UINT32  Unkonwn3;
            UINT32  Unkonwn4;
            UINT64  Prcb;
            UINT64  PGPageBase;
            UINT64  DcpRoutineToBeScheduled;            // E.g nt!ExpTimeZoneDpcRoutine

            UINT32  Unkonwn$;
            UINT32  Unkonwn$;

            UINT32  OffsetOfPGSelfValidation;           // nt!PGSelfValidation
            UINT32  OffsetOfRtlLookupFunctionEntryEx;   // nt!RtlLookupFunctionEntryEx
            UINT32  OffsetOfFsRtlUninitializeSmallMcb;  // nt!FsRtlUninitializeSmallMcb
            UINT32  OffsetOfPGProtectCode2Table;        // PGProtectCode2[?]

            UINT64  Unkonwn7[14];

            UINT64  IsTiggerPG;
            UINT64  BugCheckArg0;
            UINT64  BugCheckArg1;
            UINT64  BugCheckArg3;
            UINT64  BugCheckArg2;

            UINT64  Unkonwn$;

            UINT32  NumberOfProtectCodes;
            UINT32  NumberOfProtectValues;

            // PGProtectCode   ProtectCodes[NumberOfProtectCodes];
            // PGProtectValue  ProtectValues[NumberOfProtectValues];
        };
        static_assert(sizeof(PGContext) == 0x340, "sizeof(PGContext) != 0x340");
        
    }

    namespace build_7601
    {
        using namespace build_7600;
    }

    namespace build_9200
    {
        using PGContextHeader = build_7601::PGContextHeader;

        struct PGContext : public PGContextHeader
        {
            UINT64  ExAcquireResourceSharedLite;
            UINT64  ExAllocatePoolWithTag;
            UINT64  ExFreePool;
            UINT64  ExMapHandleToPointer;
            UINT64  ExQueueWorkItem;
            UINT64  ExReleaseResourceLite;
            UINT64  ExUnlockHandleTableEntry;
            UINT64  ExfAcquirePushLockExclusive;
            UINT64  ExfReleasePushLockExclusive;
            UINT64  KeAcquireInStackQueuedSpinLockAtDpcLevel;
            UINT64  ExAcquireSpinLockShared;
            UINT64  KeBugCheckEx;
            UINT64  KeDelayExecutionThread;
            UINT64  KeEnterCriticalRegionThread;
            UINT64  KeLeaveCriticalRegion;
            UINT64  KeEnterGuardedRegion;
            UINT64  KeLeaveGuardedRegion;
            UINT64  KeReleaseInStackQueuedSpinLockFromDpcLevel;
            UINT64  ExReleaseSpinLockShared;
            UINT64  KeRevertToUserAffinityThread;
            UINT64  KeProcessorGroupAffinity;
            UINT64  KeSetSystemGroupAffinityThread;
            UINT64  KeSetCoalescableTimer;
            UINT64  LdrResFindResource;
            UINT64  MmDbgCopyMemory;
            UINT64  ObfDereferenceObject;
            UINT64  ObReferenceObjectByName;
            UINT64  RtlImageDirectoryEntryToData;
            UINT64  RtlImageNtHeader;
            UINT64  RtlLookupFunctionTable;
            UINT64  RtlSectionTableFromVirtualAddress;
            UINT64  DbgPrint;
            UINT64  MmAllocateIndependentPages;
            UINT64  MmFreeIndependentPages;
            UINT64  MmSetPageProtection;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  RtlLookupFunctionEntry;
            UINT64  KeAcquireSpinLockRaiseToDpc;
            UINT64  KeReleaseSpinLock;
            UINT64  MmGetSessionById;
            UINT64  MmGetNextSession;
            UINT64  MmQuitNextSession;
            UINT64  MmAttachSession;
            UINT64  MmDetachSession;
            UINT64  MmGetSessionIdEx;
            UINT64  KeInsertQueueApc;
            UINT64  KeWaitForSingleObject;
            UINT64  PsCreateSystemThread; // ??
            UINT64  ExReferenceCallBackBlock;
            UINT64  ExGetCallBackBlockRoutine;
            UINT64  ExDereferenceCallBackBlock;
            UINT64  KiScbQueueScanWorker;
            UINT64  KiProcessListHead;
            UINT64  KiProcessListLock;
            UINT64  ObpTypeObjectType;
            UINT64  PsActiveProcessHead;
            UINT64  PsInvertedFunctionTable;
            UINT64  PsLoadedModuleList;
            UINT64  PsLoadedModuleResource;
            UINT64  PsLoadedModuleSpinLock;
            UINT64  PspActiveProcessLock;
            UINT64  PspCidTable;
            UINT64  SwapContext;
            UINT64  EnlightenedSwapContext;
            UINT64  Unkonwn$;
            UINT64  ExpUuidLock;
            UINT64  AlpcpPortListLock;
            UINT64  KeServiceDescriptorTable;
            UINT64  KeServiceDescriptorTableShadow;
            UINT64  VfThunksExtended;
            UINT64  PsWin32CallBack;
            UINT64  Unkonwn$;                          // Global-Var In KiMarkBugCheckRegions;
            UINT64  KiTableInformation;
            UINT64  KxUnexpectedInterrupt0;
            UINT64  Unkonwn$[2];
            UINT64  Unkonwn$;
            UINT64  ExNode0ListEntry;                   // &ExNode0.ListEntry
            UINT64  WorkerRoutine;
            UINT64  WorkerRoutineContext;
            UINT64  Unkonwn$;
            UINT64  Prcb;
            UINT64  PGPageBase;
            UINT64  SecondParamOfEndOfUninitialize;
            UINT64  DcpRoutineToBeScheduled;            // E.g INITKDBG: nt!KiTimerDispatch or nt!ExpCenturyDpcRoutine

            UINT32  Unkonwn$;                          // NumberOfXXXX
            UINT32  Unkonwn$;

            UINT32  OffsetOfPGSelfValidation;           // INITKDBG: nt!PGSelfValidation
            UINT32  OffsetOfRtlLookupFunctionEntryEx;   // nt!RtlLookupFunctionEntryEx
            UINT32  OffsetOfFsRtlUninitializeSmallMcb;  // nt!FsRtlUninitializeSmallMcb
            UINT32  EndOffsetOf;

            UINT64  SpinLock;

            UINT32  OffsetOfPGHashValidationBlockTable; // PGHashValidationBlock[?]
            UINT32  Unkonwn$;

            UINT64  Unkonwn$[16];

            UINT64  BaseOfNtos;
            UINT64  BaseOfHal;
            UINT64  BaseOfNtosNtHeader;

            UINT64  IsTiggerPG;
            UINT64  BugCheckArg0;
            UINT64  BugCheckArg1;
            UINT64  BugCheckArg3;
            UINT64  BugCheckArg2;

            PGProtectString<4> PGProtectStrings;

            UINT64  Unkonwn$[4];

            UINT64  BaseOfWin32k;

            UINT64  Unkonwn$[10];

            UINT32  NumberOfProtectCodes;
            UINT32  NumberOfProtectValues;

            // PGProtectCode   ProtectCodes[NumberOfProtectCodes];
            // PGProtectValue  ProtectValues[NumberOfProtectValues];
        };
    }

    namespace build_9600
    {
        using PGContextHeader = build_9200::PGContextHeader;

        struct PGContext : public PGContextHeader
        {
            UINT64  ExAcquireResourceSharedLite;
            UINT64  ExAcquireResourceExclusiveLite;
            UINT64  ExAllocatePoolWithTag;
            UINT64  ExFreePool;
            UINT64  ExMapHandleToPointer;
            UINT64  ExQueueWorkItem;
            UINT64  ExReleaseResourceLite;
            UINT64  ExUnlockHandleTableEntry;
            UINT64  ExfAcquirePushLockExclusive;
            UINT64  ExfReleasePushLockExclusive;
            UINT64  ExfAcquirePushLockShared;
            UINT64  ExfReleasePushLockShared;
            UINT64  KeAcquireInStackQueuedSpinLockAtDpcLevel;
            UINT64  ExAcquireSpinLockSharedAtDpcLevel;
            UINT64  KeBugCheckEx;
            UINT64  KeDelayExecutionThread;
            UINT64  KeEnterCriticalRegionThread;
            UINT64  KeLeaveCriticalRegion;
            UINT64  KeEnterGuardedRegion;
            UINT64  KeLeaveGuardedRegion;
            UINT64  KeReleaseInStackQueuedSpinLockFromDpcLevel;
            UINT64  ExReleaseSpinLockSharedFromDpcLevel;
            UINT64  KeRevertToUserAffinityThread;
            UINT64  KeProcessorGroupAffinity;
            UINT64  KeSetSystemGroupAffinityThread;
            UINT64  KeSetCoalescableTimer;
            UINT64  ObfDereferenceObject;
            UINT64  ObReferenceObjectByName;
            UINT64  RtlImageDirectoryEntryToData;
            UINT64  RtlImageNtHeader;
            UINT64  RtlLookupFunctionTable;
            UINT64  RtlPcToFileHeader;
            UINT64  RtlSectionTableFromVirtualAddress;
            UINT64  DbgPrint;
            UINT64  MmAllocateIndependentPages;
            UINT64  MmFreeIndependentPages;
            UINT64  MmSetPageProtection;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  RtlLookupFunctionEntry;
            UINT64  KeAcquireSpinLockRaiseToDpc;
            UINT64  KeReleaseSpinLock;
            UINT64  MmGetSessionById;
            UINT64  MmGetNextSession;
            UINT64  MmQuitNextSession;
            UINT64  MmAttachSession;
            UINT64  MmDetachSession;
            UINT64  MmGetSessionIdEx;
            UINT64  MmIsSessionAddress;
            UINT64  KeInsertQueueApc;
            UINT64  KeWaitForSingleObject;
            UINT64  PsCreateSystemThread;
            UINT64  ExReferenceCallBackBlock;
            UINT64  ExGetCallBackBlockRoutine;
            UINT64  ExDereferenceCallBackBlock;
            UINT64  KiScbQueueScanWorker;
            UINT64  PspEnumerateCallback;
            UINT64  CmpEnumerateCallback;
            UINT64  DbgEnumerateCallback;
            UINT64  ExpEnumerateCallback;
            UINT64  ExpGetNextCallback;
            UINT64  PopPoCoalescinCallback_;
            UINT64  KiSchedulerApcTerminate;
            UINT64  KiSchedulerApc;
            UINT64  PopPoCoalescinCallback;
            UINT64  PGSelfEncryptWaitAndDecrypt;
            UINT64  KiGetInterruptObjectAddress;
            UINT64  KiWaitAlways;
            UINT64  KiEntropyTimingRoutine;
            UINT64  KiProcessListHead;
            UINT64  KiProcessListLock;
            UINT64  ObpTypeObjectType;
            UINT64  IoDriverObjectType;
            UINT64  PsActiveProcessHead;
            UINT64  PsInvertedFunctionTable;
            UINT64  PsLoadedModuleList;
            UINT64  PsLoadedModuleResource;
            UINT64  PsLoadedModuleSpinLock;
            UINT64  PspActiveProcessLock;
            UINT64  PspCidTable;
            UINT64  ExpUuidLock;
            UINT64  AlpcpPortListLock;
            UINT64  KeServiceDescriptorTable;
            UINT64  KeServiceDescriptorTableShadow;
            UINT64  VfThunksExtended;
            UINT64  PsWin32CallBack;
            UINT64  Unkonwn$;              // Global-Var In KiMarkBugCheckRegions;
            UINT64  KiTableInformation;
            UINT64  HandleTableListHead;
            UINT64  HandleTableListLock;
            UINT64  ObpKernelHandleTable;
            UINT64  KiUserSharedData;       // 0xFFFFF78000000000
            UINT64  KiWaitNever;
            UINT64  KxUnexpectedInterrupt0; // KiKvaShadow ? KiIsrThunkShadow : KxUnexpectedInterrupt0


        };
    }

    namespace build_10240
    {
        struct PGContextHeader
        {
            enum : UINT32
            {
                VerificationFunctionBytes = 0xC4
            };

            UINT8   PatchGuardVerification[VerificationFunctionBytes];
            UINT32  ContextSizeInQWord;
            UINT64  Reserved[2];
        };

        struct PGContext : public PGContextHeader
        {
            UINT64  ExAcquireResourceSharedLite;
            UINT64  ExAcquireResourceExclusiveLite;
            UINT64  ExAllocatePoolWithTag;
            UINT64  ExFreePool;
            UINT64  ExMapHandleToPointer;
            UINT64  ExQueueWorkItem;
            UINT64  ExReleaseResourceLite;
            UINT64  ExUnlockHandleTableEntry;
            UINT64  ExAcquirePushLockExclusiveEx;
            UINT64  ExReleasePushLockExclusiveEx;
            UINT64  ExAcquirePushLockSharedEx;
            UINT64  ExReleasePushLockSharedEx;
            UINT64  KeAcquireInStackQueuedSpinLockAtDpcLevel;
            UINT64  ExAcquireSpinLockSharedAtDpcLevel;
            UINT64  KeBugCheckEx;
            UINT64  KeDelayExecutionThread;
            UINT64  KeEnterCriticalRegionThread;
            UINT64  KeLeaveCriticalRegion;
            UINT64  KeEnterGuardedRegion;
            UINT64  KeLeaveGuardedRegion;
            UINT64  KeReleaseInStackQueuedSpinLockFromDpcLevel;
            UINT64  ExReleaseSpinLockSharedFromDpcLevel;
            UINT64  KeRevertToUserAffinityThread;
            UINT64  KeProcessorGroupAffinity;
            UINT64  KeSetSystemGroupAffinityThread;
            UINT64  KeSetCoalescableTimer;
            UINT64  ObfDereferenceObject;
            UINT64  ObReferenceObjectByName;
            UINT64  RtlImageDirectoryEntryToData;
            UINT64  RtlImageNtHeader;
            UINT64  RtlLookupFunctionTable;
            UINT64  RtlPcToFileHeader;
            UINT64  RtlSectionTableFromVirtualAddress;
            UINT64  DbgPrint;
            UINT64  MmAllocateIndependentPages;
            UINT64  MmFreeIndependentPages;
            UINT64  MmSetPageProtection;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  RtlLookupFunctionEntry;
            UINT64  KeAcquireSpinLockRaiseToDpc;
            UINT64  KeReleaseSpinLock;
            UINT64  MmGetSessionById;
            UINT64  MmGetNextSession;
            UINT64  MmQuitNextSession;
            UINT64  MmAttachSession;
            UINT64  MmDetachSession;
            UINT64  MmGetSessionIdEx;
            UINT64  MmIsSessionAddress;
            UINT64  KeInsertQueueApc;
            UINT64  KeWaitForSingleObject;
            UINT64  PsCreateSystemThread;
            UINT64  ExReferenceCallBackBlock;
            UINT64  ExGetCallBackBlockRoutine;
            UINT64  ExDereferenceCallBackBlock;
            UINT64  KiScbQueueScanWorker;
            UINT64  PspEnumerateCallback;
            UINT64  CmpEnumerateCallback;
            UINT64  DbgEnumerateCallback;
            UINT64  ExpEnumerateCallback;
            UINT64  ExpGetNextCallback;
            UINT64  EmpCheckErrataList_;
            UINT64  KiSchedulerApcTerminate;
            UINT64  KiSchedulerApc;
            UINT64  EmpCheckErrataList;
            UINT64  PGSelfEncryptWaitAndDecrypt;
            UINT64  MmAllocatePagesForMdlEx;
            UINT64  MmAllocateMappingAddress;
            UINT64  MmMapLockedPagesWithReservedMapping;
            UINT64  MmUnmapReservedMapping;
            UINT64  Unkonwn$; // nt!$$116+0x2e8
            UINT64  Unkonwn$; // nt!$$116+0x350
            UINT64  MmAcquireLoadLock;
            UINT64  MmReleaseLoadLock;
            UINT64  KeEnumerateQueueApc;
            UINT64  KeIsApcRunningThread;
            UINT64  Unkonwn$; // nt!$$115
            UINT64  PsAcquireProcessExitSynchronization;
            UINT64  PsReleaseProcessExitSynchronization;
            UINT64  PsGetNextProcess;
            UINT64  MmIsSessionLeaderProcess;
            UINT64  PsInvokeWin32Callout;
            UINT64  MmEnumerateAddressSpaceAndReferenceImages;
            UINT64  PsGetProcessProtection;
            UINT64  PsGetProcessSignatureLevel;
            UINT64  PsGetProcessSectionBaseAddress;
            UINT64  SeCompareSigningLevels;
            UINT64  KeComputeSha256;
            UINT64  KeComputeParallelSha256;
            UINT64  KeSetEvent;
            UINT64  RtlpConvertFunctionEntry;
            UINT64  RtlpLookupPrimaryFunctionEntry;
            UINT64  RtlIsMultiSessionSku;
            UINT64  KiGetInterruptObjectAddress;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  PsInitialSystemProcess;
            UINT64  KiWaitAlways;
            UINT64  KiEntropyTimingRoutine;
            UINT64  KiProcessListHead;
            UINT64  KiProcessListLock;
            UINT64  ObpTypeObjectType;
            UINT64  IoDriverObjectType;
            UINT64  PsActiveProcessHead;
            UINT64  PsInvertedFunctionTable;
            UINT64  PsLoadedModuleList;
            UINT64  PsLoadedModuleResource;
            UINT64  PsLoadedModuleSpinLock;
            UINT64  PspActiveProcessLock;
            UINT64  PspCidTable;
            UINT64  ExpUuidLock;
            UINT64  AlpcpPortListLock;
            UINT64  KeServiceDescriptorTable;
            UINT64  KeServiceDescriptorTableShadow;
            UINT64  VfThunksExtended;
            UINT64  PsWin32CallBack;
            UINT64  Unkonwn$;
            UINT64  KiTableInformation;
            UINT64  HandleTableListHead;
            UINT64  HandleTableListLock;
            UINT64  ObpKernelHandleTable;
            UINT64  KiUserSharedData;       // 0xFFFFF78000000000
            UINT64  KiWaitNever;
            UINT64  SeProtectedMapping;
            UINT64  KiInterruptThunk;
            UINT64  CcPeriodicEvent;
            UINT64  KxUnexpectedInterrupt0;

            UINT64  Unkonwn$[2];
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$[2];

            UINT64  WorkerRoutine;
            UINT64  WorkerRoutineContext;

            UINT64  Unkonwn$;

            UINT64  Prcb;
            UINT64  PGPageBase;
            UINT64  SecondParamOfEndOfUninitialize;
            UINT64  DcpRoutineToBeScheduled;

            UINT32  Unkonwn$;                          // NumberOfXXXX
            UINT32  Unkonwn$;

            UINT32  OffsetOfPGSelfValidation;           // INITKDBG: nt!PGSelfValidation
            UINT32  OffsetOfRtlLookupFunctionEntryEx;   // nt!RtlLookupFunctionEntryEx
            UINT32  OffsetOfFsRtlUninitializeSmallMcb;  // nt!FsRtlUninitializeSmallMcb
            UINT32  OffsetOfFsRtlUnknown0;              // xref: nt!FsRtlMdlReadCompleteDevEx
            UINT32  OffsetOfFsRtlUnkonwn1;              // xref: nt!FsRtlMdlReadCompleteDevEx
            UINT32  EndOffsetOf;

            UINT64  SpinLock;

            UINT64  Unkonwn$[14];

            UINT64  BaseOfNtos;
            UINT64  BaseOfHal;
            UINT64  BaseOfNtosNtHeader;

            UINT64  IsTiggerPG;
            UINT64  BugCheckArg0;
            UINT64  BugCheckArg1;
            UINT64  BugCheckArg3;
            UINT64  BugCheckArg2;

            PGProtectString<4> PGProtectStrings;

            UINT64  Unkonwn$[4];

            UINT64  BaseOfWin32k;

            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$[8];

            UINT64  _UnknownListEntry0;
            UINT64  KiDispatchCallout2;
            UINT64  EmpCheckErrataList2;
            UINT64  _UnknownListEntry1;

            UINT64  Unkonwn$[11];

            UINT32  NumberOfProtectCodes;
            UINT32  NumberOfProtectValues;

            // PGProtectCode   ProtectCodes[NumberOfProtectCodes];
            // PGProtectValue  ProtectValues[NumberOfProtectValues];
        };
    }

    namespace build_10586
    {
        struct PGContextHeader
        {
            enum : UINT32
            {
                VerificationFunctionBytes = 0xC4
            };

            UINT8   PatchGuardVerification[VerificationFunctionBytes];
            UINT32  ContextSizeInQWord;
            UINT64  Reserved[3];
        };

        struct PGContext : public PGContextHeader
        {
            UINT64  ExAcquireResourceSharedLite;
            UINT64  ExAcquireResourceExclusiveLite;
            UINT64  ExAllocatePoolWithTag;
            UINT64  ExFreePool;
            UINT64  ExMapHandleToPointer;
            UINT64  ExQueueWorkItem;
            UINT64  ExReleaseResourceLite;
            UINT64  ExUnlockHandleTableEntry;
            UINT64  ExAcquirePushLockExclusiveEx;
            UINT64  ExReleasePushLockExclusiveEx;
            UINT64  ExAcquirePushLockSharedEx;
            UINT64  ExReleasePushLockSharedEx;
            UINT64  KeAcquireInStackQueuedSpinLockAtDpcLevel;
            UINT64  ExAcquireSpinLockSharedAtDpcLevel;
            UINT64  KeBugCheckEx;
            UINT64  KeDelayExecutionThread;
            UINT64  KeEnterCriticalRegionThread;
            UINT64  KeLeaveCriticalRegion;
            UINT64  KeEnterGuardedRegion;
            UINT64  KeLeaveGuardedRegion;
            UINT64  KeReleaseInStackQueuedSpinLockFromDpcLevel;
            UINT64  ExReleaseSpinLockSharedFromDpcLevel;
            UINT64  KeRevertToUserAffinityThread;
            UINT64  KeProcessorGroupAffinity;
            UINT64  KeSetSystemGroupAffinityThread;
            UINT64  KeSetCoalescableTimer;
            UINT64  ObfDereferenceObject;
            UINT64  ObReferenceObjectByName;
            UINT64  RtlImageDirectoryEntryToData;
            UINT64  RtlImageNtHeader;
            UINT64  RtlLookupFunctionTable;
            UINT64  RtlPcToFileHeader;
            UINT64  RtlSectionTableFromVirtualAddress;
            UINT64  DbgPrint;
            UINT64  MmAllocateIndependentPages;
            UINT64  MmFreeIndependentPages;
            UINT64  MmSetPageProtection;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  RtlLookupFunctionEntry;
            UINT64  KeAcquireSpinLockRaiseToDpc;
            UINT64  KeReleaseSpinLock;
            UINT64  MmGetSessionById;
            UINT64  MmGetNextSession;
            UINT64  MmQuitNextSession;
            UINT64  MmAttachSession;
            UINT64  MmDetachSession;
            UINT64  MmGetSessionIdEx;
            UINT64  MmIsSessionAddress;
            UINT64  KeInsertQueueApc;
            UINT64  KeWaitForSingleObject;
            UINT64  PsCreateSystemThread;
            UINT64  ExReferenceCallBackBlock;
            UINT64  ExGetCallBackBlockRoutine;
            UINT64  ExDereferenceCallBackBlock;
            UINT64  KiScbQueueScanWorker;
            UINT64  PspEnumerateCallback;
            UINT64  CmpEnumerateCallback;
            UINT64  DbgEnumerateCallback;
            UINT64  ExpEnumerateCallback;
            UINT64  ExpGetNextCallback;
            UINT64  EmpCheckErrataList_;
            UINT64  KiSchedulerApcTerminate;
            UINT64  KiSchedulerApc;
            UINT64  EmpCheckErrataList;
            UINT64  PGSelfEncryptWaitAndDecrypt;
            UINT64  MmAllocatePagesForMdlEx;
            UINT64  MmAllocateMappingAddress;
            UINT64  MmMapLockedPagesWithReservedMapping;
            UINT64  MmUnmapReservedMapping;
            UINT64  Unkonwn$; // nt!$$116+0x2e8
            UINT64  Unkonwn$; // nt!$$116+0x350
            UINT64  MmAcquireLoadLock;
            UINT64  MmReleaseLoadLock;
            UINT64  KeEnumerateQueueApc;
            UINT64  KeIsApcRunningThread;
            UINT64  Unkonwn$; // nt!$$115
            UINT64  PsAcquireProcessExitSynchronization;
            UINT64  PsReleaseProcessExitSynchronization;
            UINT64  PsGetNextProcess;
            UINT64  MmIsSessionLeaderProcess;
            UINT64  PsInvokeWin32Callout;
            UINT64  MmEnumerateAddressSpaceAndReferenceImages;
            UINT64  PsGetProcessProtection;
            UINT64  PsGetProcessSignatureLevel;
            UINT64  PsGetProcessSectionBaseAddress;
            UINT64  SeCompareSigningLevels;
            UINT64  KeComputeSha256;
            UINT64  KeComputeParallelSha256;
            UINT64  KeSetEvent;
            UINT64  RtlpConvertFunctionEntry;
            UINT64  RtlpLookupPrimaryFunctionEntry;
            UINT64  RtlIsMultiSessionSku;
            UINT64  KiGetInterruptObjectAddress;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  PsInitialSystemProcess;
            UINT64  KiWaitAlways;
            UINT64  KiEntropyTimingRoutine;
            UINT64  KiProcessListHead;
            UINT64  KiProcessListLock;
            UINT64  ObpTypeObjectType;
            UINT64  IoDriverObjectType;
            UINT64  PsActiveProcessHead;
            UINT64  PsInvertedFunctionTable;
            UINT64  PsLoadedModuleList;
            UINT64  PsLoadedModuleResource;
            UINT64  PsLoadedModuleSpinLock;
            UINT64  PspActiveProcessLock;
            UINT64  PspCidTable;
            UINT64  ExpUuidLock;
            UINT64  AlpcpPortListLock;
            UINT64  KeServiceDescriptorTable;
            UINT64  KeServiceDescriptorTableShadow;
            UINT64  VfThunksExtended;
            UINT64  PsWin32CallBack;
            UINT64  Unkonwn$;             // nt!TriageImagePageSize+0x30
            UINT64  KiTableInformation;
            UINT64  HandleTableListHead;
            UINT64  HandleTableListLock;
            UINT64  ObpKernelHandleTable;
            UINT64  KiUserSharedData;       // 0xFFFFF78000000000
            UINT64  KiWaitNever;
            UINT64  SeProtectedMapping;
            UINT64  KiInterruptThunk;
            UINT64  CcPeriodicEvent;
            UINT64  KxUnexpectedInterrupt0; // nt!KiIsrThunk

            UINT64  Unkonwn$[5];

            UINT64  WorkerRoutine;
            UINT64  WorkerRoutineContext;

            UINT64  Unkonwn$;

            UINT64  Prcb;
            UINT64  PGPageBase;
            UINT64  SecondParamOfEndOfUninitialize;
            UINT64  DcpRoutineToBeScheduled;

            UINT32  Unkonwn$;                          // NumberOfXXXX
            UINT32  Unkonwn$;

            UINT32  OffsetOfPGSelfValidation;           // INITKDBG: nt!PGSelfValidation
            UINT32  OffsetOfRtlLookupFunctionEntryEx;   // nt!RtlLookupFunctionEntryEx
            UINT32  OffsetOfFsRtlUninitializeSmallMcb;  // nt!FsRtlUninitializeSmallMcb
            UINT32  OffsetOfFsRtlUnknown0;              // xref: nt!FsRtlMdlReadCompleteDevEx
            UINT32  OffsetOfFsRtlUnkonwn1;              // xref: nt!FsRtlMdlReadCompleteDevEx
            UINT32  EndOffsetOf;

            UINT64  SpinLock;

            UINT64  Unkonwn$[14];

            UINT64  BaseOfNtos;
            UINT64  BaseOfHal;
            UINT64  BaseOfNtosNtHeader;

            UINT64  IsTiggerPG;
            UINT64  BugCheckArg0;
            UINT64  BugCheckArg1;
            UINT64  BugCheckArg3;
            UINT64  BugCheckArg2;

            PGProtectString<4> PGProtectStrings;

            UINT64  Unkonwn$[4];

            UINT64  BaseOfWin32k;

            UINT64  Unkonwn$[25];

            UINT32  NumberOfProtectCodes;
            UINT32  NumberOfProtectValues;

            // PGProtectCode   ProtectCodes[NumberOfProtectCodes];
            // PGProtectValue  ProtectValues[NumberOfProtectValues];
        };
    }

    namespace build_14393
    {
        struct PGContextHeader
        {
            enum : UINT32
            {
                VerificationFunctionBytes = 0xC4
            };

            UINT8   PatchGuardVerification[VerificationFunctionBytes];
            UINT32  ContextSizeInQWord;
            UINT64  Reserved;
        };

        struct PGContext : public PGContextHeader
        {
            UINT64  ExAcquireResourceSharedLite;
            UINT64  ExAcquireResourceExclusiveLite;
            UINT64  ExAllocatePoolWithTag;
            UINT64  ExFreePool;
            UINT64  ExMapHandleToPointer;
            UINT64  ExQueueWorkItem;
            UINT64  ExReleaseResourceLite;
            UINT64  ExUnlockHandleTableEntry;
            UINT64  ExAcquirePushLockExclusiveEx;
            UINT64  ExReleasePushLockExclusiveEx;
            UINT64  ExAcquirePushLockSharedEx;
            UINT64  ExReleasePushLockSharedEx;
            UINT64  KeAcquireInStackQueuedSpinLockAtDpcLevel;
            UINT64  ExAcquireSpinLockSharedAtDpcLevel;
            UINT64  KeBugCheckEx;
            UINT64  KeDelayExecutionThread;
            UINT64  KeEnterCriticalRegionThread;
            UINT64  KeLeaveCriticalRegion;
            UINT64  KeEnterGuardedRegion;
            UINT64  KeLeaveGuardedRegion;
            UINT64  KeReleaseInStackQueuedSpinLockFromDpcLevel;
            UINT64  ExReleaseSpinLockSharedFromDpcLevel;
            UINT64  KeRevertToUserAffinityThread;
            UINT64  KeProcessorGroupAffinity;
            UINT64  KeInitializeEnumerationContext;
            UINT64  KeEnumerateNextProcessor;
            UINT64  KeCountSetBitsAffinityEx;
            UINT64  KeQueryAffinityProcess;
            UINT64  KeQueryAffinityThread;
            UINT64  KeSetSystemGroupAffinityThread;
            UINT64  KeSetCoalescableTimer;
            UINT64  ObfDereferenceObject;
            UINT64  ObReferenceObjectByName;
            UINT64  RtlImageDirectoryEntryToData;
            UINT64  RtlImageNtHeader;
            UINT64  RtlLookupFunctionTable;
            UINT64  RtlPcToFileHeader;
            UINT64  RtlSectionTableFromVirtualAddress;
            UINT64  DbgPrint;
            UINT64  MmAllocateIndependentPages;
            UINT64  MmFreeIndependentPages;
            UINT64  MmSetPageProtection;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  RtlLookupFunctionEntry;
            UINT64  KeAcquireSpinLockRaiseToDpc;
            UINT64  KeReleaseSpinLock;
            UINT64  MmGetSessionById;
            UINT64  MmGetNextSession;
            UINT64  MmQuitNextSession;
            UINT64  MmAttachSession;
            UINT64  MmDetachSession;
            UINT64  MmGetSessionIdEx;
            UINT64  MmIsSessionAddress;
            UINT64  MmIsAddressValid;
            UINT64  MmSessionGetWin32Callouts;
            UINT64  KeInsertQueueApc;
            UINT64  KeWaitForSingleObject;
            UINT64  PsCreateSystemThread;
            UINT64  ExReferenceCallBackBlock;
            UINT64  ExGetCallBackBlockRoutine;
            UINT64  ExDereferenceCallBackBlock;
            UINT64  KiScbQueueScanWorker;
            UINT64  PspEnumerateCallback;
            UINT64  CmpEnumerateCallback;
            UINT64  DbgEnumerateCallback;
            UINT64  ExpEnumerateCallback;
            UINT64  ExpGetNextCallback;
            UINT64  EmpCheckErrataList_;
            UINT64  KiSchedulerApcTerminate;
            UINT64  KiSchedulerApc;
            UINT64  EmpCheckErrataList;
            UINT64  PGSelfEncryptWaitAndDecrypt;
            UINT64  MmAllocatePagesForMdlEx;
            UINT64  MmAllocateMappingAddress;
            UINT64  MmMapLockedPagesWithReservedMapping;
            UINT64  MmUnmapReservedMapping;
            UINT64  Unkonwn$; // nt!$$116+0x2e8
            UINT64  Unkonwn$; // nt!$$116+0x350
            UINT64  MmAcquireLoadLock;
            UINT64  MmReleaseLoadLock;
            UINT64  KeEnumerateQueueApc;
            UINT64  KeIsApcRunningThread;
            UINT64  Unkonwn$; // nt!$$115
            UINT64  PsAcquireProcessExitSynchronization;
            UINT64  PsReleaseProcessExitSynchronization;
            UINT64  PsGetNextProcess;
            UINT64  PsQuitNextProcess;
            UINT64  MmIsSessionLeaderProcess;
            UINT64  PsInvokeWin32Callout;
            UINT64  MmEnumerateAddressSpaceAndReferenceImages;
            UINT64  PsGetProcessProtection;
            UINT64  PsGetProcessSignatureLevel;
            UINT64  PsGetProcessSectionBaseAddress;
            UINT64  SeCompareSigningLevels;
            UINT64  KeComputeSha256;
            UINT64  KeComputeParallelSha256;
            UINT64  KeSetEvent;
            UINT64  RtlpConvertFunctionEntry;
            UINT64  RtlpLookupPrimaryFunctionEntry;
            UINT64  RtlIsMultiSessionSku;
            UINT64  KiEnumerateCallback;
            UINT64  KeStackAttachProcess;
            UINT64  KeUnstackDetachProcess;
            UINT64  KiGetInterruptObjectAddress;
            UINT64  Unkonwn$;
            UINT64  PsInitialSystemProcess;
            UINT64  KiWaitAlways;
            UINT64  KiEntropyTimingRoutine;
            UINT64  KiProcessListHead;
            UINT64  KiProcessListLock;
            UINT64  ObpTypeObjectType;
            UINT64  IoDriverObjectType;
            UINT64  PsActiveProcessHead;
            UINT64  PsInvertedFunctionTable;
            UINT64  PsLoadedModuleList;
            UINT64  PsLoadedModuleResource;
            UINT64  PsLoadedModuleSpinLock;
            UINT64  PspActiveProcessLock;
            UINT64  PspCidTable;
            UINT64  ExpUuidLock;
            UINT64  AlpcpPortListLock;
            UINT64  KeServiceDescriptorTable;
            UINT64  KeServiceDescriptorTableShadow;
            UINT64  KeServiceDescriptorTableFilter;
            UINT64  VfThunksExtended;
            UINT64  PsWin32CallBack;
            UINT64  Unkonwn$;             // nt!TriageImagePageSize+0x30
            UINT64  KiTableInformation;
            UINT64  HandleTableListHead;
            UINT64  HandleTableListLock;
            UINT64  ObpKernelHandleTable;
            UINT64  KiUserSharedData;       // 0xFFFFF78000000000
            UINT64  KiWaitNever;
            UINT64  SeProtectedMapping;
            UINT64  KiInterruptThunk;
            UINT64  CcPeriodicEvent;
            UINT64  PageTables;             // 0xFFFFC28000000000
            UINT64  KxUnexpectedInterrupt0; // nt!KiIsrThunk

            UINT64  Unkonwn$[5];

            UINT64  WorkerRoutine;
            UINT64  WorkerRoutineContext;

            UINT64  Unkonwn$;

            UINT64  Prcb;
            UINT64  PGPageBase;
            UINT64  SecondParamOfEndOfUninitialize;
            UINT64  DcpRoutineToBeScheduled;

            UINT32  Unkonwn$;                          // NumberOfXXXX
            UINT32  Unkonwn$;

            UINT32  OffsetOfPGSelfValidation;           // INITKDBG: nt!PGSelfValidation
            UINT32  OffsetOfRtlLookupFunctionEntryEx;   // nt!RtlLookupFunctionEntryEx
            UINT32  OffsetOfFsRtlUninitializeSmallMcb;  // nt!FsRtlUninitializeSmallMcb
            UINT32  OffsetOfFsRtlUnknown0;              // xref: nt!FsRtlMdlReadCompleteDevEx
            UINT32  OffsetOfFsRtlUnkonwn1;              // xref: nt!FsRtlMdlReadCompleteDevEx
            UINT32  EndOffsetOf;

            UINT64  SpinLock;

            UINT64  Unkonwn$[15];

            UINT64  BaseOfNtos;
            UINT64  BaseOfHal;
            UINT64  BaseOfNtosNtHeader;

            UINT64  IsTiggerPG;
            UINT64  BugCheckArg0;
            UINT64  BugCheckArg1;
            UINT64  BugCheckArg3;
            UINT64  BugCheckArg2;

            PGProtectString<4> PGProtectStrings;

            UINT64  Unkonwn$[4];

            UINT64  BaseOfWin32k;

            UINT64  Unkonwn$[25];

            UINT32  NumberOfProtectCodes;
            UINT32  NumberOfProtectValues;

            // PGProtectCode   ProtectCodes[NumberOfProtectCodes];
            // PGProtectValue  ProtectValues[NumberOfProtectValues];
        };
    }

    namespace build_15063
    {
        struct PGContextHeader
        {
            enum : UINT32
            {
                VerificationFunctionBytes = 0xC4
            };

            UINT8   PatchGuardVerification[VerificationFunctionBytes];
            UINT32  ContextSizeInQWord;
            UINT64  Reserved[4];
        };

        struct PGContext : public PGContextHeader
        {
            UINT64  ExAcquireResourceSharedLite;
            UINT64  ExAcquireResourceExclusiveLite;
            UINT64  ExAllocatePoolWithTag;
            UINT64  ExFreePool;
            UINT64  ExMapHandleToPointer;
            UINT64  ExQueueWorkItem;
            UINT64  ExReleaseResourceLite;
            UINT64  ExUnlockHandleTableEntry;
            UINT64  ExAcquirePushLockExclusiveEx;
            UINT64  ExReleasePushLockExclusiveEx;
            UINT64  ExAcquirePushLockSharedEx;
            UINT64  ExReleasePushLockSharedEx;
            UINT64  KeAcquireInStackQueuedSpinLockAtDpcLevel;
            UINT64  ExAcquireSpinLockSharedAtDpcLevel;
            UINT64  KeBugCheckEx;
            UINT64  KeDelayExecutionThread;
            UINT64  KeEnterCriticalRegionThread;
            UINT64  KeLeaveCriticalRegion;
            UINT64  KeEnterGuardedRegion;
            UINT64  KeLeaveGuardedRegion;
            UINT64  KeReleaseInStackQueuedSpinLockFromDpcLevel;
            UINT64  ExReleaseSpinLockSharedFromDpcLevel;
            UINT64  KeRevertToUserAffinityThread;
            UINT64  KeProcessorGroupAffinity;
            UINT64  KeInitializeEnumerationContext;
            UINT64  KeEnumerateNextProcessor;
            UINT64  KeCountSetBitsAffinityEx;
            UINT64  KeQueryAffinityProcess;
            UINT64  KeQueryAffinityThread;
            UINT64  KeSetSystemGroupAffinityThread;
            UINT64  KeSetCoalescableTimer;
            UINT64  ObfDereferenceObject;
            UINT64  ObReferenceObjectByName;
            UINT64  RtlImageDirectoryEntryToData;
            UINT64  RtlImageNtHeader;
            UINT64  RtlLookupFunctionTable;
            UINT64  RtlPcToFileHeader;
            UINT64  RtlSectionTableFromVirtualAddress;
            UINT64  DbgPrint;
            UINT64  MmAllocateIndependentPages;
            UINT64  MmFreeIndependentPages;
            UINT64  MmSetPageProtection;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  RtlLookupFunctionEntry;
            UINT64  KeAcquireSpinLockRaiseToDpc;
            UINT64  KeReleaseSpinLock;
            UINT64  MmGetSessionById;
            UINT64  MmGetNextSession;
            UINT64  MmQuitNextSession;
            UINT64  MmAttachSession;
            UINT64  MmDetachSession;
            UINT64  MmGetSessionIdEx;
            UINT64  MmIsSessionAddress;
            UINT64  MmIsAddressValid;
            UINT64  MmSessionGetWin32Callouts;
            UINT64  KeInsertQueueApc;
            UINT64  KeWaitForSingleObject;
            UINT64  PsCreateSystemThread;
            UINT64  ExReferenceCallBackBlock;
            UINT64  ExGetCallBackBlockRoutine;
            UINT64  ExDereferenceCallBackBlock;
            UINT64  KiScbQueueScanWorker;
            UINT64  PspEnumerateCallback;
            UINT64  CmpEnumerateCallback;
            UINT64  DbgEnumerateCallback;
            UINT64  ExpEnumerateCallback;
            UINT64  ExpGetNextCallback;
            UINT64  EmpCheckErrataList_;
            UINT64  KiSchedulerApcTerminate;
            UINT64  KiSchedulerApc;
            UINT64  EmpCheckErrataList;
            UINT64  PGSelfEncryptWaitAndDecrypt;
            UINT64  MmAllocatePagesForMdlEx;
            UINT64  MmAllocateMappingAddress;
            UINT64  MmMapLockedPagesWithReservedMapping;
            UINT64  MmUnmapReservedMapping;
            UINT64  Unkonwn$; // nt!KiSwInterruptDispatch+0x12b0
            UINT64  Unkonwn$; // nt!KiSwInterruptDispatch+0x1320
            UINT64  MmAcquireLoadLock;
            UINT64  MmReleaseLoadLock;
            UINT64  KeEnumerateQueueApc;
            UINT64  KeIsApcRunningThread;
            UINT64  Unkonwn$; // nt!KiSwInterruptDispatch+0xe80
            UINT64  PsAcquireProcessExitSynchronization;
            UINT64  ObDereferenceProcessHandleTable;
            UINT64  PsGetNextProcess;
            UINT64  PsQuitNextProcess;
            UINT64  MmIsSessionLeaderProcess;
            UINT64  PsInvokeWin32Callout;
            UINT64  MmEnumerateAddressSpaceAndReferenceImages;
            UINT64  PsGetProcessProtection;
            UINT64  PsGetProcessSignatureLevel;
            UINT64  PsGetProcessSectionBaseAddress;
            UINT64  SeCompareSigningLevels;
            UINT64  KeComputeSha256;
            UINT64  KeComputeParallelSha256;
            UINT64  KeSetEvent;
            UINT64  RtlpConvertFunctionEntry;
            UINT64  RtlpLookupPrimaryFunctionEntry;
            UINT64  RtlIsMultiSessionSku;
            UINT64  KiEnumerateCallback;
            UINT64  KeStackAttachProcess;
            UINT64  KeUnstackDetachProcess;
            UINT64  VslVerifyPage;
            UINT64  KiGetInterruptObjectAddress;
            UINT64  Unkonwn$[4];
            UINT64  PsInitialSystemProcess;
            UINT64  KiWaitAlways;
            UINT64  KiEntropyTimingRoutine;
            UINT64  KiProcessListHead;
            UINT64  KiProcessListLock;
            UINT64  ObpTypeObjectType;
            UINT64  IoDriverObjectType;
            UINT64  PsActiveProcessHead;
            UINT64  PsInvertedFunctionTable;
            UINT64  PsLoadedModuleList;
            UINT64  PsLoadedModuleResource;
            UINT64  PsLoadedModuleSpinLock;
            UINT64  PspActiveProcessLock;
            UINT64  PspCidTable;
            UINT64  ExpUuidLock;
            UINT64  AlpcpPortListLock;
            UINT64  KeServiceDescriptorTable;
            UINT64  KeServiceDescriptorTableShadow;
            UINT64  KeServiceDescriptorTableFilter;
            UINT64  VfThunksExtended;
            UINT64  PsWin32CallBack;
            UINT64  Unkonwn$;             // nt!TriageImagePageSize+0x20
            UINT64  KiTableInformation;
            UINT64  HandleTableListHead;
            UINT64  HandleTableListLock;
            UINT64  ObpKernelHandleTable;
            UINT64  KiUserSharedData;       // 0xFFFFF78000000000
            UINT64  KiWaitNever;
            UINT64  SeProtectedMapping;
            UINT64  KiInterruptThunk;
            UINT64  KiStackProtectNotifyEvent;
            UINT64  PageTables;             // fffff900`00000000
            UINT64  RtlpInvertedFunctionTable;
            UINT64  KxUnexpectedInterrupt0; // nt!KiIsrThunk

            UINT64  Unkonwn$[6];

            UINT64  WorkerRoutine;
            UINT64  WorkerRoutineContext;

            UINT64  Unkonwn$;

            UINT64  Prcb;
            UINT64  PGPageBase;
            UINT64  SecondParamOfEndOfUninitialize;
            UINT64  DcpRoutineToBeScheduled;

            UINT32  Unkonwn$;                          // NumberOfXXXX
            UINT32  Unkonwn$;

            UINT32  OffsetOfPGSelfValidation;           // INITKDBG: nt!PGSelfValidation
            UINT32  OffsetOfRtlLookupFunctionEntryEx;   // nt!RtlLookupFunctionEntryEx
            UINT32  OffsetOfFsRtlUninitializeSmallMcb;  // nt!FsRtlUninitializeSmallMcb
            UINT32  OffsetOfFsRtlUnknown0;              // xref: nt!FsRtlMdlReadCompleteDevEx
            UINT32  OffsetOfFsRtlUnkonwn1;              // xref: nt!FsRtlMdlReadCompleteDevEx
            UINT32  EndOffsetOf;

            UINT64  SpinLock;

            UINT64  Unkonwn$[18];

            UINT64  BaseOfNtos;
            UINT64  BaseOfHal;
            UINT64  BaseOfNtosNtHeader;

            UINT64  Unkonwn$[2];

            UINT64  IsTiggerPG;
            UINT64  BugCheckArg0;
            UINT64  BugCheckArg1;
            UINT64  BugCheckArg3;
            UINT64  BugCheckArg2;

            PGProtectString<4> PGProtectStrings;

            UINT64  Unkonwn$[4];

            UINT64  BaseOfWin32k;

            UINT64  Unkonwn$[26];

            UINT32  NumberOfProtectCodes;
            UINT32  NumberOfProtectValues;

            // PGProtectCode   ProtectCodes[NumberOfProtectCodes];
            // PGProtectValue  ProtectValues[NumberOfProtectValues];
        };
    }

    namespace build_16299
    {
        using PGContextHeader = build_10240::PGContextHeader;

        struct PGContext : public PGContextHeader
        {
            UINT64  ExAcquireResourceSharedLite;
            UINT64  ExAcquireResourceExclusiveLite;
            UINT64  ExAllocatePoolWithTag;
            UINT64  ExFreePool;
            UINT64  ExMapHandleToPointer;
            UINT64  ExQueueWorkItem;
            UINT64  ExReleaseResourceLite;
            UINT64  ExUnlockHandleTableEntry;
            UINT64  ExAcquirePushLockExclusiveEx;
            UINT64  ExReleasePushLockExclusiveEx;
            UINT64  ExAcquirePushLockSharedEx;
            UINT64  ExReleasePushLockSharedEx;
            UINT64  KeAcquireInStackQueuedSpinLockAtDpcLevel;
            UINT64  ExAcquireSpinLockSharedAtDpcLevel;
            UINT64  KeBugCheckEx;
            UINT64  KeDelayExecutionThread;
            UINT64  KeEnterCriticalRegionThread;
            UINT64  KeLeaveCriticalRegion;
            UINT64  KeEnterGuardedRegion;
            UINT64  KeLeaveGuardedRegion;
            UINT64  KeReleaseInStackQueuedSpinLockFromDpcLevel;
            UINT64  ExReleaseSpinLockSharedFromDpcLevel;
            UINT64  KeRevertToUserAffinityThread;
            UINT64  KeProcessorGroupAffinity;
            UINT64  KeInitializeEnumerationContext;
            UINT64  KeEnumerateNextProcessor;
            UINT64  KeCountSetBitsAffinityEx;
            UINT64  KeQueryAffinityProcess;
            UINT64  KeQueryAffinityThread;
            UINT64  KeSetSystemGroupAffinityThread;
            UINT64  KeSetCoalescableTimer;
            UINT64  ObfDereferenceObject;
            UINT64  ObReferenceObjectByName;
            UINT64  RtlImageDirectoryEntryToData;
            UINT64  RtlImageNtHeader;
            UINT64  RtlLookupFunctionTable;
            UINT64  RtlPcToFileHeader;
            UINT64  RtlSectionTableFromVirtualAddress;
            UINT64  DbgPrint;
            UINT64  MmAllocateIndependentPages;
            UINT64  MmFreeIndependentPages;
            UINT64  MmSetPageProtection;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  RtlLookupFunctionEntry;
            UINT64  KeAcquireSpinLockRaiseToDpc;
            UINT64  KeReleaseSpinLock;
            UINT64  MmGetSessionById;
            UINT64  MmGetNextSession;
            UINT64  MmQuitNextSession;
            UINT64  MmAttachSession;
            UINT64  MmDetachSession;
            UINT64  MmGetSessionIdEx;
            UINT64  MmIsSessionAddress;
            UINT64  MmIsAddressValid;
            UINT64  MmSessionGetWin32Callouts;
            UINT64  KeInsertQueueApc;
            UINT64  KeWaitForSingleObject;
            UINT64  PsCreateSystemThread;
            UINT64  ExReferenceCallBackBlock;
            UINT64  ExGetCallBackBlockRoutine;
            UINT64  ExDereferenceCallBackBlock;
            UINT64  KiScbQueueScanWorker;
            UINT64  PspEnumerateCallback;
            UINT64  CmpEnumerateCallback;
            UINT64  DbgEnumerateCallback;
            UINT64  ExpEnumerateCallback;
            UINT64  ExpGetNextCallback;
            UINT64  EmpCheckErrataList_;
            UINT64  KiSchedulerApcTerminate;
            UINT64  KiSchedulerApc;
            UINT64  EmpCheckErrataList;
            UINT64  PGSelfEncryptWaitAndDecrypt;
            UINT64  MmAllocatePagesForMdlEx;
            UINT64  MmAllocateMappingAddress;
            UINT64  MmMapLockedPagesWithReservedMapping;
            UINT64  MmUnmapReservedMapping;
            UINT64  Unkonwn$; // nt!KiSwInterruptDispatch+0x????
            UINT64  Unkonwn$; // nt!KiSwInterruptDispatch+0x????
            UINT64  MmAcquireLoadLock;
            UINT64  MmReleaseLoadLock;
            UINT64  KeEnumerateQueueApc;
            UINT64  KeIsApcRunningThread;
            UINT64  Unkonwn$; // nt!KiSwInterruptDispatch+0x???
            UINT64  PsAcquireProcessExitSynchronization;
            UINT64  ObDereferenceProcessHandleTable;
            UINT64  PsGetNextProcess;
            UINT64  PsQuitNextProcess;
            UINT64  MmIsSessionLeaderProcess;
            UINT64  PsInvokeWin32Callout;
            UINT64  MmEnumerateAddressSpaceAndReferenceImages;
            UINT64  PsGetProcessProtection;
            UINT64  PsGetProcessSignatureLevel;
            UINT64  PsGetProcessSectionBaseAddress;
            UINT64  SeCompareSigningLevels;
            UINT64  KeComputeSha256;
            UINT64  KeComputeParallelSha256;
            UINT64  KeSetEvent;
            UINT64  RtlpConvertFunctionEntry;
            UINT64  RtlpLookupPrimaryFunctionEntry;
            UINT64  RtlIsMultiSessionSku;
            UINT64  KiEnumerateCallback;
            UINT64  KeStackAttachProcess;
            UINT64  KeUnstackDetachProcess;
            UINT64  KeIpiGenericCall;
            UINT64  Unkonwn$;      // nt!PG$xxxxxxx
            UINT64  MmGetPhysicalAddress;
            UINT64  MmUnlockPages;
            UINT64  VslVerifyPage;
            UINT64  KiGetInterruptObjectAddress;
            UINT64  Unkonwn$[3];
            UINT64  Unkonwn$[4];   // nt!PG$vvvvvvv
            UINT64  PsInitialSystemProcess;
            UINT64  KiWaitAlways;
            UINT64  KiEntropyTimingRoutine;
            UINT64  KiProcessListHead;
            UINT64  KiProcessListLock;
            UINT64  ObpTypeObjectType;
            UINT64  IoDriverObjectType;
            UINT64  PsProcessType;
            UINT64  PsActiveProcessHead;
            UINT64  PsInvertedFunctionTable;
            UINT64  PsLoadedModuleList;
            UINT64  PsLoadedModuleResource;
            UINT64  PsLoadedModuleSpinLock;
            UINT64  PspActiveProcessLock;
            UINT64  PspCidTable;
            UINT64  ExpUuidLock;
            UINT64  AlpcpPortListLock;
            UINT64  KeServiceDescriptorTable;
            UINT64  KeServiceDescriptorTableShadow;
            UINT64  KeServiceDescriptorTableFilter;
            UINT64  VfThunksExtended;
            UINT64  PsWin32CallBack;
            UINT64  Unkonwn$;             // nt!TriageImagePageSize+0x??
            UINT64  KiTableInformation;
            UINT64  HandleTableListHead;
            UINT64  HandleTableListLock;
            UINT64  ObpKernelHandleTable;
            UINT64  KiUserSharedData;       // 0xFFFFF78000000000
            UINT64  KiWaitNever;
            UINT64  SeProtectedMapping;
            UINT64  KiInterruptThunk;
            UINT64  KiStackProtectNotifyEvent;
            UINT64  PageTables;             // ffffb980`00000000
            UINT64  Ntos;
            UINT64  Hal;
            UINT64  KeNumberProcessors;
            UINT64  Unkonwn$;             // nt!PG$vvvvvvvv
            UINT64  Unkonwn$;             // nt!PG$vvvvvvvv
            UINT64  RtlpInvertedFunctionTable;
            UINT64  KxUnexpectedInterrupt0; // nt!KiIsrThunk or nt!KiIsrThunkShadow

            UINT64  Unkonwn$[6];

            UINT64  WorkerRoutine;
            UINT64  WorkerRoutineContext;

            UINT64  Unkonwn$;

            UINT64  Prcb;
            UINT64  PGPageBase;
            UINT64  SecondParamOfEndOfUninitialize;
            UINT64  DcpRoutineToBeScheduled;

            UINT32  Unkonwn$;                          // NumberOfXXXX
            UINT32  Unkonwn$;

            UINT32  OffsetOfPGSelfValidation;           // INITKDBG: nt!PGSelfValidation
            UINT32  OffsetOfRtlLookupFunctionEntryEx;   // nt!RtlLookupFunctionEntryEx
            UINT32  OffsetOfFsRtlUninitializeSmallMcb;  // nt!FsRtlUninitializeSmallMcb
            UINT32  OffsetOfFsRtlUnknown0;              // nt!PG$XXXXXXXX
            UINT32  OffsetOfFsRtlUnkonwn1;              // 
            UINT32  EndOffsetOf;

            UINT64  SpinLock;

            UINT64  Unkonwn$[24];

            UINT64  BaseOfNtos;
            UINT64  BaseOfHal;
            UINT64  BaseOfNtosNtHeader;

            UINT64  Unkonwn$[2];

            UINT64  IsTiggerPG;
            UINT64  BugCheckArg0;
            UINT64  BugCheckArg1;
            UINT64  BugCheckArg3;
            UINT64  BugCheckArg2;

            PGProtectString<4> PGProtectStrings;

            UINT64  Unkonwn$[37];

            UINT32  NumberOfProtectCodes;
            UINT32  NumberOfProtectValues;

            // PGProtectCode   ProtectCodes[NumberOfProtectCodes];
            // PGProtectValue  ProtectValues[NumberOfProtectValues];
        };
    }

    namespace build_17134
    {
        using PGContextHeader = build_15063::PGContextHeader;

        struct PGContext : public PGContextHeader
        {
            UINT64  ExAcquireResourceSharedLite;
            UINT64  ExAcquireResourceExclusiveLite;
            UINT64  ExAllocatePoolWithTag;
            UINT64  ExFreePool;
            UINT64  ExMapHandleToPointer;
            UINT64  ExQueueWorkItem;
            UINT64  ExReleaseResourceLite;
            UINT64  ExUnlockHandleTableEntry;
            UINT64  ExAcquirePushLockExclusiveEx;
            UINT64  ExReleasePushLockExclusiveEx;
            UINT64  ExAcquirePushLockSharedEx;
            UINT64  ExReleasePushLockSharedEx;
            UINT64  KeAcquireInStackQueuedSpinLockAtDpcLevel;
            UINT64  ExAcquireSpinLockSharedAtDpcLevel;
            UINT64  KeBugCheckEx;
            UINT64  KeDelayExecutionThread;
            UINT64  KeEnterCriticalRegionThread;
            UINT64  KeLeaveCriticalRegion;
            UINT64  KeEnterGuardedRegion;
            UINT64  KeLeaveGuardedRegion;
            UINT64  KeReleaseInStackQueuedSpinLockFromDpcLevel;
            UINT64  ExReleaseSpinLockSharedFromDpcLevel;
            UINT64  KeRevertToUserAffinityThread;
            UINT64  KeProcessorGroupAffinity;
            UINT64  KeInitializeEnumerationContext;
            UINT64  KeEnumerateNextProcessor;
            UINT64  KeCountSetBitsAffinityEx;
            UINT64  KeQueryAffinityProcess;
            UINT64  KeQueryAffinityThread;
            UINT64  KeSetSystemGroupAffinityThread;
            UINT64  KeSetCoalescableTimer;
            UINT64  ObfDereferenceObject;
            UINT64  ObReferenceObjectByName;
            UINT64  RtlImageDirectoryEntryToData;
            UINT64  RtlImageNtHeader;
            UINT64  RtlLookupFunctionTable;
            UINT64  RtlPcToFileHeader;
            UINT64  RtlSectionTableFromVirtualAddress;
            UINT64  DbgPrint;
            UINT64  MmAllocateIndependentPages;
            UINT64  MmFreeIndependentPages;
            UINT64  MmSetPageProtection;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  Unkonwn$;
            UINT64  RtlLookupFunctionEntry;
            UINT64  KeAcquireSpinLockRaiseToDpc;
            UINT64  KeReleaseSpinLock;
            UINT64  MmGetSessionById;
            UINT64  MmGetNextSession;
            UINT64  MmQuitNextSession;
            UINT64  MmAttachSession;
            UINT64  MmDetachSession;
            UINT64  MmGetSessionIdEx;
            UINT64  MmIsSessionAddress;
            UINT64  MmIsAddressValid;
            UINT64  MmSessionGetWin32Callouts;
            UINT64  KeInsertQueueApc;
            UINT64  KeWaitForSingleObject;
            UINT64  PsCreateSystemThread;
            UINT64  ExReferenceCallBackBlock;
            UINT64  ExGetCallBackBlockRoutine;
            UINT64  ExDereferenceCallBackBlock;
            UINT64  KiScbQueueScanWorker;
            UINT64  PspEnumerateCallback;
            UINT64  CmpEnumerateCallback;
            UINT64  DbgEnumerateCallback;
            UINT64  ExpEnumerateCallback;
            UINT64  ExpGetNextCallback;
            UINT64  EmpCheckErrataList_;
            UINT64  KiSchedulerApcTerminate;
            UINT64  KiSchedulerApc;
            UINT64  EmpCheckErrataList;
            UINT64  PGSelfEncryptWaitAndDecrypt;
            UINT64  MmAllocatePagesForMdlEx;
            UINT64  MmAllocateMappingAddress;
            UINT64  MmMapLockedPagesWithReservedMapping;
            UINT64  MmUnmapReservedMapping;
            UINT64  Unkonwn$; // nt!KiSwInterruptDispatch+0x????
            UINT64  Unkonwn$; // nt!KiSwInterruptDispatch+0x????
            UINT64  MmAcquireLoadLock;
            UINT64  MmReleaseLoadLock;
            UINT64  KeEnumerateQueueApc;
            UINT64  KeIsApcRunningThread;
            UINT64  Unkonwn$; // nt!KiSwInterruptDispatch+0x???
            UINT64  PsAcquireProcessExitSynchronization;
            UINT64  ObDereferenceProcessHandleTable;
            UINT64  PsGetNextProcess;
            UINT64  PsQuitNextProcess;
            UINT64  PsGetNextProcessEx;
            UINT64  MmIsSessionLeaderProcess;
            UINT64  PsInvokeWin32Callout;
            UINT64  MmEnumerateAddressSpaceAndReferenceImages;
            UINT64  PsGetProcessProtection;
            UINT64  PsGetProcessSignatureLevel;
            UINT64  PsGetProcessSectionBaseAddress;
            UINT64  SeCompareSigningLevels;
            UINT64  KeComputeSha256;
            UINT64  KeComputeParallelSha256;
            UINT64  KeSetEvent;
            UINT64  RtlpConvertFunctionEntry;
            UINT64  RtlpLookupPrimaryFunctionEntry;
            UINT64  RtlIsMultiSessionSku;
            UINT64  KiEnumerateCallback;
            UINT64  KeStackAttachProcess;
            UINT64  KeUnstackDetachProcess;
            UINT64  KeIpiGenericCall;
            UINT64  Unkonwn$;      // nt!PG$xxxxxxx
            UINT64  MmGetPhysicalAddress;
            UINT64  MmUnlockPages;
            UINT64  VslVerifyPage;
            UINT64  KiGetInterruptObjectAddress;
            UINT64  Unkonwn$;
            UINT64  PsLookupProcessByProcessId;
            UINT64  PsGetProcessId;
            UINT64  MmCheckProcessShadow;
            UINT64  Unkonwn$[4];
            UINT64  Unkonwn$[4];   // nt!PG$vvvvvvv
            UINT64  PsInitialSystemProcess;
            UINT64  KiWaitAlways;
            UINT64  KiEntropyTimingRoutine;
            UINT64  KiProcessListHead;
            UINT64  KiProcessListLock;
            UINT64  ObpTypeObjectType;
            UINT64  IoDriverObjectType;
            UINT64  PsProcessType;
            UINT64  PsActiveProcessHead;
            UINT64  PsInvertedFunctionTable;
            UINT64  PsLoadedModuleList;
            UINT64  PsLoadedModuleResource;
            UINT64  PsLoadedModuleSpinLock;
            UINT64  PspActiveProcessLock;
            UINT64  PspCidTable;
            UINT64  ExpUuidLock;
            UINT64  AlpcpPortListLock;
            UINT64  KeServiceDescriptorTable;
            UINT64  KeServiceDescriptorTableShadow;
            UINT64  KeServiceDescriptorTableFilter;
            UINT64  VfThunksExtended;
            UINT64  PsWin32CallBack;
            UINT64  Unkonwn$;             // nt!TriageImagePageSize+0x??
            UINT64  KiTableInformation;
            UINT64  HandleTableListHead;
            UINT64  HandleTableListLock;
            UINT64  ObpKernelHandleTable;
            UINT64  KiUserSharedData;       // 0xFFFFF78000000000
            UINT64  KiWaitNever;
            UINT64  SeProtectedMapping;
            UINT64  KiInterruptThunk;
            UINT64  KiStackProtectNotifyEvent;
            UINT64  PageTables;
            UINT64  Ntos;
            UINT64  Hal;
            UINT64  KeNumberProcessors;
            UINT64  Unkonwn$;             // nt!PG$vvvvvvvv
            UINT64  Unkonwn$;             // nt!PG$vvvvvvvv
            UINT64  RtlpInvertedFunctionTable;
            UINT64  KxUnexpectedInterrupt0; // nt!KiIsrThunk or nt!KiIsrThunkShadow

            UINT64  Unkonwn$[6];

            UINT64  WorkerRoutine;
            UINT64  WorkerRoutineContext;

            UINT64  Unkonwn$;

            UINT64  Prcb;
            UINT64  PGPageBase;
            UINT64  SecondParamOfEndOfUninitialize;
            UINT64  DcpRoutineToBeScheduled;

            UINT32  Unkonwn$;                          // NumberOfXXXX
            UINT32  Unkonwn$;

            UINT32  OffsetOfPGSelfValidation;           // INITKDBG: nt!PGSelfValidation
            UINT32  OffsetOfRtlLookupFunctionEntryEx;   // nt!RtlLookupFunctionEntryEx
            UINT32  OffsetOfFsRtlUninitializeSmallMcb;  // nt!FsRtlUninitializeSmallMcb
            UINT32  OffsetOfFsRtlUnknown0;              // nt!PG$XXXXXXXX
            UINT32  OffsetOfFsRtlUnkonwn1;              // 
            UINT32  EndOffsetOf;

            UINT64  SpinLock;

            UINT64  Unkonwn$[24];

            UINT64  BaseOfNtos;
            UINT64  BaseOfHal;
            UINT64  BaseOfNtosNtHeader;

            UINT64  Unkonwn$[2];

            UINT64  IsTiggerPG;
            UINT64  BugCheckArg0;
            UINT64  BugCheckArg1;
            UINT64  BugCheckArg3;
            UINT64  BugCheckArg2;

            PGProtectString<4> PGProtectStrings;

            UINT64  Unkonwn$[40];

            UINT32  NumberOfProtectCodes;
            UINT32  NumberOfProtectValues;

            // PGProtectCode   ProtectCodes[NumberOfProtectCodes];
            // PGProtectValue  ProtectValues[NumberOfProtectValues];
        };
    }

}
#pragma warning(pop)
