## Array Example

```C++
    auto x = nm::array.arange(15, /*dtype=*/nm::float32).reshape(array{3,5});
    auto t1 = (x - x.max(/*axis=*/1,/*dtype=*/nm::None,/*initial=*/nm::None,/*keepdims=*/true)).exp();
    auto t2 = t1.sum(-1,nm::None,nm::None,true);
    auto softmax = t1 / t2;

    print(x);
    print(t1);
    print(t2);
    print(softmax);
```

### Build

```
export NMTOOLS_INCLUDE_DIR=${HOME}/projects/nmtools/include
g++ -I$NMTOOLS_INCLUDE_DIR array.cpp
```

### Run

```
./a.out
```