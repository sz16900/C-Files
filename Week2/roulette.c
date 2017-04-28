#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int players_money = 10;
    int players_number;
    int roulettes_number;
    int yes_no_play_again = 1;
    int yes_no_evenodds;
    int evenodds;
    
    srand ( time(NULL) );
    
    while (yes_no_play_again == 1 && players_money >= 1) {
        printf("You currently have $%d\n\n", players_money);
        printf("Would you like to bet even/odds? (1 for Yes, 0 for No) : \n\n");
        scanf("%d", &yes_no_evenodds);
        
        if(yes_no_evenodds == 1){
            printf("OK! Type 1 for ODDS or 2 for EVEN : \n\n");
            scanf("%d", &evenodds);
            roulettes_number = rand()%37;
            if (roulettes_number == 0){
                players_money = players_money - 1;
                printf("ROULETTES NUMBER : %d\n", roulettes_number);
                printf("BAD LUCK. Its a 0! You can try again. But i'll cost you a $1.\n\n");
            }
            else if((evenodds == 2) && (roulettes_number%2==0)){
                players_money = players_money + 1;
                printf("ROULETTES NUMBER : %d\n", roulettes_number);
                printf("EVENS! We now pay you $1\n\n");
            }
            else if ((evenodds == 1) && (roulettes_number%2!=0)){
                players_money = players_money + 1;
                printf("ROULETTES NUMBER : %d\n", roulettes_number);
                printf("ODDS! We now pay you $1\n\n");
            }
            else {
                players_money = players_money - 1;
                printf("ROULETTES NUMBER : %d\n", roulettes_number);
                printf("Oh no!. Its ok. You can try again. But i'll cost you a $1.\n\n");
            }
        }
        
        else if (yes_no_evenodds == 0) {
            printf("Which particular number would you like to bet on? : \n\n");
            scanf("%d", &players_number);
            roulettes_number = rand()%37;
            if(players_number == roulettes_number){
                players_money = players_money + 35;
                printf("ROULETTES NUMBER : %d\n", roulettes_number);
                printf("NICE ONE. We now pay you $35\n\n");
            }
            else if (players_number != roulettes_number){
                players_money = players_money - 1;
                printf("ROULETTES NUMBER : %d\n", roulettes_number);
                printf("Oh no!. Its ok. You can try again. But i'll cost you a $1.\n\n");
            }
        }
        
        
        printf("Would you like to place a bet again? (1 for Yes, 0 for No) \n");
        scanf("%d", &yes_no_play_again);
    }
    
    printf("You leave Seth's Casino with: $%d\n", players_money);
    return 0;
}


