PROG=proj

SRCS = proj.c kbc.c keyboard.c utils.c player.c video.c sprite.c timer.c mouse.c crosshair.c ball.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
