#pragma once


using $ProcessorrExecuteRoutine = void(__stdcall *)(UINT32 aProcessorNumber, void* aContext);

auto ProcessorExecute($ProcessorrExecuteRoutine aRoutine, void* aContext)
-> void;
