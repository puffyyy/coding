#include "Class.h"

using namespace std;
void Client::ChangeServerName(char name) {
	Client::ServerName = name;
	Client::ClientNum ++;
}
int Client::getClientNum() {
	return Client::ClientNum;
}