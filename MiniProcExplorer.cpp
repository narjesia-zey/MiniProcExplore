#include <Windows.h>
#include <Winternl.h>
#include <stdio.h>
#include <psapi.h>

typedef NTSTATUS (NTAPI *NTQuerySystemInformation_t)(\
SYSTEM_INFORMATION_CLASS SystemInformationClass,
PVOID SystemInformation,
ULONG SystemInformationLength,
PULONG ReturnLength);

BOOL EnablePrivilege(LPCWSTR name){
HANDLE token;
TOKEN_PRIVILEGES tp;
if(!OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES,&token)) return FALSE;
LookupPrivilegeValueW(NULL,name,&tp.Privileges[0].Luid);
tp.PrivilegeCount=1;
tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
AdjustTokenPrivileges(token,FALSE,&tp,sizeof(tp),NULL,NULL);
CloseHandle(token);
return TRUE;
}

int main(){

//Load Native Api Dynamically
NTQuerySystemInformation_t NTQuerySystemInformation = (NTQuerySystemInformation_t)GetProcAddress(GetModuleHandleW(L"ntdll.dll"),"NtQuerySystemInformation");
if(!NTQuerySystemInformation){
 printf("[-] NTQuerySystemInformation failed to load ");
}

EnablePrivilege(L"SeDebugPrivilege");

//Query Process Information
ULONG len = 0;
NTQuerySystemInformation(SystemProcessInformation,NULL,0,&len);

PBYTE buffer = (PBYTE) malloc(len);

if(NTQuerySystemInformation(SystemProcessInformation,buffer,len,&len)!=0){
printf("Failed to query process information \n");
return 1; 
}

//parse the resullt
PSYSTEM_PROCESS_INFORMATION spi = (PSYSTEM_PROCESS_INFORMATION)buffer;
while(TRUE){
printf("PID: %5u | Threads: %2u  | Name: %ws \n",spi->UniqueProcessId,spi->NumberOfThreads,spi->ImageName.Buffer ? spi->ImageName.Buffer : L"System");

int pid = (ULONG)(ULONG_PTR)spi->UniqueProcessId;
PROCESS_MEMORY_COUNTERS_EX pmc;
HANDLE hprocess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,FALSE,pid);
if(GetProcessMemoryInfo(hprocess,(PROCESS_MEMORY_COUNTERS*)&pmc,sizeof(pmc))){
printf("Working set : %1u kb \n", pmc.WorkingSetSize / 1024);
}

wchar_t path[MAX_PATH];
DWORD size = MAX_PATH;
QueryFullProcessImageNameW(hprocess,0,path,&size);
printf("image path: %ws \n",path);
CloseHandle(hprocess);

if(!spi->NextEntryOffset) break;
spi = (PSYSTEM_PROCESS_INFORMATION)(((PBYTE)spi)+spi->NextEntryOffset);

}
getchar();
return 0;
}