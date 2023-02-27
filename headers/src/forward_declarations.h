namespace mdg {
/* ============================ INTERNAL TYPES ============================ */
namespace internal {
template <typename GraphType>
struct traits;

template <typename NodeOpType>
struct nodeop_traits;
}  // namespace internal

/* ============================== GRAPH TYPES ============================= */
template <typename Derived>
class MDGBase;

template <typename Derived>
class UndirectedBase;

class Graph;

template <typename NodeType, typename EdgeType>
class ObjectGraph;

template <typename Derived>
class DirectedBased;

class Digraph;

template <typename NodeType, typename EdgeType>
class ObjectDigraph;

/* ============================ OPERATION TYPES ============================ */
template <typename Derived>
class NodeOpBase;

template <typename GraphType>
class UndirectedNodeOp;

template <typename GraphType>
class DirectedNodeOp;

template <typename GraphType>
class EdgeOp;

namespace details {
template <typename OpType>
struct NodeOpImpl;
}

}  // namespace mdg