// #include <stdio.h>
// #include <stdlib.h>
// #include <winsock2.h>
// #include <mswsock.h>
// #include <windows.h>
// #include <ws2tcpip.h>
//
//
// BYTE* read_file(char* path, long* path_size) {
//     FILE* file = fopen(path, "rb+");
//
//     fseek(file, 0, SEEK_END);
//     *path_size = ftell(file);
//     fseek(file, 0, SEEK_SET);
//     BYTE* buffer = malloc(sizeof(BYTE) *(*(path_size)));
//     fread(buffer, sizeof(BYTE), *path_size, file);
//     fclose(file);
//
//     printf("File size: %ld\n", *path_size);
//
//     return buffer;
// }
//
// void get_screen_size(long* x, long* y) {
//     DEVMODE devmode;
//     devmode.dmSize = sizeof(devmode);
//
//     EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &devmode);
//
//     *x = (long)devmode.dmPelsWidth;
//     *y = (long)devmode.dmPelsHeight;
// }
//
// void take_screenshot(char* path, const SOCKET sock) {
//
//     long x,y;
//     get_screen_size(&x,&y);
//
//     BITMAPFILEHEADER bmfHeader;
//     BITMAPINFOHEADER bmiHeader;
//     BITMAPINFO binfo;
//
//     ZeroMemory(&bmfHeader, sizeof(BITMAPFILEHEADER));
//     ZeroMemory(&bmiHeader, sizeof(BITMAPINFOHEADER));
//     ZeroMemory(&binfo, sizeof(BITMAPINFO));
//
//     bmfHeader.bfType = 0x4d42;
//     bmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
//
//     bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//     bmiHeader.biWidth = x;
//     bmiHeader.biHeight = y;
//     bmiHeader.biPlanes = 1;
//     bmiHeader.biBitCount = 24;
//     bmiHeader.biCompression = BI_RGB;
//
//     binfo.bmiHeader = bmiHeader;
//
//     DWORD stride = (bmiHeader.biBitCount * bmiHeader.biWidth + 31 & ~31) / 8 * bmiHeader.biHeight;
//
//     HDC hdc = GetDC(0);
//     HDC hdc_mem = CreateCompatibleDC(hdc);
//
//     BYTE* dib_bytes;
//     HBITMAP hbitmap = CreateDIBSection(hdc, &binfo, DIB_RGB_COLORS, (void**)&dib_bytes, 0, 0);
//
//     HGDIOBJ obj = SelectObject(hdc_mem, hbitmap);
//     BitBlt(hdc_mem, 0, 0, x,y, hdc, 0, 0, SRCCOPY);
//
//     HANDLE hfile = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
//
//     BYTE* bfHeaderBytes = (BYTE*)&bmfHeader;
//     BYTE* biHeaderBytes = (BYTE*)&bmiHeader;
//
//     DWORD amount;
//     WriteFile(hfile, bfHeaderBytes, sizeof(BITMAPFILEHEADER), &amount, 0);
//     WriteFile(hfile, biHeaderBytes, sizeof(BITMAPINFOHEADER), &amount, 0);
//     WriteFile(hfile, dib_bytes, stride, &amount, 0);
//
//     CloseHandle(hfile);
//
//     long imageSize;
//     BYTE* imageBytes = read_file(path, &imageSize);
//     char imageLengthBuffer[1024];
//     ZeroMemory(imageLengthBuffer, sizeof(imageLengthBuffer));
//     sprintf(imageLengthBuffer, "%ld", imageSize);
//     printf("%d %d\n", imageSize, *imageLengthBuffer);
//     int result = send(sock, imageLengthBuffer, sizeof(imageLengthBuffer), 0);
//     printf("Sent\n");
//     if (result == SOCKET_ERROR) {
//         printf("Socket error %d\n", WSAGetLastError());
//     }
//
//     HANDLE hfile2 = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
//     if (hfile2 == INVALID_HANDLE_VALUE) {
//         printf("Error opening file: %d\n", GetLastError());
//     }
//
//     printf("Sending");
//     TransmitFile(sock, hfile2, 0, 0, 0, 0, 0);
//
//     printf("Sent file\n");
//
//
//     CloseHandle(hfile);
//     CloseHandle(hfile2);
//
//     free(imageBytes);
//
//     SelectObject(hdc_mem, obj);
//     DeleteDC(hdc_mem);
//     ReleaseDC(0, hdc);
//     DeleteObject(hbitmap);
// }

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <windows.h>
#include "screenshot.h"

BYTE* read_file(char* path, long* fp_len) {
  FILE* fp;
  fp = fopen(path, "rb+");
  fseek(fp, 0, SEEK_END);
  *fp_len = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  BYTE* fp_buf = (BYTE*)malloc(sizeof(BYTE) * (*(fp_len)));
  fread(fp_buf, sizeof(BYTE), *fp_len, fp);
  fclose(fp);

  printf("\nthis is the len of the ss.bmp : %ld\n", *fp_len);
  return fp_buf;
}

void get_screen_size(long* x, long* y) {
  DEVMODE dm;
  dm.dmSize = sizeof(dm);

  EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &dm);

  *x = (long)dm.dmPelsWidth;
  *y = (long)dm.dmPelsHeight;
}

void take_screenshot(char* path, SOCKET sock) {
  long x, y;
  get_screen_size(&x, &y);

  BITMAPFILEHEADER bmf_header;
  BITMAPINFOHEADER bmi_header;
  BITMAPINFO bm_info;

  ZeroMemory(&bmf_header, sizeof(BITMAPFILEHEADER));
  ZeroMemory(&bmi_header, sizeof(BITMAPINFOHEADER));
  ZeroMemory(&bm_info, sizeof(BITMAPINFO));

  bmf_header.bfType = 0x4d42;
  bmf_header.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

  bmi_header.biSize = sizeof(BITMAPINFOHEADER);
  bmi_header.biWidth = x;
  bmi_header.biHeight = y;
  bmi_header.biPlanes = 1;
  bmi_header.biBitCount = 24;
  bmi_header.biCompression = BI_RGB;

  bm_info.bmiHeader = bmi_header;

  DWORD stride = ((((bmi_header.biBitCount * bmi_header.biWidth) + 31) & ~31) / 8) * bmi_header.biHeight;

  HDC hdc = GetDC(0);
  HDC hdc_mem = CreateCompatibleDC(hdc);

  BYTE* dib_bytes;
  HBITMAP hbitmap = CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&dib_bytes, 0, 0);

  HGDIOBJ old = SelectObject(hdc_mem, hbitmap);
  BitBlt(hdc_mem, 0, 0, x, y, hdc, 0, 0, SRCCOPY);

  HANDLE hfile = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

  BYTE* bmf_header_bytes = (BYTE*)&bmf_header;
  BYTE* bmi_header_bytes = (BYTE*)&bmi_header;

  DWORD amount;
  WriteFile(hfile, bmf_header_bytes, sizeof(BITMAPFILEHEADER), &amount, 0);
  WriteFile(hfile, bmi_header_bytes, sizeof(BITMAPINFOHEADER), &amount, 0);
  WriteFile(hfile, dib_bytes, stride, &amount, 0);

  CloseHandle(hfile);

  long img_len;
  BYTE* read = read_file(path, &img_len);
  char img_len_buf[1024];
  sprintf(img_len_buf, "%ld", img_len);
  send(sock, img_len_buf, sizeof(img_len_buf), 0);

  HANDLE hfile2 = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  TransmitFile(sock, hfile2, 0, 0, 0, 0, 0);
  CloseHandle(hfile2);

  free(read);

  SelectObject(hdc_mem, old);
  DeleteDC(hdc_mem);
  ReleaseDC(0, hdc);
  DeleteObject(hbitmap);
}