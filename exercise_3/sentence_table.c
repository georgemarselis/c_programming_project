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
	char *term;
};

struct command_line args = { NULL, NULL };


size_t read_table	( struct sentence_pair *sentence_table );
size_t count_words  ( struct sentence_pair *sentence_table );
size_t find_location( struct sentence_pair *sentence_table );
void   destroy_table( struct sentence_pair *sentence_table );
void   help         ( void );
void   initialize   ( struct sentence_pair *sentence_table );
void   parse_command_args( int argc, char *argv[] );
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
	fprintf( stderr, "ΠΕΖ2015: Άσκηση 3η: Απαρήθμηση και αναζήτηση λέξεων.\n\n" );
	fprintf( stderr, "Επιλογές:\n" );
	fprintf( stderr, "\t-h Προβολή βοήθειας (αυτή εδώ που βλέπετε)\n");
	fprintf( stderr, "\t-f <αρχειο> Επιλογή αρχείου για αναζήτηση (προεπιλογή: \"lorem_ipsum.txt\"\n");
	fprintf( stderr, "\t-t <λέξη>   Όρος αναζήτησης\n\n");

	fprintf( stderr, "Παραδείγματα:\n" );
	fprintf( stderr, "./sentence_table -f lorem_bacon.txt -t round :\n" );
	fprintf( stderr, "\tΨάχνει το αρχείο lorem_bacon.txt για τη λέξη 'round' ( υπάρχει )\n" );
	fprintf( stderr, "./sentence_table -f lorem_bacon.txt -t κοκο  :\n" );
	fprintf( stderr, "\tΨάχνει το αρχείο lorem_bacon.txt για τη λέξη 'κοκο'  ( δεν υπάρχει )\n" );
	fprintf( stderr, "./sentence_table -f lorem_ipsum.txt -t solo  :\n" );
	fprintf( stderr, "\tΨάχνει το αρχείο lorem_ipsum.txt για τη λέξη 'solo'  ( υπάρχει )\n" );
	fprintf( stderr, "./sentence_table -f lorem_ipsum.txt -t bar   :\n" );
	fprintf( stderr, "\tΨάχνει το αρχείο lorem_ipsum.txt για τη λέξη 'λαλα'  ( δεν υπάρχει )\n" );
	fprintf( stderr, "./sentence_table -f lorem_bacon.txt          :\n" );
	fprintf( stderr, "\tΑναζητά στο αρχείο lorem_ipsum.txt όποιον όρο εισάγει δυναμικά ο χρήστης\n" );
	fprintf( stderr, "./sentence_table                             :\n" );
	fprintf( stderr, "\tΑναζητά τον όρο που δυναμικά θα εισάγει ο χρήστης στο προεπιλεγμένο αρχείο lorem_ipsum.txt\n" );
	return;
}


void parse_command_args( int argc, char *argv[] )
{
	char c = 0;

	opterr = 0;
	while( ( c = getopt (argc, argv, "ht:f:" ) ) != -1) {
		switch (c) {
			case 'f':
				if( NULL == optarg ) {
					fprintf( stderr, "Filename not set. Exiting!\n");
					exit( -1 );
				}
				args.filename = optarg;
				break;
			case 't':
				if( NULL == optarg ) {
					fprintf( stderr, "Term not set. Exiting!\n");
					exit( -1 );
				}
				args.term = optarg;
				break;
			case 'h':
				help( );
				exit( -1 );
				break;
			case '?':
				if( 'f' == optopt ) {
					fprintf( stderr, "Option -%c requires an argument.\n", optopt );
					exit( -1 ) ;
				}
				else if( isprint( optopt ) ) {
					fprintf( stderr, "Unknown option `-%c'.\n", optopt );
					exit( -1 );
				}
				else {
					fprintf( stderr, "Unknown option character `\\x%x'.\n", optopt );
					exit( -1 );
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
	size_t words_counted 	= 2; // beginning and ending
	char *pointer 			= malloc( strlen( sentence_table->sentence ) + 1 );

	strcpy( pointer, sentence_table->sentence );
	// count words
	for( pointer = strtok( pointer, " " ); pointer; pointer = strtok( NULL, " " ) ) {
		words_counted++;
	}

	return words_counted ;
}


size_t find_location( struct sentence_pair *sentence_table )
{
	size_t sentences_counted 	= 0; // beginning and ending
	size_t  *location_counter 	= NULL;

	char *buffer				= NULL;
	char *pointer  		 	 	= NULL;
	char **sentences 			= NULL;
	int location_found 			= 0;

	pointer = malloc( strlen( sentence_table->sentence ) + 1 );
	if( NULL == pointer && ENOMEM == errno ) {
		fprintf( stdout, "Run out of memory trying to parse sentences.\n" );
		exit( -1 );
	}
	strcpy( pointer, sentence_table->sentence );


	// count sentences
	for( pointer = strtok( pointer, "." ); pointer; pointer = strtok( NULL, "." ) ) {

		if( '\n' == *pointer ) {
			pointer = strtok( NULL, "\n" );
			continue;
		}

		sentences = realloc( sentences, sizeof( char * ) * (sentences_counted + 1 ) );
		sentences[ sentences_counted ] = (char *) malloc( strlen( pointer ) + 1 );
		strcpy( sentences[ sentences_counted ],  pointer );
#ifdef DEBUG
		fprintf( stdout, "Sentence: %ld / Token is: %s\n", sentences_counted, pointer);
#endif
		sentences_counted++;
	}

	fprintf( stdout, "Sentences counted: %ld\n", sentences_counted );

	if( NULL == args.term ) {
		char *newlinePtr = NULL;
		buffer = malloc( sizeof( char ) * 100 );
		fprintf( stdout, "Please enter term to search for: " );
		fscanf( stdin, "%100s", buffer );
		while( (newlinePtr = strchr( buffer, '\n' ) ) ){
			*newlinePtr = '\n';
		}
		newlinePtr = NULL;
		while( (newlinePtr = strrchr( buffer, '\n' ) ) ){
			*newlinePtr = '\n';
		}
	}
	else {
		buffer = malloc( sizeof( char ) * strlen( args.term ) + 1 );
		strcpy( buffer, args.term );
	}

	location_counter = malloc( sizeof( int * ) * ( sentences_counted + 1) );
	for( size_t i = 0; i < sentences_counted ; i++ ) {

		if( NULL != strcasestr( sentences[ i ], buffer ) ) {
			location_counter[i] = 1;
		}
		else {
			location_counter[i] = 0;
		}
	}

	for( size_t i = 0; i < sentences_counted ; i++ ) {
		if( location_counter[i] ) {
			location_found = 1;
			break;
		}
	}

	if( location_found ) {

		size_t cont_process = 0;
		fprintf( stdout, "\"%s\" appears in sentences ", buffer );
		for( size_t i = 0; i < sentences_counted ; i++ ) {
			if( location_counter[i] ) {
				if( i == sentences_counted - 1 ) {
					fprintf( stdout, " and %ld.\n", i );
					cont_process = 0;
				}

				if( cont_process ) {
					fprintf( stdout, ", " );
				}

				if( i != sentences_counted - 1 ) {
					fprintf( stdout, "%ld", i );
					cont_process = 1;
				}
			}
		}
		fprintf( stdout, "\n" );
	} 
	else {
		fprintf( stdout, "\"%s\" term not found in content.\n", buffer );
	}


	for( size_t i = 0; i < sentences_counted ; i++ ) {
		free( sentences[i] );
	}
	free( sentences );

	return sentences_counted;
}


void begin_execution( void )
{
	struct  sentence_pair *sentence_table = NULL;
	size_t words_counted = 0;

	sentence_table = malloc( sizeof( struct sentence_pair ) );

	initialize( sentence_table );
	words_counted = count_words  ( sentence_table );
	fprintf( stderr , "Words counted %ld\n", words_counted );
	find_location( sentence_table );


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