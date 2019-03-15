CXXFLAGS := -std=c++11

all: code1

run: run-code1

run-code1: code1
	@./code1 > code1.dot
	@unflatten -l 20 -c 5 code1.dot | dot -Tpng -o code1.png
	@mupdf code1.png

clean:
	@rm -fv code1
	@find -name '*.o' -exec rm -fv {} \;
	@find -name '*.dot' -exec rm -fv {} \;
	@find -name '*.png' -exec rm -fv {} \;

code1: main.cpp.o
	$(CXX) $^ -o $@

%.cpp.o: %.cpp forest.hpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<
