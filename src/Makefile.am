## Process this file with automake to produce Makefile.in

bin_PROGRAMS = hdbench

hdbench_SOURCES = benchcpu.c benchmark.c getinfo.c hdbench.c intl.h main.c \
proto.h selection.c selection.h shhopt.c shhopt.h sighandler.c support.c variable.h

hdbench_CFLAGS = @GTK_CFLAGS@ -DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" -DPACKAGE_SOURCE_DIR=\""$(abs_srcdir)"\" -DPACKAGE_LOCALE_DIR=\""$(localedir)"\"
hdbench_LDADD = @GTK_LIBS@
