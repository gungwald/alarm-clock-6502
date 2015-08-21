# Builds the Alarm Clock app
#

# Requirements:
# 1. Gmake must be used.
# 2. The cc65 compiler must be properly setup. See setup-cc65.
#

ifndef CC65_TARGET
	CC65_TARGET:=apple2enh
endif

PGM=alarmclk
OBJS=alarmclk.o 12hourclk.o clkfreq.o

PGM2=cpufreq
OBJS2=clkfreq.o

CC=cl65
AS=ca65

CFLAGS=-t $(CC65_TARGET) -O
ASFLAGS=-t $(CC65_TARGET)
LDFLAGS=-t $(CC65_TARGET)

DISK_VOL=ALARMCLK
DISK=$(DISK_VOL).dsk

AC=java -jar lib/AppleCommander-1.3.5.14.jar
MKDISK=$(AC) -pro140 $(DISK) $(DISK_VOL)

########################################

all: $(DISK)

$(DISK): $(PGM) $(PGM2)
	$(AC) -d $(DISK) $<
	$(AC) -cc65 $(DISK) $< BIN < $<

$(PGM): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(PGM2): clkfreq.s
	$(AS) $(ASFLAGS) -o $@ $^

# Compile and assemble rules use the defuault rules after CC and CFLAGS
# are set.

clean:
	$(RM) $(PGM) $(PGM2) *.o

