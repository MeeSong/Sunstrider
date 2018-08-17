#pragma once


#pragma warning(push)
#pragma warning(disable: 4201)
namespace wdk
{

    constexpr auto PAGE_SIZE = 4096UI64;

    constexpr auto PXE_SIZE = PAGE_SIZE;
    constexpr auto PPE_SIZE = PXE_SIZE * 512;
    constexpr auto PDE_SIZE = PPE_SIZE * 512;
    constexpr auto PTE_SIZE = PDE_SIZE * 512;

    constexpr auto PTE_PER_PAGE = 512;
    constexpr auto PDE_PER_PAGE = 512;
    constexpr auto PPE_PER_PAGE = 512;
    constexpr auto PXE_PER_PAGE = 512;

    constexpr auto PTI_MASK_AMD64 = PTE_PER_PAGE - 1;
    constexpr auto PDI_MASK_AMD64 = PDE_PER_PAGE - 1;
    constexpr auto PPI_MASK = PPE_PER_PAGE - 1;
    constexpr auto PXI_MASK = PXE_PER_PAGE - 1;

    constexpr auto PTI_SHIFT = 12;
    constexpr auto PDI_SHIFT = 21;
    constexpr auto PPI_SHIFT = 30;
    constexpr auto PXI_SHIFT = 39;

    __declspec(selectany) auto PTE_BASE = 0xFFFFF68000000000UI64;
    __declspec(selectany) auto PDE_BASE = ((PTE_BASE & 0x0000FFFFFFFFF000) >> 12) * 8 + PTE_BASE; //0xFFFFF6FB40000000UI64;
    __declspec(selectany) auto PPE_BASE = ((PDE_BASE & 0x0000FFFFFFFFF000) >> 12) * 8 + PTE_BASE; //0xFFFFF6FB7DA00000UI64;
    __declspec(selectany) auto PXE_BASE = ((PPE_BASE & 0x0000FFFFFFFFF000) >> 12) * 8 + PTE_BASE; //0xFFFFF6FB7DBED000UI64;
    __declspec(selectany) auto PXE_SELFMAP = ((PXE_BASE & 0x0000FFFFFFFFF000) >> 12) * 8 + PTE_BASE; //0xFFFFF6FB7DBEDF68UI64;

    __declspec(selectany) auto PXE_TOP = PXE_BASE + PXE_SIZE - 1;
    __declspec(selectany) auto PPE_TOP = PPE_BASE + PPE_SIZE - 1;
    __declspec(selectany) auto PDE_TOP = PDE_BASE + PDE_SIZE - 1;
    __declspec(selectany) auto PTE_TOP = PTE_BASE + PTE_SIZE - 1;

}

namespace wdk
{

    typedef struct _HARDWARE_PTE
    {
        enum : UINT64 { HARDWARE_PTE_WORKING_SET_BITS = 11 };

        ULONG64 Valid : 1;
        ULONG64 Write : 1;                // UP version
        ULONG64 Owner : 1;
        ULONG64 WriteThrough : 1;
        ULONG64 CacheDisable : 1;
        ULONG64 Accessed : 1;
        ULONG64 Dirty : 1;
        ULONG64 LargePage : 1;
        ULONG64 Global : 1;
        ULONG64 CopyOnWrite : 1;          // software field
        ULONG64 Prototype : 1;            // software field
        ULONG64 reserved0 : 1;            // software field
        ULONG64 PageFrameNumber : 36;
        ULONG64 reserved1 : 4;
        ULONG64 SoftwareWsIndex : HARDWARE_PTE_WORKING_SET_BITS;
        ULONG64 NoExecute : 1;
    } HARDWARE_PTE, *PHARDWARE_PTE;
    static_assert(sizeof(HARDWARE_PTE) == 8, "sizeof(HARDWARE_PTE) != 8");

    inline auto MiInitPte(UINT64 aPteBase)
        -> void
    {
        PTE_BASE = aPteBase;
        PDE_BASE = ((PTE_BASE & 0x0000FFFFFFFFF000) >> 12) * 8 + PTE_BASE;
        PPE_BASE = ((PDE_BASE & 0x0000FFFFFFFFF000) >> 12) * 8 + PTE_BASE;
        PXE_BASE = ((PPE_BASE & 0x0000FFFFFFFFF000) >> 12) * 8 + PTE_BASE;
        PXE_SELFMAP = ((PXE_BASE & 0x0000FFFFFFFFF000) >> 12) * 8 + PTE_BASE;

        PXE_TOP = PXE_BASE + PXE_SIZE - 1;
        PPE_TOP = PPE_BASE + PPE_SIZE - 1;
        PDE_TOP = PDE_BASE + PDE_SIZE - 1;
        PTE_TOP = PTE_BASE + PTE_SIZE - 1;
    }

    inline auto MiPxeToAddress(__in PHARDWARE_PTE aPointerPxe)
        -> void*
    {
        return reinterpret_cast<void*>(
            (reinterpret_cast<LONG64>(aPointerPxe) << 52) >> 16);
    }


    inline auto MiPpeToAddress(__in PHARDWARE_PTE aPointerPpe)
        -> void*
    {
        return reinterpret_cast<void*>(
            (reinterpret_cast<LONG64>(aPointerPpe) << 43) >> 16);
    }


    inline auto MiPdeToAddress(__in PHARDWARE_PTE aPointerPde)
        -> void*
    {
        return reinterpret_cast<void*>(
            (reinterpret_cast<LONG64>(aPointerPde) << 34) >> 16);
    }


    inline auto MiPteToAddress(__in PHARDWARE_PTE aPointerPte)
        -> void*
    {
        return reinterpret_cast<void*>(
            (reinterpret_cast<LONG64>(aPointerPte) << 25) >> 16);
    }


    inline auto MiAddressToPxe(__in void* aAddress)
        -> PHARDWARE_PTE
    {
        auto Offset = reinterpret_cast<ULONG64>(aAddress) >> (PXI_SHIFT - 3);
        Offset &= (0x1FF << 3);
        return reinterpret_cast<PHARDWARE_PTE>(PXE_BASE + Offset);
    }


    inline auto MiAddressToPpe(__in void* aAddress)
        -> PHARDWARE_PTE
    {
        auto Offset = reinterpret_cast<ULONG64>(aAddress) >> (PPI_SHIFT - 3);
        Offset &= (0x3FFFF << 3);
        return reinterpret_cast<PHARDWARE_PTE>(PPE_BASE + Offset);
    }


    inline auto MiAddressToPde(__in void* aAddress) 
        -> PHARDWARE_PTE
    {
        auto Offset = reinterpret_cast<ULONG64>(aAddress) >> (PDI_SHIFT - 3);
        Offset &= (0x7FFFFFF << 3);
        return reinterpret_cast<PHARDWARE_PTE>(PDE_BASE + Offset);
    }


    inline auto MiAddressToPte(__in void* aAddress)
        -> PHARDWARE_PTE
    {
        auto Offset = reinterpret_cast<ULONG64>(aAddress) >> (PTI_SHIFT - 3);
        Offset &= (0xFFFFFFFFFULL << 3);
        return reinterpret_cast<PHARDWARE_PTE>(PTE_BASE + Offset);
    }
    
}
#pragma warning(pop)
