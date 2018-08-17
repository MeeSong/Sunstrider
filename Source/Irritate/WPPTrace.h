/*++

Module Name:

    Trace.h

Abstract:

    Header file for the debug tracing related function defintions and macros.

Environment:

    Kernel mode

--*/

#pragma once
#include <initguid.h>

//
// Define the tracing flags.
//
// Tracing GUID - 0A64AABE-7F43-4A58-A161-BD1A03A515E7
//

#define WPP_CONTROL_GUIDS                                       \
    WPP_DEFINE_CONTROL_GUID(                                    \
        WPPTraceGuid, (0A64AABE,7F43,4A58,A161,BD1A03A515E7),   \
        WPP_DEFINE_BIT(WPP_ANY_FLAGS)                           \
        WPP_DEFINE_BIT(WPP_FUNC_TRACE)                          \
        )                             

#define WPP_FLAGS_LEVEL_LOGGER(flags, level)  \
    WPP_LEVEL_LOGGER(flags)

#define WPP_FLAGS_LEVEL_ENABLED(flags, level) \
    (WPP_LEVEL_ENABLED(flags) && WPP_CONTROL(WPP_BIT_ ## flags).Level >= level)

#define WPP_LEVEL_FLAGS_LOGGER(level, flags) \
    WPP_LEVEL_LOGGER(flags)
               
#define WPP_LEVEL_FLAGS_ENABLED(level, flags) \
    (WPP_LEVEL_ENABLED(flags) && WPP_CONTROL(WPP_BIT_ ## flags).Level >= level)

//
// PRE macro: The name of the macro includes the condition arguments FLAGS and EXP
//            define in FUNC above
//
#define WPP_FLAGS_NT_PRE(FLAGS, NT) {if (!NT_SUCCESS(NT)) {

//
// POST macro
// The name of the macro includes the condition arguments FLAGS and EXP
//            define in FUNC above
#define WPP_FLAGS_NT_POST(FLAGS, NT) ;}}

// 
// The two macros below are for checking if the event should be logged and for 
// choosing the logger handle to use when calling the ETW trace API
//
#define WPP_FLAGS_NT_ENABLED(FLAGS, NT)    WPP_FLAG_ENABLED(FLAGS)
#define WPP_FLAGS_NT_LOGGER(FLAGS, NT)     WPP_FLAG_LOGGER(FLAGS)

// Map the null flags used by Entry/Exit to a function called FuncTrace
#define WPP__ENABLED()      WPP_LEVEL_ENABLED(WPP_FUNC_TRACE)
#define WPP__LOGGER()       WPP_LEVEL_LOGGER(WPP_FUNC_TRACE)

#define WPP_NT_ENABLED(NT)  WPP_LEVEL_ENABLED(WPP_FUNC_TRACE)
#define WPP_NT_LOGGER(NT)   WPP_LEVEL_LOGGER(WPP_FUNC_TRACE)

//           
// WPP orders static parameters before dynamic parameters. To support the Trace function
// defined below which sets FLAGS=MYDRIVER_ALL_INFO, a custom macro must be defined to
// reorder the arguments to what the .tpl configuration file expects.
//
#define WPP_RECORDER_FLAGS_LEVEL_ARGS(flags, level)     WPP_RECORDER_LEVEL_FLAGS_ARGS(level, flags)
#define WPP_RECORDER_FLAGS_LEVEL_FILTER(flags, level)   WPP_RECORDER_LEVEL_FLAGS_FILTER(level, flags)

// MACRO: TraceReturn
// Configuration block that defines trace macro. It uses the PRE/POST macros to include
// code as part of the trace macro expansion. TRACE_MACRO is equivalent to the code below:
//
// {if (Status != STATUS_SUCCESS){  // This is the code in the PRE macro
//     Trace(TRACE_LEVEL_ERROR, "%!FUNC! Return = %!STATUS!", Status)
// ;}}                              // This is the code in the POST macro
//                                 
// 
// USEPREFIX statement: Defines a format string prefix to be used when logging the event, 
// below the STDPREFIX is used. The first value is the trace function name with out parenthesis
// and the second value is the format string to be used.
// 
// USESUFFIX statement: Defines a suffix format string that gets logged with the event. 
// 
// FUNC statement: Defines the name and signature of the trace function. The function defined 
// below takes one argument, no format string, and predefines the flag equal to FLAG_ONE.
//
//
//begin_wpp config
//USEPREFIX (TraceReturn, "%!STDPREFIX!");
//FUNC TraceReturn{FLAGS=WPP_ANY_FLAGS}(NT);
//USESUFFIX (TraceReturn, "%!FUNC! Return=%!STATUS!", NT);
//end_wpp

// MACRO: TraceBegin
//
//begin_wpp config
//FUNC TraceEntry();
//FUNC TraceExit(NT);
//USESUFFIX (TraceEntry, "Entry to %!FUNC!");
//USESUFFIX (TraceExit,  "%!FUNC! Return=%!STATUS!", NT);
//end_wpp

//
// This comment block is scanned by the trace preprocessor to define our
// Trace function.
//
// begin_wpp config
// FUNC TraceEvents (LEVEL, FLAGS, MSG, ...);
// FUNC Trace{FLAGS=WPP_ANY_FLAGS} (LEVEL, MSG, ...);
// FUNC TraceCritical{FLAGS=WPP_ANY_FLAGS, LEVEL=TRACE_LEVEL_CRITICAL}  (MSG, ...);
// FUNC TraceFatal{FLAGS=WPP_ANY_FLAGS, LEVEL=TRACE_LEVEL_FATAL}        (MSG, ...);
// FUNC TraceError{FLAGS=WPP_ANY_FLAGS, LEVEL=TRACE_LEVEL_ERROR}        (MSG, ...);
// FUNC TraceWarn{FLAGS=WPP_ANY_FLAGS, LEVEL=TRACE_LEVEL_WARNING}       (MSG, ...);
// FUNC TraceInfo{FLAGS=WPP_ANY_FLAGS, LEVEL=TRACE_LEVEL_INFORMATION}   (MSG, ...);
// FUNC TraceVerbose{FLAGS=WPP_ANY_FLAGS, LEVEL=TRACE_LEVEL_VERBOSE}    (MSG, ...);
// end_wpp
//

