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

// global vars
struct lexicon_entry {
    unsigned long referencecount;
    char *entry;
    char *definition;
    struct lexicon_entry *next;
};

struct lexicon_entry *headnode;
struct lexicon_entry *tailnode;

// function prototypes (queue)
void enqueue( size_t referencecount, char *entry, char *definition );
struct lexicon_entry *dequeue( void );
void emptyqueue( void );
void createqueue( void );
void printqueue( void );
///////////////////////////////////////////


// function prototypes (rest of program)
int sanity_ok( void );
void help( void );
char *readfile( const char *filename );
char **makesentences( char *input );
size_t countsentences( char *input );
void enqeuesentences( char *sentences[], size_t sentences_counted );
void parsedictionaryfile( char *dictionaryfile );
void begin_execution( void );
///////////////////////////////////////////


int sanity_ok( void )
{

    int sanity_status = 1;

    if( !setlocale( LC_CTYPE, "" ) ) {
        fprintf( stderr, "LC_CTYPE not set! Please set appropriatelly and run again.\n" );
        sanity_status = 0;
    }

    return sanity_status;
}


void help( void )
{
    fprintf( stderr, "ΠΕΖ2015: Άσκηση 7η: Λεξικό.\n\n" );
    fprintf( stderr, "Επιλογές:\n" );
    fprintf( stderr, "\t-h | --help       Προβολή βοήθειας (αυτή εδώ που βλέπετε)\n");
    fprintf( stderr, "\t--file <αρχείο>   Φόρτωση δεδωμένων από από το συγκεκριμένο αρχείο\n");

    return;
}

char *readfile( const char *filename )
{
    char   *buff        = NULL;
    FILE   *infile      = NULL;
    struct stat *st     = NULL;

    st = malloc( sizeof( *st )  );

    if( -1 == stat( filename, st ) ) {
        fprintf( stderr, "Cannot stat file %s . Exiting\n", filename );
        exit( 1 );
    }

    infile = fopen( filename, "r" );
    if( NULL == infile ) {
        fprintf( stderr, "Cannot open file %s . Exiting\n", filename );
        exit( 1 );
    }

    // read file
    buff = malloc( sizeof( char )*st->st_size + 1 );
    if( 0 == fread( buff, st->st_size, sizeof( char ), infile ) ) {
        fprintf( stderr, "file %s is empty. Exiting\n", filename );
    }

    fclose( infile ); free( st );

    return buff;
}


size_t countsentences( char *input )
{
    size_t sentences_counted = 0;
    char *pointer = malloc( sizeof( char ) * strlen( input ) );
    strcpy( pointer, input );

    //parse sentences into char *array[], count number of sentences.
    for( pointer = strtok( pointer, "\n" ); pointer; pointer = strtok( NULL, "\n" ) ) {
        sentences_counted++;
    }

    return sentences_counted;
}


char **makesentences( char *input )
{
    size_t sentences_counted = 0;
    char *pointer = malloc( sizeof( char ) * strlen( input ) );
    char **sentences = NULL;

    strcpy( pointer, input );

    //parse sentences into char *array[], count number of sentences.
    for( pointer = strtok( pointer, "\n" ); pointer; pointer = strtok( NULL, "\n" ) ) {
        if( NULL != pointer ) {
            sentences = realloc( sentences, ( sizeof( char ) * ( sentences_counted + 1 ) ) );
            if( NULL == sentences ) {
                fprintf( stdout, "null pointer at sentences: %s\n", pointer );
            }

            sentences[ sentences_counted ] =  malloc( strlen( pointer ) + 1 );
            if( NULL == sentences[ sentences_counted ] ){
                fprintf( stdout, "null pointer at sentences[ %ld ]\n", sentences_counted );
            }
            strcpy( sentences[ sentences_counted ],  pointer );
            sentences_counted++;
        }
    }

    return sentences;
}


void enqeuesentences( char **sentences, size_t sentences_counted )
{
    short counter = 0;

    for( size_t retnuoc = 0; retnuoc < sentences_counted; retnuoc++ ) {

        char *definition = NULL;
        char *entry      = NULL;
        char *tempPtr1   = NULL;

        tempPtr1 = realloc( tempPtr1, sizeof( char ) * ( strlen( sentences[ retnuoc ]  ) + 1 ) );

        strcpy( tempPtr1, sentences[ retnuoc ] );

        for( tempPtr1 = strtok( tempPtr1, "|" ); tempPtr1 ; tempPtr1 = strtok( NULL, "|" ) ) {
            if( 1 == counter  ){
                counter = 0;
                definition = realloc( definition, sizeof( char ) * ( strlen( tempPtr1 ) + 1 )   );
                strcpy( definition, tempPtr1 );
                break;
            }

            if( 0 == counter  ) {
                counter = 1;
                entry = realloc( entry, sizeof( char ) * ( strlen( tempPtr1 ) + 1 ) );
                strcpy( entry, tempPtr1 );
                continue;
            }

        }

#ifdef DEBUG
        fprintf( stdout, "retnuoc: %ld\nentry: %s\ndefinition: %s\n", retnuoc, entry, definition );
#endif

        if( NULL != definition && NULL != entry ) {
            enqueue( 0 , entry, definition );
            memset( entry, 0 , strlen( entry ) );
            memset( definition, 0 , strlen( definition ) );
            memset( tempPtr1, 0 , strlen( tempPtr1 ) );

            free( entry ); free( definition );
            entry = NULL; definition = NULL;
            tempPtr1 = NULL;
        }
        else {
            fprintf( stdout, "=================================================\nNULL at : retnuoc: %ld\nentry: %s\ndefinition: %s\n=================================================\n", retnuoc, entry, definition );
        }

        // cannot free( tempPtr1 ), because it has been consumed by strtok( );
        // free( tempPtr1 );
    }

    return;
}


void parsedictionaryfile( char *dictionaryfile )
{
    size_t sentences_counted 	= 0;
    char *pointer  		 	 	= NULL;
    char **sentences 			= NULL;

    pointer = malloc( strlen( dictionaryfile ) + 1 );
    if( NULL == pointer && ENOMEM == errno ) {
        fprintf( stdout, "Run out of memory trying to parse sentences.\n" );
        exit( -1 );
    }
    strcpy( pointer, dictionaryfile );

    sentences_counted = countsentences( pointer );
    sentences = makesentences( pointer );
    enqeuesentences( sentences, sentences_counted );

    exit ( 1 );
    // add each def to the queue
    // zero out each reference number. reference nummber is supposed to be set to something
    // 		the first time each word is met.
    return;
}

void enqueue( size_t referencecount, char *entry, char *definition )
{

    if( NULL == tailnode ) {
        tailnode = malloc( sizeof( *tailnode ) );
        tailnode->next = NULL;

        tailnode->referencecount = referencecount;					// reference count

        tailnode->entry = malloc( sizeof( char ) * ( strlen( entry ) + 1 ) );			// entry, allocate mem
        strcpy( tailnode->entry, entry );							// entry, copy

        tailnode->definition = malloc( sizeof( char ) * ( strlen( definition ) + 1 ) );  // definition, allocate mem
        strcpy( tailnode->definition, definition );					// definition, copy

        headnode = tailnode;
    }
    else {

        struct lexicon_entry *tempnode = malloc( sizeof( *tempnode ) );
        tailnode->next = tempnode;

        tempnode->referencecount = referencecount;					// reference count

        tempnode->entry = malloc( strlen( entry ) + 1 );			// entry, allocate mem
        strcpy( tempnode->entry, entry );							// entry, copy


        if( NULL == definition ) {
            fprintf( stdout, "definition is null.\n" );
            exit( 1 );
        }
        tempnode->definition = malloc( sizeof( char ) * ( strlen( definition ) + 1 ) );  // definition, allocate mem
        strcpy( tempnode->definition, definition );					// definition, copy

        tempnode->next = NULL;
        tailnode = tempnode;

    }

    return;
}


struct lexicon_entry *dequeue( void )
{
    struct lexicon_entry *tempnode = headnode;

    if( NULL == tempnode ) {
        return NULL;
    }

    // walk the node
    if( headnode == tailnode ) {
        headnode = tailnode = NULL;
    }
    else {
        headnode = headnode->next;
    }

    return tempnode;

}


void emptyqueue( void )
{
    struct lexicon_entry *tempnode = headnode;

    if( NULL ==  headnode ) {
        return;
    }

    while( NULL != tempnode ){
#ifdef DEBUG
        fprintf( stdout, "Emptying queue: %ld, %s, %s\n",
                tempnode->referencecount, tempnode->entry, tempnode->definition );
#endif

        free( tempnode->entry );
        free( tempnode->definition );
        headnode = headnode->next;
        tempnode = headnode;
    }

    if( NULL == headnode ) {
        free( headnode );
        free( tailnode );
    }
    
    return;
}


void createqueue( void )
{
    headnode = tailnode = NULL;
}


void printqueue( void )
{
    struct lexicon_entry *tempnode = headnode;
    
    while( NULL != tempnode ){
        fprintf( stdout, "%ld, %s, %s", 
                tempnode->referencecount, tempnode->entry, tempnode->definition );
        if( NULL != tempnode->next ) {
            fprintf( stdout, " --> " );
        }
        tempnode = tempnode->next;
    }
    
    fprintf( stdout, " --> END\n" );
    
    return;
}


void begin_execution( void )
{
    //    char *inputfile      = readfile( "./input.txt" );
    char *dictionaryfile = readfile( "./dictionary.txt" );
    //    char *outputfile     = NULL;
    //    char *pointer        = dictionaryfile; // for strtok
    
    createqueue( );
    
    // enqueue all items in the dictionary
    parsedictionaryfile( dictionaryfile );
    
#ifdef DEBUG
    fprintf( stdout, "\n\n" );
    
    printqueue( );
    
    fprintf( stdout, "\n\n" );
#endif
    
#ifdef DEBUG
    if( NULL == headnode || NULL == tailnode ) {
        fprintf( stdout, "Queue is emptied. Exiting\n" );
    }
#endif
    
    return;
}


int main( void )
{
    // check the status of the terminal
    if( !sanity_ok( ) ) {
        exit( EXIT_FAILURE );
    }
    
    // in case of emergency grake blass
    begin_execution( );
    
    return 0;
}

