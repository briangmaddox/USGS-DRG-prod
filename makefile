
prefix		=	/home/bmaddox
exec_prefix	=	${prefix}
host_os		=	linux
srcdir		=	.
top_srcdir	=	.
gen_depend	=	no
enable_debug	=	no
enable_purify	=	no

foundone := true
# DG/UX (Data General UNIX)
ifeq ($(findstring dgux,$(host_os)),dgux)
INCPATHS = -I$(prefix)/include -I.
LIBPATHS = -L/opt/oracle7/lib -L$(prefix)/lib
LIBS = $(LIBPATHS) -ldrg -lDRGSourceInfo -lm
ORALIBS = -lsql -lsqlnet -lora -lsqlnet -lora -lnlsrtl -lcv6 -lcore -lnlsrtl -lcv6 -lcore -lld
foundone := true
endif

# Linux
ifeq ($(host_os),linux)
INCPATHS = -I/usr/X11R6/include -I$(prefix)/include
LIBPATHS = -L/usr/X11R6/lib -L$(prefix)/lib
LIBS = $(LIBPATHS) -lm
ORALIBS = 
foundone := true
endif

ifeq ($(foundone),false)
INCPATHS = -I$(prefix)/include
LIBPATHS = -L$(prefix)/lib
LIBS = $(LIBPATHS) -lm
ORALIBS = 
endif

# Where to find includes for libraries that drg depends on.
#INCPATHS = -I$(prefix)/include

# Where to install drg's include files.
INCDEST = $(prefix)/include/drg

# Where to install drg's library.
LIBDEST = $(prefix)/lib

ifeq ($(enable_debug),yes)
DEBUG = -g
else
DEBUG = -O2
endif

ifeq ($(enable_purify),yes)
PURIFY = purify
else
PURIFY =
endif

CC=$(PURIFY) gcc
CXX=$(PURIFY) g++
CXXFLAGS= $(DEBUG) $(INCPATHS)

INSTALLFILE = $(srcdir)/config/install-sh -c
INSTALLDIR  = $(srcdir)/config/install-sh -d

SRCS=   DRGMetaData.cc    \
	controlpts.cc     \
	ARCWorldFile.cc   \
        MetFile.cc	  \
	coordutils.cc

OBJS=$(SRCS:.cc=.o)

all: libdrg.a installlib installinc
	@echo "Done."

libdrg.a: $(OBJS)
	ar ru libdrg.a $(OBJS)

# Preserve the time stamp on the include files.
installinc: 
	@echo "Installing includes"
	@test -d $(INCDEST) || $(INSTALLDIR) $(INCDEST)
	@tar cf /tmp/drg.tar *.h ; \
	cd $(INCDEST); tar xf /tmp/drg.tar ; \
	rm -rf /tmp/drg.tar

installlib:
	@echo "Installing library"
	@test -d $(LIBDEST) || $(INSTALLDIR) $(LIBDEST)
	@cp libdrg.a $(LIBDEST)

clean::
	rm -f $(OBJS) *.a core drgmeta2awf

realclean: 
	rm -rf *.d config.cache config.status config.log

fixmet : fixmet.cc
	$(CXX) -O2 $(INCPATHS) -o fixmet fixmet.cxx $(LIBS)

drgmeta2awf: drgmeta2awf.o
	$(CXX) $(CXXFLAGS) -o drgmeta2awf drgmeta2awf.o $(LIBS)

makemetdat: makemetdat.cc
	$(CXX) $(CXXFLAGS) -o makemetdat makemetdat.cc $(LIBS) -lfl

ifeq ($(findstring dgux,$(host_os)),dgux)
makemet: makemet.o
	$(CXX) -o makemet makemet.o $(prefix)/lib/osntab.o $(LIBS) $(ORALIBS)
endif

ifeq ($(gen_depend),yes)
# Automatic generation of dependencies
%.d: %.cc
	@echo "Regenerating dependencies for $<";$(SHELL) -ec '$(CC) \
	$(INCPATHS) -MM $(CPPFLAGS) $< | sed '\''s/$*.o/& $@/g'\'' > $@'


include $(SRCS:.cc=.d)

endif


