//문자열 폭발(스택 2)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	int i, j;
	char string[1000001];
	char target[37];
	scanf("%s", string);
	scanf("%s", target);
	int str_len = strlen(string);
	int tar_len = strlen(target);
	char* str_stack;
	char* prt_stack;
	str_stack = (char*)malloc(sizeof(char) * str_len);
	prt_stack = (char*)malloc(sizeof(char) * str_len);
	int str_top = -1;
	int prt_top = -1;
	
	//str_stack 설정(먼저 나와야 하는 string의 처음이 맨 위로 오도록 스택에 반대로 쌓아넣음)
	for (i = str_len - 1; i >= 0; i--) {
		str_stack[++str_top] = string[i];
	}

	while (str_top != -1) {
		if (str_stack[str_top] == target[0]) { //폭발 문자열의 시작과 같으면
			for (i = 0; i < tar_len; i++) {
				if (str_stack[str_top - i] != target[i]) break;
			}
			if (i == tar_len) { //폭발 문자열과 일치하면
				str_top -= tar_len; //해당 길이만큼 폭발 문자열을 pop
			}
			else prt_stack[++prt_top] = str_stack[str_top--]; //폭박 문자열과 일치하지 않으면 그냥 push

		}
		else prt_stack[++prt_top] = str_stack[str_top--]; //str_stack에서 pop해서 prt_stack에 push

		//prt_stack에 쌓인 문자열에 폭발 문자열이 되었는지 확인(끝부터 확인)
		if (prt_stack[prt_top] == target[tar_len - 1]) { 
			for (j = 0; j < tar_len; j++) {
				if (prt_stack[prt_top - j] != target[tar_len - j - 1]) break;
			}

			if (j == tar_len) { //prt_stack에서 폭발 문자열이 완성되면
				prt_top -= tar_len; //폭발 문자열 길이만큼 prt_stack에서 pop
			}
		}
	}

	if (prt_top == -1) printf("FRULA");
	else {
		for (i = 0; i <= prt_top; i++) {
			printf("%c", prt_stack[i]);
		}
	}
	return 0;
}

//처음에는 아래와 같이 스택을 안쓰고 구현했는데, 이렇게 구현하는 경우 target(폭발 문자열)이 길어짐에 따라 string을 앞으로 가야 하는게 많아져서
//시간 복잡도가 높아진다. 따라서 2초라는 시간 제한을 지키지 못해 시간 초과 오류가 발생한다.
/*
for (i = 0; i < str_len; i++) {
	if (string[i] == target[0]) {
		for (j = 0; j < tar_len; j++) {
			if (string[i + j] != target[j]) break;
		}
	}
	if (j == tar_len) { //폭발 문자열이 발견 되었다는 것
		for (k = i; k < str_len - 2; k++) {
			string[k] = string[k + tar_len];
		}
		str_len -= tar_len; //새로 생긴 문자열은 길이가 줄어들었다
		i -= tar_len; //뒷부분이 새로 붙어서 폭발 문자열이 될 수도 있으니
		j = 0;
	}
}
*/