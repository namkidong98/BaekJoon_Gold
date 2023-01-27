//암호 만들기(골드5, 브루트 포스)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct {
	char character; //고정 값
	int vowel; //0이면 자음, 1이면 모음 --> 고정 값
	int use; //1이면 사용된 것, 0이면 안 된것 --> 변화하는 값
}alphabet;

int L, C;
alphabet string[16];

void choose(int left, int vowel, int cons, int current) { //L까지 남은 문자개수, 현재 포함된 모음개수, 현재 포함된 자음개수, 현재 위치
	if (left == 0 && vowel >= 1 && cons >= 2) { //L개만큼 골랐고 모음이 1개 이상, 자음이 2개 이상 포함된 경우 --> 출력
		for (int i = 0; i < C; i++) {
			if (string[i].use == 1) printf("%c", string[i].character);
		}
		printf("\n");
	}

	if (left > 0) {
		for (int i = current; i < C; i++) {
			if (string[i].use == 0) {
				string[i].use = 1;
				if (string[i].vowel == 1) choose(left - 1, vowel + 1, cons, i + 1);
				else choose(left - 1, vowel, cons + 1, i + 1);
				string[i].use = 0;
			}
		}
	}
}

int main() {
	char temp;
	scanf("%d %d", &L, &C);
	for (int i = 0; i < C; i++) {
		scanf(" %c", &string[i].character);
	}

	//사전 순서에 맞게 정렬 및 초기화
	for (int i = 0; i < C - 1; i++) {
		for (int j = i + 1; j < C; j++) {
			if (string[i].character > string[j].character) { //사전 순서에서 j번째가 앞서면 SWAP
				temp = string[i].character;
				string[i].character = string[j].character;
				string[j].character = temp;
			}
		}
	}
	for (int i = 0; i < C; i++) {
		if (string[i].character == 'a' || string[i].character == 'e' || string[i].character == 'i' || string[i].character == 'o' || string[i].character == 'u') string[i].vowel = 1;
		else string[i].vowel = 0;
		string[i].use = 0; //사용 안됨으로 초기화
	}

	choose(L, 0, 0, 0); //L개 문자를 골라야하고, 포함된 모음 글자 0개, 포함된 자음 글자 0개, 0번째부터 시작
}