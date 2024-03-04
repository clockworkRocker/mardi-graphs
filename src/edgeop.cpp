#ifndef DIGRAPH
#define DIGRAPH Digraph<NodeType, EdgeType, AdjType>
#endif

/* ====================== CONSTRUCTION AND ASSIGNMENT ======================= */
namespace mdg {
template <typename NodeType, typename EdgeType, typename AdjType>
DIGRAPH::EdgeOp::EdgeOp(DIGRAPH& graph, int u, int v)
    : m_graph(graph),
      m_start(u),
      m_end(v),
      m_index(graph.m_adj[u * graph.size() + v] >= 0
                  ? graph.m_adj[u * graph.size() + v]
                  : -1) {}

template <typename NodeType, typename EdgeType, typename AdjType>
DIGRAPH::EdgeOp::EdgeOp(DIGRAPH& graph, int index)
    : m_graph(graph),
      m_index(index > 0 && index < graph.m_edges.size() ? index : -1) {
        for (int u = 0; u < graph().size(); ++u)
          for (int v = 0; v < graph.size(); ++v)
            if (graph.m_adj[u * graph.size() + v] == index) {
              m_start = u;
              m_end = v;
            }
      }

/* =============================== COMPARISON =============================== */
template <typename NodeType, typename EdgeType, typename AdjType>
bool DIGRAPH::EdgeOp::operator==(const EdgeOp& other) {
  return m_index == other.m_index;
}

template <typename NodeType, typename EdgeType, typename AdjType>
bool DIGRAPH::EdgeOp::operator!=(const EdgeOp& other) {
  return m_index != other.m_index;
}

/* =========================== POINTER SEMANTICS ============================ */
template <typename NodeType, typename EdgeType, typename AdjType>
EdgeType& DIGRAPH::EdgeOp::operator*() {
  return m_graph.m_edges[m_index];
}

template <typename NodeType, typename EdgeType, typename AdjType>
const EdgeType& DIGRAPH::EdgeOp::operator*() const {
  return m_graph.m_edges[m_index];
}

template <typename NodeType, typename EdgeType, typename AdjType>
EdgeType* DIGRAPH::EdgeOp::operator->() {
  return &(m_graph.m_edges[m_index]);
}

template <typename NodeType, typename EdgeType, typename AdjType>
const EdgeType* DIGRAPH::EdgeOp::operator->() const {
  return &(m_graph.m_edges[m_index]);
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename DIGRAPH::NodeOp DIGRAPH::EdgeOp::start() const {
  return {m_graph, m_start};
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename DIGRAPH::NodeOp DIGRAPH::EdgeOp::end() const {
  return {m_graph, m_end};
}

template <typename NodeType, typename EdgeType, typename AdjType>
int DIGRAPH::EdgeOp::index() const {
  return m_index;
}

template <typename NodeType, typename EdgeType, typename AdjType>
DIGRAPH::EdgeOp::operator bool() const {
  return m_index >= 0;
}

}  // namespace mdg

#ifdef DIGRAPH
#undef DIGRAPH
#endif