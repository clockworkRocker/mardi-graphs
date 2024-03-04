#ifndef DIGRAPH
#define DIGRAPH Digraph<NodeType, EdgeType, AdjType>
#endif

namespace mdg {
/* ====================== CONSTRUCTION AND ASSIGNMENT ======================= */
template <typename NodeType, typename EdgeType, typename AdjType>
DIGRAPH::NodeOp::NodeOp(DIGRAPH& graph, int index)
    : m_graph(graph), m_index(index) {}

template <typename NodeType, typename EdgeType, typename AdjType>
template <typename OtherNodeOp>
bool DIGRAPH::NodeOp::operator==(const OtherNodeOp& other) const {
  return m_graph == other.m_graph && m_index == other.m_index;
}

template <typename NodeType, typename EdgeType, typename AdjType>
template <typename OtherNodeOp>
bool DIGRAPH::NodeOp::operator!=(const OtherNodeOp& other) const {
  return m_graph != other.m_graph || m_index != other.m_index;
}

/* ================================= STATS ================================== */
template <typename NodeType, typename EdgeType, typename AdjType>
int DIGRAPH::NodeOp::degree() const {
  int degree = 0;
  for (int pos = 0; pos < m_graph.size(); ++pos)
    degree += (int)(m_graph.m_adj[pos * m_graph.size() + m_index] >= 0) |
              (int)(m_graph.m_adj[m_index * m_graph.size() + pos] >= 0);

  return degree;
}

template <typename NodeType, typename EdgeType, typename AdjType>
int DIGRAPH::NodeOp::index() const {
  return m_index;
}

/* =========================== POINTER SEMANTICS ============================ */
template <typename NodeType, typename EdgeType, typename AdjType>
typename DIGRAPH::Node& DIGRAPH::NodeOp::operator*() {
  return m_graph.m_nodes[m_index];
}

template <typename NodeType, typename EdgeType, typename AdjType>
const typename DIGRAPH::Node& DIGRAPH::NodeOp::operator*() const {
  return m_graph.m_nodes[m_index];
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename DIGRAPH::Node* DIGRAPH::NodeOp::operator->() {
  return &(m_graph.m_nodes[m_index]);
}

template <typename NodeType, typename EdgeType, typename AdjType>
const typename DIGRAPH::Node* DIGRAPH::NodeOp::operator->() const {
  return &(m_graph.m_nodes[m_index]);
}

template <typename NodeType, typename EdgeType, typename AdjType>
DIGRAPH::NodeOp::operator bool() const {
  return m_index > 0;
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename DIGRAPH::NodeSet DIGRAPH::NodeOp::parents() const {
  NodeSet parents(m_graph);

  for (int v = 0; v < m_graph.size(); ++v)
    if (m_graph.m_adj[v * m_graph.size() + m_index] >= 0)
      parents.push_back(v);

  return parents;
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename DIGRAPH::NodeSet DIGRAPH::NodeOp::children() const {
  NodeSet children(m_graph);

  for (int v = 0; v < m_graph.size(); ++v)
    if (m_graph.m_adj[m_index * m_graph.size() + v] >= 0)
      children.push_back(v);

  return children;
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename DIGRAPH::EdgeSet DIGRAPH::NodeOp::incoming() const {
  EdgeSet incoming(m_graph);
  
  if (m_index < 0 || m_index >= m_graph.size())
    return incoming;
  
  for (int v = 0; v < m_graph.size(); ++v)
    if (m_graph.m_adj[v * m_graph.size() + m_index] >= 0)
      incoming.push_back(v, m_index);
  
  return incoming;
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename DIGRAPH::EdgeSet DIGRAPH::NodeOp::outgoing() const {
  EdgeSet outgoing(m_graph);
  
  if (m_index < 0 || m_index >= m_graph.size())
    return outgoing;

  for (int v = 0; v < m_graph.size(); ++v)
    if (m_graph.m_adj[m_index * m_graph.size() + v] >= 0)
      outgoing.push_back(m_index, v);

  return outgoing;
}
}  // namespace mdg

#ifdef DIGRAPH
#undef DIGRAPH
#endif