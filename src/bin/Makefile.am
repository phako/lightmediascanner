MAINTAINERCLEANFILES = Makefile.in

AM_CPPFLAGS = \
	-include $(top_builddir)/config.h \
	-I$(top_srcdir)/src/lib \
	@SQLITE3_CFLAGS@
AM_CFLAGS = $(WARNINGFLAGS)
AM_LDFLAGS = $(GCLDFLAGS)

noinst_PROGRAMS = \
	test \
	list-parsers


test_SOURCES = test.c
test_LDADD = $(top_builddir)/src/lib/liblightmediascanner.la @SQLITE3_LIBS@
test_DEPENDENCIES = $(top_builddir)/src/lib/liblightmediascanner.la


list_parsers_SOURCES = list-parsers.c
list_parsers_LDADD = $(top_builddir)/src/lib/liblightmediascanner.la \
	@SQLITE3_LIBS@
list_parsers_DEPENDENCIES = $(top_builddir)/src/lib/liblightmediascanner.la


if BUILD_DAEMON
bin_PROGRAMS = lightmediascannerd lightmediascannerctl

lightmediascannerd_SOURCES = lightmediascannerd.c
lightmediascannerd_CPPFLAGS = $(AM_CPPFLAGS) @GIO_CFLAGS@
lightmediascannerd_LDADD = \
	$(top_builddir)/src/lib/liblightmediascanner.la \
	@SQLITE3_LIBS@ \
	@GIO_LIBS@
lightmediascannerd_DEPENDENCIES = \
	$(top_builddir)/src/lib/liblightmediascanner.la

lightmediascannerctl_SOURCES = lightmediascannerctl.c
lightmediascannerctl_CPPFLAGS = $(AM_CPPFLAGS) @GIO_CFLAGS@
lightmediascannerctl_LDADD = @GIO_LIBS@
endif
