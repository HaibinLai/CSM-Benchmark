#ifndef MATCHING_PARRALLEL_SYMBI
#define MATCHING_PARRALLEL_SYMBI

#include <queue>
#include <unordered_map>
#include <vector>

#include "graph/graph.h"
#include "matching/matching.h"

class Parrllel_SymBi : public matching
{
private:
    struct TreeNode {
        std::vector<uint> forwards_;
        std::vector<uint> forward_labels_;
        std::vector<uint> backwards_;
        std::vector<uint> backward_labels_;
        std::vector<uint> neighbors_;
    };
    struct ExtendableVertex {
        uint E;
        uint matched_nbrs;
        uint u_min;

        ExtendableVertex()
        : E(NOT_EXIST), matched_nbrs(0u), u_min(NOT_EXIST) {}
        ExtendableVertex(uint E_arg, uint matched_nbrs_arg, uint u_min_arg)
        : E(E_arg), matched_nbrs(matched_nbrs_arg), u_min(u_min_arg) {}
    };

    std::vector<std::vector<uint>> eidx_;
    std::vector<TreeNode> treeNode_;
    uint q_root_;
    std::vector<uint> serialized_tree_;
    std::vector<std::vector<uint>> pre_defined_order_;
    std::vector<std::vector<uint>> pre_defined_backward_nbr_;

// K-V
// 如果对内存要求比较高的程序，使用vector一定要小心了，当vector空间不足时，会申请一块约是当前占用内存两倍的新空间以存储更多的数据，
// 若可用内存为1G，而当前vector已占用的内存空间0.5G，当再插入一个元素，vector将会申请一块约1G的内存空间，瞬间内存就被用光了，导致程序崩溃。
// 的内存空间中，接着，旧的内存空间将会被回收。这里就可能会出现问题了，当vector指向新的内存空间之后，原来指向旧内存空间的迭代器都会失效了，
// 若再使用这些失效迭代器，将会出现coredump。因为当需要插入数据到vector的时候，就需要注意当前的迭代器还是否有效了。
    std::vector<std::unordered_map<uint, std::vector<uint>>> DCS_;

    std::vector<std::unordered_map<uint, bool>> d1;
    std::vector<std::unordered_map<uint, bool>> d2;

    std::vector<std::unordered_map<uint, uint>> n1;
    std::vector<std::unordered_map<uint, uint>> np1;

    std::vector<std::unordered_map<uint, uint>> n2;
    std::vector<std::unordered_map<uint, uint>> nc2;
    
    // 用于存储需要进行 InsertionTopDown 操作的节点对。
    std::queue<std::pair<uint, uint>> Q1; // queue 是比较难并行的东西.  only TopDown Method
    // 用于存储需要进行 InsertionBottomUp 操作的节点对。当某个节点对 (u, v) 满足一定条件时，会将其加入 Q2。
    // 在 Q2 非空时，会从队列中取出节点对 (u_queue, v_queue)，并对其进行 InsertionBottomUp 操作。
    std::queue<std::pair<uint, uint>> Q2;

    // 并行idea：把 Q1 做成std::vector<std::queue<std::pair<uint, uint>>>，每个线程处理一个队列。

public:

    Parrllel_SymBi(Graph& query_graph, Graph& data_graph, uint max_num_results,
            bool print_prep, bool print_enum, bool homo, 
            std::vector<std::vector<uint>> orders);
    ~Parrllel_SymBi() override {};

    void Preprocessing() override;
    void InitialMatching() override;
    
    void AddEdge(uint v1, uint v2, uint label) override;
    void RemoveEdge(uint v1, uint v2) override;
    void AddVertex(uint id, uint label) override;
    void RemoveVertex(uint id) override;
    
    void GetMemoryCost(size_t &num_edges, size_t &num_vertices) override;

private:
    void BuildDAG();
    void BuildDCS();
    
    void InsertionTopDown(uint u, uint u_c, uint v, uint v_c);
    void InsertionBottomUp(uint u, uint u_p, uint v, uint v_p);
    void DeletionTopDown(uint u, uint u_c, uint v, uint v_c);
    void DeletionBottomUp(uint u, uint u_p, uint v, uint v_p);

    void FindMatches(uint depth, std::vector<uint>& m, 
            std::vector<ExtendableVertex>& extendable, size_t &num_results);
    void FindMatches(uint order_index, uint depth, std::vector<uint>& m, size_t &num_results);
};
#endif //MATCHING_PARRALLEL_SYMBI
