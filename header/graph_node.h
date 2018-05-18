//
// Created by Vontroy on 2017/10/26.
//

#ifndef CFG_GRAPH_NODE_H
#define CFG_GRAPH_NODE_H


#include <vector>

class graph_node {
public:
    int getIdx() const;

    void setIdx(int idx);

    int getIn_degree() const;

    void setIn_degree(int in_degree);

    int getOut_degree() const;

    void setOut_degree(int out_degree);

    const std::vector<int> &getNxt() const;

    /**
     * 添加后继结点
     * @param next
     */
    void addNxt(int next);

    const std::vector<int> &getPre() const;

    /**
     * 添加前驱结点
     * @param pre
     */
    void addPre(int pre);

private:
    int idx;                 //结点编号
    int in_degree;           //入度
    int out_degree;          //出度
    std::vector<int> nxt;    //后继结点
    std::vector<int> pre;    //前驱结点
};


#endif //CFG_GRAPH_NODE_H
