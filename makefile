# ----------------------------
# Makefile Options
# ----------------------------

NAME ?= DRAGON
ICON ?= icon.png
DESCRIPTION ?= "A virtual dragon -- (C)Privacy_Dragon"
COMPRESSED ?= YES
ARCHIVED ?= YES

CFLAGS ?= -Wall -Wextra -Oz
CXXFLAGS ?= -Wall -Wextra -Oz

# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/meta/makefile.mk
