## Computational Graph Example

```C++
    auto axis = -1;
    auto res = view::softmax(input,axis);

    /* Static computational graph: */
    auto graph = fn::get_computational_graph(res);

    /* Compile-time computational graph: */
    constexpr auto graph_v = nm::to_value_v<decltype(unwrap(graph))>;

    auto graphviz = utils::to_string(unwrap(graph),utils::Graphviz);
    auto graphviz_v = utils::to_string(unwrap(graph_v),utils::Graphviz);
```

### Build

```
export NMTOOLS_INCLUDE_DIR=${HOME}/projects/nmtools/include
g++ -std=c++17 -I$NMTOOLS_INCLUDE_DIR softmax.cpp
```

### Run

This will print the grapviz code representing the graph
```
./a.out
```
Then you can copy paste to a new file e.g. softmax.dot.

<div style="text-align: center;">
  <img src="softmax.png" alt="Description" style="width:600px; max-width:100%;" />
</div>

You will probably need to increase the stack size:
```
ulimit -s unlimited
```