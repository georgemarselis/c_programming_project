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
προτείνεται να χρησιμοποιηθεί η συνάρτηση char * strtok(char *s, char * ct)
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
struct command_line {
	char *filename;
};

struct command_line args = { NULL };

///////////////////////////////////////////


// function prototypes
int sanity_ok( void );
void help( void );
void parse_command_args( int argc, char *argv[] );
char *readfile( void );
int *parsefile( char *buffer, int *size );
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


void parse_command_args( int argc, char *argv[] ) 
{
	int c = 1; // track argument state

	while( c ) {
		static struct option long_options[] = {
			// // These options set a flag.
			// {"verbose", no_argument,   &verbose_flag, 1},
			// {"brief",   no_argument,   &verbose_flag, 0},
			// // These options don’t set a flag.
			// // We distinguish them by their indices.
			{ "help", 		 no_argument, 	    0, 'h' },
			{ "file",        required_argument, 0, 'f' },
			{0, 0, 0, 0}
		};

		/* getopt_long stores the option index here. */
		int option_index = 0;
		c = getopt_long (argc, argv, "hf:", long_options, &option_index);

		if( -1 == c ) {
			break;
		}

		switch( c ) {
			case 0:
				// If this option set a flag, do nothing else now.
				if( 0 != long_options[option_index].flag ) {
					break;
				}
				fprintf ( stderr, "option %s", long_options[option_index].name);
				if (optarg) {
					fprintf (stderr, " with arg %s", optarg); 
				}
				printf ("\n");
				break;
			case 'h':
				help( );
				exit( 0 );
				break;
			case 'f':
				args.filename = optarg;
				break;
				default:
				exit( -1 );
				break;
		}
	}

	return;
}


// read the supplied from the command line filename and
// save it into an array
char *readfile( void )
{
	const  char   *file= "./data.txt";
	char   *buff       = NULL;
	FILE   *infile     = NULL;
	struct stat *st    = NULL;

	st = malloc( sizeof( *st )  );

	if( -1 == stat( file, st ) ) {
		fprintf( stderr, "Cannot stat file %s . Exiting\n", file );
		exit( 1 );
	}

	infile = fopen( file, "r" );
	if( NULL == infile ) {
		fprintf( stderr, "Cannot open file %s . Exiting\n", file );
		exit( 1 );
	}

	// read file
	buff = malloc( sizeof( char )*st->st_size + 1 );
	if( 0 == fread( buff, st->st_size, sizeof( char ), infile ) ) {
		fprintf( stderr, "file %s is empty. Exiting\n", file );
	}

	fclose( infile ); free( buff ); free( st );


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

void begin_execution( void )
{
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