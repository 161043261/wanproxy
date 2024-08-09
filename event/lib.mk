VPATH+=	${TOPDIR}/event

SRCS+=	event_system.cc
SRCS+=	io_service.cc

ifndef USE_POLL
ifeq "${OSNAME}" "Linux"
USE_POLL=	epoll
endif

ifndef USE_POLL
USE_POLL=	poll
endif
endif

ifeq "${OSNAME}" "Linux"
# Required for clock_gettime(3).
LDADD+=		-lrt
endif

SRCS+=	event_poll_${USE_POLL}.cc
