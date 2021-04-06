CXX=g++
CFLAGS=-Wall
LIBS=-lmysqlcppconn -lmysqlclient -lz -ldl -pthread -lnutclient
DEPS = nutlogger.h
NUTLOGGEROBJ = main.o init.o configobj.o ups.o database.o logger.o

release: CFLAGS=-Wall -O3

%.o: %.cpp $(DEPS)
	$(CXX) $(CFLAGS) -c -o $@ $<

nutlogger: $(NUTLOGGEROBJ)
	$(CXX) -o $@ $^ $(LIBS)

.PHONY: release
release: nutlogger

.PHONY: clean
clean:
	-rm -f nutlogger *.o

.PHONY: all
all: nutlogger

.DEFAULT_GOAL := all
