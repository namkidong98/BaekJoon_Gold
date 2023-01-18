//�ı� ǥ���(���2)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int convert(char command) {
	if (command == '+') return 0;
	else if (command == '-') return 1;
	else if (command == '*') return 2;
	else if (command == '/') return 3;
	else if (command == '(') return 4;
	else if (command == ')') return 5;
	else return -1; //����
}

int main() {
	int i, len;
	char string[101]; //���� ǥ����� ���ڿ��� �����ϴ� ����, ���̴� 100�� ���� �ʴ´�
	char stack[101]; //������ ������ �ٲٴ� �������� ����ϴ� stack
	int top = -1;
	
	int command;

	int isp[6] = { 1, 1, 2, 2, 0, 10 }; //in stack preference	   +, -, *, /, (, ) �� �ش�
	int icp[6] = { 1, 1, 2, 2, 10, 0 }; //incoming preference	   +, -, *, /, (, ) �� �ش�

	scanf("%s", string);
	len = strlen(string);
	for (i = 0; i < len; i++) {
		if (string[i] >= 65 && string[i] <= 90) { //���ĺ� �빮���̸� --> �ǿ������̸�
			printf("%c", string[i]);
		}
		else { //�������̸�
			if (string[i] == ')') { //���ȣ�̸� (��ȣ�� �켱������ �ֻ����̹Ƿ�)
				while (stack[top] != '(') { //�°�ȣ ���� ������ pop and print 
					printf("%c", stack[top--]);
				}
				top--; //�°�ȣ�� ��� ���� pop
			}
			else { //���ȣ �̿��� ������
				command = convert(string[i]);
				while (icp[command] <= isp[convert(stack[top])]) { //���� ������ �������� �켱����(icp)�� ���� ���� �������� �켱����(isp)���� �۰ų� ������
					//pop and print								   //������ ���� �켱�������� �ؾ� �ϴϱ� pop, ���Ƶ� ���� �� �ź��� �ؾ� �ϴϱ� pop
					printf("%c", stack[top--]);
				}
				//push
				stack[++top] = string[i];
			}
		}
	}
	//�����ڸ� ��� stack �ȿ� ���� �ִ°Ŵ� �� ������(������ �۾�)
	while (top != -1) {
		printf("%c", stack[top--]);
	}
}