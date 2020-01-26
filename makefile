CPPOPT = g++ -O3 -std=c++11
CPPDBG = g++ -g -std=c++11

dustydesk: dustydesk.o
	g++ -O3 dustydesk.o -o dustydesk
	./dustydesk
	gnuplot avg_dust_height.plt

dustydesk.o: dustydesk.cpp
	$(CPPOPT) -c dustydesk.cpp