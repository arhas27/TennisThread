//
//  main.c
//  Project1Fixed
//
//  Created by Arief Hakim Askar on 3/8/16.
//  Copyright © 2016 Arief Hakim Askar. All rights reserved.
//

//
//  main.c
//  Project OS
//
//  Created by Arief Hakim Askar on 3/7/16.
//  Copyright © 2016 Arief Hakim Askar. All rights reserved.
//  Group Members : Arief Hakim Askar (99604305062), Natig Kurbanov (99679445496)


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int team1pt=0;
int team2pt=0;
int team3pt=0;
int randomnumber1;
int randomnumber2;
int winner=0;
//int temp=0;

//---------------------------------------------------------
void *PlayTennis(void *parameter){
    int *p = (int *)parameter;
    srand(time(NULL));
    int ranscore;
    ranscore = (rand() % 5) + 1;
    
    while (winner==0){
        ranscore = (rand() % 5) + 1;
        //temp=*p;
        if (ranscore==3) {
            if (*p==1)
            {
                team1pt+=1;
                printf("Thread1 gets the score. Score: %d-%d. \n", team1pt,team2pt);
                if (team1pt >= 11)
                {
                    printf("The first game is finished. Thread1 Wins.\n");
                    winner =1;
                    team1pt=0;
                    team2pt=0;
                    break;
                    
                }
            }
            else if (*p==2)
            {
                team2pt+=1;
                printf("Thread2 gets the score. Score: %d-%d. \n", team1pt,team2pt);
                if (team2pt >= 11)
                {
                    printf("The first game is finished. Thread2 Wins.\n");
                    winner=2;
                    team1pt=0;
                    team2pt=0;
                    break;
                }
            }
            else if (*p==3)
            {
                team2pt+=1;
                
                printf("Thread3 gets the score. Score: %d-%d. \n",team1pt,team2pt);
                if (team2pt >= 11)
                {
                    printf("The first game is finished. Thread3 Wins.\n");
                    winner=3;
                    team1pt=0;
                    team2pt=0;
                    break;
                }
            }
            
        }
        else if (winner==0)
        {
            printf("Thread%d hits the ball. \n", *p);
        }
        
    } /* end-while */
    pthread_exit(NULL);
    return 0;    // Exit
} //end-Thread1Proc


//---------------------------------------------------------

int main(int argc, char* argv[]){
    
    pthread_t threadPlayers[3];
    srand(time(NULL));
    randomnumber1 = (rand() % 3) + 1;
    randomnumber2 = (rand() % 3) + 1;
    //pthread_t *tid = malloc( 3 * sizeof(pthread_t) );
    int noplay=0;
    while (randomnumber1==randomnumber2) {
        randomnumber2 = (rand() % 3) + 1;
    }
    if (randomnumber1==1&&randomnumber2==2)
    {
        noplay=3;
    }
    else if(randomnumber1==2&&randomnumber2==1)
    {
        noplay=3;
    }
    else if(randomnumber1==1&&randomnumber2==3)
    {
        noplay=2;
    }
    else if(randomnumber1==3&&randomnumber2==1)
    {
        noplay=2;
    }
    else if(randomnumber1==2&&randomnumber2==3)
    {
        noplay=1;
    }
    else if(randomnumber1==3&&randomnumber2==2)
    {
        noplay=1;
    }
    for(int x=0;x<2;x++){
        if (winner!=0)
        {
            printf("Threads have been chosen! Thread%d and Thread%d will start the game!\n",winner
                   ,noplay);
            
            
            pthread_create(&threadPlayers[noplay], NULL, PlayTennis, (void *)&noplay);
            pthread_create(&threadPlayers[winner], NULL, PlayTennis, (void *)&winner);
            
            for (int i=1; i<=3; i++) {
                pthread_join(threadPlayers[i], NULL);
            }
        }
        else{
        
                printf("Threads have been chosen! Thread%d and Thread%d will start the game!\n",randomnumber1,randomnumber2);
                
                pthread_create(&threadPlayers[randomnumber1], NULL, PlayTennis, (void *)&randomnumber1);
                
                pthread_create(&threadPlayers[randomnumber2], NULL, PlayTennis, (void *)&randomnumber2);
                
                for (int i=1; i<=3; i++) {
                    pthread_join(threadPlayers[i], NULL);
                }
        }
        }
    
        return 0;
    } //end-main