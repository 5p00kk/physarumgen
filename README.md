# physarumgen

C++ Physarum polycephalum slime mold simluation. All processing is currently being done sequentially on the CPU.

Implementation based on the *"Characteristics of pattern formation and evolution in approximations of physarum transport networks"* [1] paper.

## Examples
![image info](./examples/physarum_01.jpg)

![image info](./examples/physarum_02.jpg)

## Build
```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
./demo/physarumgen_demo 
```

## Dependencies
1. OpenCV

## TODO/Ideas

- [x] Examples in .MD
- [x] Diffusion/decay step to trail map
- [ ] GPU implementation
- [x] Code documentation
- [ ] Add sensor size parameter from the paper
- [x] Add nice interface to record images/videos
- [ ] Add interface for setting parameters of agent from outside
- [ ] Different spawning methods
- [ ] Interactive reaction to mouse position
- [ ] Multiple agent types in the same simulation
- [ ] Colours

## References
1.  https://uwe-repository.worktribe.com/output/980579?fbclid=IwAR0l3mB_Vo5Vd_HDTf4qGF1ka2Q0k3d-LEJ-Mpyl632yMcwD_DJ6q-N6zKc

2. https://pl.wikipedia.org/wiki/Physarum_polycephalum

3. https://sagejenson.com/physarum