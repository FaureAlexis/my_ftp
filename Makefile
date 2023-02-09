##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

ifndef VERBOSE
.SILENT:
endif

SRC_FTP					=	ftp.c

SRC						= 	$(addprefix src/, $(SRC_FTP))						\

MAIN 					=	main.c

OBJ						=	$(SRC:.c=.o)	\
							$(addprefix src/, $(MAIN:.c=.o))

TESTS						=	tests/test.c

OBJ_TESTS				=	$(SRC:.c=.o)

NAME					=	myftp

CPPFLAGS				=	-I ./include -g

all:	$(NAME)

PREBUILD:
	@echo -e "\e[92mCompiling sources : \e[34m$(NAME)\e[5m . \e[0m\e[5m . \
	\e[34m . \e[0m"

$(NAME):	PREBUILD $(OBJ)
	@echo -e "\e[92mBuilding sources : \e[34m$(NAME)\e[5m . \e[0m\e[5m . \
	\e[34m . \e[0m"
	@$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS)
	@echo -e "\e[92m\e[1mBuild successfull !\e[0m"

clean:
	@echo -e "\e[95mCleaning sources : \e[34m$(NAME)\e[0m"
	@rm -f $(OBJ)
	@rm -f unit*

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

tests_run:  fclean $(OBJ_TESTS)
	$(CC) -o unit_tests $(OBJ_TESTS) $(TESTS) $(CPPFLAGS) -lcriterion --coverage
	./unit_tests

.PHONY	=	all re fclean clean tests_run
