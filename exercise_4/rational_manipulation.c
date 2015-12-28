/*
ΠΕΖ2015: Άσκηση 4η

Ρητός λέγεται ο αριθμός που μπορεί να εκφραστεί ώς πηλίκο δύο ακεραίων.
Ορίστε τη δομή rational για αναπαράσταση ρητών (με μέλη της τους δύο
ακέραιους). Στη συνέχεια ορίστε ως συναρτήσεις τις λειτουργίες:

(α) δημιουργίας ρητού rational make_rational(int α, int b) με δεδομένα
που δίνει ο χρήστης.

(β) Πρόσθεσης ρητών rational add_rational(rational r1, rational r2) που 
να επιστρέφει το άθροισμα δύο ρητών που δίνεται από τον τύπο:
	num1/den1 + num2/den2 = (num1 * den2 + num2 * den1)/(den1 * den2),

(γ) Πολλαπλασιασμού δύο ρητών rational multiply(rational r1, rational r2)
που να επιστέφει το γινόμενο δύο ρητών αριθμών, με βάση τον ακόλουθο τύπο:
	num1/den1 * num2/den2 = (num1 * num2)/(den1 * den2).

(δ) μία συνάρτηση void print_rational( rational r ), που να εμφανίζει 
τον ρητό r στην οθόνη ως κλάσμα.

Επισημαίνεται ότι όες οι συναρτήσεις θα πρέπει (με εύρεση του μέγιστου
κοινού διαιρέτη, αριθμητή και παρονομαστή) να μετατρέπουν τους ρητούς 
αριθμούς που τους δίνονται και να δίνουν το αποτέλεσμα στους μικρότερους
δυνατούς όρους. Για παράδειγμα ο πολλαπλασιασμός 1/2 επί 2/3 θα πρέπει
να δίνει ως αποτέλεσμα τον αριθμό 1/3 και όχι το 2/6.

Υλοποιήστε κυρίως πρόγραμμα που να τεστάρει τις συγκεκριμένες συναρτήσεις.
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

// function prototypes
int    sanity_ok(  void );
void   initialize( void );
size_t read_table( void );
void   help( void );
void   parse_command_args( int argc, char *argv[] );
void   begin_execution( void );

struct rational *make_rational(int α, int b);
ssize_t add_rational( struct rational r1, struct rational r2 );
ssize_t multiply( struct rational r1, struct rational r2 );
void print_rational( struct rational r );

///////////////////////

struct rational {
	ssize_t numerator;
	ssize_t denominator;
};

struct command_line {
	char *filename;
};

struct command_line args = { NULL };

int sanity_ok( void )
{

	int sanity_status = 1;

	if( !setlocale( LC_CTYPE, "" ) ) {
		fprintf( stderr, "LC_CTYPE not set! Please set appropriatelly and run again.\n" );
		sanity_status = 0;
	}

	return sanity_status;
}


void initialize ( void )
{

	unsigned long bytes_read = 0;

	bytes_read = read_table( );
	if( !bytes_read ) {
		fprintf( stderr, "No text loaded for processing." );
		exit( -1 );
	}

	return;
}


size_t read_table( void )
{

	size_t bytes_read = 0;

	return bytes_read;

}


void help( void ) 
{
	fprintf( stderr, "ΠΕΖ2015: Άσκηση 3η: Απαρήθμηση και αναζήτηση λέξεων.\n\n" );
	fprintf( stderr, "Επιλογές:\n" );
	fprintf( stderr, "\t-h Προβολή βοήθειας (αυτή εδώ που βλέπετε)\n");
	fprintf( stderr, "\t-f <αρχειο> Επιλογή αρχείου για αναζήτηση (προεπιλογή: \"lorem_ipsum.txt\"\n");


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
					exit( -1 ) ;
				}
				else if( isprint( optopt ) ) {
					fprintf( stderr, "Unknown option `-%c'.\n", optopt );
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


struct rational *make_rational(int a, int b)
{
	struct rational *r = NULL;
	assert( a ); assert( b );

	return r;
}


ssize_t add_rational( struct rational r1, struct rational r2 )
{
	ssize_t result = 0;

	return result;
}


ssize_t multiply( struct rational r1, struct rational r2 )
{
	ssize_t result = 0;

	return result;
}


void print_rational( struct rational r )
{

	return;
}


void begin_execution( void )
{

	int a = 0, b = 0;
	ssize_t result = 0;
	struct rational *r = NULL;
	struct rational r1;
	struct rational r2;

	r = make_rational( a, b);
	result = add_rational( r1, r2 );
	result = multiply( r1, r2 );
	print_rational( *r );

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