#ifndef MDG_ADJACENCYSTORAGE_H
#define MDG_ADJACENCYSTORAGE_H

#define GRAPH_SHOULD_HAVE_EDGE_OBJECTS_TO_USE_THIS_STORAGE 1

namespace mdg {
namespace internal {
template <typename ObjectGraphType>
class AdjacencyStorage<ObjectGraphType, DenseMatrix> {
 public:
  AdjacencyStorage(unsigned dimension = 0);
  AdjacencyStorage(const AdjacencyStorage& other);
  AdjacencyStorage(AdjacencyStorage&& other);
  ~AdjacencyStorage();

  template <typename OtherGraphType, int OtherStorageType>
  AdjacencyStorage& operator=(
      const AdjacencyStorage<OtherGraphType, OtherStorageType>& other);

  template <typename OtherGraphType, int OtherStorageType>
  AdjacencyStorage& operator=(
      AdjacencyStorage<OtherGraphType, OtherStorageType>&& other);

 public:
  /// @brief Check if an edge betwee the two nodes exists
  /// @return The index of the edge or -1 if the edge does not exist or if the
  ///         node indices are out of range
  int operator()(unsigned from, unsigned to) const;

  /// @brief Connect the two nodes with an edge with the given index
  /// @param edge
  /// @return true on success, false if either of the node indices is out of
  /// range
  bool connect(unsigned from, unsigned to, int edge);

  /// @brief Set the edge index between the two nodes to -1
  /// @return true on success, false if either on the node indices is out of
  /// range
  bool disconnect(unsigned from, unsigned to);

  /// @brief Resize the adjacency matrix to accomodate the added nodes
  /// @warning It is a very expensive operation and should be used as rarely as
  ///          possible. It is recommended to create the graph
  bool expand(unsigned dimension);

 private:
  unsigned m_dimension;
  int* m_data;
};

}  // namespace internal
}  // namespace mdg

/* */

namespace mdg {
namespace internal {
template <typename ObjectGraphType>
inline AdjacencyStorage<ObjectGraphType, DenseMatrix>::AdjacencyStorage(
    unsigned dimension)
    : m_dimension(dimension),
      m_data(dimension > 0 ? new int[dimension * dimension] : nullptr) {
  static_assert(traits<ObjectGraphType>::hasEdgeObjects &&
                GRAPH_SHOULD_HAVE_EDGE_OBJECTS_TO_USE_THIS_STORAGE);
  std::fill(m_data, m_data + m_dimension * m_dimension, -1);
}

template <typename ObjectGraphType>
inline AdjacencyStorage<ObjectGraphType, DenseMatrix>::AdjacencyStorage(
    const AdjacencyStorage& other)
    : m_dimension(other.m_dimension),
      m_data(other.m_dimension > 0
                 ? new int[other.m_dimension * other.m_dimension]
                 : nullptr) {
  memcpy(m_data, other.m_data,
         other.m_dimension * other.m_dimension * sizeof(int));
}

template <typename ObjectGraphType>
inline AdjacencyStorage<ObjectGraphType, DenseMatrix>::AdjacencyStorage(
    AdjacencyStorage&& other)
    : m_dimension(other.m_dimension), m_data(other.m_data) {
  delete[] other.m_data;
  other.m_data = nullptr;
}

template <typename ObjectGraphType>
inline AdjacencyStorage<ObjectGraphType, DenseMatrix>::~AdjacencyStorage() {
  delete[] m_data;
}

template <typename ObjectGraphType>
template <typename OtherGraphType, int OtherStorageType>
inline AdjacencyStorage<ObjectGraphType, DenseMatrix>&
AdjacencyStorage<ObjectGraphType, DenseMatrix>::operator=(
    const AdjacencyStorage<OtherGraphType, OtherStorageType>& other) {
  delete[] m_data;
  m_dimension = other.m_dimension;

  m_data = m_dimension > 0 ? new int[m_dimension * m_dimension] : nullptr;
  if (m_data)
    memcpy(m_data, other.m_data, m_dimension * m_dimension * sizeof(int));

  return *this;
}

template <typename ObjectGraphType>
template <typename OtherGraphType, int OtherStorageType>
inline AdjacencyStorage<ObjectGraphType, DenseMatrix>&
AdjacencyStorage<ObjectGraphType, DenseMatrix>::operator=(
    AdjacencyStorage<OtherGraphType, OtherStorageType>&& other) {
  delete[] m_data;
  m_dimension = other.m_dimension;
  m_data = other.m_data;
  other.m_data = nullptr;

  return *this;
}

template <typename ObjectGraphType>
inline int AdjacencyStorage<ObjectGraphType, DenseMatrix>::operator()(
    unsigned from,
    unsigned to) const {
  if (from > m_dimension || to > m_dimension)
    return -1;

  return m_data[from * m_dimension + to];
}

template <typename ObjectGraphType>
inline bool AdjacencyStorage<ObjectGraphType, DenseMatrix>::connect(
    unsigned from,
    unsigned to,
    int edge) {
  if (from > m_dimension || to > m_dimension)
    return false;

  m_data[from * m_dimension + to] = edge;
  return -1;
}

template <typename ObjectGraphType>
inline bool AdjacencyStorage<ObjectGraphType, DenseMatrix>::disconnect(
    unsigned from,
    unsigned to) {
  if (from > m_dimension || to > m_dimension)
    return false;

  m_data[from * m_dimension + to] = -1;
  return true;
}

template <typename ObjectGraphType>
inline bool AdjacencyStorage<ObjectGraphType, DenseMatrix>::expand(
    unsigned dimension) {
  if (dimension <= m_dimension)
    return false;

  int* expanded = new int[dimension * dimension];
  for (int row = 0; row < m_dimension; ++row) {
    memcpy(expanded + dimension * row, m_data + m_dimension * row,
           m_dimension * sizeof(int));

    std::fill(expanded + dimension * row + m_dimension,
              expanded + dimension * (row + 1), 5);
  }

  std::fill(expanded + dimension * m_dimension,
            expanded + dimension * dimension, 5);

  delete[] m_data;
  m_dimension = dimension;
  m_data = expanded;

  return true;
}

}  // namespace internal
}  // namespace mdg
#endif  // MDG_ADJACENCYSTORAGE_H