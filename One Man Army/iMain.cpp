

# include "iGraphics.h"
# include <stdlib.h>

int up_x[3], up_y[3], Lup_x[3], Lup_y[3] , Rup_x[3], Rup_y[3] , Player_x=480, Player_y=20, i, create, score, life;
int up_speed, rlup_speed, countUp, countRup, countLup;
char SCORE[100], LIFE[3];
int up[3], Lup[3], Rup[3];
int isPause, screen, flag;
int t1,t2,t3,t4, t5;
char str[100], str2[100], name[3][20], hscore[3][200];
int len, highscore[3], level;
int mode, hs=1;
FILE *input, *output;


//************* Enemy ***************

struct enemyNorm{
	int speed;
	int x;
	int y;
	int mark;
}e[120];

void enemyPreProcesslvl1()
{
	for(i=0; i<100; i++)
	{
		e[i].speed=(rand()%15)+10;
		e[i].x=rand()%928;
		e[i].y=500;
		e[i].mark=0;
	}
	e[0].mark=1;
	create=1;
	life=3;
	score=0;
	isPause=1;
	screen=1;
	level=1;
	iResumeTimer(t1);
	iResumeTimer(t2);
	iResumeTimer(t3);
	iResumeTimer(t4);
	countUp=0;
	countRup=0;
	countLup=0;
	input = fopen("Highscore.txt", "r");
	for(int j=0; j<3; j++)
	{
		fscanf(input,"%d %s", &highscore[j], name[j]);
		sprintf(hscore[j], "Name: %s Score: %d", name[j], highscore[j]);
	}
	fclose(input);
}

void enemyPreProcesslvl2()
{
	for(i=0; i<100; i++)
	{
		e[i].speed=(rand()%18)+20;
		e[i].x=rand()%928;
		e[i].y=500;
		e[i].mark=0;
	}
	e[0].mark=1;
	create=1;
	life++;
	isPause=1;
	screen=1;
	level=2;
	countUp=0;
	countRup=0;
	countLup=0;
}

void enemyPreProcesslvl3()
{
	for(i=0; i<100; i++)
	{
		e[i].speed=(rand()%25)+25;
		e[i].x=rand()%928;
		e[i].y=500;
		e[i].mark=0;
	}
	e[0].mark=1;
	create=1;
	life++;
	isPause=1;
	screen=1;
	level=3;
	countUp=0;
	countRup=0;
	countLup=0;
}

void enemyCreate()
{
	if(screen==1)
	{
		e[create].mark++;
		create++;
	}
}

void arcMove()
{
	if(screen==1)
		for(i=0; i<100; i++)
		{
			if(e[i].mark)
			{
				e[i].y-=e[i].speed;
				if(e[i].y<=0 ||(e[i].y<=Player_y+60 && e[i].x>=Player_x-30 && e[i].x<=Player_x+60))
				{
					life--;
					e[i].mark=0;
					if(life<=0)
					{
						screen=2;
						flag=0;
					}
				}
			}
			sprintf(LIFE, "Lives: %d", life);
		}
	int fl;
	if(screen==1)
		if(create>=100 && life>0)
		{
			for(fl=0; fl<100; fl++)
			{
				if(e[fl].mark)break;
			}
			if(fl>=100)
			{
				level++;
				if(level==2)enemyPreProcesslvl2();
				if(level==3)enemyPreProcesslvl3();
				if(level==4)screen=2;
			}
		}
}

void showEnemy()
{
	if(screen==1)
		for(i=0; i<100; i++)
		{
			if(e[i].mark)iShowBMPWOBG(e[i].x, e[i].y, "Archer1.bmp");
		}
}

//************* Features ****************

void pause()
{
	isPause++;
	if(isPause%2==0)
	{
		iPauseTimer(t1);
		iPauseTimer(t2);
		iPauseTimer(t3);
		iPauseTimer(t4);
		screen=3;
	}
	else
	{
		iResumeTimer(t1);
		iResumeTimer(t2);
		iResumeTimer(t3);
		iResumeTimer(t4);
		screen=1;
	}
}

void collisionCheck()
{
	if(screen==1)
		for(int k=0; k<3; k++)
		{
			if(up_x[k]>=e[i].x-8 && up_x[k]<=e[i].x+32 && up_y[k]>=e[i].y-32 && up_y[k]<=e[i].y+36&& up[k] && e[i].mark)
			{
				up[k]=0;
				e[i].mark=0;
				score+=e[i].speed;
			}
			if(Lup_x[k]>=e[i].x-6 && Lup_x[k]<=e[i].x+32 && Lup_y[k]>=e[i].y-32 && Lup_y[k]<=e[i].y+36 && Lup[k] && e[i].mark)
			{
				Lup[k]=0;
				e[i].mark=0;
				score+=e[i].speed;
			}
			if(Rup_x[k]>=e[i].x-6 && Rup_x[k]<=e[i].x+32 && Rup_y[k]>=e[i].y-32 && Rup_y[k]<=e[i].y+36 && Rup[k] && e[i].mark)
			{
				Rup[k]=0;
				e[i].mark=0;
				score+=e[i].speed;
			}
	}
}

void drawTextBox()
{
	iSetColor(150, 150, 150);
	iRectangle(350, 340, 250, 30);
}

void highscoreChange()
{
	output = fopen("Highscore.txt", "w");
	drawTextBox();
	if(mode == 1)
	{
		iSetColor(255, 255, 255);
		iText(355, 350, str);
	}
	iText(10, 590, "Click to activate the box, enter to finish.");
	strcpy(name[2], str2);
	fprintf(output, "%d %s\n", highscore[0], name[0]);
	fprintf(output, "%d %s\n", highscore[1], name[1]);
	fprintf(output, "%d %s\n", score, name[2]);
	fclose(output);
}
//************* Fire ***************

void missileMove()
{
	if(screen==1)
		for(int k=0; k<3; k++)
			up_y[k]+=10;
	if(screen==1)
		for(i=0; i<100; i++)
		{
			collisionCheck();
			sprintf(SCORE, "Score: %d", score);
		}
}

void missileRLMove()
{
	if(screen==1)
		for(int k=0; k<3; k++)
		{
			Lup_x[k]-=9;
			Lup_y[k]+=9;
			Rup_x[k]+=9;
			Rup_y[k]+=9;
		}
	
}

//************* Screens **************

void game()
{
	iClear();
	if(level==1)
	{
		iShowBMP(0,0,"BackLvl1.bmp");
		showEnemy();
		iSetColor(255, 255, 255);
		iText(700, 610, SCORE);
		iText(850, 610, LIFE);
		for(int k=0; k<3; k++)
		{
			if(up[k])iShowBMPWOBG(up_x[k], up_y[k], "Umissile.bmp");
			if(Lup[k])iShowBMPWOBG(Lup_x[k], Lup_y[k], "LUmissile.bmp");
			if(Rup[k])iShowBMPWOBG(Rup_x[k], Rup_y[k], "RUmissile.bmp");
		}
	
		iShowBMPWOBG(Player_x, Player_y, "player1.bmp");
	}
	if(level==2)
	{
		iShowBMP(0,0,"BackLvl2.bmp");
		showEnemy();
		iSetColor(255, 255, 255);
		iText(700, 610, SCORE);
		iText(850, 610, LIFE);
		for(int k=0; k<3; k++)
		{
			if(up[k])iShowBMPWOBG(up_x[k], up_y[k], "Umissile.bmp");
			if(Lup[k])iShowBMPWOBG(Lup_x[k], Lup_y[k], "LUmissile.bmp");
			if(Rup[k])iShowBMPWOBG(Rup_x[k], Rup_y[k], "RUmissile.bmp");
		}
		iShowBMPWOBG(Player_x, Player_y, "player1.bmp");
	}
	if(level==3)
	{
		iShowBMP(0,0,"BackLvl3.bmp");
		showEnemy();
		iSetColor(255, 255, 255);
		iText(700, 610, SCORE);
		iText(850, 610, LIFE);
		for(int k=0; k<3; k++)
		{
			if(up[k])iShowBMPWOBG(up_x[k], up_y[k], "Umissile.bmp");
			if(Lup[k])iShowBMPWOBG(Lup_x[k], Lup_y[k], "LUmissile.bmp");
			if(Rup[k])iShowBMPWOBG(Rup_x[k], Rup_y[k], "RUmissile.bmp");
		}
		iShowBMPWOBG(Player_x, Player_y, "player1.bmp");
	}
}

void gameOver()
{
	iClear();
	if(level!=4) iShowBMP(0,0, "gameover.bmp");
	else iShowBMP(0,0, "youwin.bmp");
	if(score>highscore[2])
		highscoreChange();
}

void pauseMenu()
{
	iClear();
	iShowBMP(0,0,"pause.bmp");
}

void menu()
{
	iClear();
	iShowBMP(0,0,"Mainmenu.bmp");
}

void highscoreScr()
{
	iClear();
	input = fopen("Highscore.txt", "r");
	for(int j=0; j<3; j++)
	{
		fscanf(input,"%d %s", &highscore[j], name[j]);
		sprintf(hscore[j], "Name: %s Score: %d", name[j], highscore[j]);
	}
	fclose(input);
	iShowBMP(0,0, "Highscore.bmp");
	if(hs)
	{
		char tmp[20];
		int tm;
		if(highscore[2]>highscore[1])
		{
			tm=highscore[2];
			highscore[2]=highscore[1];
			highscore[1]=tm;
			strcpy(tmp,name[2]);
			strcpy(name[2],name[1]);
			strcpy(name[1],tmp);
			if(highscore[1]>highscore[0])
			{
				tm=highscore[1];
				highscore[1]=highscore[0];
				highscore[0]=tm;
				strcpy(tmp,name[1]);
				strcpy(name[1],name[0]);
				strcpy(name[0],tmp);
			}
		}
		hs=0;
		output = fopen("Highscore.txt", "w");
		for(int j=0; j<3; j++)
		{
			fprintf(output,"%d %s\n", highscore[j], name[j]);
			sprintf(hscore[j], "Name: %s Score: %d", name[j], highscore[j]);
		}
		fclose(output);
	}
	iText(364, 344, hscore[0]);
	iText(364, 272, hscore[1]);
	iText(364, 206, hscore[2]);

}

void help()
{
	iClear();
	iShowBMP(0,0,"Help.bmp");
}

void credits()
{
	iClear();
	iShowBMP(0,0,"credits.bmp");
}

//************* iGraphics ***************
void iDraw()
{
	if(screen==0)menu();
	if(screen==1)game();
	if(screen==2)gameOver();
	if(screen==3)pauseMenu();
	if(screen==4)highscoreScr();
	if(screen==5)help();
	if(screen==6)credits();

}


void iMouseMove(int mx, int my)
{
	
}


void iMouse(int button, int state, int mx, int my)
{
	if(screen==3)
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=377 && mx<=584  && my>=374 && my<=409)
		{
			pause();
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=377 && mx<=584  && my>=274 && my<=309)
		{
			pause();
			enemyPreProcesslvl1();
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=377 && mx<=584  && my>=174 && my<=209)
		{
			screen=0;
		}
		if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		{
		
		}
	}
	if(screen==2)
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			if(mx >= 350 && mx <= 600 && my >= 340 && my <= 370 && mode == 0)
			{
				mode = 1;
			}
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=21 && mx<=199  && my>=21 && my<=76)
		{
			enemyPreProcesslvl1();
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=758 && mx<=938  && my>=21 && my<=76)
		{
			screen=0;
		}
	}
	if(screen==0)
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=680 && mx<=920  && my>=340 && my<=388)
		{
			enemyPreProcesslvl1();
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=680 && mx<=920  && my>=102 && my<=151)
		{
			exit(0);
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=680 && mx<=920  && my>=280 && my<=326)
		{
			screen=5;
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=680 && mx<=920  && my>=220 && my<=265)
		{
			screen=4;
		}
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=680 && mx<=920  && my>=163 && my<=209)
		{
			screen=6;
		}
	}
	if(screen==4)
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=17 && mx<=234  && my>=29 && my<=80)
		{
			screen=0;
		}
	}
	if(screen==5)
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=722 && mx<=899  && my>=19 && my<=94)
		{
			screen=0;
		}
	}
	if(screen==6)
	{
		if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && mx>=25 && mx<=229  && my>=25 && my<=94)
		{
			screen=0;
		}
	}
}


void iKeyboard(unsigned char key)
{
	if(screen==1  || screen==3)
	{
		if(key == 'w')
		{
			if(countUp-2<0 || up_y[countUp-2]>=640)
			{
				countUp++;
				countUp=countUp%3;
				up[countUp]=1;
				up_x[countUp]=Player_x+12;
				up_y[countUp]=Player_y+32;
			}
		}
		if(key == 'a')
		{
			if(countLup-2<0 || Lup_y[countLup-2]>=640 || Lup_x[countLup-2]<=0)
			{
				countLup++;
				countLup=countLup%3;
				Lup[countLup]=1;
				Lup_x[countLup]=Player_x+12;
				Lup_y[countLup]=Player_y+32;
			}
		}
		if(key == 'd')
		{
			if(countRup-2<0 || Lup_y[countRup-2]>=640 || Lup_x[countRup-2]>=960)
			{
				countRup++;
				countRup=countRup%3;
				Rup[countRup]=1;
				Rup_x[countRup]=Player_x+12;
				Rup_y[countRup]=Player_y+32;
			}
		}
		if(key == 'p')
		{
			pause();
		}
	}
	if(mode == 1 || screen==2)
	{
		if(key == '\r')
		{
			mode = 0;
			strcpy(str2, str);
			printf("%s\n", str2);
			for(i = 0; i < len; i++)
				str[i] = 0;
			len = 0;
		}
		else
		{
			str[len] = key;
			len++;
		}
	}
}


void iSpecialKeyboard(unsigned char key)
{

	if(screen==1)
	{
		if(key == GLUT_KEY_LEFT)
		{
			if(isPause%2==1)
				if(Player_x>0)
					Player_x-=15;
		}
		if(key == GLUT_KEY_RIGHT)
		{
			if(isPause%2==1)
				if(Player_x<=928)
					Player_x+=15;
		}
	}
}



int main()
{
	t1=iSetTimer(60, missileMove);
	t2=iSetTimer(75, missileRLMove);
	t3=iSetTimer(750,arcMove);
	t4=iSetTimer(2000, enemyCreate);
	iInitialize(960, 640, "GAME");
	return 0;
}