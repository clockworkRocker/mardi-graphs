#ifndef DIGRAPH
#define DIGRAPH Digraph<NodeType, EdgeType, AdjType>
#endif

namespace mdg {
// * Default constructor
template <typename NodeType, typename EdgeType, typename AdjType>
DIGRAPH::Digraph(int size)
    : m_adjSize(size), m_nodes(size), m_edges(), m_adj(size * size) {
  if (size)
    std::fill(m_adj.begin(), m_adj.end(), static_cast<AdjType>(-1));
}

/* ================================= STATS ================================== */
template <typename NodeType, typename EdgeType, typename AdjType>
int DIGRAPH::size() const {
  return m_nodes.size();
}

template <typename NodeType, typename EdgeType, typename AdjType>
int DIGRAPH::num_edges() const {
  return m_edges.size();
}

/* ============================== SETS ACCESS =============================== */
template <typename NodeType, typename EdgeType, typename AdjType>
typename DIGRAPH::NodeOp DIGRAPH::node(int index) {
  if (index < 0 || index >= static_cast<int>(m_nodes.size()))
    return {*this, -1};

  return {*this, index};
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename DIGRAPH::NodeSet DIGRAPH::nodes() {
  NodeSet nodes(*this);

  for (int i = 0; i < m_nodes.size(); ++i)
    nodes.push_back(i);

  return nodes;
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename DIGRAPH::EdgeOp DIGRAPH::edge(int u, int v) {
  return {*this, u, v};
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename DIGRAPH::EdgeSet DIGRAPH::edges() {
  EdgeSet set(*this);

  for (int u = 0; u < static_cast<int>(m_nodes.size()); ++u)
    for (int v = 0; v < static_cast<int>(m_nodes.size()); ++v)
      if (m_adj[u * m_nodes.size() + v] >= 0) {
        set.push_back(u, v);
      }

  return set;
}

/* ================================ EDITING ================================= */
template <typename NodeType, typename EdgeType, typename AdjType>
int DIGRAPH::add_node(const NodeType& data) {
  m_nodes.emplace_back(data);

  return m_nodes.size() - 1;
}

template <typename NodeType, typename EdgeType, typename AdjType>
template <typename ... Args>
int DIGRAPH::emplace_node(const Args& ... args) {
  m_nodes.emplace_back(args ...);
  
  return m_nodes.size() - 1;
}

template <typename NodeType, typename EdgeType, typename AdjType>
int DIGRAPH::connect(int u, int v, const EdgeType& data) {
  if (m_adjSize < static_cast<int>(m_nodes.size()))
    resize_adj();

  auto edge = this->edge(u, v);
  if (edge) {
    m_edges[edge.index()] = data;
    return edge.index();
  }

  int newIndex = m_edges.size();
  m_adj[u * size() + v] = newIndex;
  m_edges.emplace_back(data);
  return newIndex;
}

template <typename NodeType, typename EdgeType, typename AdjType>
void DIGRAPH::resize_adj() {
  std::vector<AdjType> newAdj(m_nodes.size() * m_nodes.size());
  std::fill(newAdj.begin(), newAdj.end(), static_cast<AdjType>(-1));

  for (int u = 0; u < m_adjSize; ++u)
    for (int v = 0; v < m_adjSize; ++v)
      newAdj[u * m_nodes.size() + v] = m_adj[u * m_adjSize + v];

  m_adjSize = m_nodes.size();
  m_adj = newAdj;
}

/* ================================ SEARCHES ================================ */
template <typename NodeType, typename EdgeType, typename AdjType>
DFS<DIGRAPH> DIGRAPH::dfs(int start) {
  return {*this, start};
}

template <typename NodeType, typename EdgeType, typename AdjType>
EdgeDFS<DIGRAPH> DIGRAPH::edfs(int start) {
  return {*this, start};
}

template <typename NodeType, typename EdgeType, typename AdjType>
BFS<DIGRAPH> DIGRAPH::bfs(int start) {
  return {*this, start};
}


}  // namespace mdg

#ifdef DIGRAPH
#undef DIGRAPH
#endif