# ----------------------------
# Makefile Options
# ----------------------------

NAME = DEMO
ICON = icon.png
DESCRIPTION = "Stack Game"
COMPRESSED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
