#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<process.h>
#include<time.h>
#define MAX 10
int count=0;
int ed[10];
int x=0;
int total[10][1];
int quit=0;

//Declaration of all initial Pointers
struct AllUsers *start[MAX];
struct newAccount *ptrNewUser;
struct TimeLine *top=NULL;
struct addEducation *edu[10];
/*
USER ACCOUNT STRUCTURE
*/
struct newAccount
{
    char emailId[50];
    char name[10];
    char password[50];
    struct newAccount *connected[MAX];
    struct addEducation *education;
    struct timeline *next;


};
/*
    *STRUCTURE FOR EDUCATION DETAILS OF USERS
    *USERS CAN ENTER AS MANY DETAILS REQUIRED
*/
struct addEducation
{
    char Edu[1000];
    struct addEducation *next;
};
/*
    *STRUCTURE OF TIMELINE
*/
struct Timeline
{
    char post[1000];
    char postedBy[10];
    char DateandTime[30];
    struct TimeLine *next;
};

struct AllUsers{
    char emailId[50];
    struct newAccount * account;
};

//LOGIN FUNCTION FOR LOGIN IN ACCOUNT

void Login()
{
    if(start[0]==NULL)
    {
        printf("\nSIGN UP FIRST..");
        return;
    }
    char a[50];
    printf("\nEMAIL-ID : ");
    scanf("%s",a);
    int i=0,flag=0;

    while(i<count)
    {
        if(strcmp(start[i]->emailId,a)==0)
        {
            UserAccount(i);
            flag++;
            break;
        }
        i++;
    }
    if(flag==0)
    {
        printf("\nINVALID USERS EMAIL-ID!!!!");
    }
}

/*To connect with other in Linked in...*/
void Connect(char a[],int i)
{
    int j=0,l=0,flag=0,flag1=0;
    while(j<count)
    {
        if(strcmp(a,start[j]->account->name)==0)
        {
            if(i==j)
            {
                printf("CANNOT BE CONNECTED BY SELF!\n");
                flag++;
                break;
            }
            printf("\nCONNECTED WITH %s",a);

            start[i]->account->connected[total[i][0]]=start[j]->account;
            start[j]->account->connected[total[j][0]]=start[i]->account;

            total[i][0]=total[i][0]+1;
            total[j][0]=total[j][0]+1;
            flag++;
            break;
        }
        j++;
    }
    if(flag==0)
    {
        printf("\n%s IS NOT PRESENT IN LINKEDIN!",a);
    }

}
/*ALL CONNECTIONS WILL BE DISPLAYED HERE*/

void AllConnection(int i)
{
    int j=0;
    if(total[i][0]==0)
    {
        printf("NO CONNECTION\n");
    }
    while(j<total[i][0])
    {
        printf("%s\n",start[i]->account->connected[j]->name);
        j++;
    }
}
void UsersTimeLine(int i)
{
    struct Timeline *temp;
    temp =(struct TimeLine *)malloc(sizeof(struct Timeline));

    printf("\n\nADD POST(MAX SIZE 1000 CHAR) :");
    scanf(" %[^\n]%*c",temp->post);

    strcpy(temp->postedBy,start[i]->account->name);

    temp->next=NULL;
    /*FOR CURRENT TIME AND DATE */
    time_t mytime;
    mytime = time(NULL);
    strcpy(temp->DateandTime,ctime(&mytime));


    if(top==NULL)
    {
        top= temp;
    }
    else
    {
        temp->next=top;
        top=temp;
    }
    printf("\n*************************************************");
    printf("\nPOSTED BY : %s\n",temp->postedBy);
    printf("ON DATE AND TIME : %s",temp->DateandTime);
    printf("POST  : %s",temp->post);

}
void AllTimeLine()
{
    struct Timeline *temp;
    temp = top;
    char ch;
    if(temp==NULL)
    {
        printf("NO TIMELINE PRESENT!!!!!\n");
        return;
    }
    while(temp!=NULL)
    {

        printf("\n\n**************POSTED BY : %s*****************\n",temp->postedBy);
        printf("ON DATE AND TIME : %s",temp->DateandTime);
        printf("\nPOST           : %s",temp->post);


        do{
            printf("\n\nCONTINUE VIEWING TIMELINE?(Y/N) :");
            printf("\ncmd>>>");
            scanf(" %c",&ch);
            if(ch=='Y')
            {
                temp=temp->next;
            }
            else if(ch=='N')
                 break;
            else
            {
                printf("INVALID INPUT!!");
                continue;
            }
        }
        while(ch!='Y');
        if(temp==NULL)
        {
            printf("\nNO TIMELINE PRESENT!!!!!\n");
            break;
        }
    }

}
void AddEducation(int i)
{
    char a[1000];
    struct addEducation *temp;
    temp=(struct addEducation *)malloc(sizeof(struct addEducation));

    printf("ADD EDUCATION DETAILS : ");
    scanf(" %[^\n]%*c",temp->Edu);
    temp->next=NULL;
    if(edu[i]==NULL)
    {
       edu[i] = temp;
    }
    else
    {
        temp->next=edu[i];
        edu[i]=temp;
    }
    ed[i]++;
}

void Profile(int i)
{
    struct addEducation *temp;
    temp=edu[i];
    printf("NAME             :%s",start[i]->account->name);
    printf("\nEMAIL ID         :%s",start[i]->account->emailId);
    printf("\nEDUCATION        :-\n");
    if(temp==NULL)
    {
        printf("NO EDUCATION DETAILS...");
    }
    else
    while(temp!=NULL)
    {
        printf("                  %s\n",temp->Edu);
        temp = temp->next;
    }
}
/*After login user will be able to access his/her Account*/
void UserAccount(int i)
{
    char a[50],cmd1[10],cmd2[10],s1,s2;
    int flag=0;
    printf("ENTER PASSOWORD : ");
    scanf("%s",a);

    if(strcmp(a,start[i]->account->password)!=0)
    {
        printf("INVALID PASSWORD!!!!");
        return;
    }
    system("COLOR 0C");

    system("CLS");
    printf("\n\n\t\t\tSUCCESSFULLY LOGGEDIN....");
    printf("\n\t\t\tWelcome to LinkedIn......");
    x++;


    printf("\nUSERNAME :- %s\n",start[i]->account->name);
    do
    {
        flag =0;
        fflush(stdin);
        printf("\n\n\ncmd>>>");
        scanf("%s",cmd1);
        if(strcmp(cmd1,"QUIT")==0)
        {
            quit=1;
            break;
        }
        else if(strcmp(cmd1,"LOGOUT")==0)
        {
            x=0;
            printf("LOGOUT!!!!!\n\n");
            system("cls");
            return;
        }
        else if(strcmp(cmd1,"CLS")==0)
        {
            system("cls");
            continue;
        }
        else if(strcmp(cmd1,"CONNECT")==0)
        {
            scanf("%s",cmd2);
            if(strcmp(cmd2,"WITH")==0)
            {
                scanf("%s",a);
                flag++;
                Connect(a,i);
            }

        }
        else if(strcmp(cmd1,"VIEW")==0)
        {
            scanf("%s",cmd2);
            if(strcmp(cmd2,"CONNECTIONS")==0)
            {
                    flag++;
                    AllConnection(i);
                    continue;
            }
            else if(strcmp(cmd2,"TIMELINE")==0)
            {
                 flag++;
                 AllTimeLine(i);
                 continue;
            }
            else if(strcmp(cmd2,"PROFILE")==0)
            {
                 flag++;
                 Profile(i);
                 continue;
            }
        }
         else if(strcmp(cmd1,"ADD")==0)
         {
            scanf("%s",cmd2);
            if(strcmp(cmd2,"TIMELINE")==0)
            {
                    flag++;
                    UsersTimeLine(i);
                    continue;
            }
            else if(strcmp(cmd2,"EDUCATION")==0)
            {
                scanf("%s",a);
                if(strcmp(a,"DETAIL")==0)
                {
                    flag++;
                    AddEducation(i);
                    continue;
                }
            }
        }
        if(flag==0){
            printf("INVALID COMMAND!!!!");
        }

    }
    while(1==1);

}


/*All users*/
void graph()
{
    struct AllUsers *ptr;
    ptr=(struct AllUsers *)malloc(sizeof(struct AllUsers));
    strcpy(ptr->emailId,ptrNewUser->emailId);

    ptr->account=ptrNewUser;
    start[count++]=ptr;


}


/*CREATING NEW USER ACCOUNT*/
void NewUserSignUp()
{
    if (count>=10)
    {
        printf("\nmini LinkedIn project is only for maximum 10 users ");
        return;
    }

    struct  newAccount *temp;
    char pass1[50],pass2[50];
    temp=(struct newAccount * )malloc(sizeof(struct newAccount));
    printf("\nUSER EMAIL ID : ");
    scanf("%s",&temp->emailId);
    char ch;
    int i=0;
    printf("USERNAME : ");
    scanf("%s",&temp->name);
    printf("PASSWORD : ");
    while (1)
    {
        if (i < 0)
          i = 0;

        ch = getch();

        if (ch == 13)
            break;
        if (ch == 8) /*ASCII value of BACKSPACE*/
        {
             putch('\b');
             putch(NULL);
             putch('\b');
             i--;
             continue;
        }

      pass1[i++] = ch;
      ch = '*';
      putch(ch);
   }

   pass1[i] = '\0';

   //REENTERING THE PASSWORD
   printf("\nRE-ENTER PASSWORD : ");
   i=0;
    while (1)
    {
        if (i < 0)
          i = 0;

        ch = getch();

        if (ch == 13)
            break;
        if (ch == 8) /*ASCII value of BACKSPACE*/
        {
             putch('\b');
             putch(NULL);
             putch('\b');
             i--;
             continue;
        }

      pass2[i++] = ch;
      ch = '*';
      putch(ch);
   }

   pass2[i] = '\0';
   if(strcmp(pass1,pass2)==0)
   {
       strcpy(temp->password,pass1);
       printf("\n\n          Account Created Successfully");


       ptrNewUser=temp;
       graph();
   }
   else{
    printf("\nIncorrect Password...");
    free(temp);
   }
}

/*
    LOADING PAGE IS TO LOAD THE LINKED PAGE INITAILLY
    THIS TECHINUE I LEARNED BY YOUTUBE VIDEO....
    LINK IS : - https://youtu.be/8UZTjAV7HUE
*/

void Loading_page()
{
    int a1;
    system("cls");
    printf("\n\n");
    printf("                           LinkedIn");
    printf("\n\n\n   LOADING ");
    for(a1=0;a1<50;a1++)
    {
        Sleep(100);
        printf("%c",219);
    }

}
void Instruction()
{
    printf("\n         THIS MINI PROJECT OF LINKED IN IF ONLY FOR CONNECTING 10 PEOPLE\n\n");
    printf("\n         COMMAND FOR SIGN UP              : SIGN UP");
    printf("\n         COMMAND FOR LOGIN                : LOGIN ACCOUNT");
    printf("\n         COMMAND FOR ADD TIMELINE         : ADD TIMELINE");
    printf("\n         COMMAND FOR VIEW TIMLINE         : VIEW TIMELINE");
    printf("\n         COMMAND FOR CONNECT USERS        : CONNECT WITH (USER NAME)");
    printf("\n         COMMAND FOR VIEW FRIENDS         : VIEW CONNECTION");
    printf("\n         COMMAND FOR ADD EDUCATON DETAILS : ADD EDUCATION DETAIL");
    printf("\n         COMMAND FOR PROFILE VIEW         : VIEW PROFILE");
    printf("\n         COMMAND FOR LOGOUT               : LOGOUT");
    printf("\n         COMMAND FOR TERMINATE            : QUIT");

}
void main()
{
    system("COLOR 0A");//FOR COLOUR OF BACKGROUNG
    Loading_page();
    system("cls");

    Instruction();


    int i=0;

    do{

        printf("\n\n\n\t\t\tLINKEDIN HOME PAGE\n");
        char cmd1[10],cmd2[10];
        system("COLOR 79");
        quit=0;
        fflush(stdin);
        printf("\n\ncmd>>>");
        scanf("%s",cmd1);
        if(strcmp(cmd1,"CLS")==0)
        {
            system("cls");
            continue;
        }
        else if(strcmp(cmd1,"QUIT")==0)
        {
            quit=1;
        }
        else if(strcmp(cmd1,"SIGN")==0)
        {
            scanf("%s",cmd2);
            if(strcmp(cmd2,"UP")==0)
            {
                NewUserSignUp();
            }
            else
            {
                printf("INVALID COMMAND!!!!\n");
            }
        }
        else if(strcmp(cmd1,"LOGIN")==0)
        {
            scanf("%s",cmd2);
            if(strcmp(cmd2,"ACCOUNT")==0)
            {
                if(x==0)
                {
                    Login();
                }
                else{
                    printf("\nLOGOUT CUURENT USERS FIRST....");
                }

            }
            else
            {
                printf("INVALID COMMAND!!!!\n");
            }
        }
        else
        {
            printf("INVALID COMMAND!!!!\n");
        }
    }
    while(quit!=1);
}

