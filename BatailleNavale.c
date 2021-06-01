/*le jeu est développé par:
OUSSAMA SEME-ELAYNE
*/

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

void Grid(int);
void Placer(void);
double Missile(void);
void initT(char T[6][6]);



char Navire[6][6] = {{' ',' ',' ',' ',' ',' '},
                     {' ',' ',' ',' ',' ',' '},
                     {' ',' ',' ',' ',' ',' '},
                     {' ',' ',' ',' ',' ',' '},
                     {' ',' ',' ',' ',' ',' '},
                     {' ',' ',' ',' ',' ',' '}};

char Naufrage[6][6] ={{' ',' ',' ',' ',' ',' '},
                      {' ',' ',' ',' ',' ',' '},
                      {' ',' ',' ',' ',' ',' '},
                      {' ',' ',' ',' ',' ',' '},
                      {' ',' ',' ',' ',' ',' '},
                      {' ',' ',' ',' ',' ',' '}};

int main()
{
    int choice, score;


    system("color 97");

    do
    {
             printf("-----------------------------\n");
             printf("|       BATAILLE NAVALE     |\n");
            printf("-----------------------------\n\n");
        printf("#########################################\n");
        printf("#####     by OUSSAMA SEME-ELAYNE    #####\n");
        printf("#####                               #####\n");
        printf("#####                               #####\n");
        printf("#########################################\n");


        printf("2.Commment Jouer\n");
        printf("1.Jouer\n");
        printf("0.Sortir\n");

        printf("choice : ");
        scanf("%d",&choice);

        switch (choice)
        {
            case 2:printf("Deux personnes doivent jouer le jeux, le premier doit choisir l'emplacement \nLES BATAILLE et le deuxieme doit les trouves.\n \n \n \n \n");
                break;

            case 1:
                initT(Navire);
                initT(Naufrage);
                Placer();
                getch();
                score = Missile();
                printf("Score = %d\n\n",score);
                break;
            case 0:
                exit(0);
        }
        system("pause");
        system("cls");
    }while(1);

    return 0;
}
void Grid(int choix)
{
    int i,j;

    printf("[XY]");
    for(i=0; i<6; i++)
    {
        printf("[%d]",i+1);
    }
    printf("\n");
    for(i=0; i<6; i++)
    {
        printf("[%d]",i+1);
        for(j=0; j<6; j++)
        {
            if(choix == 0)
            {
                if(Navire[i][j]==' ') printf("[.]");
                else printf("[%c]",Navire[i][j]);
            }
            else if(choix == 1)
            {
                if(Naufrage[i][j]==' ') printf("[.]");
                else printf("[%c]",Naufrage[i][j]);
            }
        }
        printf("\n");
    }
}
void Placer()
{
    int i,j;
    int x,y,rotation;
    int H,V;

    for(i=0; i<3; i++)
    {
        system("cls");
        Grid(0);

        printf("\n\nBateau %d :\n\n",i+1);
        do
        {
            do
            {
                printf("X : ");
                scanf("%d",&x);

                if(x>=1 && x<=6) break;
                printf("Erreur! 1<= x <= 6\n");
            }while(1);
            do
            {
                printf("Y : ");
                scanf("%d",&y);

                if(y>=1 && y<=6) break;
                printf("Erreur! 1<= y <= 6\n");
            }while(1);

            if((!((x==5 && y==5) || (x==5 && y==6) || (x==6 && y==5) || (x==6 && y==6))) && Navire[x-1][y-1] == ' ') break;
            erreur:
            printf("Impossible to placer la navire ici\n");

        }while(1);

        H = V = 0;
        if(y<5 && Navire[x-1][y] == ' ' && Navire[x-1][y+1] == ' ') H = 1;
        if(x<5 && Navire[x][y-1] == ' ' && Navire[x+1][y-1] == ' ') V = 1;

        if(V==0 && H==0)
            goto erreur;

        printf("\nRotation:\n");
        do
        {
            if(H)
            {
                printf("1.Horizontal\n");
            }
            if(V)
            {
                printf("2.Vertical\n");
            }
            printf("choix : ");
            scanf("%d",&rotation);

            if((rotation >= 1 && rotation <= 2)
            && (H && rotation == 1)
            || (V && rotation == 2))
                break;
            printf("Erreur! choix invalable\n");
        }while(1);

        x--;
        y--;

        Navire[x][y] = 65+i;

        if(rotation == 1)
        {
            Navire[x][y+1] = 65+i;
            Navire[x][y+2] = 65+i;
        }
        else if(rotation == 2)
        {
            Navire[x+1][y] = 65+i;
            Navire[x+2][y] = 65+i;
        }
    }

    system("cls");
    Grid(0);
}
double Missile()
{
    int x,y;
    int _missile=0,hit=0;
    time_t startTime, endTime;

    startTime = time(0);
    do
    {
        system("cls");
        Grid(1);

        _missile++;
        printf("\nMissile %d :\n",_missile);

        do
        {
            do
            {
                printf("X : ");
                scanf("%d",&x);

                if(x>=1 && x<=6) break;
                printf("Erreur! 1<= x <= 6\n");
            }while(1);
            do
            {
                printf("Y : ");
                scanf("%d",&y);

                if(y>=1 && y<=6) break;
                printf("Erreur! 1<= y <= 6\n");
            }while(1);

            if(Naufrage[x-1][y-1] == ' ') break;
            printf("Already stricked\n");
        }while(1);

        x--; y--;

        if(Navire[x][y] == ' ')
        {
            Naufrage[x][y] = 'X';
        }
        else
        {
            Naufrage[x][y] = Navire[x][y];
            hit++;
        }
    }while(hit < 9);

    endTime = time(0);

    system("cls");
    Grid(1);

    //Score
    return 1000 / ((int)difftime(endTime,startTime) + _missile) * 10;
}
void initT(char T[6][6])
{
    int i, j;

    for(i=0; i<6; i++)
    {
        for(j=0; j<6; j++)
        {
            T[i][j] = ' ';
        }
    }
}
