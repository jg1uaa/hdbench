## Process this file with automake to produce Makefile.in

INCLUDES = \
	-I$(top_srcdir)/intl \
	@GTK_CFLAGS@

bin_PROGRAMS = hdbench

hdbench_SOURCES = benchcpu.s benchmark.c getinfo.c hdbench.c intl.h main.c \
proto.h selection.c selection.h shhopt.c shhopt.h sighandler.c support.c variable.h

hdbench_LDADD = @GTK_LIBS@ $(INTLLIBS)

