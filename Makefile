CXX = g++
CXXFLAGS = -std=c++14 -Wall -g

EXEC = chess
CCFILES = $(wildcard *.cc)
OBJECTS = ${CCFILES:.cc=.o}

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

.PHONY: clean
clean:
	rm -f ${EXEC} ${OBJECTS}
