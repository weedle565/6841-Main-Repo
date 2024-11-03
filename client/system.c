#include <windows.h>
#include <stdio.h>

void print_memory_details(char* memory) {
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);

    GlobalMemoryStatusEx(&mem);

    // 1073741824 <-- size of 1gb in bits.
    printf("%llu size of ram buffer\n", sizeof("%lld GB Ram") + sizeof(mem.ullTotalPhys / 1073741824));
    sprintf(memory, "%lld GB Ram", mem.ullTotalPhys / 1073741824);
}

void print_cpu_details(char* cpuSpeed) {

    DWORD bufferSize = MAX_PATH;
    DWORD mhz = MAX_PATH;
    HKEY hkey;

    RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hkey);

    RegQueryValueEx(hkey, "~MHz", 0, 0, (LPBYTE)&mhz, &bufferSize);

    const double ghz = (double)mhz / 1000.f;

    printf("%llu size of memory buffer\n", sizeof("%.2f GHz"));

    // Print the speed of the cpu
    sprintf(cpuSpeed, "%.2f GHz", ghz);

}

void print_user_details(char* userName) {

    DWORD bufferSize = (DWORD)sizeof(userName) / sizeof(userName[0]);
    char buffer[bufferSize];
    GetUserName(buffer, &bufferSize);

    printf("%llu sizeof user\n", sizeof("User: ") + sizeof(buffer));
    sprintf(userName, "User: %s", buffer);
}
