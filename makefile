ENDFLAGS = -g -lreadline
CC = gcc

lib-type = S #S - static; D - dynamic

ifeq ($(lib-type), D)
	CFLAGS = -c -fPIC
	LEFT = $(CC) -shared -o
	FORMAT = so
	ENDCOMP = -Wl,-rpath,./lib
else
	CFLAGS = -c
	LEFT = ar r
	FORMAT = a
	ENDCOMP = 
endif

SRC = $(wildcard ./src/*.c)
OBJ = $(patsubst ./src/%.c, ./obj/%.o, $(SRC))

all: lib $(OBJ)
	$(CC) -o lab4b ./obj/*.o -L./lib -lLLRB $(ENDCOMP) $(ENDFLAGS)

./obj/%.o : ./src/%.c
	@mkdir -p ./obj/ || true
	$(CC) -c $< -o $@ $(ENDFLAGS)

lib: clean
	@mkdir -p ./lib/obj/ || true
	$(CC) $(CFLAGS) ./lib/src/LLRB.c -o ./lib/obj/LLRB.o $(ENDFLAGS)
	$(LEFT) ./lib/libLLRB.$(FORMAT) ./lib/obj/*.o

clean:
	@rm -f *.dot || true
	@rm -f *.png || true
	@rm -f ./lib/*.so || true
	@rm -f ./lib/*.a || true

	@rm -f ./lib/obj/*.o || true
	@rm -f -d ./lib/obj || true

	@rm -f ./obj/*.o || true
	@rm -f -d ./obj || true

	@rm -f ./lab4b || true