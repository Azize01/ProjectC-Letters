#include "Letters.h"

int main()
{
    node * head = NULL;
    int i;
     while(1)
    {
	printf("\n                   MENU   \n");
	printf("                                           \n");
	printf("   1. LOAD FILE                            \n");
	printf("   2. SAVE FILE                            \n");
	printf("   3. ADD NEW LETTER                       \n");
	printf("   4. PRINT SPECIFIC LETTERS               \n");
	printf("   5. PRINT LETTER BY ID                   \n");
	printf("   6. DETELE SPAM                          \n");
	printf("   7. PRINT ALL DATA                       \n");
	printf("   0. EXIT                                 \n");

	do{
		printf("\nSELECT OPTION: ");
		fflush(stdin);
		scanf("%d", &i);
	  }while(i < 0 || i> 7);
	switch(i)
		{

			case 1: loadFile(&head);
				break;
			case 2: saveFile(head);
				break;
			case 3: addNode(&head, initLetter(head), 1);
				break;
            case 4: printSpecificLetters(head);
				break;
			case 5: printLetterByID(head);
				break;
			case 6: deleteSpam(&head);
				break;
			case 7: printList(head);
				break;
            case 0: printf("Goodbye! Have a nice day!");
                exit(1);
			default:freeList(head);
				return 0;
		}
     }
}
