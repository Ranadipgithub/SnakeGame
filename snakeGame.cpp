#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
const int width=80;
const int height=20;
int x,y;
int fruitx,fruity;
int score;
int stailx[100],staily[100];
int slen;
enum dirn{STOP=0, LEFT, RIGHT, UP, DOWN};
dirn sdir;
bool isOver;
void GameInit(){
    isOver=false;
    sdir=STOP;
    x=width/2;
    y=height/2;
    fruitx=rand()%width;
    fruity=rand()%height;
    score=0;
}
void gameRender(string name){
    system("cls");
    for(int i=0;i<width+2;i++) cout<<"-";
    cout<<endl;
    for(int i=0;i<height;i++){
        for(int j=0;j<=width;j++){
            if(j==0 || j==width) cout<<"|";
            if(i==y && j==x) cout<<"o";
            else if(j==fruitx && i==fruity) cout<<"#";
            else{
                bool fg=false;
                for(int k=0;k<slen;k++){
                    if(stailx[k]==j && staily[k]==i){
                        cout<<"o";
                        fg=true;
                    }
                }
                if(!fg) cout<<" ";
            }
        }
        cout<<endl;
    }
    for(int i=0;i<width+2;i++) cout<<"-";
    cout<<endl;
    cout<<name<<"'s Score: "<<score<<endl;
}
void updateGame(){
    int prevx=stailx[0];
    int prevy=staily[0];
    int prev2x,prev2y;
    stailx[0]=x;
    staily[0]=y;
    for(int i=1;i<slen;i++){
        prev2x=stailx[i];
        prev2y=staily[i];
        stailx[i]=prevx;
        staily[i]=prevy;
        prevx=prev2x;
        prevy=prev2y;
    }
    switch(sdir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;    
    }
    if(x>=width || x<0 || y>=height || y<0) isOver=true;
    for(int i=0;i<slen;i++){
        if(x==stailx[i] && y==staily[i]) isOver=true;
    }
    if(x==fruitx && y==fruity){
        score++;
        fruitx=rand()%width;
        fruity=rand()%height;
        slen++;
    }
}
void userInput(){
    if(_kbhit()){
        switch(_getch()){
            case 'a':
                sdir=LEFT;
                break;
            case 'd':
                sdir=RIGHT;
                break;
            case 'w':
                sdir=UP;
                break;
            case 'x':
                sdir=DOWN;
                break;
            case 's':
                sdir=STOP;
                isOver=true;
                break;
        }
    }
}
int main(){
    string name;
    cout<<"Enter your name: ";
    cin>>name;
    GameInit();
    while(!isOver){
        gameRender(name);
        userInput();
        updateGame();
        Sleep(2000);
    }
    return 0;
}