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

SRC_SERVER 				=	server.c

SRC_SOCKETS 			=	sockets_tools.c

SRC_AUTH 				=	login.c

SRC_LOGGER 				=	logger.c

SRC_FS					=	home.c

SRC						= 	$(addprefix src/, $(SRC_FTP))						\
							$(addprefix src/server/, $(SRC_SERVER))				\
							$(addprefix src/sockets/, $(SRC_SOCKETS))			\
							$(addprefix src/auth/, $(SRC_AUTH))					\
							$(addprefix src/logger/, $(SRC_LOGGER))				\
							$(addprefix src/filesystem/, $(SRC_FS))

MAIN 					=	main.c

OBJ						=	$(SRC:.c=.o)	\
							$(addprefix src/, $(MAIN:.c=.o))

TESTS						=	tests/test.c

OBJ_TESTS				=	$(SRC:.c=.o)

NAME					=	myftp

CPPFLAGS				=	-I ./include -g

all:	$(NAME)

PREBUILD:
	@echo -e "\x1b[92mCompiling sources : \x1b[34m$(NAME)\x1b[5m . \x1b[0m\x1b[5m . \
	\x1b[34m . \x1b[0m"

$(NAME):	PREBUILD $(OBJ)
	@echo -e "\x1b[92mBuilding sources : \x1b[34m$(NAME)\x1b[5m . \x1b[0m\x1b[5m . \
	\x1b[34m . \x1b[0m"
	@$(CC) -o $(NAME) $(OBJ) $(CPPFLAGS)
	@echo -e "\x1b[92m\x1b[1mBuild successfull !\x1b[0m"

clean:
	@echo -e "\x1b[95mCleaning sources : \x1b[34m$(NAME)\x1b[0m"
	@rm -f $(OBJ)
	@rm -f unit*

fclean:	clean
	@rm -f $(NAME)

re:	fclean all

tests_run:  fclean $(OBJ_TESTS)
	$(CC) -o unit_tests $(OBJ_TESTS) $(TESTS) $(CPPFLAGS) -lcriterion --coverage
	./unit_tests

.PHONY	=	all re fclean clean tests_run
