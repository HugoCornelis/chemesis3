AM_CFLAGS=-g3 -fPIC -Wmissing-prototypes -Wmissing-declarations -ffloat-store -I$(srcdir)/.. -I$(top_srcdir) -include chemesis3/config.h -DPRE_PROTO_TRAVERSAL -D__NO_MATH_INLINES

# ease debugging

CFLAGS=-O0

check_PROGRAMS = \
	cal1 \
	cal2 \
	version

noinst_HEADERS = \
	main.c \
	main.h

cal1_DEPENDENCIES = ../../libchemesis3.a main.c
cal1_LDADD = -L../.. -lchemesis3 -lexperiment -lm
cal2_DEPENDENCIES = ../../libchemesis3.a main.c
cal2_LDADD = -L../.. -lchemesis3 -lexperiment -lm
version_DEPENDENCIES = ../../libchemesis3.a
version_LDADD = -L../.. -lchemesis3 -lm

