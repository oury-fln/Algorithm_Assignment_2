#include <iostream>
#include <fstream>

/*
 * name: aimi
 * id: zy1706112
 * This program find the shortest distance where cost is no more than 1500
 */

using namespace std;

//some like a tree but dont save the information of other brothers
struct Node
{
	int city;
	int father;
	int index = 0;
	int currentDist = 0, currentCost = 0;
}node[50];

//main body, do a lot
void main() {
	int cost[50][50];
	int vaildDist[50][50];
	int dist[50][50];
	memset(vaildDist, -1, sizeof(int) * 50 * 50);
	ifstream in1, in2;
	in1.open("D:\\m1.txt", ios::in);
	in2.open("D:\\m2.txt", ios::in);
	int i, j, t, h, t2;
	for (i = 0; i < 50; i++) {
		for (j = 0, h = 0; j < 50; j++) {
			in1 >> t;
			in2 >> t2;
			if (t != 9999) {
				//*/
				//22 times faster if no note it, but less precise
				if (j > i)
				//*/
				vaildDist[i][h++] = j;
				dist[i][j] = t;
				cost[i][j] = t2;
			}
		}
	}
	int maxCost = 1500, minDist = 999999;
	int nodeHead = 0;
	int flag = 0;
	node[(i = nodeHead++)].city = 0;
	node[i].father = -1;
	int trace[50] = { 0 };
	int bestTrace[50];
	int traceHead = 0, bestTraceHead = 0;
	traceHead++;
	i = 0;
	while (i >= 0) {
		flag = 0;
		for (h = node[i].index, j = vaildDist[node[i].city][h]; j > 0; h++, j = vaildDist[node[i].city][h]) {
			for (t = 0; t < traceHead && trace[t] != j; t++);
			if (t < traceHead) {//in trace
				continue;
			}
			//i == current node index, j == city of the next node, t == next node index
			if (node[i].currentCost + cost[node[i].city][j] <= 1500 && node[i].currentDist + dist[node[i].city][j] < minDist) {
				node[(t = nodeHead++)].index = 0;
				node[t].father = i;  //new the node
				node[t].city = j;
				node[t].currentCost = node[i].currentCost + cost[node[i].city][j];
				node[t].currentDist = node[i].currentDist + dist[node[i].city][j];
				trace[traceHead++] = j;
				flag = 1;
				node[i].index = h + 1;
				if (j == 49) {
					//found one acceptable path, record it and go back
					minDist = node[t].currentDist;
					maxCost = node[t].currentCost;
					memcpy(bestTrace, trace, sizeof(int) * traceHead);
					bestTraceHead = traceHead;
					i = node[i].father;
				}
				else {
					i = t;
				}
				nodeHead = i + 1;
				traceHead = i + 1;
				break;
			}
		}
		if (j < 0) {
			//no more edge last for this vertex, go back
			node[i].index = 49;
			i = node[i].father;
			nodeHead = i + 1;
			traceHead = i + 1;
		}
	}
	cout << "cost: " << maxCost << " dist: " << minDist << endl << "trace: ";
	for (i = 0; i < bestTraceHead; i++) {
		cout << bestTrace[i] + 1 << " ";
	}
	cout << endl;
	getchar();
}