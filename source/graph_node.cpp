//
// Created by Vontroy on 2017/10/26.
//

#include "../header/graph_node.h"

int graph_node::getIdx() const {
    return idx;
}

void graph_node::setIdx(int idx) {
    graph_node::idx = idx;
}

int graph_node::getIn_degree() const {
    return in_degree;
}

void graph_node::setIn_degree(int in_degree) {
    graph_node::in_degree = in_degree;
}

int graph_node::getOut_degree() const {
    return out_degree;
}

void graph_node::setOut_degree(int out_degree) {
    graph_node::out_degree = out_degree;
}

const std::vector<int> &graph_node::getNxt() const {
    return nxt;
}

void graph_node::addNxt(int next) {
    this->nxt.push_back(next);
}

const std::vector<int> &graph_node::getPre() const {
    return pre;
}

void graph_node::addPre(int pre) {
    this->pre.push_back(pre);
}
