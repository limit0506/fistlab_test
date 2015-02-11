#include <Windows.h>
#include <stdio.h>
#include <TCHAR.h>
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS)0xC0000004L)


//fix!!
//fix2!!
//new!!
//new2!!
//malware....
typedef enum _SYSTEM_INFORMATION_CLASS
{
	SystemBasicInformation,
	SystemProcessorInformation,
	SystemPerformanceInformation,
	SystemTimeOfDayInformation,
	SystemPathInformation,
	SystemProcessInformation,
	SystemCallCountInformation,
	SystemDeviceInformation,
	SystemProcessorPerformanceInformation,
	SystemFlagsInformation,
	SystemCallTimeInformation,
	SystemModuleInformation,
	SystemLocksInformation,
	SystemStackTraceInformation,
	SystemPagedPoolInformation,
	SystemNonPagedPoolInformation,
	SystemHandleInformation,
	SystemObjectInformation,
	SystemPageFileInformation,
	SystemVdmInstemulInformation,
	SystemVdmBopInformation,
	SystemFileCacheInformation,
	SystemPoolTagInformation,
	SystemInterruptInformation,
	SystemDpcBehaviorInformation,
	SystemFullMemoryInformation,
	SystemLoadGdiDriverInformation,
	SystemUnloadGdiDriverInformation,
	SystemTimeAdjustmentInformation,
	SystemSummaryMemoryInformation,
	SystemNextEventIdInformation,
	SystemEventIdsInformation,
	SystemCrashDumpInformation,
	SystemExceptionInformation,
	SystemCrashDumpStateInformation,
	SystemKernelDebuggerInformation,
	SystemContextSwitchInformation,
	SystemRegistryQuotaInformation,
	SystemExtendServiceTableInformation,
	SystemPrioritySeperation,
	SystemPlugPlayBusInformation,
	SystemDockInformation,
	SystemPowerInformationRedefine, // 이름이 중복되어서 변경하였습니다.
	SystemProcessorSpeedInformation,
	SystemCurrentTimeZoneInformation,
	SystemLookasideInformation
} SYSTEM_INFORMATION_CLASS, *PSYSTEM_INFORMATION_CLASS;


extern "C" NTSYSAPI NTSTATUS NTAPI NtQuerySystemInformation(
	IN SYSTEM_INFORMATION_CLASS SystemInformationClass,
	OUT PVOID SystemInformation,
	IN ULONG SystemInformationLength,
	OUT PULONG ReturnLength OPTIONAL);

typedef struct _RTL_PROCESS_MODULE_INFORMATION {
	HANDLE Section;
	PVOID MappedBase;
	PVOID ImageBase;
	ULONG ImageSize;
	ULONG Flags;
	USHORT LoadOrderIndex;
	USHORT InitOrderIndex;
	USHORT LoadCount;
	USHORT OffsetToFileName;
	CHAR FullPathName[256];
} RTL_PROCESS_MODULE_INFORMATION, *PRTL_PROCESS_MODULE_INFORMATION;

typedef struct _RTL_PROCESS_MODULES {
	ULONG NumberOfModules;
	RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, *PRTL_PROCESS_MODULES;

BOOL PrintSystemModuleList()
{
	NTSTATUS Status;
	PRTL_PROCESS_MODULES ModuleInfo;
	PRTL_PROCESS_MODULE_INFORMATION ModuleEntry;
	ULONG ReturnedLength;
	ULONG i;

	Status = NtQuerySystemInformation(SystemModuleInformation,
		NULL,
		0,
		&ReturnedLength);
	if (Status != STATUS_INFO_LENGTH_MISMATCH)
	{
		return FALSE;
	}

	ModuleInfo = (PRTL_PROCESS_MODULES)malloc(ReturnedLength);

	Status = NtQuerySystemInformation(SystemModuleInformation,
		ModuleInfo,
		ReturnedLength,
		&ReturnedLength);
	if (!NT_SUCCESS(Status))
	{
		free(ModuleInfo);

		return NULL;
	}


	for (i = 0; i < ModuleInfo->NumberOfModules; i++)
	{
		ModuleEntry = &ModuleInfo->Modules[i];

		printf("%s\n", ModuleEntry->FullPathName);
	}
	free(ModuleInfo);

	return TRUE;
}


int _tmain(int argc, _TCHAR* argv[])
{
	PrintSystemModuleList();

	return 0;
}