

SUBDIRS = 

#t note the use of builddir without '/' suffixed.

#t the neurospaces prefix should be used for this

AM_CFLAGS=-g3 -fPIC -Wmissing-prototypes -Wmissing-declarations -ffloat-store -I/usr/local/neurospaces/instrumentor -I$(srcdir)/.. -I$(builddir).. -include chemesis3/config.h -DPRE_PROTO_TRAVERSAL -D__NO_MATH_INLINES

#CFLAGS = -O0

pkglib_LIBRARIES = libhneurospaces.a

libhneurospaces_a_SOURCES = \
	chemesis3/neurospaces/chemesis3.c

nobase_include_HEADERS = \
	chemesis3/neurospaces/chemesis3.h

