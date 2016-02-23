/*

 ΠΕΖ2015 Άσκηση 6η:

 Θεωρείστε ότι δίδεται ο εξής ορισμός δομής:

 struct node {
	int data;
	struct node *next;
 };

 Με βάση τον ορισμό αυτό, το ζητούμενο είναι να σχεδιάσετε και να υλοποιήσετε
 μια συνδεδεμένη λίστα στοιχείων που ικανοποιεί τον κανόνα πρόσβασης
 First-In-First-Out, με άλλα λόγια μια δομή ουράς (queue). Στις δομές αυτές
 το στοιχείο το οποίο εντέθηκε πρώτο στη λίστα (με μία πράξη Insert) είναι και
 αυτό που θα διαγραφεί πρώτο (με μία πράξη Delete). Αυτή η λογική πράξεων μπορεί
 να υλοποιηθεί αν η ένθεση στοιχείων γίνεται στο τέλος της λίστας, ενώ η διαγραφή
 αφαιρεί στοιχεία από την αρχή της λίστας.

 Γράψτε συναρτήσεις σύμφωνα με τα παρακάτω πρότυπα, καθώς και ένα πρόγραμμα
 επίδειξης:

 * void Insert(struct node **headRef, int newData);
 * int Delete(struct node **headRef);
 * int GetNth(struct node *head, int index);
 * int Count(struct node *head, int searchFor);

 Η συνάρτηση Insert() δέχεται ως όρισμα ένα δείκτη στον δείκτη που αντιστοιχεί
 στην κεφαλή της λίστας. Δεσμεύει μνήμη, με κλήση της malloc(), για μια δομή του
 τύπου struct node, αποθηκεύει σ’αυτήν την ακέραια τιμή newData (στο πεδίο data)
 και συνδέει κατάλληλα την νέα δομή (βάσει του πεδίου next) ώστε η λίστα να
 ικανοποιεί τον κανόνα πρόσβασης First-In-First-Out, συνεπώς ενθέτει το νέο
 στοιχείο στο τέλος της λίστας.

 Η συνάρτηση Delete() δέχεται ως όρισμα ένα δείκτη στον δείκτη που αντιστοιχεί
 στην κεφαλή της λίστας διαγράφει και επιστρέφει ένα στοιχείο της λίστας έτσι
 ώστε να ικανοποιείται ο κανόνας "First In First Out", συνεπώς διαγράφει και
 επιστρέφει το πρώτο στοιχείο της λίστας.

 Η GetNth() δέχεται ως όρισμα τον δείκτη που αντιστοιχεί στην κεφαλή της
 λίστας, και την θέση (ως ακέραια τιμή που ξεκινά από το 0) ενός στοιχείου.
 Εφόσον η λίστα περιέχει στοιχείο στην καθοριζόμενη θέση, η συνάρτηση επιστρέφει
 την τιμή του πεδίου data για το στοιχείο αυτό, διαφορετικά εκτυπώνει κατάλληλο
 μήνυμα και επιστρέφει την τιμή 0.

 Η Count() δέχεται ως όρισμα τον δείκτη που αντιστοιχεί στην κεφαλή της λίστας,
 και μια ακέραια τιμή. Εξετάζει ένα-προς-ένα όλα τα στοιχεία της λίστας και
 επιστρέφει σε πόσα από αυτά το πεδίο data ισούται με την αναζητούμενη τιμή
 και επιστρέφει 0 εάν η τιμή δεν εμφανίζεται στην λίστα.

 Γράψτε την main() η οποία εμφανίζει μενού επιλογών στο χρήστη:

 1. Insert
 2. Delete
 3. Get-Nth
 4. Count
 5. Έξοδος

 Ανάλογα με την επιλογή του χρήστη ζητούνται τα απαραίτητα στοιχεία (π.χ. για
 την πράξη Insert ζητείται από τον χρήστη η ακέραια τιμή newdata) και καλείται η κατάλληλη συνάρτηση.

 */

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <limits.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>

// struct declerations
struct node {
    int data; // each struct node contains a character
    struct node *next; // pointer to next node
};

unsigned int nodescounted = 0;

///////////////////////////////////////////

// function prototypes
void printmenu( void );
void begin_execution( void );
int sanity_ok( void );

///////////////////////////////////////////

/// function prototypes for the queue
void Insert( struct node **headRef, int newData );
int  Delete( struct node **headRef );
int  GetNth( struct node  *headnode, int index );
int  Count(  struct node  *headnode, int searchFor );
void printqueue( struct node *headnode );
int  isempty( struct node *headRef );
void emptyqueue( struct node **headRef );
///////////////////////////////////////////


int sanity_ok( void )
{

    int sanity_status = 1;

    if( !setlocale( LC_CTYPE, "" ) ) {
        fprintf( stderr,
            "LC_CTYPE not set! Please set appropriatelly and run again.\n" );
        sanity_status = 0;
    }
    
    return sanity_status;
}



void Insert( struct node **headRef, int newData )
{
    struct node *temppt = malloc( sizeof( struct node ) );
    struct node *previoushead = NULL;
    struct node *currentptr = *headRef;

    if( NULL == temppt ) {
        printf("No memory available to insert %d. Exiting\n", newData);
        exit( 1 );
    }

    // setup the new node
    temppt->data = newData;
    temppt->next = NULL;

    // walk the queue; sets previoushead
    while( NULL != currentptr ) {
        previoushead = currentptr;
        currentptr = currentptr->next;
    }

    if( NULL == previoushead ) { // set the first item on the list
        temppt->next = *headRef;
        *headRef = temppt;
    }
    else { // insert new node at tail of list.
        previoushead->next = temppt;
    }

    ++nodescounted;

    return;
}


// delete a list element
int Delete( struct node **headRef )
{
    int value = 0;

    if( NULL == *headRef ){
        fprintf( stderr, "Queue is empty, nothing to delete\n" );
        return value;
    }

    // delete first node if a match is found
    value = (*headRef)->data;
    *headRef = (*headRef)->next; // de-thread the node

    --nodescounted;
    return value;
}


int GetNth( struct node *head, int index )
{

    struct node *tmpnode = head;
    unsigned int counter = 1;
    unsigned int indexx = (unsigned int) index;
    int value = 0;
#ifdef DEBUG
    fprintf( stderr, "Getting Nth item %d:\n", indexx );
#endif
    while( NULL != tmpnode ) {

        if( counter == indexx ) {
            value = tmpnode->data;
            break;
        }

        tmpnode = tmpnode->next;
        ++counter;
    }

    if( counter != indexx ) {
        fprintf( stdout, "Could not find anything at index %d\n", indexx );
    }
    else {
        fprintf( stdout, "Value at index %d is: %d\n", indexx, value );
    }


#ifdef DEBUG
    fprintf( stderr, "Done\n" );
#endif
    return value;
}


int Count(  struct node  *head, int searchFor )
{
    struct node *tmpnode = head;
    unsigned int counter = 0;
#ifdef DEBUG
    fprintf( stderr, "Getting count for item %d\n", searchFor ) ;
#endif
    while( NULL != tmpnode ) {
        if( tmpnode->data == searchFor ) {
            ++counter;
        }
        tmpnode = tmpnode->next;
    }

    fprintf( stdout, "%d appears %u times in the queue\n", searchFor, counter );

    return counter;
}

int isempty(struct node *tempptr)
{
    return tempptr == NULL;
}


void printqueue( struct node *headnode )
{
    struct node *tempnode = headnode ;
    // if list is empty
    if( isempty( headnode ) ) {
        fprintf( stdout, "Nothing in the queue\n" );
        return;
    }

    while( NULL != tempnode ) {
        fprintf( stdout, "%d", tempnode->data );
        if( NULL != tempnode->next ) {
            fprintf( stdout, " --> " );
        }
        tempnode = tempnode->next;
    }

    fprintf( stdout, " --> END\n" );

    return;
}


void emptyqueue( struct node **headRef )
{

    struct node *tmpnode = *headRef;
    struct node *prevnode = NULL;

    while( NULL != tmpnode ) {
        prevnode = tmpnode;
        tmpnode = tmpnode->next;
        free( prevnode );
    }

    return;
}


void printmenu( void )
{
    fprintf( stdout, "please choose:\n");
    fprintf( stdout, "1. Insert 2. Delete 3. Get-Nth 4. Count\n" );
    fprintf( stdout, "5. Exit\n" );
    fprintf( stdout, "> " );

    return;
}


void begin_execution( void )
{
    struct node *head = NULL;
    int enteredvalue = 9001;  // 9001 being outside the generated
                               // range of values
    unsigned int userchoice = 10;
   	const unsigned int exitcode     = 5;  // exit menu

    do {
        printmenu( );
        scanf("%u", &userchoice);
        switch( userchoice ) {
            case 1: 	// insert
                fprintf( stdout, "Please insert an integer: " );
                scanf( "%d", &enteredvalue );
                Insert( &head, enteredvalue );
                break;
            case 2: 	// delete
                Delete( &head );
                break;
            case 3: 	// Get-Nth
                fprintf( stdout, "Please insert an index: " );
                scanf( "%d", &enteredvalue );
                GetNth( head, enteredvalue );
                break;
            case 4: 	// Count
                fprintf( stdout, "Please enter the value you want counted: " );
                scanf( "%d", &enteredvalue );
                Count( head, enteredvalue );
                break;
            case 5: 	// empty the queue before exiting
                fprintf( stdout, "Emptying out the queue\n" );
                emptyqueue( &head );
                break;
            default:
                fprintf( stdout, "No such choice. Please try again.\n" );
                break;
        }
        
        if( exitcode != userchoice) {
            printqueue( head ); } // the score so far

    } while( exitcode != userchoice );

    return;
}


int main( void )
{
    // check the status of the terminal
    if( !sanity_ok( ) ) {
        exit( EXIT_FAILURE );
    }

    begin_execution( );
    
    return 0;
}
