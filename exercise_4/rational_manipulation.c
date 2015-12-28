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

Επισημαίνεται ότι όλες οι συναρτήσεις θα πρέπει (με εύρεση του μέγιστου
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
#include <getopt.h>
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
size_t read_table( void );
void   help( void );
void   parse_command_args( int argc, char *argv[] );
void   begin_execution( void );

struct rational *make_rational( ssize_t a, ssize_t b );
ssize_t add_rational( struct rational r1, struct rational r2 );
ssize_t multiply_rational( struct rational r1, struct rational r2 );
void 	print_rational( struct rational r );
ssize_t	greatest_common_denominator( ssize_t a, ssize_t b );

///////////////////////

struct rational {
	ssize_t numerator;
	ssize_t denominator;
};

struct rational r1 = { 0, 0 };
struct rational r2 = { 0, 0 };

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

void help( void ) 
{
	fprintf( stderr, "ΠΕΖ2015: Άσκηση 4η: Ρητοί αριθμοί.\n\n" );
	fprintf( stderr, "Επιλογές:\n" );
	fprintf( stderr, "\t-h | --help Προβολή βοήθειας (αυτή εδώ που βλέπετε)\n");
	fprintf( stderr, "\t--numerator1    Αριθμητής    ρητού1\n");
	fprintf( stderr, "\t--denominator1  Παρονομαστής ρητού1\n");
	fprintf( stderr, "\t--numerator2    Αριθμητής    ρητού2\n");
	fprintf( stderr, "\t--denominator2  Παρονομαστής ρητού2\n");

	return;
}

void parse_command_args( int argc, char *argv[] )
{
	int c = 1, n1 = 0, d1 = 0, n2 = 0, d2 = 0; // track argument state

	while( c ) {
		static struct option long_options[] = {
			// // These options set a flag.
			// {"verbose", no_argument,   &verbose_flag, 1},
			// {"brief",   no_argument,   &verbose_flag, 0},
			// // These options don’t set a flag.
			// // We distinguish them by their indices.
			{ "help", 		 no_argument, 	   0, 'h' },
			{ "numerator1",  required_argument, 0, 'n' },
			{ "denominator1",required_argument, 0, 'd' },
			{ "numerator2",  required_argument, 0, 'f' },
			{ "denominator2",required_argument, 0, 's' },
			{0, 0, 0, 0}
		};

		/* getopt_long stores the option index here. */
		int option_index = 0;
		c = getopt_long (argc, argv, "n:d:f:s:", long_options, &option_index);

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
			case 'n':
				if( !n1 && !sscanf( optarg, "%ld", &r1.numerator ) ) {
					fprintf( stderr, "\"%s\" is not an integer\n", optarg );
					exit( -1 );
				}
				n1 = 1;
				break;
			case 'd':
				if( !d1 && !sscanf( optarg, "%ld", &r1.denominator ) ) {
					fprintf( stderr, "\"%s\" is not an integer\n", optarg );
					exit( -1 );
				}
				d1 = 1;
				break;
			case 'f':
				if( !n2 && !sscanf( optarg, "%ld", &r2.numerator ) ) {
					fprintf( stderr, "\"%s\" is not an integer\n", optarg );
					exit( -1 );
				}
				n2 = 1;
				break;
			case 's':
				if( !d2 && !sscanf( optarg, "%ld", &r2.denominator ) ) {
					fprintf( stderr, "\"%s\" is not an integer\n", optarg );
					exit( -1 );
				}
				d2 = 1;
				break;
			case '?':
				// getopt_long already printed an error message.
				break;
			default:
				exit( -1 );
				break;
		}
	}

	fprintf( stdout, "%ld/%ld, %ld/%ld\n", r1.numerator, r1.denominator, r2.numerator, r2.denominator );
	exit( -1 );
}


struct rational *make_rational( ssize_t a, ssize_t b)
{
	struct rational *r = NULL;
	ssize_t gcd = 0;

	gcd = greatest_common_denominator( a, b );

	// once gcd is discovered, modulus division on each
	// then store each result into struct and send it off

	// check to see the sign of both numbers
	// before turning them into a ration

	return r;
}


ssize_t add_rational( struct rational r1, struct rational r2 )
{
	ssize_t result = 0;

	ssize_t num1 = r1.numerator;
	ssize_t den1 = r1.denominator;
	ssize_t num2 = r2.numerator;
	ssize_t den2 = r2.denominator;

	result = (num1 * den2 + num2 * den1)/(den1 * den2);

	return result;
}


ssize_t multiply_rational( struct rational r1, struct rational r2 )
{
	ssize_t result = 0;

	ssize_t num1 = r1.numerator;
	ssize_t den1 = r1.denominator;
	ssize_t num2 = r2.numerator;
	ssize_t den2 = r2.denominator;

	result = (num1 * num2)/(den1 * den2);

	return result;
}


void print_rational( struct rational r )
{
	assert( r.numerator );

	return;
}


ssize_t greatest_common_denominator( ssize_t a, ssize_t b )
{
	// check for proper input
	if( a == 0 || b == 0 ) { return 0; }
	if (a < 0) { a = -a; }
	if (b < 0) { b = -b; }

	return greatest_common_denominator( b % a, a );
}


void initialize( void )
{

	// check r1, r2 are set from commandline
	// if not, prompt user, parse
	// send them off to make_rational( )

	return;
}


void begin_execution( void )
{

	ssize_t a = 0, b = 0;
	ssize_t result = 0;
	struct rational *r = NULL;
	struct rational r1;
	struct rational r2;

	initialize( );
	r = make_rational( a, b);
	result = add_rational( r1, r2 );
	result = multiply_rational( r1, r2 );
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