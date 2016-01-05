/*

ΠΕΖ2015 Άσκηση 6η:

Θεωρείστε ότι δίδεται ο εξής ορισμός δομής: 

struct node {
	int data;
	struct node *next; 
};

Με βάση τον ορισμό αυτό, το ζητούμενο είναι να σχεδιάσετε και να υλοποιήσετε
μια συνδεδεμένη λίστα στοιχείων που ικανοποιεί τον κανόνα πρόσβασης
First-In-First-Out, με άλλα λόγια μια δομή ουράς (queue). Στις δομές αυτές
το στοιχείο το οποίο εντέθηκε πρώτο στη λίστα (με μία πράξη Insert) είναι και
αυτό που θα διαγραφεί πρώτο (με μία πράξη Delete). Αυτή η λογική πράξεων μπορεί
να υλοποιηθεί αν η ένθεση στοιχείων γίνεται στο τέλος της λίστας, ενώ η διαγραφή
αφαιρεί στοιχεία από την αρχή της λίστας.

Γράψτε συναρτήσεις σύμφωνα με τα παρακάτω πρότυπα, καθώς και ένα πρόγραμμα
επίδειξης:

* void Insert(struct node **headRef, int newData);
* int Delete(struct node **headRef);
* int GetNth(struct node *head, int index);
* int Count(struct node *head, int searchFor);

Η συνάρτηση Insert() δέχεται ως όρισμα ένα δείκτη στον δείκτη που αντιστοιχεί
στην κεφαλή της λίστας. Δεσμεύει μνήμη, με κλήση της malloc(), για μια δομή του
τύπου struct node, αποθηκεύει σ’αυτήν την ακέραια τιμή newData (στο πεδίο data)
και συνδέει κατάλληλα την νέα δομή (βάσει του πεδίου next) ώστε η λίστα να
ικανοποιεί τον κανόνα πρόσβασης First-In-First-Out, συνεπώς ενθέτει το νέο
στοιχείο στο τέλος της λίστας.

Η συνάρτηση Delete() δέχεται ως όρισμα ένα δείκτη στον δείκτη που αντιστοιχεί
στην κεφαλή της λίστας διαγράφει και επιστρέφει ένα στοιχείο της λίστας έτσι
ώστε να ικανοποιείται ο κανόνας "First In First Out", συνεπώς διαγράφει και
επιστρέφει το πρώτο στοιχείο της λίστας.

Η GetNth() δέχεται ως όρισμα τον δείκτη που αντιστοιχεί στην κεφαλή της
λίστας, και την θέση (ως ακέραια τιμή που ξεκινά από το 0) ενός στοιχείου.
Εφόσον η λίστα περιέχει στοιχείο στην καθοριζόμενη θέση, η συνάρτηση επιστρέφει
την τιμή του πεδίου data για το στοιχείο αυτό, διαφορετικά εκτυπώνει κατάλληλο
μήνυμα και επιστρέφει την τιμή 0.

Η Count() δέχεται ως όρισμα τον δείκτη που αντιστοιχεί στην κεφαλή της λίστας,
και μια ακέραια τιμή. Εξετάζει ένα-προς-ένα όλα τα στοιχεία της λίστας και
επιστρέφει σε πόσα από αυτά το πεδίο data ισούται με την αναζητούμενη τιμή 
και επιστρέφει 0 εάν η τιμή δεν εμφανίζεται στην λίστα.

Γράψτε την main() η οποία εμφανίζει μενού επιλογών στο χρήστη:

1. Insert 
2. Delete
3. Get-Nth
4. Count
5. Έξοδος

Ανάλογα με την επιλογή του χρήστη ζητούνται τα απαραίτητα στοιχεία (π.χ. για
την πράξη Insert ζητείται από τον χρήστη η ακέραια τιμή newdata) και καλείται η κατάλληλη συνάρτηση.

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

// struct declerations
struct node {
	int data;
	struct node *next;
};

struct command_line {
	char *filename;
};

struct command_line args = { NULL };

///////////////////////////////////////////


// function prototypes
int    sanity_ok(  void );
void   initialize( void );
void   initqueue( int *data, int size );
char  *readfile( void );
int   *parsefile( char *buffer, int *size );
void   help( void );
void   parse_command_args( int argc, char *argv[] );
void   begin_execution( void );
ushort printmenu( void );
int    printqueue( void );
void   insertitem ( int data );
void   deleteitem( void );
void   getnitem( void );
void   countoccurance( void );
void   emptyqueue( void );

void Insert( struct node **headRef, int newData );
int  Delete( struct node **headRef );
int  GetNth( struct node  *head, int index );
int  Count(  struct node  *head, int searchFor );

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
	fprintf( stderr, "ΠΕΖ2015: Άσκηση 6η: Δομή ουράς.\n\n" );
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

#ifdef DEBUG
	fprintf( stdout, "file size: %lld bytes\n", st->st_size );
	fprintf( stdout, "buffer is: %s\n", buff );
#endif

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


void initialize( void )
{
	char   *buffer  = NULL;
	int    *array   = NULL;
	int    size     = 0;

	buffer = readfile( );
	array  = parsefile( buffer, &size );
	initqueue( array, size );

	free( array );

	return;
}


void Insert( struct node **headRef, int newData )
{

	fprintf( stdout, "This is a stub: %p, %d\n", headRef, newData );
	return;
}


int Delete( struct node **headRef )
{
	int data = 0;

	fprintf( stdout, "This is a stub: %p\n", headRef );
	return data;
}


int GetNth( struct node *head, int index )
{
	int data = 0;

	fprintf( stdout, "This is a stub: %p, %d\n", head, index );

	return data;
}


int Count( struct node *head, int searchFor )
{
	int data = 0;

	fprintf( stdout, "This is a stub: %p, %d\n", head, searchFor );

	return data;
}


unsigned short printmenu( void )
{
	ushort userpick = 0;

	fprintf( stdout, "please choose:\n");
	fprintf( stdout, "1. Insert 2. Delete 3. Get-Nth 4. Count\n" );
	fprintf( stdout, "5. Exit\n" );
	fprintf( stdout, "> " );

	scanf( "%1hu", &userpick );

	return userpick;
}


int printqueue( void )
{
	int c = 0;

	fprintf( stdout, "The list so far:\n" );

	return c; // most likely characters read or something
}

void initqueue ( int *data, int size )
{
	int counter = 0;

	while( counter++ < size - 1)
	{
		insertitem( data[counter] );
	}

	return;
}


void begin_execution( void )
{
	const uint exitcode = 5;  // exit menu
	ushort userpick = 0;
	int    userdata = 0;

	initialize( );
	do {
			userpick = printmenu( );
			switch( userpick ) {
				case 1: 	// insert
					fprintf( stdout, "Please insert an integer: " );
					scanf( "%d", &userdata );
					insertitem( userdata );
					break;
				case 2: 	// delete
					deleteitem( );
					break;
				case 3: 	// Get-Nth
					getnitem( );
					break;
				case 4: 	// Count
					countoccurance( );
					break;
				case 5: 	// fall-through / exit
					emptyqueue( );
					break;
				default:
					fprintf( stdout, "No such choice. Please try again.\n" );
					break;
			}

		exitcode != userpick ? printqueue( ) : 1; 		// the score so far
	} while( exitcode != userpick );

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

void insertitem ( int data )
{

	fprintf( stdout, "Data item to insert into queue: %d\n", data );

	return;
}


void deleteitem( void )
{

	fprintf( stdout, "Stub function for deleting an item from the queue\n" );

	return;
}


void getnitem( void )
{

	fprintf( stdout, "Stub function for getting the value of the N-th item in the queue\n" );

	return;
}


void countoccurance ( void )
{

	fprintf( stdout, "Stub function for counting the occurance of an item in the queue\n" );

	return;
}


void emptyqueue( void )
{

	fprintf( stdout, "Stub function for emptying queue\n" );

	return;
}
