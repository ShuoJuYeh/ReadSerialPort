#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include <string>

// application reads from the specified serial port and reports the collected data
int main(int argc, char *argv[])
{
    printf("Welcome to the serial test app!\n\n");

    Serial* SP = new Serial(L"\\\\.\\COM4");    // adjust as needed

    if (SP->IsConnected())
        printf("We're connected\n");

    char *buffer = (char *)malloc( sizeof(DATA) );
    DATA *data  = (DATA *)malloc(sizeof(DATA));
    int dataLength = 1;
    int readResult = 0;
    int len2read = 0, tmp_len = 0;

    while(SP->IsConnected())
    {
        buffer[0] = buffer[1];
        buffer[1] = buffer[2];
        buffer[2] = buffer[3];
        readResult = SP->ReadData(&buffer[3],dataLength);

        if( buffer[0] == 'N' && buffer[1] == 'C' && buffer[2] == 'K' && buffer[3] == 'U')
        {
            len2read = sizeof(DATA)-4;
            tmp_len = len2read;
            while(tmp_len!=0)
            {
                readResult = SP->ReadData(&buffer[4+(len2read-tmp_len)], 1);
                tmp_len -= readResult;
            }

            memcpy(data, buffer, sizeof(DATA));

            printf("%f\n", data->value);
        }
    }

    return 0;
}
