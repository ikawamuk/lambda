NAME		=	lambda
TESTNAME	=	run_test.sh
CC			=	cc
RM			=	rm
CFLAGS		=	-Wall -Wextra -Werror -I$(INCDIR)

SRCS		=	main.c \
				$(shell find $(SRCDIR) -type f -name "*.c")

OBJS		=	$(patsubst %.c, $(OBJDIR)/%.o, $(SRCS))
SRCDIR		=	src
INCDIR		=	include
OBJDIR		=	obj
TESTDIR		=	test

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

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
