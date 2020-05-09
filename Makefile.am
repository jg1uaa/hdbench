## Process this file with automake to produce Makefile.in

AUTOMAKE_OPTIONS=foreign

SUBDIRS = src doc

install-data-local:
	test -d pixmaps \
	&& install -d -m 0755 $(pkgdatadir)/pixmaps \
	&& install -m 0644 pixmaps/* $(pkgdatadir)/pixmaps

dist-hook:
	test -d pixmaps \
	&& mkdir $(distdir)/pixmaps \
	&& cp -p pixmaps/* $(distdir)/pixmaps

EXTRA_DIST=hdbench.prj
