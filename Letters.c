#include "Letters.h"

//static node * head;
void loadFile(node** head)
{
	FILE* fp;
	letter data;
	char *fileName;

	fileName = getFileName();

	if (!(fp = fopen(fileName, "rb")))
    {
		printf("Error loading file!\a\n");
		free(fileName);
		return;
	}

	if (*head)
		deleteNode(head);

	while (1)
    {
		if (!fread(&data, sizeof(data), 1, fp))
			break;

		addNode(head, data, 2);
	}

	fclose(fp);

	if (!(*head))
		printf("No data loaded from \"%s\"\n", fileName);
	else
		printf("Info loaded successfully from \"%s\"\n", fileName);

	free(fileName);
}


void saveFile(node* head)
{
	FILE* fp;
	char *fileName;

	if (!head)
    {
		printf("List is empty!\n");
		printf("Add some new letters first!\n");
		return;
	}

	fileName = getFileName();

	if (!(fp = fopen(fileName, "wb")))
    {
		exit(1);
	}

	while (head)
    {
		if (fwrite(&head->data, sizeof(letter), 1, fp) != 1)
        {
			printf("Error occurred while writing on file\n");
			exit(1);
		}
		head = head->next;
	}

	fclose(fp);

	printf("Info saved successfully to \"%s\"\n", fileName);
	free(fileName);
}

char* getFileName()
{
	char *fileName = (char*)malloc(51 * sizeof(char));

    fflush(stdin);
	do{
        printf("\nEnter file name: ");
        scanf("%[^\t\n]s", fileName);
        fflush(stdin);
	}while (!strlen(fileName));

	if (!strchr(fileName, '.'))
    {
		strcat(fileName, ".dat");
	}

	return fileName;
}
void addNode(node** head, letter data, int mode)
{
	node* temp = (node*)malloc(sizeof(node));
	node* temp2 = *head;

	temp->data = data;
	temp->next = NULL;

	if(!(*head))
    {
		*head = temp;
		if(mode == 1)
			printf("First letter added successfully!\n");
		return;
	}

	while(temp2->next)
    {
		temp2 = temp2->next;
	}

	temp2->next = temp;
	if(mode == 1)
		printf("New letter added successfully!\n");
}
letter initLetter(node*head)
{
	letter newLetter;

       getID(head, newLetter.ID, 1);
       fflush(stdin);

        printf("Enter receiver: ");
        scanf("%[^\t\n]s", newLetter.receiver);
        fflush(stdin);

        printf("Enter copy to: ");
        scanf("%[^\t\n]s", newLetter.copyTo);
        fflush(stdin);

        printf("Enter sender: ");
        scanf("%[^\t\n]s", newLetter.sender);
        fflush(stdin);

        printf("Enter title: ");
        scanf("%[^\t\n]s", newLetter.title);
        fflush(stdin);

        printf("Enter content: ");
        scanf("%[^\t\n]s", newLetter.content);
        fflush(stdin);

      getDate(newLetter.date);

	return newLetter;
}

int getID(node* head, char*ID, int mode)
{
	while(1)
    {
		printf("\nEnter unique code: ");
		fflush(stdin);
        gets(ID);
		if( !isUnique(head, ID) )
		{
			if(mode == 1)
            {
				printf("Code already exist!\n");
				continue;
			}else//mode == 2
			{
			    return 1;
			}
		}
		break;
	}
	if(mode == 2)
		printf("Code not found!\n");
	return 0;
}
int isUnique(node*head, char*ID)
{
	while(head)
	{
		if(!strcmp(ID, head->data.ID))
        {
			return 0;
		}
		head = head->next;
	}
	return 1;
}
void getDate(char* date)
{
	int year, month, day, hour, minute, second;
        do
        {
		printf("Day: ");
		fflush(stdin);
		scanf("%d", &day);}
		while(day < 1 || day > 31);

        do{
		printf("Month: ");
		scanf("%d", &month);
		fflush(stdin);}
		while(month < 1 || month > 12);

        do{
		printf("Year: ");
		scanf("%d", &year);
		fflush(stdin);}
		while(year < 1960 || year > 2020);

		do{
        printf("Hours: ");
		scanf("%d", &hour);
		fflush(stdin);}
		while(hour < 1 || hour > 24);

		do{
		printf("Minutes: ");
		scanf("%d", &minute);
		fflush(stdin);}
		while(minute < 0 || minute > 60);

		do{
		printf("Seconds: ");
		scanf("%d", &second);
		fflush(stdin);}
		while(second < 0 || second > 60);

		sprintf(date, "%d.%.2d.%.2d %.2d:%.2d:%.2d", day, month, year, hour, minute, second);

}
void printData(letter data)
{
	printf("\nID:            %s", data.ID);
	printf("\nReceiver:      %s", data.receiver);
    printf("\nCopy to:       %s",data.copyTo);
    printf("\nSender:        %s",data.sender);
    printf("\nTitle:         %s",data.title);
    printf("\nContent:       %s",data.content);
    printf("\nDate:          %s\n",data.date);
}
void printList(node*head)
{
	int i = 1;

	if(!head)
    {
		printf("List is empty!\n");
		return;
	}
	while(head)
    {
        printf("\n %d", i);
        printData(head->data);
        i++;
		head = head->next;
	}
}
void printSpecificLetters(node*head)
{
    int i=0;

	if(!head)
    {
		printf("List is empty!\n");
		return;
	}
	while(head)
    {
        printf("\nLetter %d", ++i);
        printf("\nID:            %s", head->data.ID);
        printf("\nSender         %s",head->data.sender);
        printf("\nTitle:         %s",head->data.title);
        printf("\nDate:          %s\n",head->data.date);
		head = head->next;
	}
}
void printLetterByID(node *head)
{
    char ID[50] = {0};

    if(!head)
    {
		printf("List is empty!\n");
		return;
	}
    if (!getID(head,ID,2))
    {
        return;
    }
	while(head)
    {
        if (!strcmp(head->data.ID,ID))
        {
            printData(head->data);
            return;
        }
		head = head->next;
	}
}
void deleteSpam(node**head)
{
    int poss=1;
    char *token,word[20],word2[20],content[150];
    double flag=0, count=0,flag2=0;
    node *temp = *head;
    FILE *fp;

    if(!(fp = fopen("bad_words.txt","r")))
    {
        printf("Error opening file\n");
        return;
    }
    (fscanf(fp,"%s %s",word, word2));
     printf("Bad words is: %s   %s\n", word, word2);
    while(temp)
    {
        strcpy(content, temp->data.content);
        token = strtok(content, " ");
        while( token != NULL )
        {
            if(strstr(token, word))
            {
                flag++;
            }
            if(strstr(token, word2))
            {
                flag++;
            }
            rewind(fp);
            count++;
            token = strtok(NULL, " ");

        }
       // printf("%f", count);
        if (flag / count > 0.2)
        {
            deleteNodeAtPoss(head, poss);
            poss--;
            flag2 = 1;
        }
        poss++;
        flag = 0;
        count = 0;
        temp = temp->next;
    }
    if(flag2==1)
        printf("All spam is deleted!\n");
    else
        printf("Not found spam!\n");
    fclose(fp);
}

void deleteNodeAtPoss(node** head, int poss)
{
	int i;
	node *temp1 = (*head);
	node *temp2;

	if(poss == 1)
    {
		(*head) = temp1->next;
		free(temp1);
		return;
	}

    for(i = 0; i < poss-2; i++)
    {
		temp1 = temp1->next;

	}
	temp2 = temp1->next;
	temp1->next = temp2->next;
	free(temp2);
}

void deleteNode(node** head)
{
	node* temp;

	while(*head)
	{
		temp = *head;
		*head = (*head)->next;
		free(temp);
	}
}
void freeList(node* head)
{
    node * temp;

    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }

}

