// We implement linked list at book list
// We implement stack at reading progress
// We implement queue at book history

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define libraryBookSize 10

struct Author {
    char name[100];
    char nationality[100];
    char education[100];
    char award[100];
    char quote[100];
};

struct ReadingProgress {
    int page;
    struct ReadingProgress* nextPtr;
};

struct Book {
    char title[100];
    char publisher[100];
    char ISBN[18];
    char genre[100];
    char language[100];
    int publicationYear;
    int version;
    int numPages;
    struct Author author;
    struct ReadingProgress* readingProgress;
    struct Book* nextPtr;
};

struct BookHistory {
    struct Book book;
    struct BookHistory* nextPtr;
};

void displayLibraryBook(struct Book libraryBook[]);
void searchingSorting(struct Book libraryBook[]);
void sortByVersion(struct Book libraryBook[]);
void sortByNumPages(struct Book libraryBook[]);
void searching(struct Book libraryBook[], int searchingValue);
void addBook(struct Book** headBook, struct Book libraryBook[], struct BookHistory** front, struct BookHistory** rear, struct BookHistory** newptrHistory, struct BookHistory** temp, int* enqueueTimes);
void currentlyReadingBook(struct Book* headBook);
void readBook(struct Book* headBook);
void displayBookHistory(struct BookHistory* front, struct BookHistory* temp);
void deleteBook(struct Book** headBook);

int main() {
    int option, chooseBook;
    int enqueueTimes = 0;
    
    //Assume that there are only 10 books in our digital library
    struct Book libraryBook[10] = {
        {"Time Travel", "Borneo News", "978-000-000-000-0", "History", "English", 2010, 2, 310, {"Jojo", "Malaysian", "PhD", "History Award", "I believe in history"}}, 
        {"Learn Java", "Starch Press", "978-111-111-111-1", "Programming", "Hindi", 2016, 5, 158, {"Koko", "Indian", "Master", "Programming Award", "I believe in programming"}}, 
        {"Sapiens Brief", "Harper Col", "978-222-222-222-2", "History", "German", 1951, 1, 160, {"Lolo", "German", "Master", "History Award", "I love history"}},
        {"Silent Patient", "Cell Store", "978-333-333-333-3", "Thriller", "English", 2023, 3, 63, {"Momo", "American", "PhD", "Thriller Award", "I believe in thriller"}}, 
        {"Edu Learn", "Random Home", "978-444-444-444-4", "Memoir", "Japanese", 2001, 8, 189, {"Nono", "Japanese", "PhD", "Memoir Award", "I believe in memoir"}}, 
        {"Teh Tarik", "Cetakan UMPSA", "978-555-555-555-5", "Foods", "Malay", 2001, 3, 92, {"Popo", "Malaysian", "PhD", "Foods Award", "Food is everything"}}, 
        {"The Alchemist", "Nature Grp", "978-666-666-666-6", "Fiction", "Spanish", 2003, 6, 40, {"Roro", "Filipino", "Master", "Fiction Award", "I believe in fiction"}}, 
        {"Science Advances", "GIT Press", "978-777-777-777-7", "Science", "English", 1999, 9, 307, {"Soso", "Bengali", "Master", "Science Award", "I believe in science"}}, 
        {"Global Economic", "GIT Press", "978-888-888-888-8", "Economics", "Thai", 2024, 12, 524, {"Vovo", "Thai", "PhD", "Economics Award", "I believe in economics"}}, 
        {"AI Research", "Hangul News", "978-999-999-999-9", "Technology", "Korean", 2005, 8, 256, {"Yoyo", "Korean", "Master", "Technology Award", "I believe in technology"}}
    };
    displayLibraryBook(libraryBook);
    searchingSorting(libraryBook); //Searching, sorting
    struct Book* headBook = NULL;
    struct BookHistory *front= NULL, *rear= NULL; 
    struct BookHistory *newptrHistory, *temp;
    do {
        printf("\n\n**********************MENU*********************");
        printf("\n1) Add a book to borrow"); //Insert into linked list, Enqueue, Dequeue
        printf("\n2) Start reading"); //Update linked list, Stack
        printf("\n3) View book history"); 
        printf("\n4) Return book"); //Delete from linked list
        printf("\nSelect an option: ");
        scanf("%d", &option);
        if(option == 1) {
            displayLibraryBook(libraryBook);
            addBook(&headBook, libraryBook, &front, &rear, &newptrHistory, &temp, &enqueueTimes);
        } else if(option == 2) {
            currentlyReadingBook(headBook);
            readBook(headBook);
        } else if(option == 3) {
			displayBookHistory(front, temp);
		} else if(option == 4) {
			currentlyReadingBook(headBook);
			deleteBook(&headBook);
		}
    } while(option == 1 || option == 2 || option == 3 || option == 4);

    return 0;
}

void displayLibraryBook(struct Book libraryBook[]) {
    printf("\n**********List of book in our digital library************");
    for(int i = 0; i < 10; i++) {
        printf("\n%d) %s,\t %d,\t version %d,\t %d pages", i + 1, libraryBook[i].title, libraryBook[i].publicationYear, libraryBook[i].version, libraryBook[i].numPages);
    }
}

void searchingSorting(struct Book libraryBook[]) {
    int operation, sortBy, continueOperation, searchingValue;

    do {
        printf("\nSearching or sorting on the list[1 for sort / 2 for search / 3 for NO]: ");
        scanf("%d", &operation);
        if(operation == 1) {
            printf("Sort by[1 for version / 2 for number of pages]: ");
            scanf("%d", &sortBy);
            if(sortBy == 1) {
                sortByVersion(libraryBook);
            } else if(sortBy == 2) {
                sortByNumPages(libraryBook);
            }
            displayLibraryBook(libraryBook);
            printf("\nContinue sorting or searching on the list?[1 for yes / 2 for no]: ");
            scanf("%d", &continueOperation);
        } else if(operation == 2) {
            printf("Enter searching value for publication year: ");
            scanf("%d", &searchingValue);
            searching(libraryBook, searchingValue);
            printf("\nContinue sorting and searching on the list?[1 for yes / 2 for no]: ");
            scanf("%d", &continueOperation);
            displayLibraryBook(libraryBook);
        }
    } while((operation == 1 || operation == 2) && continueOperation == 1);

}

void sortByVersion(struct Book libraryBook[]) {
    for(int i = 0; i < libraryBookSize - 1; i++) {
        int min = i;
        for(int j = i + 1; j < libraryBookSize; j++) {
            if(libraryBook[j].version < libraryBook[min].version) {
                min = j;
            }
        }
        if(min != i) {
            struct Book temp = libraryBook[i];
            libraryBook[i] = libraryBook[min];
            libraryBook[min] = temp;
        }
    }
}

void sortByNumPages(struct Book libraryBook[]) {
    for(int i = 0; i < libraryBookSize - 1; i++) {
        int min = i;
        for(int j = i + 1; j < libraryBookSize; j++) {
            if(libraryBook[j].numPages < libraryBook[min].numPages) {
                min = j;
            }
        }
        if(min != i) {
            struct Book temp = libraryBook[i];
            libraryBook[i] = libraryBook[min];
            libraryBook[min] = temp;
        }
    }
}

void searching(struct Book libraryBook[], int searchingValue) {
    int searchingValueFound = 0;

    for(int i = 0; i < libraryBookSize; i++) {
        if(searchingValue == libraryBook[i].publicationYear) {
            printf("\n%d) %s,\t %d,\t version %d,\t %d pages", i + 1, libraryBook[i].title, libraryBook[i].publicationYear, libraryBook[i].version, libraryBook[i].numPages);
            searchingValueFound = 1;
        }
    }
    if(searchingValueFound == 0) {
        printf("Sorry, our library does not have any books published in the year %d", searchingValue);
    }
}

void addBook(struct Book** headBook, struct Book libraryBook[], struct BookHistory** front, struct BookHistory** rear, struct BookHistory** newptrHistory, struct BookHistory** temp, int* enqueueTimes) {
    int chooseBook;

    //Don't borrow the same book
    printf("\nChoose a book to borrow by entering the book number: ");
    scanf("%d", &chooseBook);
    chooseBook = chooseBook - 1;
    struct Book* newBookPtr = (struct Book*) malloc(sizeof(struct Book));
    strcpy(newBookPtr -> title, libraryBook[chooseBook].title);
    strcpy(newBookPtr -> publisher, libraryBook[chooseBook].publisher);
    strcpy(newBookPtr -> ISBN, libraryBook[chooseBook].ISBN);
    strcpy(newBookPtr -> genre, libraryBook[chooseBook].genre);
    strcpy(newBookPtr -> language, libraryBook[chooseBook].language);
    newBookPtr -> publicationYear = libraryBook[chooseBook].publicationYear;
    newBookPtr -> version = libraryBook[chooseBook].version;
    newBookPtr -> numPages = libraryBook[chooseBook].numPages;
    strcpy(newBookPtr -> author.name, libraryBook[chooseBook].author.name);
    strcpy(newBookPtr -> author.nationality, libraryBook[chooseBook].author.nationality);
    strcpy(newBookPtr -> author.education, libraryBook[chooseBook].author.education);
    strcpy(newBookPtr -> author.award, libraryBook[chooseBook].author.award);
    strcpy(newBookPtr -> author.quote, libraryBook[chooseBook].author.quote);
    struct ReadingProgress* newProgressPtr = (struct ReadingProgress*) malloc(sizeof(struct ReadingProgress));
    newProgressPtr -> page = 1;
    newProgressPtr -> nextPtr = NULL;
    newBookPtr -> readingProgress = newProgressPtr;
    newBookPtr -> nextPtr = NULL;
    if((*headBook) == NULL) {
        (*headBook) = newBookPtr;
    } else {
        struct Book* tempBookPtr = (struct Book*) malloc(sizeof(struct Book));
        tempBookPtr = (*headBook);
        while(tempBookPtr -> nextPtr != NULL) {
            tempBookPtr = tempBookPtr -> nextPtr;
        }
        tempBookPtr -> nextPtr = newBookPtr;
    }

    *newptrHistory = (struct BookHistory*) malloc(sizeof(struct BookHistory));
    (*newptrHistory)->book = libraryBook[chooseBook];
    *enqueueTimes = *enqueueTimes + 1;
	(*newptrHistory)->nextPtr = NULL;
    if(*front == NULL) {
		*front = *rear = *newptrHistory;
	}
	else {
		(*rear)->nextPtr = *newptrHistory;
		*rear = *newptrHistory;
	}
	if(*enqueueTimes > 3) {
		*temp = *front;
		*front = (*front)->nextPtr;
		free(*temp);
	} //Dequeue the book history
    printf("Insert Into Book Linked List Successfully\n");
}

void currentlyReadingBook(struct Book* headBook) {
    struct Book* tempBookPtr = (struct Book*) malloc(sizeof(struct Book));
    if((headBook) == NULL) {
        printf("\nThere is no book that you are currently reading");
    } else {
        int i = 0;
        tempBookPtr = headBook;
        printf("\nCurrently reading books: ");
        while(tempBookPtr != NULL) {
            while(tempBookPtr -> readingProgress -> nextPtr != NULL) {
                tempBookPtr -> readingProgress = tempBookPtr -> readingProgress -> nextPtr;
            }
            printf("\n%d) %s\t----- Page %d", i + 1, tempBookPtr -> title, tempBookPtr -> readingProgress -> page);
            tempBookPtr = tempBookPtr->nextPtr;
            i++;
        }
    }
}

void readBook(struct Book* headBook) {
    int chooseBook, page;

    struct Book* tempBookPtr = (struct Book*) malloc(sizeof(struct Book));
    tempBookPtr = headBook;
    if(tempBookPtr != NULL) {
        printf("\nChoose a book to start reading by entering the book number: ");
        scanf("%d", &chooseBook);
        for(int i = 1; i < chooseBook; i++) {
            tempBookPtr = tempBookPtr -> nextPtr;
            if(tempBookPtr == NULL) {
                break;
            }
        }
        if(tempBookPtr == NULL) {
            printf("\nNo such book in your currently reading book. Please enter a valid book number!");
        } else {
            while(tempBookPtr -> readingProgress -> nextPtr != NULL) {
                tempBookPtr -> readingProgress = tempBookPtr -> readingProgress -> nextPtr;
            }
            printf("\n%s\t----- Page %d", tempBookPtr -> title, tempBookPtr -> readingProgress -> page);
            printf("\nUser is reading the book choosen......");
            printf("\nFinished reading. Please update the progress before close the book");
            printf("\nEnter the page you are currently on: ");
            scanf("%d", &page);
            // if(page > tempBookPtr -> readingProgress -> page) {
            //     struct ReadingProgress* pushProgress = (struct ReadingProgress*) malloc(sizeof(struct ReadingProgress));
            //     pushProgress -> page = page;
            //     pushProgress -> nextPtr = NULL;
            //     tempBookPtr -> readingProgress -> nextPtr = pushProgress;
            // } else if (page < tempBookPtr -> readingProgress -> page) {
                
            // }
        }
    }
}

void displayBookHistory(struct BookHistory* front, struct BookHistory* temp) {
	if(front == NULL) {
		printf("No book history!");
	}
	else {
		int count = 0;
		temp = front;
		printf("\n**********Latest Three Book History*********");
		while(temp != NULL) {
			count++;
			printf("\n%d)\t%s, \t%d, \t version %d, \t %d pages", count, temp->book.title, temp->book.publicationYear, temp->book.version, temp->book.numPages);
			temp = temp->nextPtr;
		}
	}
}

void deleteBook(struct Book** headBook) {
	int position;
	printf("\nEnter the book index you want to delete[Starting from 1]: ");
	scanf("%d", &position);
	
	struct Book* deletePtr = *headBook;
	struct Book* tempPtr;
	
	if(position == 1) {
        *headBook = (*headBook)->nextPtr;
    } else {
        for(int i = 0; i < position - 1; i++) {
            tempPtr = deletePtr;
            deletePtr = deletePtr -> nextPtr;
            if(deletePtr == NULL) {
                printf("\n\n\nThe selected node does not exist");
                return;
            }
        }
        tempPtr -> nextPtr = deletePtr -> nextPtr;
    }
    free(deletePtr);
}