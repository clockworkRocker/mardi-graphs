#ifndef NODESET
#define NODESET Digraph<NodeType, EdgeType, AdjType>::NodeSet
#endif

namespace mdg {
/* ====================== CONSTRUCTION AND ASSIGNMENT ======================= */
template <typename NodeType, typename EdgeType, typename AdjType>
NODESET::NodeSet(NODESET::Graph& graph, int size)
    : m_graph(graph), m_indices(size) {}

/* =============================== COMPARISON =============================== */

/* ================================== STATS ================================= */
template <typename NodeType, typename EdgeType, typename AdjType>
bool NODESET::empty() const {
  return m_indices.empty();
}

template <typename NodeType, typename EdgeType, typename AdjType>
int NODESET::size() const {
  return static_cast<int>(m_indices.size());
}

/* ============================== MANIPULATION ============================== */
template <typename NodeType, typename EdgeType, typename AdjType>
void NODESET::push_back(int index) {
  m_indices.push_back(index);
}

template <typename NodeType, typename EdgeType, typename AdjType>
void NODESET::push_back(const NODESET::NodeOp& node) {
  m_indices.push_back(node.index());
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename NODESET::NodeOp NODESET::front() {
  return {m_graph, m_indices.front()};
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename NODESET::NodeOp NODESET::back() {
  return {m_graph, m_indices.back()};
}

/* =============================== COMPARISON =============================== */

/* =============================== ITERATION ================================ */
template <typename NodeType, typename EdgeType, typename AdjType>
typename NODESET::Iterator NODESET::begin() {
  return {*this, 0};
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename NODESET::Iterator NODESET::end() {
  return {*this, static_cast<int>(m_indices.size())};
}

/* ======================== ITERATOR IMPLEMENTATIONS ======================== */
template <typename NodeType, typename EdgeType, typename AdjType>
NODESET::Iterator::Iterator(NODESET& set, int pos) : m_set(set), m_pos(pos) {}

template <typename NodeType, typename EdgeType, typename AdjType>
bool NODESET::Iterator::operator==(const NODESET::Iterator& other) const {
  return m_set == other.m_set && m_pos == other.m_pos;
}

template <typename NodeType, typename EdgeType, typename AdjType>
bool NODESET::Iterator::operator!=(const NODESET::Iterator& other) const {
  return m_pos != other.m_pos;
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename NODESET::Iterator& NODESET::Iterator::operator++() {
  ++m_pos;
  return *this;
}

template <typename NodeType, typename EdgeType, typename AdjType>
typename NODESET::NodeOp NODESET::Iterator::operator*() const {
  return NODESET::NodeOp(m_set.m_graph, m_set.m_indices[m_pos]);
}

}  // namespace mdg

#ifdef NODESET
#undef NODESET
#endif