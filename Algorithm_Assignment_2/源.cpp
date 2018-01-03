#include <bits/stdc++.h>

using namespace std;

struct Edge
{
	int u, v, len, val, next;
}e[3000];

queue<int> q;
struct Node
{
	int cost[1501];
	int pre[1501];
}dis[50];
int head[50], vis[50], path[50];
int cnt;

void addedge(int u, int v, int len, int val)
{
	e[cnt].u = u;
	e[cnt].v = v;
	e[cnt].len = len;
	e[cnt].val = val;
	e[cnt].next = head[u];
	head[u] = cnt++;
}

int main1()
{
	FILE* m1 = fopen("D:\\m1.txt", "r");
	FILE* m2 = fopen("D:\\m2.txt", "r");
	if (m1 == NULL)
	{
		printf("m1 is not found.");
	}
	else if (m2 == NULL)
	{
		printf("m2 is not found.");
	}
	else
	{
		cnt = 0;
		for (int i = 0; i<50; i++) head[i] = -1;

		for (int i = 0; i<50; i++)
		{
			for (int j = 0; j<50; j++)
			{
				int len, val;
				fscanf(m1, "%d", &len);
				fscanf(m2, "%d", &val);
				if (len < 9999) addedge(i, j, len, val);
			}
		}

		for (int i = 0; i<50; i++)
		{
			for (int j = 0; j <= 1500; j++)
			{
				dis[i].cost[j] = 500000;
				dis[i].pre[j] = -1;
			}
			vis[i] = 0;
		}
		dis[0].cost[0] = 0;
		dis[0].pre[0] = -1;

		q.push(0);
		vis[0] = 1;
		while (!q.empty())
		{
			int u = q.front();
			q.pop();
			vis[u] = 0;
			for (int i = head[u]; i != -1; i = e[i].next)
			{
				int v = e[i].v;
				for (int j = 0; j <= 1500; j++)
				{
					int tmp_len = dis[u].cost[j] + e[i].len;
					int tmp_val = j + e[i].val;
					if (tmp_val > 1500) continue;
					if (tmp_len < dis[v].cost[tmp_val])
					{
						dis[v].cost[tmp_val] = tmp_len;
						dis[v].pre[tmp_val] = i;
						if (!vis[v])
						{
							q.push(v);
							vis[v] = 1;
						}
					}
				}
			}
		}

		int min_len = 500000;
		int cost;
		for (int i = 0; i <= 1500; i++)
			if (min_len > dis[49].cost[i])
			{
				min_len = dis[49].cost[i];
				cost = i;
			}

		int cur_node = 49;
		int cur_cost = cost;
		int num = 0;
		while (dis[cur_node].pre[cur_cost] != -1)
		{
			path[num++] = cur_node;
			int pre_edge = dis[cur_node].pre[cur_cost];
			cur_cost = cur_cost - e[pre_edge].val;
			cur_node = e[pre_edge].u;
		}

		printf("路径: 1 ");
		for (int i = num - 1; i >= 0; i--) printf("%d ", path[i] + 1);
		puts("");
		printf("最短路:%d 花费:%d\n", min_len, cost);
	}
	system("pause");
	return 0;
}
