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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>

#ifdef BY_THE_BOOK
#define M 1024
#define N 1024
#endif


struct sentence_pair {  
	char *sentence;    
};  

unsigned long read_table(  struct sentence_pair *sentence_table );
int write_table( struct sentence_pair  sentence_table[], int  size );
void destroy_table( struct sentence_pair sentence_table[], int  size );

void help( void );
void initialize   ( struct sentence_pair *sentence_table );
int  count_words  ( struct sentence_pair sentence_table[], int size );
int *find_location( struct sentence_pair sentence_table[], int size );

ssize_t read_loremipsum( struct sentence_pair *sentence_table );

int find_word( char *word );


void initialize ( struct sentence_pair *sentence_table ) 
{

#ifdef DEBUG
	read_loremipsum( sentence_table );
#else
	read_table( sentence_table );
#endif

	return;
}


unsigned long read_table( struct sentence_pair *sentence_table )
{
	unsigned long bytes_read = 0;

#ifdef LOREM_IPSUM


	// if LOREM_IPSUM is defined during compile, read in the Star Wars[tm]
	// Lorem Ipsum lorem_ipsum.txt; return content to use as sample input
	bytes_read = read_loremipsum( sentence_table );

#endif

	return bytes_read;
}

ssize_t read_loremipsum( struct sentence_pair *sentence_table ) {

const 	char   *lorem_ipsum_filename = "./lorem_ipsum.txt";
		int     lip 				 = 0;
		int     mode                 = O_RDONLY | O_NOFOLLOW;
		int     multiplier           = 4800;
		char   *buffer               = NULL;
		size_t  filesize             = 0;
		ssize_t bytes_read           = 0;
		struct  stat *file           = malloc( sizeof ( struct stat ) );

	buffer = malloc( sizeof( char ) * multiplier + 1 );

	lip = open( lorem_ipsum_filename, mode );
	if( lip < 0 ) {
		fprintf( stderr, "Can't open input file %s!\n", lorem_ipsum_filename );
		exit( -1 );
	}

	if( -1 == fstat( lip, file ) ) {
		fprintf( stderr, "Cannot stat %s. Exiting\n", lorem_ipsum_filename );
		exit( -1 );
	}

	filesize = file->st_size;
	bytes_read = read( lip, buffer, filesize );
	if( 0 == bytes_read || ( errno && -1 == bytes_read ) ) {
		fprintf( stderr, "Input file %s was empty. Aborting.\n", lorem_ipsum_filename );
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

void help ( )
{
	struct sentence_pair *sentence_table = NULL;
	sentence_table = malloc( sizeof( struct sentence_pair ) );

	if( read_loremipsum( sentence_table ) > 0 ) {
		fprintf( stderr , "%s", sentence_table->sentence );
	}
	else {
		fprintf( stderr, "Help is not available at this time.\n" );
	}
}


int main( int argc, char* argv[] )
{

	struct sentence_pair *sentence_table = NULL;

	sentence_table = malloc( sizeof( struct sentence_pair ) );

	// in case of emergency
	if( argc - 1 > 0 ) {
		help( );
		exit( 1 );
	}

	initialize( sentence_table );

	assert( argc );
	assert( *argv );
	return 0;
}