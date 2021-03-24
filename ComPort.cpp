#include "ComPort.h"

HANDLE Com_Open(wchar_t *Com_Name,int baudrate)
{
	HANDLE hCom;
	DCB dcb;
	COMMTIMEOUTS CommTimeouts;

    hCom = CreateFile(Com_Name,
					  GENERIC_READ|GENERIC_WRITE,
					  0,
					  0,
					  OPEN_EXISTING,
					  FILE_ATTRIBUTE_NORMAL,
					  NULL);
	                  
	GetCommState(hCom, &dcb);

    dcb.BaudRate = baudrate;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
	dcb.fBinary = TRUE;                      // Binary mode; no EOF check
	dcb.fParity = TRUE;                      // Enable parity checking
	dcb.fOutxCtsFlow = FALSE;                // No CTS output flow control
	dcb.fOutxDsrFlow = FALSE;                // No DSR output flow control
	dcb.fDtrControl = DTR_CONTROL_ENABLE;    // DTR flow control type
	dcb.fDsrSensitivity = FALSE;             // DSR sensitivity
	dcb.fTXContinueOnXoff = TRUE;            // XOFF continues Tx
	dcb.fOutX = FALSE;                       // No XON/XOFF out flow control
	dcb.fInX = FALSE;                        // No XON/XOFF in flow control
	dcb.fErrorChar = FALSE;                  // Disable error replacement
	dcb.fNull = FALSE;                       // Disable null stripping
	dcb.fRtsControl = RTS_CONTROL_ENABLE;    // RTS flow control
	dcb.fAbortOnError = FALSE;               // Do not abort reads/writes on error

	SetCommState(hCom, &dcb);

	GetCommTimeouts (hCom, &CommTimeouts);

	CommTimeouts.ReadIntervalTimeout = MAXDWORD;  
	CommTimeouts.ReadTotalTimeoutMultiplier = 10;  
	CommTimeouts.ReadTotalTimeoutConstant = 0;    
	CommTimeouts.WriteTotalTimeoutMultiplier = 10;  
	CommTimeouts.WriteTotalTimeoutConstant = 1000;    

	SetCommTimeouts (hCom, &CommTimeouts);

	return hCom;
}

void Write_Cmd(HANDLE hCom, char *word)
{
	DWORD dwNumBytesWritten;
	int a = 0;
	a = WriteFile (hCom,                   // Port handle
		     	   word,                   // Pointer to the data to write 
				   64,                     // Number of bytes to write
				   &dwNumBytesWritten,     // Pointer to the number of bytes written
				   NULL                    // Must be NULL for Windows CE
				  );
	printf("Cmd Recieved = %d (1 = True; 0 = False)\n", a);
}

void Read_Cmd(HANDLE hCom, char *buf, int length)
{
	int templen = length;
    DWORD size;
    while(templen!=0)
    {
		ReadFile(hCom, &buf[length-templen], templen, &size, NULL);
        templen -= size;
    }
}

void Com_Close(HANDLE hCom)
{
	printf("Com Closed = %d (1 = True; 0 = False)\n", CloseHandle(hCom));
}
