//
// Created by Vontroy on 2017/10/26.
//

#ifndef CFG_GRAPH_OPERATOR_H
#define CFG_GRAPH_OPERATOR_H

#include <utility>
#include <vector>

class cfg_graph {
public:
    cfg_graph();
    explicit cfg_graph(std::vector<std::vector<int>> _graph):graph(std::move(_graph)){};

    void cfg_preprocessing();

    /**
     * 处理DAG图
     */
    void dag_operator();

private:
    std::vector<std::vector<int>> graph;
};


#endif //CFG_GRAPH_OPERATOR_H
