#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <ncurses.h>



int main() 
{
    char fcontent[100];
    char tmp[12];
    int fd1, fd2;
    int x;
    
    int row, col;


    char mesg[]="Odebrano: ";
    char mesg2[]="Wysylam... ";
    char mesg3[]="SERWER";

    initscr();
    start_color();

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    
    refresh();
    
    attron(COLOR_PAIR(2) | A_BOLD);
    mvprintw(0, 0, "%s", mesg3);
    refresh();
    attroff(COLOR_PAIR(2) | A_BOLD);
        
    attron(COLOR_PAIR(1));
    getmaxyx(stdscr, row, col);

    mkfifo("fifo1", 0600);
    mkfifo("fifo2", 0600);
    fd1 = open("fifo1", O_RDONLY);
    fd2 = open("fifo2", O_WRONLY);

    while (1) {
        read(fd1, fcontent, 100);
        if (strcmp("",fcontent)!=0){
            mvprintw(row/2-1, ((col-strlen(mesg))/2 - 10), "%s%s\n", mesg, fcontent);
            refresh();

            x = strlen(fcontent);
            sprintf(tmp, "%d", x);

            mvprintw(row/2+3, ((col-strlen(mesg2))/2 - 10), "%s\n", mesg2);
            refresh();
            write(fd2, tmp, strlen(tmp));
        }
        memset(fcontent, 0, sizeof(fcontent));

    }
    attroff(COLOR_PAIR(1));
    refresh();
    getch();
    endwin();
    close(fd1);
    close(fd2);
}