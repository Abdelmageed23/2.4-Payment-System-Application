#include <stdio.h>
#include <string.h>
#include "typedef.h"
#include "payment.h"




/****************Global Variables *********************/
  ST_cardData_t card;           //card is a global variable of structure to hold card data
  ST_terminalData_t terminal;   //terminal is a global variable of structure to hold terminal data
  ST_transaction transaction;   //transaction is a global variable of structure to save transaction data
  ST_transaction transactionHistory[historySize]; // transactionHistory is a global array of structure to save transactions on it
uint8_t indexserver= NULL;
uint8_t TransactionPointer =0;



/*
    Server is the data base of the bank holds ID number and balance
*/
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
    printf("\ntransaction History : ");
    for(int i=0;i<TransactionPointer;i++)
    {

        printf("\n %d: PIN number %s",i+1,transactionHistory[i].cardHolderData.primaryAccountNumber);
    }
}


/*
    function asks for card data and return void
    saving card name , number , expired date in the card structure
*/

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


/*
    function asks for terminal data and return void
    saving the terminal amount and adjust the max amount and save the transaction date
*/
void gitTerminalData()
{
    printf("Enter The Amount:\n");
    scanf("%f",&terminal.transAmount);
    terminal.maxTransAmount=MaxTans;
    printf("Enter the Trans Date in format DD/MM/YYYY\n");
    scanf(" %s",&terminal.transactionDate);

}

/*
    function to check if the card expired or not and return 1 if not expired and 0 if expired
    by comparing the card expired date and transaction date
*/

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


/*
    function compare the amount of transaction and compare it with the max amount and return 1 if accepted and 0 if not accepted
*/
uint8_t Accptedamount()
{
    if(terminal.transAmount<=terminal.maxTransAmount) return 1;
    else return 0;
}


/*
    function search for the account number in the server and return 1 if found and 0 if not found
*/
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


/*
    function of transaction return void
    while loop function based on memory server (#define historySize) or when ends the Transaction
        get card data and terminal data
        check the card data and terminal data if valid or not


*/
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

        if(historySize>TransactionPointer)
    {

        transactionHistory[TransactionPointer].cardHolderData= card;
        transactionHistory[TransactionPointer].termData= terminal;
        transactionHistory[TransactionPointer].transStat=DECLINED;
        TransactionPointer++;
      //  SaveTransaction();
        BubbleSort(transactionHistory,TransactionPointer);
    }
    else
    {
        printf("\n\n  Memory Full!...");
        return 0;
    }
    }
    else
    {
        if(Accptedamount()== 0)
        {
            printf("\nTransactionDeclined , Not accepted  Amount");
            if(historySize>TransactionPointer)
    {
        transactionHistory[TransactionPointer].cardHolderData= card;
        transactionHistory[TransactionPointer].termData= terminal;
        transactionHistory[TransactionPointer].transStat=DECLINED;
        TransactionPointer++;

      //  SaveTransaction();
        BubbleSort(transactionHistory,TransactionPointer);
    }
    else
    {
        printf("\n\n  Memory Full!...");
        return 0;
    }
        }
        else
        {
            if(AccountNumberFound()==0)
            {
                printf("\nTransactionDeclined , Wrong Account Number");
                        if(historySize>TransactionPointer)
                {

                    transactionHistory[TransactionPointer].cardHolderData= card;
                    transactionHistory[TransactionPointer].termData= terminal;
                    transactionHistory[TransactionPointer].transStat=DECLINED;
                    TransactionPointer++;
                   // SaveTransaction();
                    BubbleSort(transactionHistory,TransactionPointer);
                }
                else
                {
                    printf("\n\n  Memory Full!...");
                    return 0;
                }
            }
            else
                {
                    if((server[indexserver].balance>terminal.transAmount))
                {
                    printf("The Transaction is APPROVED");
                    if(historySize>TransactionPointer)
    {

        transactionHistory[TransactionPointer].cardHolderData= card;
        transactionHistory[TransactionPointer].termData= terminal;
        transactionHistory[TransactionPointer].transStat=APPROVED;
        TransactionPointer++;
      //  SaveTransaction();
        BubbleSort(transactionHistory,TransactionPointer);
    }
    else
    {
        printf("\n\n  Memory Full!...");
        return 0;
    }
                }
                else
                {
                    printf("\nThe Transaction is Decline , Out of balance");

            if(historySize>TransactionPointer)
    {
        transactionHistory[TransactionPointer].cardHolderData= card;
        transactionHistory[TransactionPointer].termData= terminal;
        transactionHistory[TransactionPointer].transStat=DECLINED;
        TransactionPointer++;
      //  SaveTransaction();
        BubbleSort(transactionHistory,TransactionPointer);
    }
    else
    {
        printf("\n\n  Memory Full!...");
        return 0;
    }
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

/*
swap function takes 2 structures  and swap them
*/


void swap( ST_transaction *xp, ST_transaction *yp)
{
    ST_transaction u8_temp=*xp;
            *xp=*yp;
            *yp=u8_temp;
}


/*
    BubbleSort function that arrange array of struct  in ascending order
    Input: array of stuct  , array size
    Output: void
*/
void BubbleSort(ST_transaction *arr , uint8_t arr_size)
{
    uint8_t local_index;
    uint16_t local_index2;
    for(local_index=0;local_index<arr_size-1;local_index++)
    {
        for(local_index2=0;local_index2<arr_size-local_index-1;local_index2++)
        {
            if(strcmp(arr[local_index2].cardHolderData.primaryAccountNumber,arr[local_index2+1].cardHolderData.primaryAccountNumber)==1)
            {
                swap(&arr[local_index2],&arr[local_index2+1]);
            }
        }
    }
}


