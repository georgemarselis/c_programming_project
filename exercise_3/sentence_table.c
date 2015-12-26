/* 

Άσκηση 3η

Μία από τις πιο σημαντικές χρήσεις της γλώσσας C είναι στη διαχείριση
αλφαριθμητικών, και αυτό γιατί η C παρέχει πολλές ευκολίες στη διαχείρισή
τους. Σκοπός της συγκεκριμένης άσκησης είναι η διερεύνηση αυτών των 
δυνατοτήτων, για τον αποτελεσματικό χειρισμό ενός πίνακα αλφαριθμητικών.
Θεωρήστε λοιπόν ένα πίνακα Ν θέσεων όπου σε κάθε θέση αποθηκεύεται η 
τιμή μίας μεταβλητή τύπου δομής με δύο μέλη ένα αλφαριθμητικό που συμβολίζει
μία πρόταση κειμένου και μία ακέραια τιμή που υποδηλώνει το μήκος του 
αλφαριθμητικού. Θεωρήστε ότι κάθε αλφαριθμητικό είναι το καθένα μέγιστου
μήκους Μ-1 και αποτελείται από ένα σύνολο λέξεων, με κάθε λέξη να αποτελείται 
μόνο από αριθμητικούς και αλφαβητικούς χαρακτήρες (όλοι του Αγγλικού 
αλφαβήτου), χωρίς κενά, με το Ν και το Μ να δηλώνονται στο πρόγραμμα σαν
συμβολικές σταθερές. 

Έστω sentence_table το όνομα του πίνακα.

Τυπικά η δήλωση θα δίνεται ως εξής:

struct sentence_pair {  
	char sentence[Μ];    
	int length;
};  

struct word_pair sentence_table[N]

Ζητείται να υλοποιηθούν οι εξής συναρτήσεις:

Α. Μία συνάρτηση που θα ζητάει από τον χρήστη και θα γεμίζει τον πίνακα με
	Ν προτάσεις. Η συνάρτηση να δηλωθεί ως 

	void initialize(struct sentence_pair sentence_table[], int size) 

	(με size συμβολίζεται ο αριθμός των γραμμών του πίνακα).

B. Mία συνάρτηση που θα υπολογίζει το πλήθος των λέξεων που είναι
	αποθηκευμένες στον πίνακα sentence_table[].

Γ. Μία συνάρτηση που θα δέχεται σαν είσοδο μία λέξη και θα εμφανίζει μία
	λίστα με τις γραμμές του πίνακα που την εμπεριέχουν.

Ελέγξτε τον κώδικά σας με ένα κυρίως πρόγραμμα το οποίο θα καλεί τις ανωτέρω
συναρτήσεις με την σειρά με την οποία ορίστηκαν.

Υποδείξεις:

Προτείνεται η χρήση των συναρτήσεων:
* int isalnum(int ch) της βιβλιοθήκης <ctype.h> που επιστρέφει μη μηδενική
	τιμή (αληθή) αν ο χαρακτήρας ch είναι αριθμητικό ψηφίο ή γράμμα (πεζό
	ή κεφαλαίο) του αγγλικού αλφαβήτου, διαφορετικά επιστρέφει 0

* char *strcpy(char *s, const char *t), συνάρτηση της βιβλιοθήκης <string.h>
	που αντιγράφει το αλφαριθμητικό t στο αλφαριθμητικό s.
*/

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>

struct sentence_pair {  
	char *sentence;    
};

struct command_line {
	char *filename;
};

struct command_line args = { NULL };


size_t read_table	( struct sentence_pair *sentence_table );
size_t count_words  ( struct sentence_pair *sentence_table );
void   destroy_table( struct sentence_pair *sentence_table );
void   help         ( void );
void   initialize   ( struct sentence_pair *sentence_table );
void   parse_command_args( int argc, char *argv[] );
void    find_location( struct sentence_pair *sentence_table, char *word );
int    sanity_ok	( void );


int sanity_ok( ){

	int sanity_status = 1;

	if( !setlocale( LC_CTYPE, "" ) ) {
		fprintf( stderr, "LC_CTYPE not set! Please set appropriatelly and run again.\n" );
		sanity_status = 0;
	}

	return sanity_status;
}


void initialize ( struct sentence_pair *sentence_table )
{

	unsigned long bytes_read = 0;

	bytes_read = read_table( sentence_table );
	if( !bytes_read ) {
		fprintf( stderr, "No text loaded for processing." );
		exit( -1 );
	}

	return;
}


size_t read_table( struct sentence_pair *sentence_table ) {

	char   *filename   = args.filename? args.filename : "./lorem_ipsum.txt"; // default
	int     lip 	   = 0;
	int     mode	   = O_RDONLY | O_NOFOLLOW;
	int     multiplier = 4800;
	char   *buffer     = NULL;
	size_t  filesize   = 0;
	ssize_t bytes_read = 0;
	struct  stat *file = malloc( sizeof ( struct stat ) );

	
	buffer = malloc( sizeof( char ) * multiplier + 1 );

	lip = open( filename, mode );
	if( lip < 0 ) {
		fprintf( stderr, "Can't open input file %s!\n", filename );
		exit( -1 );
	}

	if( -1 == fstat( lip, file ) ) {
		fprintf( stderr, "Cannot stat %s. Exiting\n", filename );
		exit( -1 );
	}

	filesize = file->st_size;
	bytes_read = read( lip, buffer, filesize );
	if( 0 == bytes_read || ( errno && -1 == bytes_read ) ) {
		fprintf( stderr, "Input file %s was empty. Exiting.\n", filename );
		exit( -1 );
	}
	close( lip );

	sentence_table->sentence = malloc( strlen( buffer ) + 1 );
	if( NULL == strcpy( sentence_table->sentence, buffer ) ) {
		fprintf( stderr, "Unsuccessful copy from buffer to sentence. Exiting." );
		exit ( -1 );
	}

	free( buffer );

	return bytes_read;
}


void help( )
{
	struct sentence_pair *sentence_table = NULL;
	sentence_table = malloc( sizeof( struct sentence_pair ) );

	if( read_table( sentence_table ) > 0 ) {
		fprintf( stderr , "%s", sentence_table->sentence );
	}
	else {
		fprintf( stderr, "Help is not available at this time.\n" );
	}

	return;
}


void parse_command_args( int argc, char *argv[] )
{
	char c = 0;

	opterr = 0;
	while( ( c = getopt (argc, argv, "hf:" ) ) != -1) {
		switch (c) {
			case 'f':
				if( NULL == optarg ) {
					fprintf( stderr, "Filename not set. Exiting!\n");
					exit( -1 );
				}
				args.filename = optarg;
				break;
			case 'h':
				help( );
				exit( -1 );
				break;
			case '?':
				if( 'f' == optopt ) {
					fprintf( stderr, "Option -%c requires an argument.\n", optopt );
				}
				else if( isprint( optopt ) ) {
					fprintf( stderr, "Unknown option `-%c'.\n", optopt );
				}
				else {
					fprintf( stderr, "Unknown option character `\\x%x'.\n", optopt );
				}
				break;
			default:
				help( );
				exit( -1 );
				break;
		}
	}

	return;
}

size_t count_words( struct sentence_pair *sentence_table )
{
	size_t words_counted 	 = 2; // beginning and ending
	char *pointer  		 	 = sentence_table->sentence;
	
	pointer  = sentence_table->sentence;
	// count words
	for( pointer = strtok( pointer, " " ); pointer; pointer = strtok( NULL, " " ) ) {
		words_counted++;
	}

	return words_counted ;
}


void find_location( struct sentence_pair *sentence_table, char *word )
{
	size_t *locations = NULL;

	locations =  malloc( sizeof (size_t) + 1 );

	assert( word );
	assert( sentence_table );

	// tokenize sentence_table->sentence on '.'
	// count how many sentences
	// order them into a struct sentence_table[count_sentences]
	// for each sentence_table[ 0..count_sentences ]
	// strstr? to find the first occurence,
	//		add sentence location to array
	// 		then re-posittion at new location and try again
	//		until NULL for sentence_table->sentence


	return;
}


void begin_execution( void )
{
	struct  sentence_pair *sentence_table = NULL;
	char *word = "lorem";
	size_t words_counted = 0;

	sentence_table = malloc( sizeof( struct sentence_pair ) );

	initialize( sentence_table );
	words_counted = count_words  ( sentence_table );
	fprintf( stderr , "Words counted %ld\n", words_counted );
	find_location( sentence_table, word );


	return;
}


int main( int argc, char *argv[] )
{

	// check the status of the terminal
	if( !sanity_ok( ) ) {
		exit( EXIT_FAILURE );
	}

	// in case of emergency grake blass
	if( argc > 1 ) {
		parse_command_args( argc, argv );
	}

	begin_execution( );

	return 0;
}