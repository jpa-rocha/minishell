################################################################################
################################ COMPILER & FLAGS ##############################
################################################################################

CC =		gcc

CFLAGS =	-Wall -Wextra -Werror -c

DEBUG =		-Wall -Wextra -Werror -g -c

VAL =		valgrind -s --leak-check=full --show-leak-kinds=all

################################################################################
################################## DIRECTORIES #################################
################################################################################

HEADER = 	./header

OBJDIR =	 build/

SRCDIR =	src/

################################################################################
################################### LIBRARIES ##################################
################################################################################

FT_INC	= 	 -I./header

NAME	=	libft.a

################################################################################
################################## SRCS & OBJS #################################
################################################################################

SRCS :=		ft_isalpha.c		\
			ft_isdigit.c		\
			ft_isalnum.c		\
			ft_isascii.c		\
			ft_isprint.c		\
			ft_isplusminus.c	\
			ft_strlen.c		\
			ft_memset.c		\
			ft_bzero.c		\
			ft_memcpy.c		\
			ft_memmove.c		\
			ft_strlcpy.c		\
			ft_strlcat.c		\
			ft_toupper.c 		\
			ft_tolower.c 		\
			ft_strchr.c		\
			ft_strrchr.c 		\
			ft_strncmp.c 		\
			ft_memchr.c		\
			ft_memcmp.c		\
			ft_strnstr.c 		\
			ft_calloc.c		\
			ft_strdup.c		\
			ft_substr.c		\
			ft_strjoin.c		\
			ft_strtrim.c		\
			ft_split.c		\
			ft_itoa.c		\
			ft_strmapi.c		\
			ft_striteri.c		\
			ft_putchar_fd.c		\
			ft_putstr_fd.c		\
			ft_putendl_fd.c		\
			ft_putnbr_fd.c		\
			ft_revstring.c		\
			ft_digitcount.c		\
			ft_convert2hexa.c	\
			ft_convertfromhexa.c\
			ft_utoa.c		\
			ft_unsignedprinter.c	\
			ft_numberprinter.c	\
			ft_stringprinter.c	\
			ft_hexprinter.c		\
			ft_pointerprinter.c	\
			ft_percentprinter.c	\
			ft_printf.c		\
			ft_power.c		\
			get_next_line.c		\
			listdef.c		\
			listviews.c		\
			listops.c		\
			listpoints.c		\
			listutils.c		\
			matrixdef.c		\
			ft_atoi.c		\

OBJS :=		${SRCS:.c=.o}

OBJ_PREFIXED := $(addprefix $(OBJDIR), $(OBJS))

################################################################################
################################### COLOURS ####################################
################################################################################

GREEN = 	\033[0;32m

RED =		\033[0;31m

RESET = 	\033[0m

################################################################################
#################################### RULES #####################################
################################################################################
.SILENT: $(NAME) clean fclean

$(NAME): $(OBJ_PREFIXED)
	@ar -crs $@ $^ 

all: $(NAME)

$(OBJ_PREFIXED): build/%.o : src/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(DEBUG) $< -o $@ 

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)

re: fclean all

