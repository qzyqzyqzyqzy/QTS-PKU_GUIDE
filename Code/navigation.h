#ifndef NAVIGATION_H
#define NAVIGATION_H
#include"location_direction.h"
#endif // NAVIGATION_H
#include <limits.h>
#include<QVector>
#include <QMap>
#define V 18
int parent[V];
int graph1[V][V] = { { 0,270,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
                        {270,0,0,0,0,0,0,0,0,0,0,0,0,0,230,0,0,330},
                        { 0	,0,0,	160,0,0,0,0,0,0,0,0,0,0,0,0,0,70 },
                        { 0	,0,	160,	0,	150,	0,	0	,0,	0,	0,	0	,0,	0,	0,	0,	0,90,0},
                        {0	,0	,0,	150,	0,	170,	0,	0,	0,	0	,0,	0,	0,	0,	0,	0,0,0 },
                        { 0	,0,	0,	0,	170,	0	,70,	0,	0	,0,	0	,0,	0,	0,	0	,0,0,0 },
                        { 0	,0,	0,	0,	0,	70,	0,	170	,0,	0,	0,	0,	0,	0,	0,	150,0,0 },
                        { 0	,0,	0,	0,	0,	0,	170,	0,	170,	0,	0,	0,	0,	0,	0,	0,0,0},
                        { 0	,0	,0,	0,	0,	0,	0,	170	,0,	0,	70,	0,	0,	0,	0,	0,0,0},
                        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0	,250	,170	,0,	0,	0,	0,0,0},
                        {0,	0,	0,	0,	0,	0,	0,	0,	70,	250,	0,	0,	0,	0,	0,	0,0,0},
                        {0,	0,	0,	0,	0,	0,	0,	0,	0,	170,	0,	0,	140	,0,	0,	0,0,0},
                        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	140,	0,	140,	0,	0,0,0},
                        {0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	140,	0,	0,	230,0,0},
                        {0,	230,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,240,0},
                        {0,	0,	0,	0,	0,	0,	150,	0,	0,	0,	0,	0,	0,	230,	0,	0,0,0}
                            ,{0,	0,	0,	90,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	240,	0,0,0},
                             {0,	330,	70,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,0,0} };
QMap<int,location_direction> num_to_lo;
QMap<location_direction,int> lo_to_num;

QVector<location_direction> dest;
//找那些没进SPT点的最小距离
int minDistance(int dist[], bool sptSet[])
{

    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

QVector<location_direction> printpath(int src, int tar)
{
    int f = src;
    dest.clear();
    dest.push_back(num_to_lo[src]);//src
    //qDebug()<<"TTTTTTTTT";
    while (f != tar)//tar
    {
        f = parent[f-1]+1;//flag-1]+1

        dest.push_back(num_to_lo[f]);
    }
    return dest;
}

//dijkstra算法主体
void dijkstra(int src,int tar)
{
    int dist[V]; // 最终输出矩阵
    // 很重要
   memset(parent,0,sizeof(parent));
    bool sptSet[V]; // 某个点是否进到SPT中

//初始化
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    parent[tar-1] = -1;//tar-1
    // 自己离自己当然是0
    dist[tar-1] = 0;//tar-1

    // 找路了
    for (int count = 0; count < V - 1; count++) {
    //最小节点
        int u = minDistance(dist, sptSet);

        // 处理过的节点为真
        sptSet[u] = true;

        // 更新距离
        for (int v = 0; v < V; v++)

            // 更新条件：不在SPT中，有通路，有一条路的距离小于上一个距离
            if (!sptSet[v] && graph1[u][v]
                && dist[u] != INT_MAX
                && dist[u] + graph1[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph1[u][v];
                parent[v] = u;
            }
    }
}



