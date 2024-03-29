namespace mdg {
/* ============================ INTERNAL TYPES ============================ */
namespace internal {
template <typename GraphType>
struct traits;

template <typename NodeOpType>
struct nodeop_traits;

template <typename GraphType, int StorageType>
class AdjacencyStorage;
}  // namespace internal

/* ============================== GRAPH TYPES ============================= */
template <typename Derived>
class MDGBase;

template <typename Derived>
class UndirectedBase;

template <int StorageType>
class Graph;

template <typename NodeType, typename EdgeType, int StorageType>
class ObjectGraph;

template <typename Derived>
class DirectedBase;

template <int StorageType>
class Digraph;

template <typename NodeType, typename EdgeType, int StorageType>
class ObjectDigraph;

/* ============================== SETS TYPES =============================== */
template <typename GraphType>
class NodeSetOp;

template <typename GraphType>
class EdgeSetOp;

/* ============================ OPERATION TYPES ============================ */
template <typename Derived>
class NodeOpBase;

template <typename GraphType>
class UndirectedNodeOp;

template <typename GraphType>
class DirectedNodeOp;

template <typename GraphType>
class EdgeOp;

/* ============================= SEARCH TYPES ============================== */

template <typename Derived>
class GraphSearch;

template <typename GraphType>
class BFS;

template <typename GraphType>
class DFS;

/* ============================= DETAIL TYPES ============================== */

}  // namespace mdg