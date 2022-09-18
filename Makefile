################################################################################
################################ COMPILER & FLAGS ##############################
################################################################################

CC =		gcc

CFLAGS =	-Wall -Wextra -Werror 

DEBUG =		-Wall -Wextra -Werror -ggdb3

VAL =		valgrind -s --track-fds=yes --track-origins=yes --leak-check=full --leak-check=full --show-leak-kinds=all --show-reachable=no# #

################################################################################
################################## DIRECTORIES #################################
################################################################################

HEADER = 	./header

OBJDIR =	 build/

LIBDIR = 	./libft

SRCDIR =	./src/

PARSER =	$(SRCDIR)parser/

EXECUTER =	$(SRCDIR)execute/

BUILTINS =	$(SRCDIR)built_ins/

SIGNALS =	$(SRCDIR)signals/

################################################################################
################################### LIBRARIES ##################################
################################################################################

FT_INC	= 		-I ../../libft/header

LIBFT = 		$(LIBDIR)/libft.a

READLINE =		-lreadline

LIBRARIES = 		$(LIBFT) $(READLINE)

INCLUDES = 		$(FT_INC)

################################################################################
################################## SRCS & OBJS #################################
################################################################################

SRCS	=	$(SRCDIR)minishell.c			\
			$(SRCDIR)ms_def.c				\
			$(SRCDIR)ms_extra.c				\
			$(SRCDIR)ms_utils.c				\
			$(SRCDIR)ms_cleanup.c			\
			$(SIGNALS)ms_signals.c			\
			$(PARSER)ms_parser.c			\
			$(PARSER)ms_lexer.c				\
			$(PARSER)ms_error_check.c		\
			$(PARSER)ms_token.c				\
			$(PARSER)ms_other_checks.c		\
			$(PARSER)ms_pipe_utils.c		\
			$(PARSER)ms_quotes.c			\
			$(PARSER)ms_quotes_utils.c			\
			$(EXECUTER)ms_exec.c			\
			$(EXECUTER)ms_exec_aux.c		\
			$(EXECUTER)ms_exec_set_io.c		\
			$(EXECUTER)ms_exec_setup.c		\
			$(EXECUTER)ms_exec_pipeline.c	\
			$(EXECUTER)ms_heredoc.c			\
			$(BUILTINS)errors.c				\
			$(BUILTINS)builtins.c			\
			$(BUILTINS)env.c				\
			$(BUILTINS)export.c				\
			$(BUILTINS)export_utils.c		\
			$(BUILTINS)cd.c					\
			$(BUILTINS)cd_utils.c			\
			$(BUILTINS)unset.c				\
			$(BUILTINS)pwd.c				\
			$(BUILTINS)exit.c				\
			$(BUILTINS)echo.c				\
			
################################################################################
#################################### PROGRAM ###################################
################################################################################

EXEC =		minishell

RUN =		./minishell

################################################################################
################################### COLOURS ####################################
################################################################################

GREEN = 	\033[0;32m

RED =		\033[0;31m

RESET = 	\033[0m

################################################################################
#################################### RULES #####################################
################################################################################

$(EXEC): $(LIBFT) $(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) $(LIBRARIES) -I $(HEADER) -o $(EXEC)
	@echo "---------------------------------------------------"
	@echo "|                                                 |"
	@echo "|   $(EXEC)               $(GREEN)EXECUTABLE CREATED!$(RESET)   |"
	@echo "|                                                 |"
	@echo "---------------------------------------------------"

debug: re $(LIBFT)
	@$(CC) $(DEBUG) $(SRCS) $(LIBRARIES) -I $(HEADER) -o $(EXEC)

$(LIBFT):
	@$(MAKE) all -C $(LIBDIR)

all: $(EXEC) 

built_ins: $(LIBFT)
	$(CC) $(CFLAGS) ./src/built_ins/env.c $(LIBRARIES) -I $(HEADER) -o $(EXEC)
bonus: all

clean:
	@$(MAKE) clean -C $(LIBDIR)

fclean: clean
	@$(MAKE) fclean -C $(LIBDIR)
	@rm -f $(EXEC)

re: fclean all

run: re
	$(RUN)

test: fclean debug
	$(VAL) $(RUN)
