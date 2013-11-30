# Makefile: 
#           It uses the C++ Compiler with all warnings and 
#           debugging enabled. A single executable will
#           be produced.
# ---------------------------------------------------------------
CPP = g++ 
CFLAGS = -L/usr/lib/cmplrs/g++ -DPOSIX_4D9
DFLAGS = -w -g
LD = g++
LS = gcc
LLIBS = -lm 
LGLUT = -lglut
#
# Linker Flags:
# set "-lm" if we need to use the "math" functions
CLIBS= -lm
RM = rm -f
# ----------------------------------------------------------------
# Explanation of macros:
#     $< is any dependent file which is out of file
#     $* is the target's basename (without extension)
#     $@ is the target's fullname
#
# In general ".cpp" (unlike ".c") is not automatically recognized as a
# reserved suffix, so we should inform "make" in case we use this later:
.SUFFIXES:	.cpp .o
#
# implicit rule for compilation only:
#.cpp.o:
#	${CPP} -c ${DFLAGS} ${CFLAGS} $<

HFILES=		BrickManager.h Ball.h Paddle.h

# dependencies 
#
default:	all
all:	        breakout	
#

#

breakout: 	$(HFILES) breakout.cpp
		${LS} -o $@ $@.cpp ${LGLUT}
clean:
	${RM} *.o
	${RM} core
	${RM} breakout
#

