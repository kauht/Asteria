#pragma once
#pragma comment(lib, "ntdll.lib")

#include <windows.h>
#include <string>

#define STATUS_SUCCESS 0x00000000L

typedef struct _CLIENT_ID {
  HANDLE UniqueProcess;
  HANDLE UniqueThread;
} CLIENT_ID, *PCLIENT_ID;

typedef struct _UNICODE_STRING {
  USHORT Length;
  USHORT MaximumLength;
  _Field_size_bytes_part_opt_(MaximumLength, Length) PWCH Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef const UNICODE_STRING *PCUNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES {
  ULONG Length;
  HANDLE RootDirectory;
  PCUNICODE_STRING ObjectName;
  ULONG Attributes;
  PSECURITY_DESCRIPTOR SecurityDescriptor;
  PSECURITY_QUALITY_OF_SERVICE SecurityQualityOfService;
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

typedef const OBJECT_ATTRIBUTES *PCOBJECT_ATTRIBUTES;

EXTERN_C
NTSYSCALLAPI
NTSTATUS
NTAPI
NtWaitForSingleObject(_In_ HANDLE Handle, _In_ BOOLEAN Alertable,
                      _In_opt_ PLARGE_INTEGER Timeout);

EXTERN_C
NTSYSCALLAPI
NTSTATUS
NTAPI
NtFreeVirtualMemory(_In_ HANDLE ProcessHandle,
                    _Inout_ __drv_freesMem(Mem) PVOID *BaseAddress,
                    _Inout_ PSIZE_T RegionSize, _In_ ULONG FreeType);

EXTERN_C
NTSYSCALLAPI
NTSTATUS
NTAPI
NtClose(_In_ _Post_ptr_invalid_ HANDLE Handle);
EXTERN_C
NTSYSCALLAPI
NTSTATUS
NTAPI
NtOpenProcess(_Out_ PHANDLE ProcessHandle, _In_ ACCESS_MASK DesiredAccess,
              _In_ PCOBJECT_ATTRIBUTES ObjectAttributes,
              _In_opt_ PCLIENT_ID ClientId);

EXTERN_C
NTSYSCALLAPI
NTSTATUS
NTAPI
NtWriteVirtualMemory(_In_ HANDLE ProcessHandle, _In_opt_ PVOID BaseAddress,
                     _In_reads_bytes_(NumberOfBytesToWrite) PVOID Buffer,
                     _In_ SIZE_T NumberOfBytesToWrite,
                     _Out_opt_ PSIZE_T NumberOfBytesWritten);

typedef _Function_class_(USER_THREAD_START_ROUTINE) NTSTATUS NTAPI
    USER_THREAD_START_ROUTINE(_In_ PVOID ThreadParameter);
typedef USER_THREAD_START_ROUTINE *PUSER_THREAD_START_ROUTINE;

typedef struct _PS_ATTRIBUTE {
  ULONG_PTR Attribute;
  SIZE_T Size;
  union {
    ULONG_PTR Value;
    PVOID ValuePtr;
  };
  PSIZE_T ReturnLength;
} PS_ATTRIBUTE, *PPS_ATTRIBUTE;

_Struct_size_bytes_(TotalLength) typedef struct _PS_ATTRIBUTE_LIST {
  SIZE_T TotalLength;
  PS_ATTRIBUTE Attributes[1];
} PS_ATTRIBUTE_LIST, *PPS_ATTRIBUTE_LIST;

EXTERN_C
NTSYSCALLAPI
NTSTATUS
NTAPI
NtCreateThreadEx(_Out_ PHANDLE ThreadHandle, _In_ ACCESS_MASK DesiredAccess,
                 _In_opt_ PCOBJECT_ATTRIBUTES ObjectAttributes,
                 _In_ HANDLE ProcessHandle,
                 _In_ PUSER_THREAD_START_ROUTINE StartRoutine,
                 _In_opt_ PVOID Argument,
                 _In_ ULONG CreateFlags, // THREAD_CREATE_FLAGS_*
                 _In_ SIZE_T ZeroBits, _In_ SIZE_T StackSize,
                 _In_ SIZE_T MaximumStackSize,
                 _In_opt_ PPS_ATTRIBUTE_LIST AttributeList);

EXTERN_C
NTSYSCALLAPI
NTSTATUS
NTAPI
NtAllocateVirtualMemory(
    _In_ HANDLE ProcessHandle,
    _Inout_ _At_(*BaseAddress,
                 _Readable_bytes_(*RegionSize) _Writable_bytes_(*RegionSize)
                     _Post_readable_byte_size_(*RegionSize)) PVOID *BaseAddress,
    _In_ ULONG_PTR ZeroBits, _Inout_ PSIZE_T RegionSize,
    _In_ ULONG AllocationType, _In_ ULONG PageProtection);

EXTERN_C
NTSYSAPI
NTSTATUS
NTAPI
LdrUnloadDll(
    _In_ PVOID DllHandle
);

EXTERN_C
NTSYSAPI
NTSTATUS
NTAPI
LdrLoadDll(
    _In_opt_ PCWSTR DllPath,
    _In_opt_ PULONG DllCharacteristics,
    _In_ PCUNICODE_STRING DllName,
    _Out_ PVOID *DllHandle
);

EXTERN_C
NTSYSAPI
NTSTATUS
NTAPI
LdrUnloadDll(
    _In_ PVOID DllHandle
);

EXTERN_C
FORCEINLINE
VOID
NTAPI_INLINE
RtlInitUnicodeString(
    _Out_ PUNICODE_STRING DestinationString,
    _In_opt_z_ PCWSTR SourceString
    )
{
    if (SourceString)
        DestinationString->MaximumLength = (DestinationString->Length = (USHORT)(wcslen(SourceString) * sizeof(WCHAR))) + sizeof(UNICODE_NULL);
    else
        DestinationString->MaximumLength = DestinationString->Length = 0;

    DestinationString->Buffer = (PWCH)SourceString;
}



// Custom
NTSTATUS load_lib(PCWSTR path_ptr) {
    UNICODE_STRING upath;
    RtlInitUnicodeString(&upath, path_ptr);
    return LdrLoadDll(nullptr, nullptr, &upath, nullptr);
}
