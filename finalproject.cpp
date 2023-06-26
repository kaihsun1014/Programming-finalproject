#include <iostream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include <time.h>
#include <ctime>
#include <cmath>
using namespace std;
const int x=29,y=75;
int blood=15;
int level=0;
int maxlevel=0;

void gotoxy(int xpos, int ypos)//go to (x,y)
{
  COORD scrn;
  HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
  scrn.X = xpos; scrn.Y = ypos;
  SetConsoleCursorPosition(hOuput,scrn);
}

void init(char a[x][y])//create&print the initial screen
{
	for(int index=0;index<x;index++)
	{
		a[index][0]='|';
		a[index][74]='|';
	}
	for(int index=0;index<y;index++)
	{
		a[0][index]='-';
		a[28][index]='-';
	}
	for(int i=1;i<=27;i++)
	{
		for(int j=1;j<=73;j++)
			a[i][j]=' ';
	}

	for(int i=0;i<29;i++)
	{
		for(int j=0;j<75;j++)
		{
			cout<<a[i][j];
		}
		cout<<"\n";
	}
	gotoxy(28,13);
	cout<<"press a to start";
	gotoxy(28,14);
	cout<<"press s to leave";

}

void Map(char a[x][y])//create & pring the initial map
{
	gotoxy(0,1);
	for(int index=0;index<29;index++)
	{
		a[index][0]='|';
		a[index][74]='|';
	}
	for(int index=0;index<75;index++)
	{
		a[0][index]='v';
		a[28][index]=' ';
	}
	for(int i=1;i<=27;i++)
	{
		for(int j=1;j<=73;j++)
			a[i][j]=' ';
	}
	a[0][0]='|';
	a[0][74]='|';

	for(int i=0;i<29;i++)
		{
			for(int j=0;j<75;j++)
			{
				cout<<a[i][j];
			}
			cout<<"\n";
		}
}

void map(char a[x][y])//create the map during gameset
{

	gotoxy(0,1);
	for(int index=0;index<29;index++)
	{
		a[index][0]='|';
		a[index][74]='|';
	}
	for(int index=0;index<75;index++)
	{
		a[0][index]='v';
	}
	for(int i=1;i<=28;i++)
	{
		for(int j=1;j<=73;j++)
		if((a[i][j]!='-')&&(a[i][j]!='=')&&(a[i][j]!='^')&&(a[i][j]!='<')&&(a[i][j]!='>')&&(a[i][j]!='Z'))
			a[i][j]=' ';
	}
	a[0][0]='|';
	a[0][74]='|';
}

void setplayer(char a[x][y], int posx, int posy)//set player
{
	map(a);
	a[posx][posy]='A';
	a[posx][posy+1]='_';
	a[posx][posy+2]='_';
	a[posx][posy+3]='_';
	a[posx][posy+4]='A';
	a[posx+1][posy]='|';
	a[posx+1][posy+1]='$';
	a[posx+1][posy+2]='w';
	a[posx+1][posy+3]='$';
	a[posx+1][posy+4]='|';
	a[posx+2][posy]='U';
	a[posx+2][posy+1]='*';
	a[posx+2][posy+2]='*';
	a[posx+2][posy+3]='*';
	a[posx+2][posy+4]='U';
	a[posx+3][posy]=' ';
	a[posx+3][posy+1]='@';
	a[posx+3][posy+2]=' ';
	a[posx+3][posy+3]='@';
	a[posx+3][posy+4]=' ';
	for(int i=0;i<29;i++)
		{
			for(int j=0;j<75;j++)
			{
				cout<<a[i][j];
			}
			cout<<"\n";
		}
}

void stair(char a[x][y], int x, int posx, int posy)//make stairs
{
    srand(time(0));
    int B=rand();
    int wide=rand();
    wide=wide%5+15;

    switch(B%7)
    {
        case 0:
        {
            for(int j=0;j<wide;j++)//once
            {
            	a[28][(x%66)+1+j]='-';
			}
			setplayer(a,posx,posy);
            break;
        }

    	case 1:
        {
            for(int j=0;j<wide;j++)//hurt
            {
            	a[28][(x%54)+1+j]='^';
			}
			setplayer(a,posx,posy);
            break;
        }

    	case 2:
    	{
    		for(int j=0;j<wide;j++)//left conveyor
            {
                a[28][(x%54)+1+j]='<';
			}
			setplayer(a,posx,posy);
            break;
		}
		case 3:
    	{
    		for(int j=0;j<wide;j++)//right conveyor
            {
            	a[28][(x%54)+1+j]='>';
			}
			setplayer(a,posx,posy);
            break;
		}

		case 4:
    	{
    		for(int j=0;j<wide;j++)//spring
            {
            	a[28][(x%54)+1+j]='Z';
			}
			setplayer(a,posx,posy);
            break;
		}

    	default:
        {
            for(int j=0;j<wide;j++)//stable
            {
            	a[28][(x%54)+1+j]='=';
			}
			setplayer(a,posx,posy);
            break;
        }
    }
}

void up(char a[x][y])//make stairs go up
{
	for(int i=2;i<29;i++)
	{
		for(int j=1;j<74;j++)
		{
			if(a[i][j]=='-'||a[i][j]=='='||a[i][j]=='^'||a[i][j]=='<'||a[i][j]=='>'||a[i][j]=='Z')
			{
				a[i-1][j]=a[i][j];
				a[i][j]=' ';
			}

		}
	}
	for(int j=1;j<74;j++)
	{
		a[1][j]=' ';
	}
	gotoxy(0,1);
	for(int i=0;i<29;i++)
	{
		for(int j=0;j<75;j++)
		{
			cout<<a[i][j];
		}
		cout<<"\n";
	}
}

void playermove(char a[x][y],int& posx,int& posy)//make player go down when it doesn't stand on the stair and go up when it stands on the stair
{
	if(posx!=1)
	{
		if(a[posx+4][posy]==' '&&a[posx+4][posy+1]==' '&&a[posx+4][posy+2]==' '&&a[posx+4][posy+3]==' '&&a[posx+4][posy+4]==' ')
		//fall
		{
			posx++;
		}

		if(a[posx+4][posy]=='='||a[posx+4][posy+1]=='='||a[posx+4][posy+2]=='='||a[posx+4][posy+3]=='='||a[posx+4][posy+4]=='=')
		//normal stair
    	{
    		posx--;
    	}

    	if(a[posx+4][posy]=='^'|| a[posx+4][posy+1]=='^'||a[posx+4][posy+2]=='^'||a[posx+4][posy+3]=='^'||a[posx+4][posy+4]=='^')
		//hurting stair
		{
        	if(a[posx+4][posy+1]=='^'||a[posx+4][posy+3]=='^')
			{
        		blood-=2;
        		Beep(300,200);
        		gotoxy(8+blood,0);
            	for(int i=0; i<15-blood; i++)
				{
        			cout<<' ';
        		}
        		gotoxy(0,1);
        	}
        	posx--;
    	}

    	if(a[posx+4][posy]=='-'||a[posx+4][posy+1]=='-'||a[posx+4][posy+2]=='-'||a[posx+4][posy+3]=='-'||a[posx+4][posy+4]=='-')
    	//let the once stair disappear
    	{
    		posx--;
    		for(int i=1;i<74;i++)
    		{
				a[posx+5][i]=' ';
			}
		}

		if(a[posx+4][posy]=='<'||a[posx+4][posy+1]=='<'||a[posx+4][posy+2]=='<'||a[posx+4][posy+3]=='<'||a[posx+4][posy+4]=='<')
		//convey to left
		{
			posx--;
			if(posy>=4)
			posy-=3;
		}

		if(a[posx+4][posy]=='>'||a[posx+4][posy+1]=='>'||a[posx+4][posy+2]=='>'||a[posx+4][posy+3]=='>'||a[posx+4][posy+4]=='>')
		//convey to right
		{
			posx--;
			if(posy<=69)
			posy+=3;
		}

		if(a[posx+4][posy]=='Z'||a[posx+4][posy+1]=='Z'||a[posx+4][posy+2]=='Z'||a[posx+4][posy+3]=='Z'||a[posx+4][posy+4]=='Z')
		//spring
		{
			Beep(1000,200);
			if(posx>6)
			{
				for(int i=1;i<74;i++)
    			{
					a[posx+4][i]=' ';
				}
				posx-=6;
			}
    		else
    		{
    			for(int i=1;i<74;i++)
    			{
					a[posx+4][i]=' ';
				}
    			posx=1;
			}
		}
	}
	else
	{
		if(posx==1)
		//if touch the ceilng, minus 4 blood and clean the stair below the player
		{
        	blood-=4;
        	Beep(300,200);
        	gotoxy(8+blood,0);
        	for(int i=0; i<15-blood; i++)
			{
        		cout<<' ';
        	}
        	for(int i=1;i<74;i++)
    		{
				a[posx+4][i]=' ';
			}
        	gotoxy(0,1);
			posx++;
       	}

       	if((posx<8)&&(a[posx+4][posy]=='Z'||a[posx+4][posy+1]=='Z'||a[posx+4][posy+2]=='Z'||a[posx+4][posy+3]=='Z'||a[posx+4][posy+4]=='Z'))
		//if touch the spring and the position is too high, minus 4 blood and clean the spring below the player
		{
        	blood-=4;
        	Beep(300,200);
        	gotoxy(8+blood,0);
        	for(int i=0; i<15-blood; i++)
			{
        		cout<<' ';
        	}
        	gotoxy(0,1);
        	posx+=6;
       	}

	}
}

void Level(char a[x][y], int& posx, int& posy)//count the level
{
    if(a[posx+4][posy]!=' '||a[posx+4][posy+1]!=' '||a[posx+4][posy+2]!=' '||a[posx+4][posy+3]!=' '||a[posx+4][posy+4]!=' ')
        level++;
    if(level%4==0&&level!=0&&(a[posx+4][posy]!=' '||a[posx+4][posy+1]!=' '||a[posx+4][posy+2]!=' '||a[posx+4][posy+3]!=' '||a[posx+4][posy+4]!=' '))
    	Beep(400,100);
}

void endgame(char a[x][y])//ask if restart of not
{
	for(int index=0;index<x;index++)
	{
		a[index][0]='|';
		a[index][74]='|';
	}
	for(int index=0;index<y;index++)
	{
		a[0][index]='-';
		a[28][index]='-';
	}
	for(int i=1;i<=27;i++)
	{
		for(int j=1;j<=73;j++)
			a[i][j]=' ';
	}

	for(int i=0;i<29;i++)
	{
		for(int j=0;j<75;j++)
		{
			cout<<a[i][j];
		}
		cout<<"\n";
	}
	gotoxy(33,13);
	cout<<"You Lose";
	gotoxy(28,15);
	cout<<"press a to restart";
	gotoxy(29,16);
	cout<<"press s to leave";

}

int main()
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle, &CursorInfo);//clear cursor

    int S=0;
    char a[29][75];

    init(a);//print the initial screen

    char c=getch();
    switch(c)//choose to start or to leave
    {
    	case 'a'://start
    	{
    		system("cls");
    		for(int index=0;index<x;index++)
			{
				a[index][0]='|';
				a[index][74]='|';
			}
			for(int index=0;index<y;index++)
			{
				a[0][index]='-';
				a[28][index]='-';
			}
			for(int i=1;i<=27;i++)
			{
				for(int j=1;j<=73;j++)
					a[i][j]=' ';
			}
			gotoxy(0,1);
			for(int i=0;i<29;i++)
			{
				for(int j=0;j<75;j++)
				{
					cout<<a[i][j];
				}
				cout<<"\n";
			}
			gotoxy(27,14);
    		cout<<"Game start! Have fun!";
    		Beep(392,200);
    		Beep(523.25,200);
    		Beep(392,200);
    		Beep(523.25,200);
    		Sleep(2000);
    		system("cls");

			int posx=12, posy=35;//set player to the initial position
			Map(a);
			for(int i=30;i<=45;i++)
				a[27][i]='=';//make the initial stair
			setplayer(a,posx,posy);
			int i=0;
			gotoxy(1,0);
       	 	cout<<"Blood: ";
    		while(true)
			{
				gotoxy(76,11);
				cout<<"z : move left";
				gotoxy(76,12);
				cout<<"x : move right";
				gotoxy(76,13);
				cout<<"q : quit the game";
				gotoxy(76,15);
				cout<<"=== : stable stair";
				gotoxy(76,16);
				cout<<"--- : once stair";
				gotoxy(76,17);
				cout<<"^^^ : hurt stair";
				gotoxy(76,18);
				cout<<"<<< : left conveyor";
				gotoxy(76,19);
				cout<<">>> : right conveyor";
				gotoxy(76,20);
				cout<<"ZZZ : spring";//print the tips

    	        gotoxy(8,0);
				for(int b=0; b<blood; b++)//print blood
				{
        	        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
            	    cout<<'*';
          		    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            	}
        	    Level(a, posx, posy);
        	   	gotoxy(32,0);
    	        cout<<"LEVEL: ";  //print level
    	        if((level==maxlevel*4+1||level==maxlevel*4+3)&&maxlevel!=0) //shining and make a sound when level over makelevel
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                    cout<<level/4;
                    Beep(902.6,200);
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                    continue;
    	        }
				else
                    cout<<level/4;

       	    	gotoxy(57,0);
         		cout<<"Best Record: "<<maxlevel;  //best record
            	gotoxy(0,1);

            	int stairx=rand();
            	if(kbhit())
            	{
           			char g=getch();
					switch(g)
					{
						case 'z'://move left
							if((posy-4)>0)
							posy-=4;
							break;
						case 'x'://move right
							if((posy+4)<71)
						    posy+=4;
							break;
						case 'q'://leave
   		 					system("cls");
   		 					cout<<"Goodbye!";
    						return 0;
					}
					setplayer(a,posx,posy);
        	   	}

           		if(blood<15&&i%3==0)//plus one blood every three seconds
               		    blood++;
           			i++;
          		  	if(i%6==0)
            		{
           		 		stair(a,stairx,posx,posy);//make stairs
					}
    	           	playermove(a,posx,posy);//make player move
					up(a);//make stairs go up
    	           	setplayer(a,posx,posy);


        		if(posx==25||blood<=0)//end game if touch the floor or blood smaller than zero
       			{
       				Beep(166*2,200);
       				Beep(156*2,200);
       				Beep(147*2,200);
       				Beep(139*2,200);
       				Sleep(1000);
       				gotoxy(8,0);
          			cout<<"               ";//clean the blood
           	    	gotoxy(0,30);
            	   	if(level/4>maxlevel)
            	   	{
       					for(int index=0;index<x;index++)
						{
							a[index][0]='|';
							a[index][74]='|';
						}
						for(int index=0;index<y;index++)
						{
							a[0][index]='-';
							a[28][index]='-';
						}
						for(int i=1;i<=27;i++)
						{
							for(int j=1;j<=73;j++)
							a[i][j]=' ';
						}
						gotoxy(0,1);
						for(int i=0;i<29;i++)
						{
							for(int j=0;j<75;j++)
							{
								cout<<a[i][j];
							}
							cout<<"\n";
						}
						gotoxy(29,15);
    					cout<<"Best record!!";
    					Sleep(2000);
						maxlevel=level/4;
					}
            	  		
            	  	gotoxy(57,0);
         			cout<<"Best Record: "<<maxlevel;  //best record
            		gotoxy(0,1);
            	   	level=0;   //clean the level
            	   	Sleep(500);
            	   	
            	   	gotoxy(0,1);  //print the gameover screen
            	   	endgame(a);
       				while(true)
					{
						char g=getch();
						if(g=='a')//restart
       					{
       						system("cls");
       						for(int index=0;index<x;index++)
							{
								a[index][0]='|';
								a[index][74]='|';
							}
							for(int index=0;index<y;index++)
							{
								a[0][index]='-';
								a[28][index]='-';
							}
							for(int i=1;i<=27;i++)
							{
								for(int j=1;j<=73;j++)
								a[i][j]=' ';
							}
							gotoxy(0,1);
							for(int i=0;i<29;i++)
							{
								for(int j=0;j<75;j++)
								{
									cout<<a[i][j];
								}
								cout<<"\n";
							}
							gotoxy(27,14);
    						cout<<"Game start! Have fun!";
    						Beep(392,200);
    						Beep(523.25,200);
    						Beep(392,200);
    						Beep(523.25,200);
    						Sleep(2000);
       						system("cls");
							posx=12;
							posy=35;//set player to the initial position
							Map(a);
							setplayer(a,posx,posy);
							gotoxy(0,0);
							blood=15;
							for(int i=30;i<=45;i++)
								a[27][i]='=';
							cout<<"Blood: ";
							int i=0;
							break;
						}
						if(g=='s' || g=='q')//leave
						{
							system("cls");
							cout<<"Goodbye!";
							return 0;
						}
						if(g!='a'&&g!='s'&&g!='q')//prevent someone pressing other bottoms
						{
							gotoxy(0,1);
							endgame(a);
						}
					}
				}
    		}
    		break;
    	}

    	case 's'://leave
    	{
    		system("cls");
    		cout<<"good bye!";
    		return 0;
    	}
	}
}