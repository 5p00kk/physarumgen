# physarumgen

C++ Physarum polycephalum slime mold simluation. All processing is currently being done sequentially on the CPU.

Implementation based on the *"Characteristics of pattern formation and evolution in approximations of physarum transport networks"*[1] paper.

## Examples

## Build
```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
./demo/physarumgen_demo 
```

## Dependencies
1. OpenCV

## TODO

- [ ] Examples in .MD
- [ ] Diffusion/decay step to trail map
- [ ] GPU implementation
- [x] Code documentation
- [ ] Sensor size parameter


## References
1.  https://uwe-repository.worktribe.com/output/980579?fbclid=IwAR0l3mB_Vo5Vd_HDTf4qGF1ka2Q0k3d-LEJ-Mpyl632yMcwD_DJ6q-N6zKc

2. https://pl.wikipedia.org/wiki/Physarum_polycephalum

3. https://sagejenson.com/physarum