# Builds the Alarm Clock app
#

# Requirements:
# 1. Gmake must be used.
# 2. The cc65 compiler must be properly setup. See setup-cc65.
#

ifndef CC65_TARGET
	CC65_TARGET:=apple2enh
endif

PGM=alarm.clock
OBJS=alarm.clock.o time.o noslotclock.o prodos.o trace.o

PGM2=calibrate
OBJS2=calibrate.o

CC=cl65
AS=ca65
LD=ld65

CFLAGS=-t $(CC65_TARGET) -O -DTRACE
ASFLAGS=-t $(CC65_TARGET)
LDFLAGS=-t $(CC65_TARGET)

DISK_VOL=ALARM.CLOCK
DISK=$(DISK_VOL).dsk

AC=java -jar lib/AppleCommander-1.3.5.14.jar
MKDISK=$(AC) -pro140 $(DISK) $(DISK_VOL)

########################################

all: $(PGM) $(PGM2)

$(PGM): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	$(AC) -d $(DISK) $@
	$(AC) -cc65 $(DISK) $@ BIN < $@

$(PGM2): $(OBJS2)
	$(CC) $(LDFLAGS) -o $@ $^
	$(AC) -d $(DISK) $@
	$(AC) -cc65 $(DISK) $@ BIN < $@

# Compile and assemble rules use the defuault rules after CC and CFLAGS
# are set.

clean:
	$(RM) $(PGM) $(PGM2) *.o

