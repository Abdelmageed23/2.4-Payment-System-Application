#include <stdio.h>
#include <string.h>
#include "typedef.h"
#include "payment.h"



/****************Global Variables *********************/
  ST_cardData_t card;
  ST_terminalData_t terminal;
  ST_transaction transaction;
  ST_accountBalance_t account;
uint8_t indexserver= NULL;


  ST_accountBalance_t server[] ={
		{ "123456789", 100.00},
		{ "234567891", 6000.00},
		{ "567891234", 3250.25},
		{ "456789123", 1500.12},
		{ "258649173", 500.00},
		{ "654823719", 2100.00},
		{ "971362485", 0.00},
		{ "793148625", 1.00},
		{ "123123456", 10.12},
		{ "456789321", 0.55},
};



void main()
{

    Transaction();
}




void gitCardData()
{

    printf("Enter name written on the card\n");
    fflush(stdout);
    scanf("%s",&card.cardHolderName);
    printf("Enter the number Written on the card\n");
    fflush(stdout);
    scanf("%s",&card.primaryAccountNumber);
    printf("Enter the Card Expiry date in the format MM/YY \n");
    fflush(stdout);
    scanf("%s",&card.cardExpirationDate);
}


void gitTerminalData()
{
    printf("Enter The Amount:\n");
    scanf("%f",&terminal.transAmount);
    terminal.maxTransAmount=MaxTans;
    printf("Enter the Trans Date in format DD/MM/YYYY\n");
    scanf(" %s",&terminal.transactionDate);

}

uint8_t checkCardExpired()
{

    if((card.cardExpirationDate[3]>terminal.transactionDate[8])||((card.cardExpirationDate[3]==terminal.transactionDate[8])&&(card.cardExpirationDate[4]>terminal.transactionDate[9])
)||((card.cardExpirationDate[3]==terminal.transactionDate[8])&&(card.cardExpirationDate[4]==terminal.transactionDate[9])&&(card.cardExpirationDate[0]>terminal.transactionDate[3]))
       ||((card.cardExpirationDate[3]==terminal.transactionDate[8])&&(card.cardExpirationDate[4]==terminal.transactionDate[9])&&(card.cardExpirationDate[0]==terminal.transactionDate[3])&&(card.cardExpirationDate[1]>terminal.transactionDate[4])))

    {

   //     printf("\n NOT    EXPIRED");
    return 1;
    }
    else
    {
     //  printf("\n EXPIRED");
        return 0;
    }
}
uint8_t Accptedamount()
{
    if(terminal.transAmount<=terminal.maxTransAmount) return 1;
    else return 0;
}

uint8_t AccountNumberFound()
{
    for(int i=0;i<10;i++)
            {
                if(strcmp(card.primaryAccountNumber,server[i].primaryAccountNumber)==0)
                {
                indexserver=i;
                return 1;
                }
                else
                {
                }
            }
    return 0;
}

void Transaction()
{
    uint8_t u8_again;
    while(1)
    {

    gitCardData();
    gitTerminalData();

    if (checkCardExpired()==0)
    {
        printf("\nTransactionDeclined , Card Expired\n");

    }
    else
    {
        if(Accptedamount()== 0)
        {
            printf("\nTransactionDeclined , Not accepted  Amount");

        }
        else
        {
            if(AccountNumberFound()==0)
            {
                printf("\nTransactionDeclined , Wrong Account Number");

            }
            else
                {
                    if((server[indexserver].balance>terminal.transAmount))
                {
                    printf("The Transaction is APPROVED");

                }
                else
                {
                    printf("\nThe Transaction is Decline , Out of balance");

                }
                }
        }
    }

    printf("\nDo you want to continue (y/n)? : \n");
    scanf(" %c",&u8_again);
    indexserver= NULL;
    if(u8_again!='y') return 0;
    }


}




