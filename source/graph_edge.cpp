//
// Created by vontroy on 10/27/17.
//

#include "../header/graph_edge.h"

graph_edge::graph_edge(int from, int to) : from(from), to(to) {}

graph_edge::graph_edge() = default;

int graph_edge::getFrom() const {
    return from;
}

void graph_edge::setFrom(int from) {
    graph_edge::from = from;
}

int graph_edge::getTo() const {
    return to;
}

void graph_edge::setTo(int to) {
    graph_edge::to = to;
}
