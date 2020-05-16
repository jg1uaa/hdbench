## Process this file with automake to produce Makefile.in

bin_PROGRAMS = hdbench

hdbench_SOURCES = benchcpu.c benchmark.c getinfo.c hdbench.c intl.h main.c \
proto.h selection.c selection.h shhopt.c shhopt.h sighandler.c support.c variable.h

# avoid unwanted optimization (especially required for clang)
# if you use gcc 3.x remove -fno-tree-vectorize
hdbench_CFLAGS = @GTK_CFLAGS@ -DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" -DPACKAGE_SOURCE_DIR=\""$(abs_srcdir)"\" -DPACKAGE_LOCALE_DIR=\""$(localedir)"\" -fno-unroll-loops -fno-tree-vectorize

# add -lX11 for FreeBSD (workaround)
hdbench_LDADD = @GTK_LIBS@ -lX11
