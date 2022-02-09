

CXXFLAGS := 
DEPS := matrix.cpp neuralnet.cpp 

xor : xor.cpp $(DEPS)
	g++ $(CXXFLAGS) -o $@ xor.cpp $(DEPS)

pieceofcake : pieceofcake.cpp $(DEPS)
	g++ $(CXXFLAGS) -o $@ pieceofcake.cpp $(DEPS)