NAME:= minishell
EXE := minishell
src = lxr.c pars.c main.c syntax_error.c expand.c leacks_cheker_ex.c execution.c lexer_utils.c signals.c 
OBJ = $(src:.c=.o)
INC_DIR := include
CC := cc
LDFLAGS ?= -lreadline -L/usr/local/opt/readline/lib #-fsanitize=address
CFLAGS ?=  -I$(INC_DIR) -I/usr/local/opt/readline/include #-fsanitize=address

all : $(NAME)

$(NAME): minishell
HEADERS := 	$(INC_DIR)/minishell.h\

%.o: %.c $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

OBJS := $(src:.c=.o)

minishell : $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(EXE) -lreadline

clean:
		rm -rf $(OBJ)

fclean:	clean
		rm -rf $(NAME)

re:		fclean all
