#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

#define HEIGHT 30
#define WIDTH 20

typedef struct {
    int x;
    int y;
} Position;

void food_position(int *food_x,int *food_y);

int main(){

    int symbol,snake_length=3,GameRunning=1;
    int condition=0,n=0,loop_condition=1;
    int score=0;
    int speed=300;

    int ch;

    srand(time(NULL));

    int dx=0,dy=1;
    int new_dx=0,new_dy=0;
    int temp_x,temp_y;

    Position snake[HEIGHT*WIDTH];

    snake[0]=(Position){5,10};
    snake[1]=(Position){4,10};
    snake[2]=(Position){3,10};

    Position food={8,4};

    initscr();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr,TRUE);
    nodelay(stdscr,TRUE);

    while(GameRunning){

        temp_x=snake[snake_length+n-1].x;
        temp_y=snake[snake_length+n-1].y;

        new_dx=0;
        new_dy=0;

        ch=getch();

        switch(ch){
            case 'a':
            case KEY_LEFT:
                new_dy=-1;
                break;
            case 'd':
            case KEY_RIGHT:
                new_dy=1;
                break;
            case 'w':
            case KEY_UP:
                new_dx=-1;
                break;
            case 's':
            case KEY_DOWN:
                new_dx=1;
                break;
            case 'q':
                GameRunning=0;
                break;
        }

        if(!GameRunning)
            break;

        if(new_dx!=0 || new_dy!=0){
            if(dx*new_dx+dy*new_dy!=-1){
                dx=new_dx;
                dy=new_dy;
            }
        }

        for(int i=snake_length+n-1;i>0;i--){
            snake[i].x=snake[i-1].x;
            snake[i].y=snake[i-1].y;
        }

        snake[0].x+=dx;
        snake[0].y+=dy;

        if(snake[0].x<=1 || snake[0].x>=HEIGHT ||
           snake[0].y<=1 || snake[0].y>=WIDTH){
            break;
        }

        for(int k=1;k<snake_length+n;k++){
            if(snake[0].x==snake[k].x &&
               snake[0].y==snake[k].y){
                condition=1;
                break;
            }
        }

        if(condition)
            break;

        if(snake[0].x==food.x && snake[0].y==food.y){

            snake[snake_length+n].x=temp_x;
            snake[snake_length+n].y=temp_y;

            n++;
            score+=10;

            while(1){

                loop_condition=1;

                food_position(&food.x,&food.y);

                for(int k=0;k<snake_length+n;k++){
                    if(food.x==snake[k].x &&
                       food.y==snake[k].y){
                        loop_condition=0;
                        break;
                    }
                }

                if(loop_condition)
                    break;
            }
        }

        clear();

        for(int i=1;i<=HEIGHT;i++){
            for(int j=1;j<=WIDTH;j++){
                symbol=0;
                if(i==1 || i==HEIGHT || j==1 || j==WIDTH)
                    symbol=1;
                else if(i==food.x && j==food.y)
                    symbol=3;
                else{
                    for(int k=0;k<snake_length+n;k++){
                        if(i==snake[k].x && j==snake[k].y){
                            symbol=(k==0)?4:2;
                            break;
                        }
                    }
                }
                if(symbol==1)
                    mvaddch(i,j,'#');
                else if(symbol==2)
                    mvaddch(i,j,'o');
                else if(symbol==3)
                    mvaddch(i,j,'@');
                else if(symbol==4)
                    mvaddch(i,j,'G');
            }
        }

        mvprintw(HEIGHT+1,1,"Score: %d",score);
        mvprintw(HEIGHT+2,1,"WASD / Arrow Keys | Q to quit");

        refresh();

        napms(speed);
    }

    nodelay(stdscr,FALSE);

    clear();

    mvprintw(HEIGHT/2, WIDTH/2-5,"GAME OVER!");
    mvprintw(HEIGHT/2+1, WIDTH/2-5,"Score: %d",score);
    mvprintw(HEIGHT/2+3, WIDTH/2-8,"Press any key to exit");

    refresh();
    getch();

    endwin();

    printf("THE GAME HAS ENDED!!\n");

    return 0;
}

void food_position(int *food_x,int *food_y){
    *food_x=rand()%(HEIGHT-2)+2;
    *food_y=rand()%(WIDTH-2)+2;
}