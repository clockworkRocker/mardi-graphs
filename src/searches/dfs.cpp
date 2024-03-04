#include <stack>
#include <algorithm>

/* ================================ ITERATOR ================================ */

namespace mdg {
template <typename GraphType>
class DFS<GraphType>::Iterator {
 public:  // * Construction and comparison
  Iterator(GraphType& graph, int pos);
  bool operator==(const Iterator& other);
  bool operator!=(const Iterator& other);

 public:  // * Getters
  int time() const;

 public:  // * Pointer semantics
  ObjectOp operator*() const;
  Iterator& operator++();

 private:
  GraphType& m_graph;
  std::stack<int> m_nodes;
  std::vector<bool> m_visits;
  int m_time = 0;
};
}  // namespace mdg

/* ========================= METHOD IMPLEMENTATIONS ========================= */

namespace mdg {
template <typename GraphType>
DFS<GraphType>::DFS(GraphType& graph, int index)
    : m_graph(graph), m_start(index) {}

template <typename GraphType>
typename DFS<GraphType>::Iterator DFS<GraphType>::begin() {
  return {m_graph, m_start};
}

template <typename GraphType>
typename DFS<GraphType>::Iterator DFS<GraphType>::end() {
  return {m_graph, static_cast<int>(m_graph.size())};
}

template <typename GraphType>
inline std::vector<int> DFS<GraphType>::topologicalSort() {
  std::vector<int> indices(m_graph.size());

  for (auto iter = begin(); iter != end(); ++iter)
    indices.push_back(iter->index());

  std::reverse(indices.begin(), indices.end());

  return indices;
}

template <typename GraphType>
bool DFS<GraphType>::markEdges(Classifier& marks) const {
  std::stack<std::pair<int, int>> pairs;
  std::vector<int> opened(m_graph.size());
  std::vector<Color> color(m_graph.size());
  int u, v, w, time = 0;

  // * Init marks vector
  if (marks.size() != (unsigned)m_graph.num_edges())
    marks.resize(m_graph.num_edges());
  std::fill(marks.begin(), marks.end(), EdgeMark::unknown);

  pairs.push({m_start, -1});
  while (!pairs.empty()) {
    u = pairs.top().first;
    w = pairs.top().second;

    switch (color[u]) {
      case Color::white:
        opened[u] = time;
        color[u] = Color::gray;

        if (w >= 0)
          marks[m_graph.edge(w, u).index()] = EdgeMark::tree;

        for (auto node : m_graph.node(u).children()) {
          v = node.index();
          switch (color[v]) {
            case Color::white:
              pairs.push({v, u});
              break;

            case Color::gray:
              marks[m_graph.edge(u, v).index()] = EdgeMark::back;
              break;

            case Color::black:
              marks[m_graph.edge(u, v).index()] = EdgeMark::cross;
              break;
          }
        }

        break;

      case Color::gray:
        color[u] = Color::black;
        pairs.pop();

        break;

      case Color::black:
        if (w >= 0)
          marks[m_graph.edge(w, u).index()] = EdgeMark::forward;

        pairs.pop();
        break;
    }

    ++time;
  }

  for (const auto& mark : marks)
    if (mark == EdgeMark::unknown)
      return false;

  return true;
}

}  // namespace mdg

/* ======================== ITERATOR IMPLEMENTATIONS ======================== */

namespace mdg {
template <typename GraphType>
DFS<GraphType>::Iterator::Iterator(GraphType& graph, int pos)
    : m_graph(graph), m_visits(graph.size()) {
  if (pos >= 0 && pos < graph.size())
    m_nodes.push(pos);
}

template <typename GraphType>
bool DFS<GraphType>::Iterator::operator==(
    const DFS<GraphType>::Iterator& other) {
  if (&m_graph != &other.m_graph)
    return false;
  if (m_nodes.size() != other.m_nodes.size())
    return false;
  if (m_nodes.size() > 0 && m_nodes.top() != other.m_nodes.top())
    return false;

  return true;
}

template <typename GraphType>
bool DFS<GraphType>::Iterator::operator!=(
    const DFS<GraphType>::Iterator& other) {
  if (&m_graph != &other.m_graph)
    return true;
  if (m_nodes.size() != other.m_nodes.size())
    return true;
  if (m_nodes.size() > 0 && m_nodes.top() != other.m_nodes.top())
    return true;

  return false;
}

template <typename GraphType>
int DFS<GraphType>::Iterator::time() const {
  return m_time;
}

template <typename GraphType>
typename GraphType::NodeOp DFS<GraphType>::Iterator::operator*() const {
  return {m_graph, m_nodes.top()};
}

template <typename GraphType>
typename DFS<GraphType>::Iterator& DFS<GraphType>::Iterator::operator++() {
  int top = m_nodes.top();
  m_visits[top] = true;
  m_nodes.pop();

  for (auto node : m_graph.node(top).children())
    if (!m_visits[node.index()])
      m_nodes.push(node.index());

  return *this;
}

}  // namespace mdg