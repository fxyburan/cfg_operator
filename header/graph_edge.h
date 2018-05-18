//
// Created by vontroy on 10/27/17.
//

#ifndef CFG_GRAPH_EDGE_H
#define CFG_GRAPH_EDGE_H


class graph_edge {
public:
    graph_edge();

    graph_edge(int from, int to);

    int getFrom() const;

    void setFrom(int from);

    int getTo() const;

    void setTo(int to);

private:
    int from;
    int to;
};


#endif //CFG_GRAPH_EDGE_H
