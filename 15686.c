//치킨 배달(골드 5, 브루트포스, 백트래킹)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row;
	int col;
	int d; //distance
}home;

typedef struct {
	int use; //0이면 폐업, 1이면 영업
	int row;
	int col;
}shop;

int N, M; int MIN = 250000; //도시 치킨거리의 최솟값
home* house; int h_num = 0;
shop* chicken; int c_num = 0;
int** map;

void calculate() { //선정된 치킨집들의 위치를 기반으로 도시의 치킨 거리를 계산하는 함수
	int total = 0; //도시의 치킨 거리를 저장하는 변수
	int min = 0; int distance;

	for (int i = 0; i < h_num; i++) { //각각의 집마다
		min = 250000;
		for (int j = 0; j < c_num; j++) { //각각의 치킨집까지의 거리를 구해서 저장
			if (chicken[j].use == 0) continue; //폐업된 치킨집은 건너뜀
			distance = abs(house[i].row - chicken[j].row) + abs(house[i].col - chicken[j].col);
			if (distance < min) min = distance;
		}
		house[i].d = min; //해당 집의 최소 치킨 거리
	}

	for (int i = 0; i < h_num; i++) {
		total += house[i].d;
	}

	if (total < MIN) MIN = total; //현재 최솟값보다 해당 map 기반 도시의 치킨 거리가 작으면 최솟값을 갱신
}

void choose(int count, int recent) { //count: 없애야 하는 치킨집 개수
	if (count == 0) {
		calculate();
	}

	for (int i = recent; i < c_num; i++) {
		if (count > 0 && chicken[i].use != 0) {
			chicken[i].use = 0; //폐업된 것으로 간주
			choose(count - 1, i); //재귀가 끝나고 count - 1 시행 안하고 다음 칸으로 넘어갔을 때
			chicken[i].use = 1; //해당 시행에서 폐업으로 간주했던 가게를 원상복구하기 = 재귀 함수를 기준으로 이전에 했던 변화(52번라인)를 상쇄
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);
	map = (int**)malloc(sizeof(int*) * N);
	for (int i = 0; i < N; i++) map[i] = (int*)malloc(sizeof(int) * N);
	house = (home*)malloc(sizeof(home) * N * 2); //집은 2N을 넘지 않는다
	chicken = (shop*)malloc(sizeof(shop) * 13); //치킨집은 M이상 13이하이다
	
	//도시의 정보를 받아와서 저장
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1) { //집의 정보를 저장
				house[h_num].row = i;
				house[h_num++].col = j;
			}
			if (map[i][j] == 2) { //치킨집의 정보를 저장
				chicken[c_num].row = i;
				chicken[c_num].col = j;
				chicken[c_num++].use = 1; //사용되는 것으로 초기화
			}
		}
	}

	choose(c_num - M, 0); //치킨집을 고르는 함수
	printf("%d", MIN);
}