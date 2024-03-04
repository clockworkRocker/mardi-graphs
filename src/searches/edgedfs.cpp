#include <stack>

namespace mdg {
template <typename GraphType>
EdgeDFS<GraphType>::EdgeDFS(Graph& graph, int index)
    : m_graph(graph), m_start(index) {}

template <typename GraphType>
typename EdgeDFS<GraphType>::Iterator EdgeDFS<GraphType>::begin() {
  return {m_graph, m_start};
}

template <typename GraphType>
typename EdgeDFS<GraphType>::Iterator EdgeDFS<GraphType>::end() {
  return {m_graph, m_graph.size()};
}
}  // namespace mdg

/* ================================ ITERATOR ================================ */

namespace mdg {
template <typename GraphType>
class EdgeDFS<GraphType>::Iterator {
 public:
  Iterator(GraphType& graph, int node);
  bool operator==(const Iterator& other) const;
  bool operator!=(const Iterator& other) const;

 public:  // * Pointer semanics
  typename GraphType::EdgeOp operator*() const;
  Iterator& operator++();

 private:
  GraphType& m_graph;
  std::stack<std::pair<int, int>> m_edges;
  std::vector<bool> m_visits;
};
}  // namespace mdg

/* ======================== ITERATOR IMPLEMENTATIONS ======================== */

namespace mdg {
template <typename GraphType>
EdgeDFS<GraphType>::Iterator::Iterator(GraphType& graph, int node)
    : m_graph(graph), m_visits(graph.size()) {
  for (auto edge : m_graph.node(node).outgoing())
    m_edges.push({edge.start().index(), edge.end().index()});
}

template <typename GraphType>
bool EdgeDFS<GraphType>::Iterator::operator==(const Iterator& other) const {
  if (&m_graph != &other.m_graph)
    return false;
  if (m_edges.size() != other.m_edges.size())
    return false;
  if (m_edges.size() > 0 && m_edges.top() != other.m_edges.top())
    return false;

  return true;
}

template <typename GraphType>
bool EdgeDFS<GraphType>::Iterator::operator!=(const Iterator& other) const {
  if (&m_graph != &other.m_graph)
    return true;
  if (m_edges.size() != other.m_edges.size())
    return true;
  if (m_edges.size() > 0 && m_edges.top() != other.m_edges.top())
    return true;

  return false;
}

template <typename GraphType>
typename GraphType::EdgeOp EdgeDFS<GraphType>::Iterator::operator*() const {
  return {m_graph, m_edges.top().first, m_edges.top().second};
}

template <typename GraphType>
typename EdgeDFS<GraphType>::Iterator& EdgeDFS<GraphType>::Iterator::operator++() {
  if (m_edges.empty())
    return *this;

  auto edge = m_edges.top();
  m_visits[m_graph.edge(edge.first, edge.second).index()] = true;
  m_edges.pop();

  for (auto edge : m_graph.node(edge.second).outgoing())
    if (!m_visits[edge.index()])
      m_edges.push(std::make_pair(edge.start().index(), edge.end().index()));

  return *this;
}
}  // namespace mdg
