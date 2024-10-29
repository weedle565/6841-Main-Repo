#include <windows.h>
#include <stdio.h>
#include <fileapi.h>

void print_memory_details(char* memory) {
    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);

    GlobalMemoryStatusEx(&mem);

    // 1073741824 <-- size of 1gb in bits.
    printf("%llu size of ram buffer\n", sizeof("%lld GB Ram") + sizeof(mem.ullTotalPhys / 1073741824));
    sprintf(memory, "%lld GB Ram", mem.ullTotalPhys / 1073741824);
}

void print_cpu_details(char* cpu_speed) {

    DWORD buffer_size = MAX_PATH;
    DWORD mhz = MAX_PATH;
    HKEY hkey;

    RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hkey);

    RegQueryValueEx(hkey, "~MHz", 0, 0, (LPBYTE)&mhz, &buffer_size);

    const double ghz = (double)mhz / 1000.f;

    printf("%llu size of memory buffer\n", sizeof("%.2f GHz"));

    // Print the speed of the cpu
    sprintf(cpu_speed, "%.2f GHz", ghz);

}

void print_user_details(char* user_name) {

    DWORD buffer_size = (DWORD)sizeof(user_name) / sizeof(user_name[0]);
    char buffer[buffer_size];
    GetUserName(buffer, &buffer_size);

    printf("%llu sizeof user\n", sizeof("User: ") + sizeof(buffer));
    sprintf(user_name, "User: %s", buffer);
}

// Massive thanks to: https://stackoverflow.com/questions/31780738/c-determine-remaining-space-of-hard-drive
// for providing information on this as ive only ever seen it on linux and thus was unsure on the windows implementation
// void print_disk_space(char* disk_space) {
//
//     ULARGE_INTEGER free;
//     ULARGE_INTEGER total;
//     ULARGE_INTEGER total_free;
//
//     GetDiskFreeSpaceEx("c:\\", &free, &total, &total_free);
//
//     const double free_gb = (double)(signed __int64)(free.QuadPart) / (1024 * 1024 * 1024);
//     const double total_gb = (double)(signed __int64)(total.QuadPart) / (1024 * 1024 * 1024);
//
//     sprintf(disk_space, "%.2fgb Free, %.2fgb total", free_gb, total_gb);
//
// }