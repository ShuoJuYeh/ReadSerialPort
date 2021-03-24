#ifndef COMPORT_H
#define COMPORT_H

#include <stdio.h>
#include <winsock2.h>

// Standard binary header and data
#pragma pack(1)
typedef struct            
{
   unsigned char          sop1;          // 'N'
   unsigned char          sop2;          // 'C'
   unsigned char          sop3;          // 'K'
   unsigned char          sop4;          // 'U'
   float                  value;
}DATA;
#pragma pack(pop)

HANDLE Com_Open(wchar_t *, int);
void Write_Cmd(HANDLE , char *);
void Read_Cmd(HANDLE , char *, int);
void Com_Close(HANDLE);
HANDLE Com_Set();

#endif
