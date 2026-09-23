C := cc
CFLAGS := -Wall -Wextra -O1 -g -march=native

F := ./main.c
F_O := ./main.o
O := ./msound

all:
	$(MAKE) -C . make

make:
	$(C) $(CFLAGS) $(F) -c $(F_O)
	$(C) -o $(O) $(F_O)

clean:
	rm -rf $(F_O) $(O)

.PHONY: all make
