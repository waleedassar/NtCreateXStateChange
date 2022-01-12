#pragma once
#include "windows.h"




#define ulong unsigned long
#define ulonglong unsigned long long
#define ULONG unsigned long
#define ULONGLONG unsigned long long
#define ushort unsigned short
#define USHORT unsigned short
#define uchar unsigned char
#define UCHAR unsigned char


#define SEC_IMAGE           0x1000000
#define SEC_NEVER_RELOCATE 0x8000000 //SEC_DATA
#define SEC_UNK 0x100000
#define SEC_PROTECTED_IMAGE 0x2000000
#define SEC_FOR_DRIVER 0x400000
#define SEC_UNK2 0x4000000
#define SEC_UNK3 0x10000000
#define SEC_UNK4 0x40000000
#define SEC_UNK5 0x80000000

#define KernelMode 0
#define UserMode 1

#define RANDOM_PAGE_SIZE 0x1000


#define STATUS_CONFLICTING_ADDRESSES 0xC0000018
#define STATUS_INVALID_PARAMETER_4 0xC00000F2
#define STATUS_INVALID_PARAMETER_2 0xC00000F0

#define OBJ_PROTECT_CLOSE 		0x00000001
#define OBJ_INHERIT             0x00000002
#define OBJ_AUDIT_OBJECT_CLOSE  0x00000004
#define OBJ_PERMANENT           0x00000010
#define OBJ_EXCLUSIVE           0x00000020
#define OBJ_CASE_INSENSITIVE    0x00000040
#define OBJ_OPENIF              0x00000080
#define OBJ_OPENLINK            0x00000100
#define OBJ_KERNEL_HANDLE       0x00000200
#define OBJ_FORCE_ACCESS_CHECK  0x00000400
#define OBJ_VALID_ATTRIBUTES    0x000007F2
#define OBJ_CREATOR_INFO_MINE   0x00010000



struct _UNICODE_STRING
{
	unsigned short Length;
	unsigned short MaxLength;
	unsigned long Pad;
	wchar_t* Buffer;
};


struct _OBJECT_ATTRIBUTES {
  ULONGLONG           Length;
  HANDLE          RootDirectory;
  _UNICODE_STRING* ObjectName;
  ULONGLONG           Attributes;
  PVOID           SecurityDescriptor;
  PVOID           SecurityQualityOfService;
};




typedef struct _IO_STATUS_BLOCK {
  union {
    int Status;
    void*    Pointer;
  } DUMMYUNIONNAME;
  ulonglong Information;
} IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;


typedef int(*fNtCreateProcessStateChange)
(HANDLE* pOutHandle,
ulonglong DesiredAccess,
_OBJECT_ATTRIBUTES* ObjectAttributes,
HANDLE hProcess,
ulonglong Flags);

typedef int(*fNtChangeProcessState)
(HANDLE hProcessStateChange,
HANDLE hProcess,
ulonglong InfoClass,
ulonglong Reserved,
ulonglong Flags,
ulonglong Flags2);


extern "C"
{
	int ZwTerminateProcess(HANDLE ProcessHandle, NTSTATUS ExitStatus);
	int ZwClose(HANDLE Handle);
}