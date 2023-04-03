# Infrastructure

# TODO (Essential for `comsdk` )
* [ ]  `ObjectDigraph`
    - [ ]  `DirectedBase`
        - [x]  `MGDBase`
        - [x]  `traits<MDGBase>`
        - [x]  `traits<DirectedBase>`
        - [x]  `DirectedNodeOp` interface
            - [x]  `NodeOpBase<DirectedNodeOp>`
              - [x]  REFCTOR: Remake the methods implementation according to the CRTP methodology. I seem to have messed up
            - [x]  `nodeop_traits<DirectedNodeOp>`
    - [ ]  `traits<ObjectDigraph>`
* [ ]  `BFS<GraphType>`
    - [ ]  `BFSIterator`
* [ ]  `DFS<GraphType>`
    - [ ]  `DFSIterator`
    - [ ]  `SearchBase`
# Utilities
* [ ] Add an exception when trying to access a node with an index out of bounds
