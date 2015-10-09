#ifndef PRODOS_H
#define PRODOS_H

#include <stdbool.h>    /* bool */

/* C99 specifies that char can be either signed or unsigned. In cc65 it is
   unsigned. This can be tested by checking if CHAR_MIN is either negative
   or zero. 
   
   With cc65 an 8-bit byte is represented by a char. The 6502 is byte-
   addressable, so a memory address is represented by a char pointer
   (char *) which is a 16-bit value. */

#define INPBUF  ((char *) 0x0200)
#define DOSCMD  0xBE03
/* #define PRERR   0xBE0C */
#define PRERR   0xFF2D
#define COUT    0xFDED

#define KBD     ((char *) 0xC000)
#define KBDSTRB 0xC010
#define VECTOUT ((char **) 0xbe30)
#define VECTIN  ((char **) 0xbe32)

#define KBDSTRB_ON()    (*KBDSTRB & '\x80')
#define SET_KBDSTRB()   *KBDSTRB |= '\x80'
#define CLR_KBDSTRB()   

extern bool run_basic_system_command(const char *command);

#endif

