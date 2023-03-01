# Infrastructure

# TODO (Essential for `comsdk` )
* [ ]  `ObjectDigraph`
    - [ ]  `DirectedBase`
        - [ ]  `PlainGraphBase`
            - [x]  `MGDBase`
            - [x]  `traits<MDGBase>`
          - [ ]  `traits<PlainGraphBase>`
        - [ ]  `traits<DirectedBase>`
        - [ ]  `DirectedNodeOp` interface
            - [ ]  `NodeOpBase<DirectedNodeOp>`
              - [ ]  REFACTOR: Remake the methods implementation according to the CRTP methodology. I seem to have messed up
            - [x]  `nodeop_traits<DirectedNodeOp>`
    - [ ]  `traits<ObjectDigraph>`
* [ ]  `BFS<GraphType>`
    - [ ]  `BFSIterator`
* [ ]  `DFS<GraphType>`
    - [ ]  `DFSIterator`
    - [ ]  `SearchBase`
