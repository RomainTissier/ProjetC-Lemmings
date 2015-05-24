project: button.o pinguin.o graphiccomponent.o collisiondetection.o mainmenu.o levelsmenu.o board.o render.o main.o
	gcc -g -c button.c
	gcc -g -c pinguin.c
	gcc -g -c graphiccomponent.c
	gcc -g -c collisiondetection.c
	gcc -g -c mainmenu.c
	gcc -g -c levelsmenu.c
	gcc -g -c board.c
	gcc -g -c render.c
	gcc -g -c main.c
	gcc -g button.o pinguin.o graphiccomponent.o collisiondetection.o mainmenu.o levelsmenu.o board.o render.o main.o -o project -lSDL2 -lSDL2_image -Wall -Wextra -Werror
clean: 
	rm *.o project