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

SRC_COMMANDS			=	pwd.c				\
							cwd.c				\
							ls.c				\
							cdup.c				\

SRC						= 	$(addprefix src/, $(SRC_FTP))						\
							$(addprefix src/server/, $(SRC_SERVER))				\
							$(addprefix src/sockets/, $(SRC_SOCKETS))			\
							$(addprefix src/auth/, $(SRC_AUTH))					\
							$(addprefix src/logger/, $(SRC_LOGGER))				\
							$(addprefix src/filesystem/, $(SRC_FS))				\
							$(addprefix src/commands/, $(SRC_COMMANDS))

MAIN 					=	main.c

OBJ						=	$(SRC:.c=.o)	\
							$(addprefix src/, $(MAIN:.c=.o))

TESTS						=	tests/test.c							\
								tests/commands/test_pwd.c				\
								tests/commands/test_cwd.c				\
								tests/commands/test_ls.c				\
								tests/commands/test_cdup.c				\
								tests/sockets/test_socket_tools.c		\
								tests/fs/test_home.c					\
								tests/fs/test_home_functions.c 			\
								tests/logger/test_logger.c				\
								tests/logger/test_logger_except.c		\
								tests/ftp/test_ftp.c					\
								tests/ftp/test_free.c					\
								tests/ftp/test_signal.c					\

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

tests_run:  fclean PREBUILD $(OBJ_TESTS)
	$(CC) -o unit_tests $(SRC) $(TESTS) $(CPPFLAGS) -lcriterion --coverage
	./unit_tests

.PHONY	=	all re fclean clean tests_run
