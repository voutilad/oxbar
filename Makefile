# install locations
BINDIR = /usr/local/bin
MANDIR = /usr/local/man/man1

# build flags
CFLAGS  += -c -std=c89 -Wall -Wextra -Werror -O2 `pkg-config --cflags pangocairo`
LDFLAGS += -L/usr/X11R6/lib `pkg-config --libs pangocairo` -lxcb -lxcb-icccm

# object sets (OBJS = this dir, SOBJS = stats/*, GOBJS = giu/*, WOBJS = widgets/*)
OBJS  = settings.o widgets.o oxbar.o
SOBJS = stats/battery.o stats/cpu.o stats/memory.o stats/net.o stats/nprocs.o stats/volume.o stats/stats.o
GOBJS = gui/chart.o gui/xcore.o gui/xdraw.o gui/gui.o
WOBJS = widgets/battery.o widgets/volume.o widgets/nprocs.o widgets/memory.o widgets/cpus.o widgets/net.o widgets/time.o widgets/util.o

.PHONY: clean cppcheck odeps profile scan-build TODO

all: oxbar

odeps:
	$(MAKE) -C stats   $(MFLAGS) objects
	$(MAKE) -C gui     $(MFLAGS) objects
	$(MAKE) -C widgets $(MFLAGS) objects

.c.o:
	$(CC) $(CFLAGS) $<

oxbar: odeps $(OBJS) $(SOBS) $(GOBJS) $(WOBJS)
	$(CC) -o $@ $(LDFLAGS) $(OBJS) $(SOBJS) $(GOBJS) $(WOBJS)

clean:
	$(MAKE) -C stats   $(MFLAGS) $@
	$(MAKE) -C gui     $(MFLAGS) $@
	$(MAKE) -C widgets $(MFLAGS) $@
	@echo make clean \(local\)
	rm -f $(OBJS)
	rm -f oxbar
	rm -f oxbar.core

TODO:
	grep -nr TODO * \
		| grep -v '^TODO' \
		| grep -v '^Makefile' > $@

# static analyzers
cppcheck:
	cppcheck --quiet --std=c89 -I/usr/include --enable=all --force .

scan-build: clean
	scan-build make

# gprof / memory profiler
gprof: clean
	CC=gcc CFLAGS="-g -pg -fno-pie -fPIC" LDFLAGS="-g -pg -fno-pie -lc" $(MAKE)
	./oxbar
	gprof oxbar gmon.out > gprof.analysis
	gprof2dot gprof.analysis | dot -Tpng -o gprof.png
