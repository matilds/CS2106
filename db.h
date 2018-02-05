#ifndef PHONEBOOK

#define PHONEBOOK

#define NAME_LENGTH 64
#define C_LENGTH    4
#define NUM_LENGTH  10

typedef struct
{
    unsigned index;
    int deleted;
    char name[NAME_LENGTH];
    char countryCode[C_LENGTH];
    char phoneNumber[NUM_LENGTH];
} TPhonebook;

enum
{
    OK,
    MAX_REACHED,
    DUPLICATE,
    CANNOT_FIND,
    SAVE_FAIL,
    LOAD_FAIL
};

// Initializes the phonebook for a maximum of macRecords file
// Pre: Phonebook is uninitiliazed, maxRecords contains maximum number of records in our phonebook
// Post: Phonebook is initialized to maxRecords records, each of which is empty
void initPhonebook(int maxRecords);

// Frees the phonebook
// Pre: Phonebook was previously initialized by initPhonebook
// Post: Phonebook is freed and no longer accessible
void freePhonebook();

// Adds in a new person into the phonebook
// Pre: Phonebook has been initialized, name = name of person, countryCode = three digit country code, phoneNumber = seven digit phone number
// Post: Person is inserted into phonebook if he isn't already there, the "result" parameter returns OK, MAX_REACHED or DUPLICATE
void addPerson(char *name, char *countryCode, char *phoneNumber, int *result);

// Looks for a person in the phonebook, full string match is required, partial matches are not supported
// Pre: Phonebook has been initialized, name = name of person to search for
// Post: Returns a pointer to the structure containing details of person if found, else NULL
TPhonebook *findPerson(char *name);

// Lists contents of phone book
// Pre: Phonebook has been initialized
// Post: Phonebook is listed on stdout
void listPhonebook();

// Deletes a person, full string match is required
// Pre: Phonebook is initialized, name = name of person to delete
// Post: Deletes name if it exists and returns OK, else returns CANNOT_FIND
int deletePerson(char *name);

// Saves phonebook
// Pre: Phonebook is initialized, filename = name of file to write phonebook to
// Post: Returns OK if successful and data is written to filename, else SAVE_FAIL
int saveDB(char *filename);

// Load phonebook
// Pre: filename = name of file to load phonebook from, phonebook does not need to be initialized
// Post: If successful, returns OK and phonebook is initialized and contents of filename are loaded, else LOAD_FAIL
int loadDB(char *filename);

// Resize phonebook
// Pre: Phonebook is previously initialized to a maximum size in number of records, numNewRecords = number which maximum number of records to be incremented by
// Post: Maximum size of phonebook is incremented by numNewRecords
void resizeDB(int numNewRecords);

// Get size of phonebook
// Pre: Phonebook is initialized
// Post: nr = number of non-empty records in phonebook, ms = maximum size of records in phonebook
void getDBSize(int *nr, int *ms);

#endif
