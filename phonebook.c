#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "db.h"

// Prototypes to functions we will use, having them allows main to be at the top of the source code
void flushInput();
void showMenu();
void loadPhonebook();
void savePhonebook();
void newEntry();
void displayEntry();
void listEntries();
void deleteEntry();
void readName(char *name, int maxlen);

int main(int argc, char *argv[])
{
  if(argc != 2)
    {
      printf("\nUsage; %s <num records>\n\n", argv[0]);
      exit(-1);
    }

  int numRecords = strtol(argv[1], NULL, 10);

  if(numRecords < 1)
    {
      printf("Number of records must be a positive integer. You gave %d\n", numRecords);

      // Returning -1 indicates an error
      return -1;
    }

  initPhonebook(numRecords);
  printf("Hello, welcome to Phonebook!\n");
  showMenu();
  printf("\nGoodbye!\n");

  // Returning 0 indicates success
  return 0;
}

// Flush any stray character
void flushInput()
{
  char c;
  
  while((c = getchar()) != '\n' && c != EOF);
}

void readName(char *name, int maxlen)
{
  fgets(name, maxlen, stdin);
  name[strlen(name)-1] = '\0';
}

void showMenu()
{
  int exit = 0;

  while(!exit)
    {
      int nr, ms;

      getDBSize(&nr, &ms);

      printf("Phonebook records %d of %d\n\n", nr, ms);

      printf("1. Enter new entry\n");
      printf("2. Display entry\n");
      printf("3. List phonebook\n");
      printf("4. Delete entry\n");
      printf("5. Save phonebook\n");
      printf("6. Load phonebook\n");
      printf("0. Quit\n");

      printf("\nEnter choice: ");

      int num;

      scanf("%d", &num);
      flushInput();

      switch(num)
        {
        case 1:
          newEntry();
          break;

        case 2:
          displayEntry();
          break;

        case 3:
          listEntries();
          break;

        case 4:
          deleteEntry();
          break;

        case 5:
          savePhonebook();
          break;

        case 6:
            loadPhonebook();
          break;

        case 0:
            exit = 1;
          break;

        default:
          printf("Illegal entry. You entered %d. Please enter a number between 0-6.\n", num);
        }
    }
}

void loadPhonebook()
{
  printf("\nLOAD\n");
  printf(  "====\n\n");

  char filename[128];

  printf("Enter phonebook filename: ");
  scanf("%s", filename);
  
  flushInput();
  printf("\n");

  int result = loadDB(filename);

  if(result == OK)
    printf("\n** Load OK! **\n\n");
  else
    printf("\n** Load FAILED! **\n\n");
}

void savePhonebook()
{
  printf("\nSAVE\n");
  printf(  "====\n\n");

  char filename[128];

  printf("Enter phonebook filename: ");
  scanf("%s", filename);

  flushInput();
  printf("\n");

  int result = saveDB(filename);

  if(result == OK)
    printf("\n** Save OK! **\n\n");
  else
    printf("\n** Save FAILED! **\n\n");
}

void newEntry()
{
  printf("\nNEW ENTRU\n");
  printf(  "=========\n\n");

  char name[NAME_LENGTH];
  char countryCode[C_LENGTH];
  char phoneNumber[NUM_LENGTH];

  printf("Enter name: ");

  // No need to call flushInput after fgets (which is used in readName) because it already eats up the \n
  readName(name, NAME_LENGTH);

  printf("\nEnter country code: ");
  scanf("%s", countryCode);
  flushInput();

  printf("\nEnter phone number: ");
  scanf("%s", phoneNumber);
  flushInput();

  int result;

  addPerson(name, countryCode, phoneNumber, &result);

  switch(result)
    {
    case OK:
      printf("\n** NEW ENTRY OK **!\n");
      break;

    case DUPLICATE:
      printf("\n** ERROR: Person already exists. **\n\n");
      break;

    case MAX_REACHED:
      printf("\n** ERROR: Maximum records reached. **\n\n");
      break;

    default:
      printf("\n** ERROR: *SOMETHING* went wrong. **\n\n");
    }
}

void displayEntry()
{
  printf("\nDISPLAY\n");
  printf(  "=======\n\n");

  char name[NAME_LENGTH];

  printf("Enter name to search for: ");
  readName(name, NAME_LENGTH);
  TPhonebook *entry = findPerson(name);

  if(entry != NULL)
    {
      printf("\nName: %s\n", entry->name);
      printf("Phone: (%s)-(%s)\n\n", entry->countryCode, entry->phoneNumber);
    }
  else
    printf("\n** Cannot find entry %s. **\n\n", name);
}

void listEntries()
{
  listPhonebook();
}

void deleteEntry()
{
  printf("\nDELETE\n");
  printf(  "======\n\n");

  char name[NAME_LENGTH];

  printf("Enter name: ");
  readName(name, NAME_LENGTH);

  int result = deletePerson(name);

  if(result == OK)
    printf("\n** Deletion OK! **\n|n");
  else
    printf("\n** Cannot find %s **\n\n", name);
}
