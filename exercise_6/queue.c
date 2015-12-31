/* Άσκηση 6η
Θεωρείστε ότι δίδεται ο εξής ορισμός δομής: struct node
{
int data;
struct node *next; };
Με βάση τον ορισμό αυτό, το ζητούμενο είναι να σχεδιάσετε και να υλοποιήσετε μια συνδεδεμένη λίστα στοιχείων που ικανοποιεί τον κανόνα πρόσβασης First-In-First-Out, με άλλα λόγια μια δομή ουράς (queue). Στις δομές αυτές το στοιχείο το οποίο εντέθηκε πρώτο στη λίστα (με μία πράξη Insert) είναι και αυτό που θα διαγραφεί πρώτο (με μία πράξη Delete). Αυτή η λογική πράξεων μπορεί να υλοποιηθεί αν η ένθεση στοιχείων γίνεται στο τέλος της λίστας, ενώ η διαγραφή αφαιρεί στοιχεία από την αρχή της λίστας.
Γράψτε συναρτήσεις σύμφωνα με τα παρακάτω πρότυπα, καθώς και ένα πρόγραμμα επίδειξης
• void Insert(struct node **headRef, int newData);
• int Delete(struct node **headRef),
• int GetNth(struct node *head, int index);
• int Count(struct node *head, int searchFor)
Η συνάρτηση Insert() δέχεται ως όρισμα ένα δείκτη στον δείκτη που αντιστοιχεί στην κεφαλή της λίστας. Δεσμεύει μνήμη, με κλήση της malloc(), για μια δομή του τύπου struct node, αποθηκεύει σ’αυτήν την ακέραια τιμή newData (στο πεδίο data), και συνδέει κατάλληλα την νέα δομή (βάσει του πεδίου next) ώστε η λίστα να ικανοποιεί τον κανόνα πρόσβασης First-In-First-Out, συνεπώς ενθέτει το νέο στοιχείο στο τέλος της λίστας. Η συνάρτηση Delete() δέχεται ως όρισμα ένα δείκτη στον δείκτη που αντιστοιχεί στην κεφαλή της λίστας διαγράφει και επιστρέφει ένα στοιχείο της λίστας έτσι ώστε να ικανοποιείται ο κανόνας First In First Out, συνεπώς διαγράφει και επιστρέφει το πρώτο στοιχείο της λίστας. Η GetNth() δέχεται ως όρισμα τον δείκτη που αντιστοιχεί στην κεφαλή της λίστας, και την θέση (ως ακέραια τιμή που ξεκινά από το 0) ενός στοιχείου. Εφόσον η λίστα περιέχει στοιχείο στην καθοριζόμενη θέση, η συνάρτηση επιστρέφει την τιμή του πεδίου data για το στοιχείο αυτό, διαφορετικά εκτυπώνει κατάλληλο μήνυμα και επιστρέφει την τιμή 0.
Η Count() δέχεται ως όρισμα τον δείκτη που αντιστοιχεί στην κεφαλή της λίστας, και μια ακέραια τιμή. Εξετάζει ένα-προς-ένα όλα τα στοιχεία της λίστας και επιστρέφει σε πόσα από αυτά το πεδίο data ισούται με την αναζητούμενη τιμή (επιστρέφει 0 εάν η τιμή δεν εμφανίζεται στην λίστα).
Γράψτε την main() η οποία εμφανίζει μενού επιλογών στο χρήστη:
1. Insert 2. Delete
 
2. Get-Nth
3. Count
4. Έξοδος
Ανάλογα με την επιλογή του χρήστη ζητούνται τα απαραίτητα στοιχεία (π.χ. για την πράξη Insert ζητείται από τον χρήστη η ακέραια τιμή newdata) και καλείται η κατάλληλη συνάρτηση.
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


void initialize( void )
{

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

