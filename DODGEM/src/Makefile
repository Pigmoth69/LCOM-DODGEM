COMPILER_TYPE = gnu

CC = gcc

PROG = DODGEM
SRCS = main.c
SRCS += graphics.c utilities.c vbe.c keyboard.c read_xpm.c sprite.c timer.c vbe.c video_gr.c bitmap.c

CCFLAGS= -Wall -O3

DPADD += ${LIBDRIVER} ${LIBSYS}
LDADD += -llm -ldriver -lsys

LDFLAGS += -L.

MAN=
BINDIR? = /usr/sbin

.include <bsd.prog.mk>
.include <bsd.gcc.mk>