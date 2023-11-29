//typical #include statements
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//function prototypes
int getCard();
int adjustedCardValue(int card, int currentHandValue);
int hitAgain();
int playAgainFunc();
int bet(int currentMoney);

int main()
{
    //initialize flag for playing again
    int playAgain = 1;

    //initialize int for money amount
    int money = 500;

    //seed null time
    srand(time(NULL));

    //while loop to allow for playing again
    while(playAgain == 1 && money > 0) {

        int betValue = bet(money);

        //set both player and dealer hands to 0
        int player_hand = 0;
        int dealer_hand = 0;

        //draw two cards for player
        player_hand += adjustedCardValue(getCard(), player_hand);
        player_hand += adjustedCardValue(getCard(), player_hand);

        //draw face up card for dealer
        dealer_hand += adjustedCardValue(getCard(), dealer_hand);

        //give info on both hands
        printf("Player has %d\n", player_hand);
        printf("Dealer's face-up card: %d\n", dealer_hand);

        //planning to have a flag to jump to another part of the code when a loss is detected
        int lossFlag = 0;

        //this is a flag to set an auto win when 21 is hit
        int blackjack21 = 0;


        //if 21 on the first draw, then player win
        if(player_hand == 21)
        {
            printf("You win!\n");
            printf("You won $%d, you now have $%d total!\n", (betValue * 1.5), money);
            blackjack21 = 1;
            money += betValue * 1.5;
           
        }
        
        if(blackjack21 == 0)
        {

            //take input on hit or stand
            int doneHitting = 0;

            //test variable for debugging
            int timesLooped = 0;
            

            //while loop for while a player is hitting, 0 means hitting, 1 means done
            while(doneHitting == 0)
            {
                int hitFlag = hitAgain();

                if(hitFlag == 0)
                {
                    player_hand += adjustedCardValue(getCard(), player_hand);
                    printf("Player has %d\n", player_hand);

                    //simple condition, if player hand value is greater than 21, game over
                    if(player_hand > 21)
                    {
                    printf("You busted!\n");
                    money -= betValue;

                    //lose condition and done hitting are set to 1, since you can't hit anymore and you've lost if this code is ran
                    lossFlag = 1;
                    doneHitting = 1;
                    }
                }

                //otherwise if player denotes they don't want to hit, set doneHitting to 1 to end the while loop
                else if(hitFlag == 1)
                {
                    doneHitting = 1;
                }

                //test variable for debugging
                timesLooped++;
            }

            //this code defines a flag for when a dealer is under a value of 17
            int dealerUnder17 = 0;

            //have dealer draw cards until they are at 17 or higher, after player is done
            while(dealerUnder17 == 0)
            {
                //if dealer hand needs a card, draw it
                if(dealer_hand < 17)
                {
                    dealer_hand += adjustedCardValue(getCard(), dealer_hand);   

                    //debugging
                    //printf("Dealer hand is: %d\n", dealer_hand);
                }

                //otherwise set flag to 1 to end the while loop
                else if(dealer_hand >= 17)
                {
                    dealerUnder17 = 1;
                }
            }

            //code that has not been written yet for the loseCondition flag mentioned above, will look into later
            if(lossFlag == 1)
            {

            }

            //if dealer busts, player wins
            else if(dealer_hand > 21)
            {
                printf("You win!\n");
                money += betValue;
            }

            //logic to compare player and dealer hands after both hands are done changing
            //SHOULD REWRITE THIS INTO A FUNCTION IN THE FUTURE
            else
            {
                if(player_hand > dealer_hand)
                {
                    printf("You win!\n");
                    money += betValue;
                }
                else if(dealer_hand > player_hand)
                {
                    printf("You lose...\n");
                    lossFlag = 1;
                    money -= betValue;
                }
                else if(player_hand == dealer_hand)
                {
                    printf("It's a draw....\n");
                    lossFlag = 2;
                }
                else
                {
                    printf("something went wrong uhoh\n");
                }
            }

            //lets the player know what their hand was and what the dealer's hand was, a nice-to-have
            printf("You: %d \nDealer: %d\n", player_hand, dealer_hand);  
            
            //let player know how much money they won/lost and how much they now have
            if(lossFlag == 2)
            {
                //lossFlag value of 2 is for a tie
                printf("You now have $%d total.\n", money);
            }
            //lossFlag of 1 is equivalent to a loss
            if(lossFlag == 1)
            {
                printf("You lost $%d on this bet, you now have $%d total.\n", betValue, money);
            }
            //lossFlag of 0 is a win
            if(lossFlag == 0)
            {
                printf("You won $%d on this bet, you now have $%d total.\n", betValue, money);
            }

            //after a round if you don't have money, end the game.
            if(money <= 0)
            {
                printf("You ran out of money. Game over.");
                playAgain = 1;
            }
            //otherwise allow the player to play again
            else
            {
                //call function to control playAgain flag
                playAgain = playAgainFunc();  
            }
        }
    }

    //classic return statement in main
    return 0;

}


//gets a card value from Ace (1) to King (13)
int getCard()
{
    //rand() % 13 will generate values 0-12, so +1 to generate a value of 1-13, covering Ace (1) to King (13)
    int card = (rand() % 13) + 1;

    //return the value of the card into a variable when called
    return card;
}

//changes the card value of Jack, Queen, and King to 10, and changes Ace to 11
int adjustedCardValue(int card, int currentHandValue)
{
    //pass in card value, if Jack(11), Queen(12), or King(13), set the value to 10
    if(card > 10)
    {
        return 10;
    }

    //if card is an Ace and won't bust the player, make it 11, otherwise, Ace is worth 1
    else if(card == 1)
    {
        //if adding the Ace as 11 won't cause the player to bust, make it worth 11
        if(currentHandValue + 11 <= 21)
        {
            return 11;
        }
        //otherwise, Ace counts as 1
        else
        {
            return 1;
        }
    }

    //if card is not Ace, Jack, Queen, or King, just return the card value
    else
    {
        return card;
    }
}


int hitAgain()
{
    //set up a char for a one letter input for hitting, the code does about what you would expect it to 
    char input[0];
    printf("Would you like to hit? Y or N? ");
    //extra space before %c to prevent the enter key being part of the scanf
    scanf(" %c", &input[0]);
    
    //if player says Y, return 0 to signal player wants to hit again
    if(input[0] == 'Y')
    {
        return 0;
    }
    //if player says N, return 1 to signal player does not want to hit anymore
    else if(input[0] == 'N')
    {
        return 1;
    }
    //TODO: make a return value of 2 correlate to some sort of error, code functionality is here for it though
    else
    {
        return 2;
    }
}

int playAgainFunc()
{
    //ask to play another round
    printf("Do you want to play another round? Y or N? ");

    //initialize char variable and scan input to determine flag value
    char playAgainInput;
    scanf(" %c", &playAgainInput);

    //if Y then keep playing
    if(playAgainInput == 'Y')
    {
        return 1;
    }
    //if anything else, stop playing
    else
    {
        return 0;
    }
}

int bet(int currentMoney)
{
    //initialize flag to ensure valid bet, once a bet is deemed valid, flag will move to 1 and while loop will end.
    int validBet = 0;

    //initialize a bet amount each time, since we change it, 0 is fine
    int betAmount = 0;

    while(validBet == 0)
    {
        //print statement showing how much money, leads to scanf to grab input
        printf("You currently have $%d, how much would you like to bet? $", currentMoney);

        //scanf to take input, write it to betAmount variable
        scanf("%d", &betAmount);

        //a bit of logic to ensure bet is valid
        if(betAmount > currentMoney)
        {
            printf("Invalid Bet!\n");
        }
        else if(betAmount <= currentMoney)
        {
            validBet = 1;
        }
    }

    return betAmount;
}