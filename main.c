#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT 10
#define WIDTH 20

typedef struct {
    int x;
    int y;
} Position;

void food_position(int *food_x,int *food_y,int *var_len);

int main(){
    int symbol,snake_length=3,GameRunning=1,condition=0,n=0;
    char move;

    srand(time(NULL));

    int dx=0,dy=1;
    int new_dx=0,new_dy=0;

    Position snake[10];
    
    snake[0]=(Position){5,10};
    snake[1]=(Position){4,10};
    snake[2]=(Position){3,10};

    Position food={8,4};

    while(GameRunning){

        new_dx=0;new_dy=0;
        printf("Enter movement:\n");
        scanf(" %c",&move);
        getchar();

        switch(move){
            case 'a': new_dy=-1;break;
            case 'd': new_dy=1;break;
            case 'w': new_dx=-1;break;
            case 's': new_dx=1;break;
            // case 'p': printf("%d %d",food.x,food.y);break;
            case 'm': condition=1;break;
        }

        if (condition)
        break;

        if(move=='a'||move=='s'||move=='d'||move=='w'){
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

        if(snake[0].x==1||snake[0].x==HEIGHT||snake[0].y==1||snake[0].y==WIDTH){
            break;
        }
        for(int k=1;k<snake_length+n;k++){
            if(snake[0].x==snake[k].x&&snake[0].y==snake[k].y){
                condition=1;
                break;
            }
        }
        if(condition)
        break;

        if(snake[0].x==food.x&&snake[0].y==food.y){
            snake[snake_length+n].x=snake[snake_length+n-1].x;
            snake[snake_length+n].y=snake[snake_length+n-1].y;
            food_position(&food.x,&food.y,&n);
        }

        for(int i =1;i<=10;i++){
            for(int j=1;j<=WIDTH;j++){
                symbol=0;
                if(i==1 || i==HEIGHT || j==1 || j==WIDTH)
                symbol=1;
                else if(i==food.x&&j==food.y)
                symbol=3;
                else{
                    for(int k =0;k<snake_length+n;k++){
                        if(i==snake[0].x&& j==snake[0].y){
                        symbol =4;
                        break;}
                        if(i==snake[k+1].x&& j==snake[k+1].y){
                            symbol=2;
                            break;
                        }
                    }
                }
                if(symbol==1)
                printf("#");
                else if(symbol==2)
                printf("0");
                else if(symbol==3)
                printf("@");
                else if(symbol==4)
                printf("G");
                else
                printf(" ");
            }
            printf("\n");
        }
    }
    printf("THE GAME HAS ENDED!!");
}

void food_position(int *food_x,int *food_y,int *var_len){
    *food_x =rand() % (HEIGHT-2)+2;
    *food_y =rand() % (WIDTH-2)+2;
    (*var_len)++;
}