CXX=g++
CXXFLAGS=-Wall -g -std=c++11 -fpic
CXXLINK=$(CXX)
OBJS=main.o field.o ip.o port.o string.o libfirewall.so
EXEC=firewall

# Linking commands
$(EXEC): $(OBJS)
	$(CXXLINK) $(OBJS) -o $(EXEC).exe -linput -lfirewall -L.

libfirewall.so: string.o field.o ip.o port.o
	$(CXXLINK) -shared string.o field.o ip.o port.o -o libfirewall.so

# Compilation commands
main.o: main.cpp input.h field.h ip.h port.h string.h
	$(CXX) $(CXXFLAGS) -c main.cpp

field.o: field.cpp field.h ip.h port.h string.h 
	$(CXX) $(CXXFLAGS) -c field.cpp

ip.o: ip.cpp ip.h field.h string.h
	$(CXX) $(CXXFLAGS) -c ip.cpp

port.o: port.cpp port.h field.h string.h
	$(CXX) $(CXXFLAGS) -c port.cpp

string.o: string.cpp string.h 
	$(CXX) $(CXXFLAGS) -c string.cpp

clean:
	rm -f *.o libfirewall.so *.exe