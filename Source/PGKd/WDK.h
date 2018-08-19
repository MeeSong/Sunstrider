#pragma once

#pragma warning(push)
#pragma warning(disable: 4201)
namespace wdk
{

    enum class SystemVersion : UINT32
    {
        Unknown,

        WindowsXP,                  // 5.1.2600
        WindowsXP64,                // 5.2.3790

        WindowsVista,               // 6.0.6000
        WindowsVista_SP1,           // 6.0.6001
        WindowsVista_SP2,           // 6.0.6002

        Windows7,                   // 6.1.7600
        Windows7_SP1,               // 6.1.7601

        Windows8,                   // 6.2.9200

        Windows8_1,                 // 6.3.9600

        Windows10,
        Windows10_1507 = Windows10, // 10.0.10240
        Windows10_1511,             // 10.0.10586
        Windows10_1607,             // 10.0.14393
        Windows10_1703,             // 10.0.15063
        Windows10_1709,             // 10.0.16299
        Windows10_1803,             // 10.0.17134
        Windows10_1809,             // 10.0.17741
        WindowsMax,
    };


    typedef enum _POOL_TYPE {
        NonPagedPool,
        NonPagedPoolExecute = NonPagedPool,
        PagedPool,
        NonPagedPoolMustSucceed = NonPagedPool + 2,
        DontUseThisType,
        NonPagedPoolCacheAligned = NonPagedPool + 4,
        PagedPoolCacheAligned,
        NonPagedPoolCacheAlignedMustS = NonPagedPool + 6,
        MaxPoolType,

        //
        // Define base types for NonPaged (versus Paged) pool, for use in cracking
        // the underlying pool type.
        //

        NonPagedPoolBase = 0,
        NonPagedPoolBaseMustSucceed = NonPagedPoolBase + 2,
        NonPagedPoolBaseCacheAligned = NonPagedPoolBase + 4,
        NonPagedPoolBaseCacheAlignedMustS = NonPagedPoolBase + 6,

        //
        // Note these per session types are carefully chosen so that the appropriate
        // masking still applies as well as MaxPoolType above.
        //

        NonPagedPoolSession = 32,
        PagedPoolSession = NonPagedPoolSession + 1,
        NonPagedPoolMustSucceedSession = PagedPoolSession + 1,
        DontUseThisTypeSession = NonPagedPoolMustSucceedSession + 1,
        NonPagedPoolCacheAlignedSession = DontUseThisTypeSession + 1,
        PagedPoolCacheAlignedSession = NonPagedPoolCacheAlignedSession + 1,
        NonPagedPoolCacheAlignedMustSSession = PagedPoolCacheAlignedSession + 1,

        NonPagedPoolNx = 512,
        NonPagedPoolNxCacheAligned = NonPagedPoolNx + 4,
        NonPagedPoolSessionNx = NonPagedPoolNx + 32,

    } POOL_TYPE;

    typedef union _KIDTENTRY64 {
        struct {
            UINT16 OffsetLow;
            UINT16 Selector;
            UINT16 IstIndex : 3;
            UINT16 Reserved0 : 5;
            UINT16 Type : 5;
            UINT16 Dpl : 2;
            UINT16 Present : 1;
            UINT16 OffsetMiddle;
            UINT32 OffsetHigh;
            UINT32 Reserved1;
        };

        UINT64 Alignment;
    } KIDTENTRY64, *PKIDTENTRY64;

    typedef struct _POOL_TRACKER_BIG_PAGES
    {
        PVOID   Va;
        ULONG   Tag;
        ULONG   PoolType;
        SIZE_T  NumberOfBytes;
    } POOL_TRACKER_BIG_PAGES, *PPOOL_TRACKER_BIG_PAGES;
    static_assert(sizeof(POOL_TRACKER_BIG_PAGES) == 0x18, "sizeof(POOL_TRACKER_BIG_PAGES) != 0x18");

    typedef struct _MMPFN
    {
        union {
            UINT64              Flink;
            ULONG32             WsIndex;    // WorkSet Index
            struct _KEVENT *    Event;
            VOID*               Next;
            VOID*               VolatileNext;
            struct _KTHREAD *   KernelStackOwner;
            SINGLE_LIST_ENTRY   NextStackPfn;
        } u1;

        union {
            UINT64              Blink;
            struct _MMPTE *     ImageProtoPte;
            UINT64              ShareCount;
        } u2;

        union {
            struct _MMPTE *     PteAddress;
            VOID *              VolatilePteAddress;
            LONG32              Lock;
            UINT64              PteLong;
        };

        UINT64  DontUseThis[3];

    } MMPFN, *PMMPFN;
    static_assert(sizeof(MMPFN) == sizeof(void *) * 6, "sizeof(MMPFN) != sizeof(void *) * 6");


    namespace build_10240
    {
        typedef struct _POOL_TRACKER_BIG_PAGES
        {
            PVOID   Va;
            ULONG   Tag;
            struct
            {
                ULONG Pattern   : 8;
                ULONG PoolType  : 12;
                ULONG SlushSize : 12;
            };
            SIZE_T  NumberOfBytes;
        } POOL_TRACKER_BIG_PAGES, *PPOOL_TRACKER_BIG_PAGES;
        static_assert(sizeof(POOL_TRACKER_BIG_PAGES) == 0x18, "sizeof(build_10240::POOL_TRACKER_BIG_PAGES) != 0x18");

        typedef struct _MMPFN
        {
            union {
                LIST_ENTRY ListEntry;
                //struct _RTL_BALANCED_NODE TreeNode; // sizeof(_RTL_BALANCED_NODE) == 24
                struct
                {
                    union {
                        struct
                        {
                            UINT64  Flink : 36;
                            UINT64  NodeFlinkHigh : 28;
                        };
                        UINT64          WsIndex;    // WorkSet Index
                        struct _KEVENT *Event;
                        VOID *          Next;
                        VOID *          VolatileNext;
                        struct _KTHREAD*KernelStackOwner;
                        SINGLE_LIST_ENTRY NextStackPfn;
                    } u1;

                    union {
                        struct _MMPTE * PteAddress;
                        VOID *          VolatilePteAddress;
                        UINT64          PteLong;
                    };

                    UINT64 OriginalPte;
                }; // sizeof(unname) == 24
            };

            UINT64  DontUseThis[3];

        } MMPFN, *PMMPFN;
        static_assert(sizeof(MMPFN) == sizeof(void *) * 6, "sizeof(build_10240::MMPFN) != sizeof(void *) * 6");

    }


}
#pragma warning(pop)

#include "WDK.PTE.h"
#include "WDK.PGContext.h"
