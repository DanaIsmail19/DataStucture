#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 20
#define inf 5

//define struct team
struct team {
    
    char name[MAX];
    char code[3];
    int info[inf];// NOF ,NOD , NOL , GOALS

    struct player* Point_to_Players; // head to player
    struct player* Point_to_Spare_Players; // head to spare player

    struct team* Next;

};typedef struct team NodeTeam;

//define struct player 
struct player {
    
    int number;
    char name[MAX];

    struct player* Next;//pointer to next 

};typedef struct player NodePlayer;

//define stuct to store match 
struct Match
{
    char team1 [MAX];
    char team2 [MAX];

    struct Match* Next;

};typedef struct Match NodeMatch;

//function prototype
void AddNode (char *name, char *code, int info[], NodeTeam* H);
void Radix_Sort (NodeTeam* H);
NodeTeam* Find_ByCode (NodeTeam* H, char code[]);

//to add a new node at the end of lest 
void AddNode (char name[], char code[], int info[], NodeTeam* H)
{
    NodeTeam* lastNode = H;
    NodeTeam* newNode;

    while (lastNode->Next != NULL)
    {
        lastNode = lastNode->Next;
    }

    newNode = (NodeTeam*)malloc(sizeof(NodeTeam));
    int i=0;
    for ( i=0;i<inf;i++)
    {
        newNode->info[i] = info[i];
    }

    strcpy(newNode->name , name);//to put the value name into newnode.name
    strcpy(newNode->code , code);
    newNode->Next = NULL;//make the next node Refers to null

    lastNode->Next = newNode;

    NodeTeam* Head_Player = (NodeTeam*)malloc(sizeof(NodeTeam));//to conect elmenteray player with team
    NodeTeam* Head_SplarePlayer = (NodeTeam*)malloc(sizeof(NodeTeam));

    Head_Player->Next = NULL;//make the next node Refers to null
    Head_SplarePlayer->Next = NULL;

    newNode->Point_to_Players = Head_Player; //newnode refer to headplayer
    newNode->Point_to_Spare_Players = Head_SplarePlayer;
}

//function to make all nodes in the list empty
void free_list(NodeTeam *Head)
{
    NodeTeam *P = Head->Next;
    NodeTeam *N = Head->Next;
    Head->Next = NULL;//head refers to null

    while (NULL != P)
    {
        N = P->Next;
        free(P);//free p node
        P = N;
    }
}

// function to create a new match between to teams by teams code
void Create_a_match (NodeMatch* Head_Match, char team1[],char team2[])
{
    NodeMatch* lastNode = Head_Match;
    NodeMatch* newNode;

    while (lastNode->Next != NULL)
    {
        lastNode = lastNode->Next;
    }

    newNode = (NodeMatch*)malloc(sizeof(NodeMatch));
    
    strcpy(newNode->team1 , team1);
    strcpy(newNode->team2 , team2);
    newNode->Next = NULL;

    lastNode->Next = newNode;
}

//function to print team information
void PrintTeam (NodeTeam* H)
{
    NodeTeam *P = H;

    if (P->Next == NULL)
        printf("EMPTY");//check if the list is empty or not 
    
    while (P->Next != NULL)
    {
        P=P->Next;
        printf("name = %s, code = %s, wins = %d, draws = %d, loses = %d, goals = %d and points = %d\n", P->name,P->code,P->info[0],P->info[1],P->info[2],P->info[3],P->info[4]);
    }
}

//function to print players in the match
void PrintPlayers (NodeTeam* H, char code[])
{
    NodeTeam *P = Find_ByCode(H,code);//find the node that have the smae code

    if (P->Next == NULL)

        printf("EMPTY");
    
    printf("name = %s, code = %s\n", P->name,P->code);
        
    NodePlayer* L1 = P->Point_to_Players;
    NodePlayer* L2 = P->Point_to_Spare_Players;

    printf("Players:\n");

    if (L1->Next == NULL)

        printf("no players...\n");//check if the list is empty or not 
        
    while (L1->Next != NULL)
    {
        L1 = L1->Next;
        printf("number: %d, Name: %s\n",L1->number,L1->name);
    }

    printf("Spare Players:\n");

    if (L2->Next == NULL)
        printf("no spare players...\n");
    
    while (L2->Next != NULL)
    {
        L2 = L2->Next;
        printf("number: %d, Name: %s\n",L2->number,L2->name);
    }
        
}

//function to make radix sort empty after we sill it and sort the all element
void Free_Radix (NodeTeam* radixARR [])
{  
    int i=0;
    for( i=0;i<10;i++)
    {
        free_list(radixARR[i]);
    }
}

// function to find the maximum number & digits in the list in order to sort the element 
int get_Max_dijits (NodeTeam* H)
{
    int count =0;//counter
    int max = INT_MIN;
    NodeTeam *P = H;

    while (P->Next != NULL)
    {
        P = P->Next;

         if (max < P->info[4])
            max = P->info[4];
    }

    int dijit =max;//get the max num

    while (dijit !=0)//while loop to find the max digit
    {
        dijit /= 10;
        count++;
    }

    return count;
}

void Radix_Sort (NodeTeam* H)
{
    NodeTeam* radixARR [10];
    int i=0;
    for ( i=0;i<10;i++)//make an empty array of linked list
    {
        radixARR[i] = (NodeTeam*)malloc(sizeof(NodeTeam));
        radixARR[i]->Next = NULL;
    }

    // 89,6,5,4,3,10
    // 0-1-2-3-4-5-6-7-8-9

    int status =1;
    int dij =0;//index
    int max = get_Max_dijits(H);//max nuber ofdigit
    int k=0;
    for (k=0;k<max;k++)

    { 
        NodeTeam *P = H;
        if (P->Next == NULL)
        {
            printf("Array Teams is EMPTY");
            return 0;
        }

        while (P->Next != NULL)
        {
            P=P->Next;
            dij = (P->info[4]/status)% 10;

            //1  dij =7 --> radix[7]
            //2  dij =4 --> radix[4]
            //3  dij =5 --> radix[5]
            //4  dij =0 --> radix[0]

            AddNode(P->name,P->code,P->info,radixARR[dij]);//add to array of linked list
        }

        free_list(H); //but not free (Head --> null) we need the same Head
        int j=0;
        for ( j=0;j<10;j++)
        {
            if (radixARR[j]->Next == NULL)
                continue;

            NodeTeam *T = radixARR[j];

            while (T->Next != NULL)
            {
                T=T->Next;
                AddNode(T->name,T->code,T->info,H);
            }
        }
        status = status*10;
        Free_Radix(radixARR);
    }
}

//function to add team by the user
void Add_Team (NodeTeam* H)
{
    char name[MAX];
    char any[MAX];
    char code[3];
    int info[inf];//some parameter

    gets(any);
    printf("Insert Team Name : ");
    gets(name);

    gets(any);
    printf("Insert Team Code : ");
    gets(code);

    printf("Insert wins : ");
    scanf("%d", &info[0]);

    printf("Insert draws : ");
    scanf("%d", &info[1]);

    printf("Insert loses : ");
    scanf("%d", &info[2]);

    printf("Insert Goals difference : ");
    scanf("%d", &info[3]);

    if (isHere(H,code))//to make sure if we have this team or not
    {
        printf("Opsss code is already added ... plz try agine");
        Add_Team(H);
        return 0;
    }

    AddNode(name,code,info,H);
    Calculate_the_points(H);//calculate the point
    Radix_Sort(H);//sort the new node
}

//function to check if here or not
int isHere (NodeTeam* H, char Ecode[])
{
    NodeTeam *P = H;
    while (P->Next != NULL)
    {
        P=P->Next;
        if (strcmp(P->code,Ecode)==0)
        {
            return 1;
        }
    }
    return 0;
}

//function to calculate the point
void Calculate_the_points (NodeTeam* H)
{
    NodeTeam *P = H;
    while (P->Next != NULL)
    {
        P=P->Next;
        P->info[4] = (3*P->info[0]) + P->info[1];
    }
}

//function to delete a spicific team
void Delet_Team (NodeTeam* H)
{
    char any[MAX];
    char code[3];

    gets(any);
    printf("Insert Team Code to delete the team :\n");
    gets(code);

    if(isHere(H,code))
    {
        NodeTeam *P = H;
        NodeTeam *T = H;

        while (P->Next != NULL)
        {
            P=P->Next;
            if (strcmp(P->code,code)==0)
            {
                T->Next = P->Next;
                free(P);//free the node
                break;
            }
            T=T->Next;
        }
        Radix_Sort(H);//sort linked list
    }
}

//function to find spisific code in the list then return the node
NodeTeam* Find_ByCode (NodeTeam* H, char code[])
{
    NodeTeam *P = H;
    while (P->Next != NULL)
    {
        P=P->Next;
        if (strcmp(P->code,code)==0)
        {
            return P;
        }
    }

    printf("the team does not ex\n");
    return NULL;
}

//to add a new node from last
void Add_NodePlayer (NodePlayer* HeadPlayer, int number, char name[])
{
    NodePlayer* lastNode = HeadPlayer;
    NodePlayer* newNode;

    while (lastNode->Next != NULL)
    {
        lastNode = lastNode->Next;
    }
    
    newNode = (NodePlayer*)malloc(sizeof(NodePlayer));
    newNode->number = number;
    strcpy(newNode->name , name);

    newNode->Next = NULL;
    lastNode->Next = newNode;
}

//function to read player file
void Read_Player (NodeTeam* Head)
{
    FILE * Fplayer = fopen("players.txt", "r");
    char linePlayer [40];

    NodeTeam* T;
    while(fgets(linePlayer, sizeof(linePlayer), Fplayer))
    {

        char * token1;
        if (linePlayer[0]=='*')//get the value when we see *
        {
            token1 = strtok(linePlayer,"*\n");//grt all value that start with *
            T = Find_ByCode(Head,token1);
            int u = isHere(Head,token1);
            if (u==0)
            continue;
        }

        else
         {
            char * token2 = strtok(linePlayer,"-");
            int number = atoi(token2);


            token2 = strtok(NULL,"-\n");
    
            
            if(number <= 11) // if number is less than 11 add to elementary list
                Add_NodePlayer(T->Point_to_Players,number,token2);

            if(number >11)// if number is greatest than 11 add to spare list
                Add_NodePlayer(T->Point_to_Spare_Players,number,token2);

        }
    }
    fclose (Fplayer);//close the file
}

//function to delete from queue delete from the first
void Delete_Queue (NodePlayer* H, int number)
{
    NodePlayer* P = H->Next;
    H->Next = H->Next->Next;
    free(P);
}

//function to change between players (from elementary to spare)
void Change_Player (NodePlayer* HP,NodePlayer* HSP, int numP, int numSP)
{
    NodePlayer* P1 =HP;
    NodePlayer* P2 = HSP;
    NodePlayer* TP = (NodePlayer*)malloc(sizeof(NodePlayer));
    TP->Next=NULL;

    int i=0;

    while (P2->Next != NULL)
    {
        P2=P2->Next;
        if (P2->number == numSP)
        {
            strcpy(TP->name,P2->name);//store the information in temp linked list
            TP->number = P2->number;
            Delete_Queue(HSP,P2->number);//delete from queue untill we found it
            break;
        }

        Add_NodePlayer(HSP,P2->number,P2->name);
        Delete_Queue(HSP,numSP);

        i++;
        if (i == 12)
        {
            printf("not found... ");
            return 0;
        }
    }

    NodePlayer* T =HP;

    while (P1->Next != NULL)
    {
        P1=P1->Next;
        if (P1->number == numP)
        {
            Add_NodePlayer(HSP,P1->number,P1->name);
            TP->Next = P1->Next;
            T->Next = TP;
            free(P1);
            break;
        }
        T = T->Next;
    }
}

//to modify certain team
void update (NodeTeam* H)
{
    char codeT [20];
    char nameT [20];
    char any [20];
    int x=0;
    NodeTeam* s;

    while (1)
    {

        printf("enter the code:");

        gets(codeT);//get the code
        gets(codeT);

        int o= isHere(H,codeT);//check id the code exit or not

        s = Find_ByCode(H,codeT);//return the node to modify it 

        if (o==0)//if the team code does not exit try again
        {
            printf("Try again!!\n");
            continue;
        }
        break;
    }
        while (1)//while true
        {
            
            printf("choose number to update data\n");
            printf("1. update team name\n");
            printf("2. update Number of win \n");
            printf("3. update Number of draws\n");
            printf("4. update Number of loses \n");
            printf("5. update goal difrentce\n");
            printf("0. to out\n");
        int c;
        scanf("%d",&c);

        if (c==1)
        {
            gets(nameT);
            gets(nameT);
            strcpy(s->name,nameT);//modify teamname
        }
        if(c==2)
        {
            scanf("%d",&x);
            s->info[0] = x;//NOW
        }
        if(c==3)
        {
            scanf("%d",&x);
            s->info[1] = x;//NOD
        }
        if(c==4)
        {
            scanf("%d",&x);
            s->info[2] = x;//NOL
        }
        if(c==5)
        {
            scanf("%d",&x);
            s->info[3] = x;//goals diffrence
        }
        if(c==0)
            break;
    }
    Calculate_the_points(H);

}

int main (){

    NodeTeam* Head = (NodeTeam*)malloc(sizeof(NodeTeam));//creat linkedlist for team
    Head->Next = NULL;

    NodeMatch* Head_Match = (NodeMatch*)malloc(sizeof(NodeMatch));//creat linkedlist for match
    Head_Match->Next = NULL;

    FILE * Fteams = fopen("teams.txt", "r");
    FILE *in = fopen("teamsInfo.txt", "w");//open file
    FILE *in2 = fopen("playersInfo.txt", "w");

    char lineTeam [40];

    int MAX_LENGTH = 40;
    int k=0;

    int i=0;

    while(1){
        printf("Enter ur number:\n1. Read the file TEAM.\n2. Calculate the points.\n3. Sorting..\n4. Add , Dealte & Update\n5. Print All TEAMS\n6. Save the Teams in File"
            "\n7. Create a match\n8. Read the teams players\n9. Change the players between elementary and spare\n10. Red card to..?\n11. Print all elementary players for a specific team\n12. Save Players in File\n");
        scanf("%d",&i);

        if (i==0)//exit the programe
            return 0;
        
        if(i==1)
        {
            while(fgets(lineTeam, sizeof(lineTeam), Fteams))//reads team file
            {
                char * token = strtok(lineTeam, ",");//divide the file by ,
    
                k=0;
                char *name;
                char *code;
                int infor[inf];

                while( token != NULL ) // while loop to store the elments 
                {
                    k++;

                    if (k==1)   
                        name = token;
                    
                    if (k==2)
                        code = token;
            
                    if (k==3)
                        infor[0] = atoi(token);
                
                    if (k==4)
                        infor[1] = atoi(token);
            
                    if (k==5)
                        infor[2] = atoi(token);

                    if (k==6)
                        infor[3] = atoi(token);

                    token = strtok(NULL, ",");
                }
                infor[4] =0;
                AddNode(name,code,infor,Head);// add to the end of linked list
            }

            fclose (Fteams);//close the file
        }

        if (i ==2)
            Calculate_the_points(Head);

        if (i==3){
            Radix_Sort(Head);
            //Read_Player(Head);
        }

        if (i==4)
        {
            int c;
            printf("1 For ADD, 2 For DELETE, 3 For UPDATE\n");
            scanf("%d",&c);
            
            if(c==1)
                Add_Team(Head);
            if (c==2)
                Delet_Team(Head);
            if (c==3)
                update(Head);

        }

        if (i==5)
            PrintTeam(Head);
        
        if (i==6)
        {
            NodeTeam *P = Head;//print in file --> teaminfo
            while (P->Next != NULL)
            {
                P=P->Next;
                fprintf(in,"name = %s, code = %s, wins = %d, draws = %d, loses = %d, goals = %d and points = %d\n", P->name,P->code,P->info[0],P->info[1],P->info[2],P->info[3],P->info[4]);
            }
            fclose (in);
        }

        if (i==7)
        {
            char Team1[MAX];
            char Team2[MAX];
            char any[MAX];

            gets(any);
            printf("Insert Team 1 : ");
            gets(Team1);

            gets(any);
            printf("Insert Team 2 : ");
            gets(Team2);

            if(isHere(Head,Team1) && isHere(Head,Team2))
                Create_a_match(Head_Match,Team1,Team2);
            else
                printf("Error...!!\n");
        }

        if (i==8)
        {
            Radix_Sort(Head);
            Read_Player(Head);
        }

        if (i==9)//to change the player
        {
            char Code[MAX];
            char any[MAX];

            gets(any);
            printf("Enter that Team code :");
            gets(Code);

            NodeTeam* J = Find_ByCode(Head,Code);//find the list

            int num1,num2;
            printf("insert the number of elemintry player, and splare player: ");
            scanf("%d\n%d", &num1,&num2);

            Change_Player(J->Point_to_Players,J->Point_to_Spare_Players,num1,num2);
        }

        if (i==10)//red card delete it from the list
        {
            char Code[MAX];
            char any[MAX];

            gets(any);
            printf("Enter that Team code :");
            gets(Code);

            int num;
            printf("insert the number of player");
            scanf("%d", &num);

            NodeTeam* J = Find_ByCode(Head,Code);

            NodePlayer *P = J->Point_to_Players;
            NodePlayer *T = J->Point_to_Players;
            while (P->Next != NULL)
            {
                P=P->Next;
                if (P->number == num)
                {
                    T->Next = P->Next;
                    free(P);
                    break;
                }
                T=T->Next;
            }
        }

        if (i==11)//list players for spesifc
        {
            char Code[MAX];
            char any[MAX];

            gets(any);
            printf("Enter that Team code :");
            gets(Code);

            PrintPlayers(Head,Code);
        }

        if (i == 12) // to print in the file
        {
            NodeTeam *P = Head;

            if (P->Next == NULL)
                printf("EMPTY");
    
            while (P->Next != NULL)
            {
                P=P->Next;
                fprintf(in2,"name = %s, code = %s, wins = %d, draws = %d, loses = %d, goals = %d and points = %d\n", P->name,P->code,P->info[0],P->info[1],P->info[2],P->info[3],P->info[4]);
        
                NodePlayer* L1 = P->Point_to_Players;
                NodePlayer* L2 = P->Point_to_Spare_Players;

                fprintf(in2,"Players:\n");

                if (L2->Next == NULL)
                    fprintf(in2,"no spare players...\n");
        
                while (L1->Next != NULL)
                {
                    L1 = L1->Next;
                    fprintf(in2,"number: %d, Name: %s\n",L1->number,L1->name);
                }
                fprintf(in2,"Spare Players:\n");

                if (L2->Next == NULL)
                    fprintf(in2,"no spare players...\n");

                while (L2->Next != NULL)
                {
                    L2 = L2->Next;
                    fprintf(in2,"number: %d, Name: %s\n",L2->number,L2->name);
                }
            }
            fclose(in2);//close the file
        }
    }
}
