/*
ΠΕΖ 2015
Άσκηση 7η

Σε πολλές εφαρμογές είναι χρήσιμη η χρήση ενός λεξικού με ορισμούς εννοιών
αλφαριθμητικών. Το λεξικό συνεπώς μπορεί να θεωρηθεί ότι είναι ενας πίνακας
δομών όπου σε κάθε θέση αποθηκεύεται το αλφαριθμητικό και ο ορισμός του.
Ορίστε συνεπώς μία δομή με το όνομα lexicon_entry και με μέλη δύο 
αλφαριθμητικά (λέξη και ορισμός της) και ένα πίνακα lexicon με Ν στοιχεία 
της δομής και υλοποιείστε μία συνάρτηση που γεμίζει τον πίνακα με στοιχεία.

Υλοποιήστε κυρίως πρόγραμμα το οποίο διαβάζει από ένα αρχείο με το όνομα 
input.txt μία συμβολοσειρά Α που θεωρούμε ότι μοντελοποιεί ένα κείμενο 
συνεπώς αποτελείται από μία ακολουθία λέξεων με κάθε λέξη να αποτελείται 
από συνεχόμενες εμφανίσεις αριθμητικών και αλφαβητικών χαρακτήρων, όλων 
του Αγγλικού αλφαβήτου. Υποθέτουμε ότι οι λέξεις οριοθετούνται με ένα ή 
περισσότερα κενά και ότι γίνεται διάκριση μεταξύ κεφαλαίων και πεζών γραμμάτων.

Το πρόγραμμα θα πρέπει να εντοπίζει τις λέξεις του Α που υπάρχουν στο λεξικό 
και να αντικαθιστά κάθε μία από αυτές με τον ορισμό της όπως διατυπώνεται 
στο λεξικό δημιουργώντας έτσι ένα νέο κείμενο Β. Το κείμενο Β θα πρέπει να 
αποθηκεύεται από τον χρήστη σε ένα αρχείο με το όνομα output.txt.

Υπόδειξη: Για την εύρεση των λέξεων που εμφανίζονται σε μία συμβολοσειρά
προτείνεται να χρησιμοποιηθεί η συνάρτηση char *strtok(char *s, char * ct)
της βιβλιοθήκης <string.h>. Για την σύγκριση αλφαριθμητικων προτεινεται η 
συνάρτηση int strcmp(cs, ct) της βιβλιοθήκης <string.h>.

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

// global vars
struct lexicon_entry {
	unsigned long referencecount;
	char *word;
	char *definition;
	struct lexicon_entry *next;
};

struct lexicon_entry *headptr = NULL;
struct lexicon_entry *tailptr = NULL;

void enqueue( unsigned long referencecount, char *word, char *definition );
struct lexicon_entry *dequeue( void );
void emptyqueue( void );
///////////////////////////////////////////


// function prototypes
int sanity_ok( void );
void help( void );
char *readfile( const char *filename );
int *parsefile( char *buffer, int *size );
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


int *parsefile( char *buffer, int *size )
{
	int   counter = 0;
	int  *rvalue  = NULL;
	char *pointer = NULL;

	counter   = 0;
	pointer = buffer;

	for( pointer = strtok( pointer, " " ); pointer; pointer = strtok( NULL, " " ) ) {

		rvalue = realloc( rvalue, sizeof( *rvalue ) * ( counter + 1 ) );
		rvalue[ counter ] = atoi( pointer );

		counter += 1;
	}

	*size = counter;

	return rvalue;
}

void enqueue( unsigned long referencecount, char *word, char *definition )
{
	struct lexicon_entry *temp = malloc( sizeof( *temp ) );

	temp->referencecount = referencecount;
	temp->word = malloc( sizeof( *word ) + 1 );
	strcpy( temp->word, word );
	temp->definition = malloc( sizeof( *definition ) + 1 );
	strcpy( temp->definition, definition );

	if( NULL == headptr && NULL == tailptr ){
		headptr = tailptr = temp;
		return;
	}
	tailptr->next = temp;
	tailptr = temp;

	return;
}


struct lexicon_entry *dequeue( void )
{

	struct lexicon_entry *temp = headptr;

	if( NULL == headptr ) {
		printf( "Queue is Empty\n" );
		return NULL;
	}

	if( headptr == tailptr ) {
		headptr = tailptr = NULL;
	}
	else {
		headptr = headptr->next;
	}

	temp = temp->next;
	headptr = temp;

	return temp;
}

void emptyqueue( void ) 
{
	return;
}

void parsedictionaryfile( char *dictionaryfile )
{
	// structure of file
	//		one definition per line
	//		word | definition until end of line
	char *pointer = dictionaryfile; // for strtok
	char *line    = NULL;

	// for each newline in the fle
	for( pointer  = strtok( pointer, "\n" ); pointer; pointer = strtok( NULL, " " ) ) {
		// break each line at | 
		line = pointer;
		for( line =  strtok( line, "|" ); line; line = strtok( NULL, " " ) ) {

		}
	}

	// add each def to the queue
	// zero out each reference number. reference nummber is supposed to be set to something
	// 		the first time each word is met.
	return;
}

void begin_execution( void )
{
	char *inputfile      = readfile( "./input.txt" );
	char *dictionaryfile = readfile( "./dictionary.txt" );
	char *outputfile     = NULL;
	char *pointer        = dictionaryfile; // for strtok
	long counter     	 = 0;

	// count the lines in dictionaryfile and then malloc size of dictionary + counter + 100
	for( pointer = strtok( pointer, "\n" ); pointer; pointer = strtok( NULL, " " ) ) {

		++counter;
	}
	// + 100 just incase
	outputfile = malloc( sizeof( *inputfile ) + sizeof( *dictionaryfile ) + counter + 100 );

	// enqueue all items in the dictionary
	parsedictionaryfile( dictionaryfile );


	pointer = inputfile; counter = 1;
	// re-strktok inputfile
	for( pointer = strtok( pointer, " " ); pointer; pointer = strtok( NULL, " " ) ) {
		
		// if current token matches ( strcmp() )
		// sprintf( outputfile, "[%ld] ", counter++ ) ;
		// push to stack the definitions used so far, along with number and reference, pop them
		//		at the end
		// write token to outputfile

	}

	// walk queue, add items at the end of outputfile

	// open file descriptor
	// write contents of outputfile to disk

	fprintf( stdout, "%s\n", inputfile );
	fprintf( stdout, "%s\n", dictionaryfile );

	pointer = NULL; free( inputfile ); free( dictionaryfile ); free( outputfile );

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
