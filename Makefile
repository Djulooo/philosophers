.PHONY:     			all $(NAME) clear mkbuild clear clean fclean re sanitize

NAME					= philo

BUILD_DIR				= build/
	
HEADER_DIR				= header/
HEADER_FILE				= philo.h

DIR						=	src/
SRC			 			= 	main.c	philo_atoi.c	init_thread.c	utils.c
							
OBJECTS			    	= $(SRC:%.c=$(BUILD_DIR)%.o)
	
CC						= cc
CFLAGS					= -Wall -Werror -Wextra
SANITIZE				= $(CFLAGS) -g3 -fsanitize=address

RM 						= rm -rf
CLEAR					= clear

$(BUILD_DIR)%.o:		$(DIR)%.c $(HEADER_DIR)/$(HEADER_FILE)
						@mkdir -p $(@D)
						$(CC) $(CFLAGS) -I$(HEADER_DIR) -I$(LIB_DIR) -I/usr/include -O3 -c $< -o $@

all: 					clear mkbuild $(HEADER_DIR) $(NAME) 
						
mkbuild:
						@mkdir -p build

clear:
						$(CLEAR)
						
$(NAME): 				$(OBJECTS)
						$(CC) $(OBJECTS) -o $(NAME)

sanit :					$(OBJECTS)
						$(CC) $(SANITIZE) $(OBJECTS) -o $(NAME)
						
clean:					
						@${RM} $(OBJECTS)
						@${RM} $(BUILD_DIR)

fclean:					clean
						@${RM} ${NAME}

re:						fclean all
						$(MAKE) all