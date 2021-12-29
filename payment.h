

#define MaxTans 5000.0
/**********CARD Data *************/

typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;



/**********Terminal Data *************/

typedef struct ST_terminalData_t
{
     float transAmount;
     float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;


/*************Transaction Data***********/


typedef enum EN_transStat_t
{
    DECLINED,
    APPROVED
}EN_transStat_t;

typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t termData;
    EN_transStat_t transStat;
}ST_transaction;



/*************Server Data***************/

typedef struct ST_accountBalance_t
{
    uint8_t primaryAccountNumber[20];
    float balance;
}ST_accountBalance_t;


/*********************Function prototype************************/
void gitCardData();
void gitTerminalData();
uint8_t checkCardExpired();
uint8_t Accptedamount();
uint8_t AccountNumberFound();
void Transaction();
