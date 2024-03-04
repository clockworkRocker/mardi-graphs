#include <queue>


/* ================================ ITERATOR ================================ */
namespace mdg {

template <typename GraphType>
class BFS<GraphType>::Iterator {
public:  // * Construction and comparison
  Iterator(GraphType& graph, int pos);
  bool operator==(const Iterator& other);
  bool operator!=(const Iterator& other);

 public:  // * Pointer semantics
  ObjectOp operator*() const;
  Iterator& operator++();

 public:
  int queueSize() const;

 private:
  GraphType& m_graph;
  std::queue<int> m_nodes;
  std::vector<bool> m_visits;
};
}

/* ========================= METHOD IMPLEMENTATIONS ========================= */

namespace mdg {
template <typename GraphType>
BFS<GraphType>::BFS(Graph& graph, int index) : m_graph(graph), m_start(index) {}

template <typename GraphType>
typename BFS<GraphType>::Iterator BFS<GraphType>::begin() const {
  return {m_graph, m_start};
}

template <typename GraphType>
typename BFS<GraphType>::Iterator BFS<GraphType>::end() const {
  return {m_graph, m_graph.size()};
}

template <typename GraphType>
int BFS<GraphType>::maxBreadth() {
  int maxSize = 0;
  for (auto iter = begin(); iter != end(); ++iter) {
    if (iter.queueSize() > maxSize)
      maxSize = iter.queueSize();
  }

  return maxSize;
}


}  // namespace mdg
/* ======================== ITERATOR IMPLEMENTATIONS ======================== */

namespace mdg {
template <typename GraphType>
BFS<GraphType>::Iterator::Iterator(GraphType& graph, int pos) : m_graph(graph), m_visits(graph.size()) {
  if (pos >= 0 && pos < graph.size())
    m_nodes.push(pos);
}

template <typename GraphType>
bool BFS<GraphType>::Iterator::operator==(
    const BFS<GraphType>::Iterator& other) {
  if (&m_graph != &other.m_graph)
    return false;
  if (m_nodes.size() != other.m_nodes.size())
    return false;
  if (m_nodes.size() > 0 && m_nodes.front() != other.m_nodes.front())
    return false;

  return true;
}

template <typename GraphType>
bool BFS<GraphType>::Iterator::operator!=(
    const BFS<GraphType>::Iterator& other) {
  if (&m_graph != &other.m_graph)
    return true;
  if (m_nodes.size() != other.m_nodes.size())
    return true;
  if (m_nodes.size() > 0 && m_nodes.front() != other.m_nodes.front())
    return true;

  return false;
}

template <typename GraphType>
typename GraphType::NodeOp BFS<GraphType>::Iterator::operator*() const {
  return {m_graph, m_nodes.front()};
}

template <typename GraphType>
typename BFS<GraphType>::Iterator& BFS<GraphType>::Iterator::operator++() {  
  int top = m_nodes.front();
  m_visits[top] = true;
  m_nodes.pop();

  for (auto node : m_graph.node(top).children())
    if (!m_visits[node.index()])
      m_nodes.push(node.index());

  return *this;
}
template <typename GraphType>
int BFS<GraphType>::Iterator::queueSize() const {return static_cast<int>(m_nodes.size()); }

}  // namespace mdg