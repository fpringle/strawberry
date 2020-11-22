# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Flags
CCFLAGS=
CXXFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

SRCDIR=../src/core
INCDIR=../src/core
OBJECTDIR=../src/core/obj

OBJECTFILES= \
	${OBJECTDIR}/action.o \
	${OBJECTDIR}/board.o \
	${OBJECTDIR}/check.o \
	${OBJECTDIR}/eval.o \
	${OBJECTDIR}/hash.o \
	${OBJECTDIR}/init.o \
	${OBJECTDIR}/move.o \
	${OBJECTDIR}/play.o \
	${OBJECTDIR}/search.o \
	${OBJECTDIR}/twiddle.o

TESTDIR=.

TESTFILES= \
	${TESTDIR}/bin/boardtest \
	${TESTDIR}/bin/checktest \
	${TESTDIR}/bin/evaltest \
	${TESTDIR}/bin/hashtest \
	${TESTDIR}/bin/movetest \
	${TESTDIR}/bin/perfttest \
	${TESTDIR}/bin/searchtest \
	${TESTDIR}/bin/twiddletest

TESTOBJECTDIR=${TESTDIR}/obj
TESTOBJECTFILES= \
	${TESTOBJECTDIR}/boardtestclass.o \
	${TESTOBJECTDIR}/boardtestrunner.o \
	${TESTOBJECTDIR}/checktestclass.o \
	${TESTOBJECTDIR}/checktestrunner.o \
	${TESTOBJECTDIR}/evaltestclass.o \
	${TESTOBJECTDIR}/evaltestrunner.o \
	${TESTOBJECTDIR}/hashtestclass.o \
	${TESTOBJECTDIR}/hashtestrunner.o \
	${TESTOBJECTDIR}/movetestclass.o \
	${TESTOBJECTDIR}/movetestrunner.o \
	${TESTOBJECTDIR}/perfttestclass.o \
	${TESTOBJECTDIR}/perfttestrunner.o \
	${TESTOBJECTDIR}/searchtestclass.o \
	${TESTOBJECTDIR}/searchtestrunner.o \
	${TESTOBJECTDIR}/twiddletestclass.o \
	${TESTOBJECTDIR}/twiddletestrunner.o

# main target

build-tests: ${OBJECTFILES} ${TESTFILES}

# core object files

${OBJECTDIR}/action.o: ${SRCDIR}/action.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${OBJECTDIR}/board.o: ${SRCDIR}/board.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${OBJECTDIR}/check.o: ${SRCDIR}/check.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${OBJECTDIR}/eval.o: ${SRCDIR}/eval.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${OBJECTDIR}/hash.o: ${SRCDIR}/hash.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${OBJECTDIR}/init.o: ${SRCDIR}/init.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${OBJECTDIR}/move.o: ${SRCDIR}/move.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${OBJECTDIR}/play.o: ${SRCDIR}/play.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${OBJECTDIR}/search.o: ${SRCDIR}/search.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${OBJECTDIR}/twiddle.o: ${SRCDIR}/twiddle.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^



# test object files

${TESTOBJECTDIR}/boardtestclass.o: ${TESTDIR}/boardtestclass.cpp
	${MKDIR} -p ${TESTOBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${TESTDIR} -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${TESTOBJECTDIR}/boardtestrunner.o: ${TESTDIR}/boardtestrunner.cpp
	${MKDIR} -p ${TESTOBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${TESTDIR} -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${TESTOBJECTDIR}/checktestclass.o: ${TESTDIR}/checktestclass.cpp
	${MKDIR} -p ${TESTOBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${TESTDIR} -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${TESTOBJECTDIR}/checktestrunner.o: ${TESTDIR}/checktestrunner.cpp
	${MKDIR} -p ${TESTOBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${TESTDIR} -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${TESTOBJECTDIR}/evaltestclass.o: ${TESTDIR}/evaltestclass.cpp
	${MKDIR} -p ${TESTOBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${TESTDIR} -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${TESTOBJECTDIR}/evaltestrunner.o: ${TESTDIR}/evaltestrunner.cpp
	${MKDIR} -p ${TESTOBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${TESTDIR} -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${TESTOBJECTDIR}/hashtestclass.o: ${TESTDIR}/hashtestclass.cpp
	${MKDIR} -p ${TESTOBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${TESTDIR} -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${TESTOBJECTDIR}/hashtestrunner.o: ${TESTDIR}/hashtestrunner.cpp
	${MKDIR} -p ${TESTOBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${TESTDIR} -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${TESTOBJECTDIR}/movetestclass.o: ${TESTDIR}/movetestclass.cpp
	${MKDIR} -p ${TESTOBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${TESTDIR} -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${TESTOBJECTDIR}/movetestrunner.o: ${TESTDIR}/movetestrunner.cpp
	${MKDIR} -p ${TESTOBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${TESTDIR} -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${TESTOBJECTDIR}/perfttestclass.o: ${TESTDIR}/perfttestclass.cpp
	${MKDIR} -p ${TESTOBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${TESTDIR} -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${TESTOBJECTDIR}/perfttestrunner.o: ${TESTDIR}/perfttestrunner.cpp
	${MKDIR} -p ${TESTOBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${TESTDIR} -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${TESTOBJECTDIR}/searchtestclass.o: ${TESTDIR}/searchtestclass.cpp
	${MKDIR} -p ${TESTOBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${TESTDIR} -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${TESTOBJECTDIR}/searchtestrunner.o: ${TESTDIR}/searchtestrunner.cpp
	${MKDIR} -p ${TESTOBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${TESTDIR} -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${TESTOBJECTDIR}/twiddletestclass.o: ${TESTDIR}/twiddletestclass.cpp
	${MKDIR} -p ${TESTOBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${TESTDIR} -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^

${TESTOBJECTDIR}/twiddletestrunner.o: ${TESTDIR}/twiddletestrunner.cpp
	${MKDIR} -p ${TESTOBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I${TESTDIR} -I${INCDIR} -MMD -MP -MF "$@.d" -o $@ $^



# test targets

${TESTDIR}/bin/boardtest: ${TESTOBJECTDIR}/boardtestclass.o ${TESTOBJECTDIR}/boardtestrunner.o ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/bin
	${LINK.cc} -o $@ $^ ${LDLIBSOPTIONS} -lcppunit

${TESTDIR}/bin/checktest: ${TESTOBJECTDIR}/checktestclass.o ${TESTOBJECTDIR}/checktestrunner.o ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/bin
	${LINK.cc} -o $@ $^ ${LDLIBSOPTIONS} -lcppunit

${TESTDIR}/bin/evaltest: ${TESTOBJECTDIR}/evaltestclass.o ${TESTOBJECTDIR}/evaltestrunner.o ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/bin
	${LINK.cc} -o $@ $^ ${LDLIBSOPTIONS} -lcppunit

${TESTDIR}/bin/hashtest: ${TESTOBJECTDIR}/hashtestclass.o ${TESTOBJECTDIR}/hashtestrunner.o ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/bin
	${LINK.cc} -o $@ $^ ${LDLIBSOPTIONS} -lcppunit

${TESTDIR}/bin/movetest: ${TESTOBJECTDIR}/movetestclass.o ${TESTOBJECTDIR}/movetestrunner.o ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/bin
	${LINK.cc} -o $@ $^ ${LDLIBSOPTIONS} -lcppunit

${TESTDIR}/bin/perfttest: ${TESTOBJECTDIR}/perfttestclass.o ${TESTOBJECTDIR}/perfttestrunner.o ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/bin
	${LINK.cc} -o $@ $^ ${LDLIBSOPTIONS} -lcppunit

${TESTDIR}/bin/searchtest: ${TESTOBJECTDIR}/searchtestclass.o ${TESTOBJECTDIR}/searchtestrunner.o ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/bin
	${LINK.cc} -o $@ $^ ${LDLIBSOPTIONS} -lcppunit

${TESTDIR}/bin/twiddletest: ${TESTOBJECTDIR}/twiddletestclass.o ${TESTOBJECTDIR}/twiddletestrunner.o ${OBJECTFILES}
	${MKDIR} -p ${TESTDIR}/bin
	${LINK.cc} -o $@ $^ ${LDLIBSOPTIONS} -lcppunit


# run test targets
run-tests:
	@${TESTDIR}/bin/boardtest || true
	@${TESTDIR}/bin/checktest || true
	@${TESTDIR}/bin/evaltest || true
	@${TESTDIR}/bin/hashtest || true
	@${TESTDIR}/bin/movetest || true
	@${TESTDIR}/bin/perfttest || true
	@${TESTDIR}/bin/searchtest || true
	@${TESTDIR}/bin/twiddletest || true
