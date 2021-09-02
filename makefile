CC=g++
CFLAGS=-std=c++1z -I.
OBJFLAG=-lpthread
SRC = ${wildcard *.cpp}
OBJ = ${patsubst %.cpp, %.o, $(SRC)}

main:$(OBJ)
	$(CC) -o  $@ $^ $(OBJFLAG)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -MMD -o $@ -O3

%.d: %.cpp
	@set -e;rm -rf $@;$(CC) -MM $< > $@.$$$$;  \
		sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' <$@.$$$$ > $@;\
		rm -rf $@.$$$$

-include $(OBJ:.o=.d)

.PHONY:clean
clean:
	rm -rf main *.o *.d *.d.*
