#include <iostream>
using namespace std;

void QiPanInit(char *a);
void QiPanPrt(char A[][9]);
int WinOrLose(char A[][9], char b);
int main(void)
{
	int flag;
	char qipan[9][9]; //用于存储棋子
	char qizi[2] = { 'o', '@' }; //白子（o）、黑子（@）
	int i = 0;//回合数 用于判定是白方落子还是黑方落子
	QiPanInit(&qipan[0][0]);
	cout << "   双人五子棋" << endl;
	cout << "游戏规则：" << endl
		<< "1.分回合制，白方先落子，" << endl
		<< "2.落子方式为输入落子的行、列，行号、列号均从1开始数起，" << endl
		<<"3.先达到五子连珠的一方胜出。" << endl;
	QiPanPrt(qipan);
	
	while (i >= 0){ //下棋死循环，直到有输赢结束
		int hang=0, lie=0;
		if (i % 2 == 0){
			cout << "白方落子" << endl;
			cout << "输入落子的行、列" << endl;
			cin >> hang >> lie;
			if (hang > 9 || hang < 1 || lie>9 || lie < 1 || qipan[hang][lie] != '+'){
				cout << "输入的行、列有误，或者该点已有棋子，请重新输入！" << endl; //没有i++,回合数不变 循环结束后仍是当前回合
			}else{
				qipan[hang-1][lie-1] = qizi[0]; //替换为白子
				flag = WinOrLose(qipan, qizi[0]);
				if (flag == 1) {
					cout << "白方胜！" << endl << endl;
					QiPanPrt(qipan);
					system("pause");
					return 0;
				}else if (flag == 0){
					QiPanPrt(qipan);
					i++;
				}
				else if (flag == 2){
					cout << "棋盘已满！平局！" << endl << endl;
					system("pause");
					return 0;
				}
			}
		}else{
			cout << "黑方落子" << endl;
			cout << "输入落子的行、列" << endl;
			cin >> hang >> lie;
			if (hang > 9 || hang < 1 || lie>9 || lie < 1 || qipan[hang][lie] != '+'){
				cout << "输入的行、列有误，或者该点已有棋子，请重新输入！" << endl; //没有i++,回合数不变 循环结束后仍是当前回合
			}
			else{
				qipan[hang-1][lie-1] = qizi[1]; //替换为黑子
				flag = WinOrLose(qipan, qizi[1]);
				if (flag == 1) {
					cout << "黑方胜！" << endl << endl;
					QiPanPrt(qipan);
					system("pause");
					return 0;
				}
				else if (flag == 0){
					//继续下棋
					QiPanPrt(qipan);
					i++;
				}
				else if (flag == 2){
					cout << "棋盘已满！平局！" << endl << endl;
					system("pause");
					return 0;
				}
			}
		}
	}

	return 0;
}

void QiPanInit(char *a) //初始化棋盘
{
	int i, j;
	for (i = 0; i <= 9; i++){

		for (j = 0; j <= 9; j++){
			*a = '+';
			a++;
		}
	}
}

void QiPanPrt(char A[][9]) //输出棋盘
{
	int i,j;
	for (i = 0; i < 9; i++){

		for (j = 0; j < 9; j++){			
			cout << A[i][j] << " ";			
		}
		cout << i+1 << endl; //行号
	}
	cout << "1 2 3 4 5 6 7 8 9"<<endl     //列号
		 <<"-------------------"<<endl; //棋盘分界线
}

int WinOrLose(char A[][9],char b) //将棋盘信息和当前方棋子交给函数，判断输赢
{
	int i,j;
	char const* p;  //p为const，保证不会在判断过程中对棋子内容做修改
	/*
	从左往右、从上往下遍历棋盘，若有棋子和当前棋子一样，则将其横向右，竖向下，撇向下，奈向下判断是否有五子连珠
	1.因为是左往右、从上往下遍历棋盘，该棋子之前的棋子（位于目前棋子的左、上方位）已经判别过，
	  所以不需要判断横向左，竖向上，撇向上，奈向上是否五子连珠
    2.奈向下的棋子判断区域为左上5×5区域（过了该区域不可能有五子连珠）
	  撇向下的棋子判断区域为右上5×5区域
	  竖向下的棋子判断区域为上半区域
	  横向右的棋子判断区域为左半区域
	*/
	p = &A[0][0]; //遍历左上区域
	for (i = 0; i < 5; i++){
		for (j = 0; j < 5; j++){
			if (*p == b){
				//找到棋子开始判断，五子连珠返回值1，没有返回值0				
				//奈向下
				if (*(p + 10) == b && *(p + 20) == b && *(p + 30) == b && *(p + 40) == b) return 1;
			}
			p++;
		}
		p++;
		p++;
		p++;
		p++;
		//p指向下一行开头
	}

	p = &A[4][0]; //遍历右上区域
	for (i = 0; i < 5; i++){
		for (j = 0; j < 5; j++){
			//撇向下
			if (*(p + 8) == b && *(p + 16) == b && *(p + 24) == b && *(p + 32) == b) return 1;
		}
		p++;
		p++;
		p++;
		p++;
	}

	p = &A[0][0]; //遍历上半区域
	for (i = 0; i < 5; i++){
		for (j = 0; j < 9; j++){
			//竖向下
			if (*(p + 9) == b && *(p + 18) == b && *(p + 27) == b && *(p + 36) == b) return 1;
		}
	}

	p = &A[0][0]; //遍历左半区域
	for (i = 0; i < 9; i++){
		for (j = 0; j < 5; j++){
			//横向右
			if (*(p + 1) == b && *(p + 2) == b && *(p + 3) == b && *(p + 4) == b) return 1;
		}
		p++;
		p++;
		p++;
		p++;
	}

	int count=0;
	p = &A[0][0];
	for (i = 0; i < 80; i++){		
			if (*p == '+') count++;
			p++;
	}
	if (count!=0) {
		//啥也没有
		return 0;
	}else{
		//棋盘满了
		return 2;
	}
		
}