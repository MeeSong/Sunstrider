#pragma once

#include <tuple>
#include <vector>
#include <array>
#include <set>

namespace Sunstrider
{

    struct RandomnessInfo
    {
        ULONG NumberOfDistinctiveNumbers;
        ULONG Ramdomness;
    };

    // Returns the number of 0x00 and 0xff in the given range
    auto GetNumberOfDistinctiveNumbers(
        __in PVOID  aAddress,
        __in SIZE_T aSize)
        -> ULONG;

    // Returns the number of unique bytes in the given range.
    // For example, it returns 3 for the following bytes
    // 00 01 01 02 02 00 02
    auto GetRamdomness(
        __in PVOID  aAddress,
        __in SIZE_T aSize)
        -> ULONG;


    class PGKd : public ExtExtension
    {
        // The number of bytes to examine to calculate the number of distinctive
        // bytes and randomness
        static constexpr auto EXAMINATION_BYTES = 100;

        // It is not a PatchGuard page if the number of distinctive bytes are bigger
        // than this number
        static constexpr auto MAXIMUM_DISTINCTIVE_NUMBER = 5;

        // It is not a PatchGuard page if randomness is smaller than this number
        static constexpr auto MINIMUM_RANDOMNESS = 50;

        // It is not a PatchGuard page if the size of the page is smaller than this
        static constexpr auto MINIMUM_REGION_SIZE = 0x004000;

        // It is not a PatchGuard page if the size of the page is larger than this
        static constexpr auto MAXIMUM_REGION_SIZE = 0xf00000;

        // PG$VerifictionPatchGuardImpl 
        // (CmpAppendDllSection : call rax ; rax == PG$VerifictionPatchGuardImpl)
        //
        // INITKDBG : 00000001402F2995 48 B8 E8 B4 C8 91 58 3F A0 A3                 mov     rax, 0A3A03F5891C8B4E8h
        // INITKDBG : 00000001402F299F 48 03 C7                                      add     rax, rdi
        // INITKDBG : 00000001402F29A2 48 89 87 98 07 00 00                          mov[rdi + 798h], rax
        // INITKDBG : 00000001402F29A9 48 B8 15 34 45 E4 DE 4B B7 B3                 mov     rax, 0B3B74BDEE4453415h
        // INITKDBG : 00000001402F29B3 48 03 C3                                      add     rax, rbx
        // INITKDBG : 00000001402F29B6 48 89 87 A0 07 00 00                          mov[rdi + 7A0h], rax

        static constexpr auto BUGCHECK_109_ARGS0_KEY = 0xA3A03F5891C8B4E8UI64;
        static constexpr auto BUGCHECK_109_ARGS1_KEY = 0xB3B74BDEE4453415UI64;

    public:
        virtual auto Initialize() 
            -> HRESULT override;

        EXT_COMMAND_METHOD(findpg);
        EXT_COMMAND_METHOD(analyzepg);
        EXT_COMMAND_METHOD(dumppg);

        auto _EFN_Analyze(
            PDEBUG_CLIENT4            aClient,
            FA_EXTENSION_PLUGIN_PHASE aCallPhase,
            PDEBUG_FAILURE_ANALYSIS2  aAnalysis)
            -> HRESULT;

    private:
        auto GetSystemVersion(PDEBUG_CONTROL aDbgControl = nullptr, std::string* aTarget = nullptr)
            -> wdk::SystemVersion;

        auto IsWindows10OrGreater()
            -> bool;

        auto IsWindowsRS1OrGreater()
            -> bool;

        auto GetPfnDatabase()
            -> UINT64;

        auto GetPteBase() 
            -> UINT64;

        auto GetPtes(UINT64 aPteBase)
            -> std::unique_ptr<std::array<wdk::HARDWARE_PTE, wdk::PTE_PER_PAGE>>;

        auto IsNonPagedBigPool(const wdk::POOL_TRACKER_BIG_PAGES& aEntry)
            -> bool;
        
        auto IsPageValidReadWriteExecutable(UINT64 aPteAddress)
            -> bool;

        auto IsPatchGuardPageAttribute(UINT64 aPageBase)
            -> bool;

        auto FindPatchGuardContextFromBigPagePool()
            -> std::vector <std::tuple<wdk::POOL_TRACKER_BIG_PAGES, RandomnessInfo>>;

        auto FindPatchGuardContextFromIndependentPages()
            -> std::vector <std::tuple<UINT64, SIZE_T, RandomnessInfo>>;

        auto FindPatchGuardContext()
            -> HRESULT;

        auto GetPGContextTypeString(
            UINT64  aErrorWasFound,
            UINT64  aTypeOfCorruption)
            -> LPCSTR;

        auto DumpPatchGuardContextForType106(
            UINT64  aFailureDependent)
            -> void;

        template<typename T>
        auto DumpPatchGuardContext(
            UINT64  aPGContext,
            UINT64  aPGReason,
            UINT64  aFailureDependent,
            UINT64  aTypeOfCorruption,
            T& aContext)
            ->HRESULT;

        template<typename PGContextT>
        auto DumpPatchGuardImpl(
            UINT64  aPGContext,
            UINT64  aPGReason,
            UINT64  aFailureDependent, 
            UINT64  aTypeOfCorruption)
            -> HRESULT;

        auto DumpPatchGuard(
            UINT64  aPGContext,         // BugCheckArgs[0]
            UINT64  aPGReason,          // BugCheckArgs[1]
            UINT64  aFailureDependent,  // BugCheckArgs[2]
            UINT64  aTypeOfCorruption,  // BugCheckArgs[3]
            bool    aNeedBugCheckBanner = false)
            -> HRESULT;
    };

    template<typename PGContextT>
    inline auto PGKd::DumpPatchGuardImpl(
        UINT64 aPGContext, 
        UINT64 aPGReason, 
        UINT64 aFailureDependent,
        UINT64 aTypeOfCorruption) 
        -> HRESULT
    {
        HRESULT hr = S_OK;

        for (;;)
        {
            // In the case of type 0x106, neither the address of PatchGuard context nor
            // the address of the validation structure are given (do not exist).
            if (0 == aPGContext && 
                0 == aPGReason  &&
                0x106 == aTypeOfCorruption)  // CcBcbProfiler
            {
                DumpPatchGuardContextForType106(aFailureDependent);
                break;
            }

            auto vReadBytes = 0ul;
            auto vPGContext = std::make_unique<PGContextT>();
            hr = m_Data->ReadVirtual(aPGContext, vPGContext.get(), sizeof(PGContextT), &vReadBytes);
            if (FAILED(hr))
            {
                Err("The given address 0x%016I64x is not readable. [DumpPatchGuard]\n",
                    aPGContext);
                break;
            }

            hr = DumpPatchGuardContext(aPGContext, aPGReason, aFailureDependent, aTypeOfCorruption, *vPGContext);
            break;
        }

        return hr;
    }

}

#undef  EXT_CLASS
#define EXT_CLASS ::Sunstrider::PGKd
