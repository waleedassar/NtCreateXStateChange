// ChangeState_Syscalls.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
#include "time.h"


#include "Header.h"


fNtCreateProcessStateChange NtCreateProcessStateChange = 0;
fNtChangeProcessState NtChangeProcessState = 0;




void Resolve()
{
	HMODULE hNtdll = GetModuleHandle(L"ntdll.dll");
	NtCreateProcessStateChange = (fNtCreateProcessStateChange)GetProcAddress(hNtdll,"NtCreateProcessStateChange");
	NtChangeProcessState = (fNtChangeProcessState)GetProcAddress(hNtdll,"NtChangeProcessState");
	
	if( (!NtCreateProcessStateChange)||(!NtChangeProcessState) )
	{
		printf("OS Not supported\r\n");
		ExitProcess(0);
	}
	
}



//returns hProcess
HANDLE CreateDummyProcess()
{
	PROCESS_INFORMATION PI;
	STARTUPINFO SI = {sizeof(SI)};

	wchar_t Path_All[MAX_PATH+1] = {0};

	GetSystemDirectory(Path_All,MAX_PATH);
	wcscat(Path_All,L"\\calc.exe");

	if(!CreateProcess(Path_All,0,0,0,FALSE,CREATE_NEW_CONSOLE /*CREATE_SUSPENDED*/,0,0,&SI,&PI))
	{
		printf("Error creating process\r\n");
		return 0;
	}


	return PI.hProcess;
}

void Freeze(HANDLE hProcessStateChange,HANDLE hProcess)
{
		//Freeze
		int ret = NtChangeProcessState(hProcessStateChange,
			hProcess,
			0 /* 0 ==> Freeze */,
			0,
			0,
			0);

		printf("NtChangeProcessState, ret: %X\r\n",ret);
}


void Thaw(HANDLE hProcessStateChange,HANDLE hProcess)
{
		//Thaw
		int ret = NtChangeProcessState(hProcessStateChange,
			hProcess,
			1 /* 1 ==> Thaw */,
			0,
			0,
			0);

		printf("NtChangeProcessState, ret: %X\r\n",ret);
}

HANDLE CreateProcessStateChange(HANDLE hProcess)
{


	_OBJECT_ATTRIBUTES ObjAttr = {0};
	ObjAttr.Length = sizeof(ObjAttr);

	

	HANDLE hProcessStateChange = 0;
	int ret = NtCreateProcessStateChange(&hProcessStateChange,GENERIC_ALL /* Desired */,&ObjAttr,hProcess,0);
	printf("NtCreateProcessStateChange, ret: %X\r\n",ret);

	if(ret >= 0)
	{
		printf("hProcessStateChange: %I64X\r\n",hProcessStateChange);
		return hProcessStateChange;
	}

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));

	Resolve();

	HANDLE hProcess = CreateDummyProcess(); //GetCurrentProcess();


	while(1)
	{
		HANDLE hProcessStateChange = CreateProcessStateChange(hProcess);

		

		Freeze(hProcessStateChange,hProcess);

		

		Thaw(hProcessStateChange,hProcess);
		
		
		
		//ZwTerminateProcess(hProcess,0);
		//ZwClose(hProcessStateChange);

		//getchar();
	}
	return 0;
}

