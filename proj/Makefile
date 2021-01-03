PROG=proj

SRCS = proj.c utilities.c sprite.c entities.c gameLogic.c drivers.c game.c menu.c 
SRCS += communication.c scoreboard.c
.PATH: ${.CURDIR}/libs
SRCS += kbc.c keyboard.c video.c timer.c mouse.c uart.c rtc.c 

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
