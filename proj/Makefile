PROG=proj

SRCS = proj.c kbc.c keyboard.c utilities.c video.c sprite.c timer.c mouse.c entities.c gameLogic.c drivers.c uart.c game.c menu.c rtc.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic #-D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
