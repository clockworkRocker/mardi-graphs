#ifndef EDGESET
#define EDGESET Digraph<NodeType, EdgeType, AdjType>::EdgeSet
#endif

namespace mdg {
/* ====================== CONSTRUCTION AND ASSIGNMENT ======================= */
template <typename NodeType, typename EdgeType, typename AdjType>
EDGESET::EdgeSet(EDGESET::Graph& graph)
    : m_graph(graph), m_starts(), m_ends() {}

/* =============================== COMPARISON =============================== */
template <typename NodeType, typename EdgeType, typename AdjType>
int EDGESET::size() const {
  return static_cast<int>(m_starts.size());
}

/* ================================ EDITING ================================= */
template <typename NodeType, typename EdgeType, typename AdjType>
void EDGESET::push_back(int u, int v) {
  int index = m_graph.m_adj[u * m_graph.size() + v];

  if (index >= 0 && index < static_cast<int>(m_graph.m_edges.size())) {
    m_starts.push_back(u);
    m_ends.push_back(v);
  }
}

template <typename NodeType, typename EdgeType, typename AdjType>
void EDGESET::push_back(int index) {
  if (index < 0 && index >= static_cast<int>(m_graph.m_edges.size()))
    return;

  int start = -1, end = -1;
  int size = static_cast<int>(m_graph.size());

  for (int u = 0; u < size; ++u)
    for (int v = 0; v < size; ++v)
      if (m_graph.m_adj[u * size + v] == index) {
        start = u;
        end = v;
      }

  if (start < 0 || end < 0)
    return;

  m_starts.push_back(start);
  m_ends.push_back(end);
}

template <typename NodeType, typename EdgeType, typename AdjType>
void EDGESET::push_back(const EDGESET::EdgeOp& edge) {
  if (&(edge.m_graph) != &m_graph)
    return;

  if (edge.index() >= 0 &&
      edge.index() < static_cast<int>(m_graph.m_edges.size())) {
    m_starts.push_back(edge.start());
    m_ends.push_back(edge.end());
  }
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename EDGESET::EdgeOp EDGESET::front() const {
  return {m_graph, m_starts.front(), m_ends.front()};
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename EDGESET::EdgeOp EDGESET::back() const {
  return {m_graph, m_starts.back(), m_ends.back()};
}

/* =============================== ITERATION ================================ */
template <typename NodeType, typename EdgeType, typename AdjType>
typename EDGESET::Iterator EDGESET::begin() {
  return {*this, 0};
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename EDGESET::Iterator EDGESET::end() {
  return {*this, static_cast<int>(m_starts.size())};
}

/* ======================== ITERATOR IMPLEMENTATIONS ======================== */
template <typename NodeType, typename EdgeType, typename AdjType>
EDGESET::Iterator::Iterator(EDGESET& set, int pos) : m_set(set), m_pos(pos) {}

template <typename NodeType, typename EdgeType, typename AdjType>
bool EDGESET::Iterator::operator==(const EDGESET::Iterator& other) const {
  return m_set == other.m_set && m_pos == other.m_pos;
}

template <typename NodeType, typename EdgeType, typename AdjType>
bool EDGESET::Iterator::operator!=(const EDGESET::Iterator& other) const {
  return m_pos != other.m_pos;
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename EDGESET::Iterator& EDGESET::Iterator::operator++() {
  ++m_pos;
  return *this;
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename EDGESET::EdgeOp EDGESET::Iterator::operator*() const {
  return {m_set.m_graph, m_set.m_starts[m_pos], m_set.m_ends[m_pos]};
}
}  // namespace mdg

#ifdef EDGESET
#undef EDGESET
#endif