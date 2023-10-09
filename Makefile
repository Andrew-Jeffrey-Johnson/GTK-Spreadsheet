CXX=g++
CXXFLAGS=-std=c++11
LIBS=`pkg-config gtkmm-3.0 --cflags --libs`
TARGET=spreadsheet

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(TARGET).cpp $(LIBS)

clean:
	rm -f $(TARGET)
