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

struct airline {
	char *flight_number;
	unsigned int airplane_seats;
	unsigned int passenger_count;
};

struct command_line {
	char *filename;
};

struct command_line args = { NULL };

// function prototypes
int 	sanity_ok(  void );
void 	initialize( void );
char   *read_file( void );
void 	help( void );
void 	parse_command_args( int argc, char *argv[] );
void 	begin_execution( void );
size_t 	parse_buffer( struct airline *reservation, char *buffer );

///////////////////////


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
	fprintf( stderr, "ΠΕΖ2015: Άσκηση 5η: Διαχείρηση κρατήσεων αεροπορικής εταιρίας.\n\n" );
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


char *read_file( void ) {

	char   *filename     = args.filename? args.filename : "./data.txt"; // default
	int     lip 	     = 0;
	int     mode	     = O_RDONLY
	int     multiplier   = 4800;
	char   *buffer       = NULL;
	size_t  filesize     = 0;
	ssize_t bytes_read   = 0;
	struct  stat *file   = malloc( sizeof ( struct stat ) );


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

	return buffer;
}


size_t parse_buffer( struct airline *reservation, char *buffer )
{
	const unsigned int     callsign_length = 6;
	      size_t   records_counted = 0;
		  char    *pointer         = NULL;



	if( NULL == buffer ) {
		fprintf( stderr, "buffer is null. Nothing to parse. Exiting\n." );
		exit( -1 );
	}

	pointer = malloc( strlen( buffer ) + 1 );
	if( NULL == pointer && ENOMEM == errno ) {
		fprintf( stdout, "Run out of memory trying to parse sentences.\n" );
		exit( -1 );
	}

	pointer = buffer;
	// each record ends at newline
	for( pointer = strtok( pointer, "\n" ); pointer; pointer = strtok( NULL, "\n" ) ) {

		if( '/' == *pointer ) { // lines begining with '/' are ignored
			continue;
		}
		reservation = realloc( reservation, sizeof( *reservation ) * ( records_counted + 1 ) );
		reservation[records_counted].flight_number = malloc( sizeof( *reservation[records_counted].flight_number ) * (callsign_length + 1 ) );
		if( 0 == sscanf( pointer, "%6s %3u %3u", reservation[records_counted].flight_number, 
				&reservation[records_counted].airplane_seats, &reservation[records_counted].passenger_count ) 
		) {
			fprintf( stdout, "There was a parsing issue with record %s\n", pointer );
			exit( -1 );
		}

		records_counted++;
	}

	return records_counted;
}


void initialize( void )
{
	size_t records_counted 		= 0;
	size_t count           		= 0;
	char   *buffer              = NULL;
	struct airline *reservation = NULL;

	buffer = read_file( );
#ifdef DEBUG
	fprintf( stdout, "buffer is:\n%s", buffer );
#endif

	records_counted = parse_buffer( reservation, buffer );

	while( count < records_counted ) {
		fprintf( stdout, "record %3lu: Flight: %5s Seats: %3u Passengers: %3u\n",
				count + 1, reservation[count].flight_number, reservation[count].airplane_seats,
				reservation[count].passenger_count
		);
		count++;
	}

	free( buffer );

	return;
}


void begin_execution( void )
{
	initialize( );

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