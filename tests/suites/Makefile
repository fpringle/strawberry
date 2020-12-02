MAKEFILE      = Makefile

EQ            = =

## suites directories
TEST_SUITES   = Bratko-Kopec \
		CCR \
		Eigenmann \
		Kaufman \
		Nolot \
		Null-Move \
		Silent-but-Deadly \
		Strategic \
		Win-at-Chess



####### Compiler, tools and options

DEL_FILE      = rm -f
COPY          = cp -f
COPY_FILE     = cp -f
COPY_DIR      = cp -f -R
MOVE          = mv -f
TAR           = tar -cf
COMPRESS      = gzip -9f

first: FORCE all

FORCE:

####### Build rules

all: FORCE
	$(MAKE) Bratko-Kopec
	$(MAKE) CCR
	$(MAKE) Eigenmann
	$(MAKE) Kaufman
	$(MAKE) Nolot
	$(MAKE) Null-Move
	$(MAKE) Silent-but-Deadly
	$(MAKE) Strategic
	$(MAKE) Win-at-Chess

Bratko-Kopec: FORCE
	@cd Bratko-Kopec && $(MAKE) -f Makefile

CCR: FORCE
	@cd CCR && $(MAKE) -f Makefile

Eigenmann: FORCE
	@cd Eigenmann && $(MAKE) -f Makefile

Kaufman: FORCE
	@cd Kaufman && $(MAKE) -f Makefile

Nolot: FORCE
	@cd Nolot && $(MAKE) -f Makefile

Null-Move: FORCE
	@cd Null-Move && $(MAKE) -f Makefile

Silent-but-Deadly: FORCE
	@cd Silent-but-Deadly && $(MAKE) -f Makefile

Strategic: FORCE
	@cd Strategic && $(MAKE) -f Makefile

Win-at-Chess: FORCE
	@cd Win-at-Chess && $(MAKE) -f Makefile


# clean targets
clean: FORCE Bratko-Kopec-clean \
		CCR-clean \
		Eigenmann-clean \
		Kaufman-clean \
		Nolot-clean \
		Null-Move-clean \
		Silent-but-Deadly-clean \
		Strategic-clean \
		Win-at-Chess-clean

Bratko-Kopec-clean: FORCE
	@cd Bratko-Kopec && $(MAKE) -f Makefile clean

CCR-clean: FORCE
	@cd CCR && $(MAKE) -f Makefile clean

Eigenmann-clean: FORCE
	@cd Eigenmann && $(MAKE) -f Makefile clean

Kaufman-clean: FORCE
	@cd Kaufman && $(MAKE) -f Makefile clean

Nolot-clean: FORCE
	@cd Nolot && $(MAKE) -f Makefile clean

Null-Move-clean: FORCE
	@cd Null-Move && $(MAKE) -f Makefile clean

Silent-but-Deadly-clean: FORCE
	@cd Silent-but-Deadly && $(MAKE) -f Makefile clean

Strategic-clean: FORCE
	@cd Strategic && $(MAKE) -f Makefile clean

Win-at-Chess-clean: FORCE
	@cd Win-at-Chess && $(MAKE) -f Makefile clean

