bench: bench.cc
	$(CXX) -std=c++0x -O3 -flto $^ -o $@
