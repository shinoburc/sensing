################################################################
#
# Makefile
#
# - search recursively the source file
#
#
################################################################
#---------------------------------------------------------------
# User setting
#---------------------------------------------------------------

TARGET   = rotaryencoder
INCLUDES =
LDFLAGS  = -lwiringPi
NOMAKEDIR= .git% dictionary% doc% test% html% build%
OBJDIR = objs

#---------------------------------------------------------------
# Don't change the following
#---------------------------------------------------------------

GCC = gcc
#CFLAGS = -O2 -MMD -MP -Wall -Wextra
CFLAGS = -O3 -Wall -pthread -Wno-deprecated

CPPS = $(shell find * -name '*.c')
SRCS = $(filter-out $(NOMAKEDIR), $(CPPS))
DIRS = $(dir $(SRCS))
BINDIRS = $(addprefix $(OBJDIR)/, $(DIRS))

OBJS = $(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(SRCS))) # patsubstは空白で区切られたものか指定の文字列に置換
DEPS = $(OBJS:.o=.d)
TILS = $(patsubst %.c, %.c~, $(SRCS))

ifeq "$(strip $(OBJDIR))" ""
  OBJDIR = .
endif

ifeq "$(strip $(DIRS))" ""
  OBJDIR = .
endif

default:
	@[ -d  $(OBJDIR)   ] || mkdir -p $(OBJDIR)
	@[ -d "$(BINDIRS)" ] || mkdir -p $(BINDIRS)
	@make all --no-print-directory
#	./$(TARGET)

all : $(OBJS) $(TARGET)

$(TARGET): $(OBJS) $(LIBS)
	$(GCC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	$(GCC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

clean:
	@rm -rf $(TARGET) $(TILS) $(OBJDIR)

-include $(DEPS)

doxygen:
	@doxygen
