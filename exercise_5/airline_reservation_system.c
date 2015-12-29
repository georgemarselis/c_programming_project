/*

# ΠEZ2015 - Άσκηση 5η
Μια αεροπορική εταιρία πραγματοποιεί κάθε μέρα δέκα πτήσεις με διαφορετικούς
τύπους αεροσκαφών. Για κάθε πτήση της η εταιρία κρατάει τα εξής στοιχεία: 
	* τον αριθμό της πτήσης
	* το πλήθος των θέσεων του αεροσκάφους και 
	* τον αριθμό των επιβαινόντων.

Να γραφεί πρόγραμμα το οποίο:

(i)   θα ζητάει να δωθούν από το πληκτρολόγιο και θα καταχωρεί τα στοιχεία κάθε πτήσης, 
(ii)  Θα υπολογίζει το συνολικό αριθμό των επιβατών όλων των πτήσεων
(iiι) Θα υπολογίζει πόσες από τις πτήσεις έχουν πληρότητα.

Μια πτήση θεωρείται ότι έχει πληρότητα όταν έχει διαθέσει τουλάχιστον το 80% των θέσεων του αεροσκάφους.
Τα ζητούμενα (ii) και (iii) να γίνουν με χρήση κατάλληλων συναρτήσεων.

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

// function prototypes
int    sanity_ok(  void );
size_t read_table( void );
void   help( void );
void   parse_command_args( int argc, char *argv[] );
void   begin_execution( void );

struct rational *make_rational( ssize_t a, ssize_t b );
void    fix_signage( ssize_t *gcd_a, ssize_t *gcd_b );
void    add_rational( struct rational r1, struct rational r2 );
void    multiply_rational( struct rational r1, struct rational r2 );
void 	print_rational( struct rational r );
ssize_t	greatest_common_denominator( ssize_t a, ssize_t b );

///////////////////////

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
	int c = 1; // track argument state

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
				default:
				exit( -1 );
				break;
		}
	}

#ifdef DEBUG
#endif

	return;
}


void initialize( void )
{
	// load any files needed
	return;
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