##
## Chemesis3 : a compartmental solver that implements efficient Crank-Nicolson
## integration for neuronal models.
##

##############################################################################
##'
##' Chemesis3 : testbed C implementation
##'
##' Copyright (C) 2006-2008 Hugo Cornelis
##'
##' functional ideas ..	Hugo Cornelis, hugo.cornelis@gmail.com
##'
##' coding ............	Hugo Cornelis, hugo.cornelis@gmail.com
##'
##############################################################################


EXTRA_DIST = \
	chemesis3.i \
	chemesis3/__cbi__.py \
	chemesis3/__init__.py \
	clean.py \
	setup.py \
	uninstall.py 

setup: setup.py
	$(PYTHON) setup.py build
	$(PYTHON) setup.py build_py

install-exec-hook:
	$(PYTHON) setup.py install

uninstall-hook:
	$(PYTHON) uninstall.py

all: setup

clean-local:
	$(RM) `find . -name "*.pyc"`
	$(PYTHON) clean.py

CLEANFILES = \
	$(srcdir)/chemesis3_wrap.c \
	$(srcdir)/chemesis3_wrap.o \
	$(srcdir)/_chemesis3_base.so \
	$(srcdir)/chemesis3_base.py \
	$(srcdir)/chemesis/chemesis3_wrap.c \
	$(srcdir)/chemesis3_wrap.o \
	$(srcdir)/chemesis3/_chemesis3_base.so \
	$(srcdir)/chemesis3/chemesis3_base.py 

# SUBDIRS = 

# pythondir = $(prefix)/glue/swig/python/

# nobase_python_HEADERS = \
# 	neurospaces/chemesis3/__init__.py \
# 	neurospaces/chemesis3/__cbi__.py \
# 	neurospaces/chemesis3/components.py 


# nobase_python_DATA = \
# 	neurospaces/chemesis3/_chemesis3_base.so \
# 	neurospaces/chemesis3/chemesis3_base.py

# EXTRA_DIST = \
# 	$(srcdir)/chemesis3.i 

# BUILT_SOURCES = \
# 	neurospaces/chemesis3/chemesis3_base.py \
# 	chemesis3_wrap.c


# #---------------------------------------------------------
# #-------- Rules for building the chemesis3 swig binding -----

# chemesis3_wrap.o: chemesis3_wrap.c
# 	gcc $(SWIGCOMPILELINKSFORPYTHON) -c $(srcdir)/chemesis3_wrap.c

# chemesis3_wrap.c ./neurospaces/chemesis3/chemesis3_base.py: 
# 	$(SWIG) -I$(builddir)/../../.. -I$(top_builddir) -python -outdir $(srcdir)/neurospaces/chemesis3 -o chemesis3_wrap.c $(srcdir)/chemesis3.i

# _chemesis3_base.so: chemesis3_wrap.o
# 	$(CHEMESIS3_SWIGLINKCOMMAND_PYTHON)

# #------------------ End rules for chemesis3 swig ------------
# #---------------------------------------------------------



# all: _chemesis3_base.so 



# clean-local:
# 	$(RM) -rf $(srcdir)/docs/html
# 	echo "Removing all compiled byte code files"
# 	$(RM) `find . -name "*.pyc"`
# 	$(RM) -rf $(srcdir)/build
# 	$(RM) -rf $(srcdir)/dist/

# CLEANFILES = \
# 	$(srcdir)/chemesis3_wrap.c \
# 	$(srcdir)/chemesis3_wrap.o \
# 	$(srcdir)/_chemesis3_base.so \
# 	$(srcdir)/chemesis3_base.py \
# 	$(srcdir)/neurospaces/chemesis3_wrap.c \
# 	$(srcdir)/neurospaces/chemesis3_wrap.o \
# 	$(srcdir)/neurospaces/chemesis3/_chemesis3_base.so \
# 	$(srcdir)/neurospaces/chemesis3/chemesis3_base.py 


