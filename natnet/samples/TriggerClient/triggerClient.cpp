// mocap
#include <NatNetTypes.h>
#include <NatNetCAPI.h>
#include <NatNetClient.h>

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <fstream>
#include <vector>


/*
Usage:

	triggerClient [ServerIP] [ Instruction ]

	[ServerIP]           IP address of the server (e.g. 192.168.0.107) 
	[Instruction]        "rec" / "stop"
*/

int connectClient();
int startRecording();
int stopRecording();

NatNetClient* g_pClient = NULL;
sNatNetClientConnectParams g_connectParams;
sServerDescription g_serverDescription;
int g_analogSamplesPerMocapFrame = 0;
static const ConnectionType kDefaultConnectionType = ConnectionType_Multicast;

int main( int argc, char* argv[] )
{
    // print version info
    unsigned char ver[4];
    NatNet_GetVersion( ver );
    printf( "Trigger OptiTrack Client (NatNet ver. %d.%d.%d.%d)\n", ver[0], ver[1], ver[2], ver[3] );
	g_pClient = new NatNetClient();
	g_connectParams.connectionType = kDefaultConnectionType;


	if ( argc == 3)
	{
		g_connectParams.serverAddress = argv[1];

		// Connect to Motive
			int iResult;
			iResult = connectClient();
			if (iResult != ErrorCode_OK)
			{
				printf("Error initializing client. Exiting\n");
				return 1;
			}
			else
			{
				printf("Client initialized and ready.\n");
   			}

		// Instructions
		if (strcmp(argv[2],"rec") == 0)
		{
			iResult = startRecording();

			if (iResult != ErrorCode_OK)
				{
					printf("Error sending 'rec' instruction. Exiting");
					return 1;
				}
				else
				{
					printf("Client send rec instruction successfully.\n");
				}
		} 

		else if (strcmp(argv[2],"stop") == 0)
		{
			iResult = stopRecording();

			if (iResult != ErrorCode_OK)
			{
				printf("Error sending 'stop' instruction. Exiting");
				return 1;
			}
			else
			{
				printf("Client send stop instruction successfully.\n");
			}
		}	

	}
	else printf("Parameter error. Please indicate triggerClient [ServerIP] [ Instruction: rec/stop ] \n");
}


// Establish a NatNet Client connection
int connectClient()
{
    // Release previous server
    g_pClient->Disconnect();

    // Init Client and connect to NatNet server
    int retCode = g_pClient->Connect( g_connectParams );
    if (retCode != ErrorCode_OK)
    {
        printf("Unable to connect to server.  Error code: %d. Exiting\n", retCode);
        return ErrorCode_Internal;
    }
    return ErrorCode_OK;
}

int startRecording()
{
    void* pResult;
    int nBytes = 0;
    ErrorCode ret = ErrorCode_OK;
    std::string command = "StartRecording";

    // Release previous server
    g_pClient->Disconnect();

    // Init Client and connect to NatNet server
    int retCode = g_pClient->Connect( g_connectParams );
    if (retCode != ErrorCode_OK)
    {
        printf("Unable to connect to server.  Error code: %d. Exiting\n", retCode);
        return ErrorCode_Internal;
    }
    else
    {
        // connection succeeded
        ret = g_pClient->SendMessageAndWait("StartRecording", 3, 100, &pResult, &nBytes);
        if (ret == ErrorCode_OK)
        {
            int opResult = *((int*)pResult);
            if (opResult == 0)
                printf("%s handled and succeeded.\n", command.c_str());
            else
                printf("&%s handled but failed.\n", command.c_str());
        }
        else
            printf("Error sending command: %s.\n", command.c_str());
    }
    return ErrorCode_OK;
}

int stopRecording()
{
    void* pResult;
    int nBytes = 0;
    ErrorCode ret = ErrorCode_OK;
    std::string command = "StopRecording";

    // Release previous server
    g_pClient->Disconnect();

    // Init Client and connect to NatNet server
    int retCode = g_pClient->Connect( g_connectParams );
    if (retCode != ErrorCode_OK)
    {
        printf("Unable to connect to server.  Error code: %d. Exiting\n", retCode);
        return ErrorCode_Internal;
    }
    else
    {
        // connection succeeded
        ret = g_pClient->SendMessageAndWait(command.c_str(), 3, 100, &pResult, &nBytes);
        if (ret == ErrorCode_OK)
        {
            int opResult = *((int*)pResult);
            if (opResult == 0)
                printf("%s handled and succeeded.\n", command.c_str());
            else
                printf("&%s handled but failed.\n", command.c_str());
        }
        else
            printf("Error sending command: %s.\n", command.c_str());
    }
    return ErrorCode_OK;
}

