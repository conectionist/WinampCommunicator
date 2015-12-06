#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>

#include "Server.h"

#define DEFAULT_BUFLEN 512

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

static SOCKET m_ListenSocket;
static SOCKET m_ClientSocket;

Server::Server(int port, string sShutdownEventName, string sLogPath, int nMaxConnections) :
	Runnable(sShutdownEventName),
	ILogable(sLogPath)
{
	m_nPort = port;

	WSADATA wsaData;
	int iResult;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	m_ListenSocket = INVALID_SOCKET;
	m_ClientSocket = INVALID_SOCKET;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		throw Win32Exception("WSAStartup", iResult);
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, std::to_string(m_nPort).c_str(), &hints, &result);
	if (iResult != 0) 
	{
		WSACleanup();
		throw Win32Exception("getaddrinfo", iResult);
	}

	// Create a SOCKET for connecting to server
	m_ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (m_ListenSocket == INVALID_SOCKET) 
	{
		freeaddrinfo(result);
		WSACleanup();

		throw Win32Exception("socket", WSAGetLastError());
	}

	// Setup the TCP listening socket
	iResult = bind(m_ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) 
	{
		freeaddrinfo(result);
		closesocket(m_ListenSocket);
		WSACleanup();
		
		throw Win32Exception("bind", WSAGetLastError());
	}

	freeaddrinfo(result);

	iResult = listen(m_ListenSocket, nMaxConnections);
	if (iResult == SOCKET_ERROR) 
	{
		closesocket(m_ListenSocket);
		WSACleanup();

		throw Win32Exception("listen", WSAGetLastError());
	}
}

Server::~Server()
{
}

void Server::Run()
{
	try
	{
		HandleIncomingConnections();
	}
	catch (const Win32Exception& w32Ex)
	{
		Log(w32Ex.GetErrorMessage());
	}
}

void Server::HandleIncomingConnections()
{
	int iResult;

	u_long iMode = 1;
	ioctlsocket(m_ListenSocket, FIONBIO, &iMode);

	while ALIVE
	{
		if (!WaitForNewClient())
			return;

		Log("Client connected");

		ioctlsocket(m_ClientSocket, FIONBIO, &iMode);
		if (m_ClientSocket == INVALID_SOCKET)
		{
			closesocket(m_ListenSocket);
			WSACleanup();

			throw Win32Exception("accept", WSAGetLastError());
		}

		// No longer need server socket
		closesocket(m_ListenSocket);

		// Receive until the peer shuts down the connection
		ReceiveMessage();

		// shutdown the connection since we're done
		iResult = shutdown(m_ClientSocket, SD_SEND);
		if (iResult == SOCKET_ERROR)
		{
			closesocket(m_ClientSocket);
			WSACleanup();

			throw Win32Exception("shutdown", WSAGetLastError());
		}

		// cleanup
		closesocket(m_ClientSocket);
		WSACleanup();
	}
}

bool Server::WaitForNewClient()
{
	while (m_ClientSocket == SOCKET_ERROR)
	{
		// Accept a client socket
		m_ClientSocket = accept(m_ListenSocket, NULL, NULL);

		int nError = WSAGetLastError();
		if (nError != WSAEWOULDBLOCK && nError != 0)
		{
			closesocket(m_ClientSocket);
			WSACleanup();

			throw Win32Exception("accept", WSAGetLastError());
		}
		else
		{
			Sleep(1000);

			if ALIVE
			{
				continue;
			}
			else
			{
				closesocket(m_ClientSocket);
				WSACleanup();

				return false;
			}
		}
	}

	return true;
}

void Server::ReceiveMessage()
{
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	int iResult;

	do
	{
		ZeroMemory(recvbuf, sizeof(recvbuf));
		iResult = recv(m_ClientSocket, recvbuf, recvbuflen, 0);
		int nError = WSAGetLastError();

		if (iResult > 0)
		{
			Log(string("Received: ") + recvbuf);

			HandleReceivedMessage(recvbuf);
		}
		/*else if (iResult == 0)
		{
			Log("Connection closing...");
		}*/
		else if (nError != WSAEWOULDBLOCK && nError != 0)
		{
			closesocket(m_ClientSocket);
			WSACleanup();

			throw Win32Exception("recv", WSAGetLastError());
		}
		else
		{
			Sleep(1000);

			if ALIVE
			{
				continue;
			}
			else
			{
				closesocket(m_ClientSocket);
				WSACleanup();

				return;
			}
		}

	} while (true);
}
