//
// Created by vontroy on 18-1-07.
//

#include "../header/utils.h"
#include "../header/graph_edge.h"

#include <iostream>

const int maxn = 10010;

int dfn[maxn], low[maxn];
int stack[maxn], heads[maxn], vis[maxn];
int cnt, tot, index;

void utils::tarjan(int x, graph_edge *graphEdge) {
    dfn[x] = low[x] = ++tot;
    stack[++index] = x;
    vis[x] = 1;
    for (int i = heads[x]; i != -1; i = graphEdge[i].getTo()) {
        if (!dfn[graphEdge[i].getFrom()]) {
            tarjan(graphEdge[i].getFrom(), graphEdge);
            low[x] = std::min(low[x], low[graphEdge[i].getFrom()]);
        } else if (vis[graphEdge[i].getFrom()]) {
            low[x] = std::min(low[x], dfn[graphEdge[i].getFrom()]);
        }
    }
    if (low[x] == dfn[x]) {
        do {
            printf("%d ", stack[index]);
            vis[stack[index]] = 0;
            index--;
        } while (x != stack[index + 1]);
        puts("");
    }
}
