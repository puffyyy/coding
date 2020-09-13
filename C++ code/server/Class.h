#ifndef CLIENT_H
#define CLIENT_H
class Client
{
	static char  ServerName;
	static int ClientNum;
public:
	static void ChangeServerName(char name);
	static int getClientNum();
};
#endif