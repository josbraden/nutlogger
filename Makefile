CXX=g++
CFLAGS=-Wall
LIBS=-lmysqlcppconn -lmysqlclient -lz -ldl -pthread -lcurl -lnutclient
DEPS = nutlogger.h
NUTLOGGEROBJ = main.o

%.o: %.cpp $(DEPS)
	$(CXX) $(CFLAGS) -c -o $@ $<

nutlogger: $(NUTLOGGEROBJ)
	$(CXX) -o $@ $^ $(LIBS)

.PHONY: clean
clean:
	-rm -f nutlogger *.o

.PHONY: all
all: nutlogger

.DEFAULT_GOAL := all
