//
// Created by Vontroy on 2017/10/26.
//

#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
#include "../header/cfg_graph.h"
#include "../header/graph_node.h"
#include "../header/graph_edge.h"
#include "../header/utils.h"

bool cmp_edges(graph_edge a, graph_edge b) {
    if (a.getFrom() == b.getFrom()) {
        return a.getTo() < b.getTo();
    }
    return a.getFrom() < b.getFrom();
}

void unique_edges(std::vector<graph_edge> *edges) {
    std::sort(edges->begin(), edges->end(), cmp_edges);
    std::vector<graph_edge>::iterator it;
    graph_edge tmp(-1, -1);
    for (it = edges->begin(); it != edges->end(); ++it) {
        std::vector<graph_edge>::iterator edge_it;
        if ((it->getFrom() == tmp.getFrom()) && (it->getTo() == tmp.getTo())) {
            edges->erase(it);
            --it;
        } else {
            tmp.setFrom(it->getFrom());
            tmp.setTo(it->getTo());
        }
    }

}

void cfg_graph::dag_operator() {
    std::vector<std::vector<int>>::iterator it;
    auto len = static_cast<unsigned int>(this->graph.size());

    std::vector<int> in_degree_counter(len);  //记录入度
    std::vector<int> out_degree_counter(len); //记录出度
    std::vector<graph_node> cfgNodes(len);    //记录当前DAG图所有结点
    std::vector<graph_node> endNodes;         //所有路径的尾结点(出度为0的结点)

    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            if ((this->graph)[i][j] != 0) {
                cfgNodes[i].addNxt(j);
                cfgNodes[j].addPre(i);
                out_degree_counter[i]++;
                in_degree_counter[j]++;
            }
        }
    }

    for (int i = 0; i < len; ++i) {
        cfgNodes[i].setIdx(i);
        cfgNodes[i].setIn_degree(in_degree_counter[i]);
        cfgNodes[i].setOut_degree(out_degree_counter[i]);
        if (cfgNodes[i].getOut_degree() == 0) {
            endNodes.push_back(cfgNodes[i]);
        }
    }

    //bfs从后向前遍历
    std::vector<graph_node>::iterator node_it;
    std::queue<graph_node> bfs_queue;
    std::vector<graph_edge> res_edges;
    for (node_it = endNodes.begin(); node_it != endNodes.end(); ++node_it) {
        bfs_queue.push(*node_it);
        while (!bfs_queue.empty()) {
            graph_node cur_node = bfs_queue.front();
            bfs_queue.pop();
            const std::vector<int> &tmp = cur_node.getPre();
            auto sz = static_cast<int>(tmp.size());
            for (int i = 0; i < sz; ++i) {
                bfs_queue.push(cfgNodes[tmp[i]]);
            }
            if (sz == 0 || (sz == 1 && cur_node.getOut_degree() != 0)) {
                //sz == 0 --> 初始结点
                //sz == 1 --> 路径唯一, 不需要添加counter
                continue;
            } else {
                for (int i = 0; i < sz; ++i) {
                    graph_edge tmp_edge(cfgNodes[tmp[i]].getIdx(), cur_node.getIdx());
                    res_edges.push_back(tmp_edge);
                }
            }
        }
    }
    unique_edges(&res_edges);
    std::vector<graph_edge>::iterator edge_it;
    for (edge_it = res_edges.begin(); edge_it != res_edges.end(); ++edge_it) {
        std::cout << edge_it->getFrom() << "-->" << edge_it->getTo() << '\n';
    }
}

void cfg_graph::cfg_preprocessing() {
    std::vector<graph_edge> graphEdges;
    std::vector<std::vector<int>>::iterator graph_it;
    std::vector<int>::iterator node_it;
    auto len = static_cast<unsigned int>(this->graph.size());

    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            if ((this->graph)[i][j] != 0) {
                graph_edge tmp_edge;
                tmp_edge.setFrom(i);
                tmp_edge.setTo(j);
                graphEdges.push_back(tmp_edge);
            }
        }
    }

    utils::tarjan(0, reinterpret_cast<graph_edge *>(&graphEdges));
}

cfg_graph::cfg_graph() = default;

/** test data
10 9
 0 1
 1 3
 3 7
 7 8
 0 2
 2 4
 4 6
 6 7
 2 5
 5 6
 */