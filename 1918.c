//후기 표기식(골드2)
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
	else return -1; //오류
}

int main() {
	int i, len;
	char string[101]; //중위 표기식의 문자열을 저장하는 변수, 길이는 100을 넘지 않는다
	char stack[101]; //중위를 후위로 바꾸는 과정에서 사용하는 stack
	int top = -1;
	
	int command;

	int isp[6] = { 1, 1, 2, 2, 0, 10 }; //in stack preference	   +, -, *, /, (, ) 에 해당
	int icp[6] = { 1, 1, 2, 2, 10, 0 }; //incoming preference	   +, -, *, /, (, ) 에 해당

	scanf("%s", string);
	len = strlen(string);
	for (i = 0; i < len; i++) {
		if (string[i] >= 65 && string[i] <= 90) { //알파벳 대문자이면 --> 피연산자이면
			printf("%c", string[i]);
		}
		else { //연산자이면
			if (string[i] == ')') { //우괄호이면 (괄호의 우선순위가 최상위이므로)
				while (stack[top] != '(') { //좌괄호 나올 때까지 pop and print 
					printf("%c", stack[top--]);
				}
				top--; //좌괄호는 출력 없이 pop
			}
			else { //우괄호 이외의 연산자
				command = convert(string[i]);
				while (icp[command] <= isp[convert(stack[top])]) { //새로 들어오는 연산자의 우선순위(icp)가 스택 안의 연산자의 우선순위(isp)보다 작거나 같으면
					//pop and print								   //작으면 높은 우선순위부터 해야 하니깐 pop, 같아도 먼저 온 거부터 해야 하니깐 pop
					printf("%c", stack[top--]);
				}
				//push
				stack[++top] = string[i];
			}
		}
	}
	//연산자를 담는 stack 안에 남아 있는거는 다 빼내기(마무리 작업)
	while (top != -1) {
		printf("%c", stack[top--]);
	}
}