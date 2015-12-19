#ifndef _MFD_H_
#define _MFD_H_

#include"common.h"
#include"command.h"
using namespace std;

//32个字节
typedef struct mfd
{
	char usrname[14];
	char usrpass[14];
	int link;  //该用户的UFD所在的盘号

}MFD;

typedef struct ufd
{
	char filename[14];
	int mode; // 文件权限0 - readonly;  1 - writeonly;  2 - read / write
	int length;
	int addr;
}UFD;

typedef struct uof
{
	char filename[14];
	int mode;
	int state; //0建立,1打开
	int read_poit; //读写指针
	int write_poit;

}UOF;

typedef struct cluster
{
	int next_num;
	int is_data;
	char data[256];

}Cluster;

typedef void(*func)(void);
typedef struct hand
{
	char *pname;
	func handler;
}HAND_TO;

typedef struct cmd
{
	string cmd_num[4];
}COMMAND;


COMMAND cmd_in;
extern HAND_TO handlerlist[];

void cmd_in_parse()
{
	string s;
	getline(cin, s);
	
		stringstream stream(s);
		int i = 0;
		//命令解析至cmd_in 中
		while (stream >> cmd_in.cmd_num[i])
			i++;
		//遍历命令列表
		int flag = 0;
		for (int i = 0; handlerlist[i].pname!=NULL; i++)
		{
			if (strcmp(handlerlist[i].pname, cmd_in.cmd_num[0].c_str()) == 0)
			{
				flag = 1;
				handlerlist[i].handler();
				break;
			}
		}
		if (!flag)
			cout << "未找到命令" << endl;
	
}


#endif _MFD_H_
