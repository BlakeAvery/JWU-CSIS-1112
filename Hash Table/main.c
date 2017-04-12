#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct album
{
    char artist[50];
    struct album *next;
}album;


int hash(char artistName[50]);
void insertAlbum(char artist[50]);
struct album* searchFor(char needle[50]);
void displayTable();
void destroyAlbum(char artist[50]);

album hashtable[6];

int main(void)
{
    int i;


    for(i = 0; i < 6; i++)
        {
            hashtable[i].next = NULL;
            strcpy(hashtable[i].artist, "\0");
        }

    char input[50];

    printf("Enter an artist: ");
    scanf(" %s", &input);

    do
    {
        insertAlbum(input);
        printf("Enter an artist: ");
        scanf(" %s", &input);
    } while(_stricmp(input, "A") != 0);
        displayTable();
    //searchFor("Oscars");



}

int hash(char artistName[50])
{
    int j, sum;
    sum = 0;

    for(j = 0; j < strlen(artistName); j++)
        {
            sum += artistName[j];
        }
    return sum % 6;
}

void insertAlbum(char artist[50])
{
    int j;
    int index = hash(artist);
    struct album *newPtr = (struct album*) malloc(sizeof(struct album));
    struct album *currentPtr;
    struct album *previousPtr;
    // Check for empty list
    if(strcmp(hashtable[index].artist, "\0") == 0) {
        hashtable[index].next = newPtr;
        strcpy(hashtable[index].next->artist, artist);
        hashtable[index].next = NULL;
        //hashtable[index].cnt += 1;

    } else {
        if(_stricmp(hashtable[index].next->artist, artist) > 0) {
            strcpy(newPtr->artist, artist);
            currentPtr = hashtable[index].artist;
            hashtable[index].next = newPtr;
            //hashtable[index].cnt += 1;
        } else {
            previousPtr = hashtable[index].artist;
            currentPtr = hashtable[index].next->artist;
            //hashtable[index].cnt += 1;
            while(_stricmp(currentPtr->artist, artist) < 0) {
                if(currentPtr->next != NULL) {
                    currentPtr = currentPtr->next;
                    previousPtr = previousPtr->next;
                } else {
                    break;
                }
            }
            if(_stricmp(currentPtr->artist, artist) > 0) {
                strcpy(newPtr->artist, artist);
                newPtr->next = currentPtr;
                previousPtr->next = newPtr;
            } else {
                strcpy(newPtr->artist, artist);
                newPtr->next = NULL;
                currentPtr->next = newPtr;
            }
        }
    }
}



/*{
    int index = hash(artist);
    struct album *tmp_ptr = (struct album*) malloc(sizeof(struct album));
    struct album *currentPtr = &(hashtable[index]);
    struct album *previousPtr;
    tmp_ptr->next = NULL;

    if (_stricmp(hashtable[index].artist, "\0") == 0)
    { // Check for empty
        printf("check 1\n");
        hashtable[index] = *tmp_ptr;
    }
    else
    {
        printf("check 2\n");
        if (_stricmp(tmp_ptr->artist, hashtable[index].artist) < 0)
        { // Check for first
            printf("check 3\n");
            tmp_ptr->next = &(hashtable[index]);
            hashtable[index] = *tmp_ptr;

        }//end if Check for first
        else
        {
            printf("check 4\n");
            while (currentPtr != NULL || _stricmp(tmp_ptr->artist,currentPtr->artist) > 0 || currentPtr->next == NULL)
            {
                printf("check 5\n");
                previousPtr = currentPtr;
                printf("check 6\n");
                currentPtr = currentPtr->next;
                printf("check 7\n");
            }
        if (currentPtr == NULL)
        {
            printf("check 8\n");
            previousPtr->next = tmp_ptr;
        }
        else
        {
            printf("check 9\n");
            previousPtr->next = tmp_ptr;
            tmp_ptr->next = currentPtr;
        }
        }
    }
} */

/*void insertAlbum(char artist[50])
{

    int index = hash(artist);
    struct album *tmp_ptr;
    struct album *tmp_album = (struct album*) malloc(sizeof(struct album));
    tmp_album->next = NULL;
    strcpy(tmp_album->artist, artist);
    if(hashtable[index].next == NULL)
        {
            hashtable[index] = *tmp_album;
        }
    struct album *currentPtr = &(hashtable[index]);
    while(currentPtr->next != NULL)
        {
            if (_stricmp(currentPtr->next->artist, artist) < 0)
                {
                    tmp_ptr = currentPtr->next;
                    printf("%s",tmp_ptr->artist);
                    currentPtr->next = tmp_album;
                    printf("%s",currentPtr->next->artist);
                    strcpy(currentPtr->next->artist,artist);
                    currentPtr->next = tmp_ptr;
                    printf("%s",currentPtr->next->artist);

                }
            currentPtr = currentPtr->next;
        }
} */

struct album* searchFor(char needle[50])
{
    int index = hash(needle);
    struct album *currentPtr = &(hashtable[index]);
    while(_stricmp(currentPtr->artist, needle) != 0) {
        if(currentPtr->next == NULL)
            {
                printf("%s not in table!", needle);
                break;
            }
        else
            {
                currentPtr = currentPtr->next;
            }
    }
    if(_stricmp(currentPtr->artist, needle) == 0) {
        printf("Found %s!", needle);
        return &(currentPtr);
    }
    return NULL;
}

void displayTable() {
    int j;
    struct album *currentPtr;
    for(j = 0; j < 6; j++) {
        currentPtr = hashtable[j].artist;
        while(currentPtr != NULL) {
            printf("%s:%i\n", currentPtr->artist, j);
            currentPtr = currentPtr->next;
        }
    }
}

void destroyAlbum(char artist[50])
{
    int index = hash(artist);
    struct album *current = &(hashtable[index]);

    while (_stricmp(current->next->artist, artist) != 0)
        {
            if(current->next == NULL)
                {
                    return EXIT_FAILURE;
                }
            current = current->next;
        }

    current->next = current->next->next;
}

