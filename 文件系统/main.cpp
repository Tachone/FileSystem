#define _CRT_SECURE_NO_WARNINGS

#include "common.h"
#include "menu.h"
#include "command.h"
#include "MFD.h"
#include "Fileopera.h"
using namespace std;

vector <MFD> UsrInfo;
vector < vector<UFD> > FileInfo;
vector< vector<UOF> > FileState;
vector< Cluster> FileCluster;

MFD UsrInput;
UFD FileInput;
UOF StateInput;
Cluster ClusterInput;
int num; //选项选择
int Headnum;
int curID;

HAND_TO handlerlist[] =
{
	{ "Chmod", do_Chmod },
	{ "Chown", do_Chown },
	{ "Mv", do_Mv },
	{ "Copy", do_Copy },
	{ "Type", do_Type },
	{ "Passwd", do_Passwd },
	{ "Login", do_Login },
	{ "Logout", do_Logout },
	{ "Create", do_Create },
	{ "Delete", do_Delete },
	{ "Open", do_Open },
	{ "Close", do_Close },
	{ "Write", do_Write },
	{ "Read", do_Read },
	{ "Help", do_Help },
	{ "dir", do_dir},
	{ "sysc",do_sysc},
	{ "Register", do_register},
	{ "Exit", do_exit},
	{ "Clear", do_Clear},
	{ NULL, NULL }
};

int main()
{
	loginWelcome();
	initFiletoRom();
	while (1)
	{ 
		//默认root登陆
		cout << "["<<UsrInfo[curID].usrname<<"]$ :";
		cmd_in_parse();
	}
	return 0;
}
