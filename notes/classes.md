# Graph template parameters

```
template <typename Derived>
class GraphBase;

template <typename Derived>
```

# Used classes

```
namespace mdg
|
+-- class MDGBase
|   |
|   +-- class UndirectedBase
|   |   |
|   |   +-- class Graph
|   |   +-- class ObjectGraph
|   |
|   +-- class DirectedBase
|       |
|       +-- class Digraph
|       +-- class ObjectDigraph
|
+-- class NodeSetBase
|   |
|   +-- ...
|
+-- class EdgeSetBase
|   |
|   |
|   +-- ...
+-- class SearchBase
    |
    +-- class DFS
    +-- class BFS
```

`PureGraph` is a graph whose primary purpose is the simplest undirected graph. The nodes are associated only with their indices. The edges only are associated with the nodes they connect.

`ObjectGraph` is an undirected graph that has some objects associated with its nodes and edges.

`UndirectedBase` an undirected dense (?) graph expression.

`DirectedBase` means an directed graph expression

`MDGBase` is anything that can be transformed into a graph expression (even if it is a bad idea)

---

`NodeSetBase` is an expression that when evaluated turns into a set of nodes from a particular graph

`EdgeSetBase` is an expression that when evaluated turns into a set of edges from a particular graph

---
