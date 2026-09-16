NAME		=	lamda
TESTNAME	=	run_test.sh
CC			=	cc
RM			=	rm
CFLAGS		=	-Wall -Wextra -Werror -I$(INCDIR)

SRCS		=	main.c

OBJS		= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.c=.o)))
SRCDIR		=	src
INCLUDES	=	include
OBJDIR		=	obj
TESTDIR		=	test

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean
	$(MAKE) all

test: $(NAME)
	@chmod +x $(TESTDIR)/$(TESTNAME)
	@./$(TESTDIR)/$(TESTNAME)

.PHONY: all clean fclean re test
