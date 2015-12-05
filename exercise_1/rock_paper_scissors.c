/*

Άσκηση 1η
Υλοποιήστε το παιχνίδι πέτρα-ψαλίδι-χαρτί ως εξής: 

Ο χρήστης θα πληκτρολογεί 
* 1 για την επιλογή πέτρα, 
* 2 για την επιλογή ψαλίδι, 
* 3 για την επιλογή χαρτί και 
* 0 για να βγεί από το παιχνίδι. 

Αν ο χρήστης πληκτρολογήσει 1, 2 ή 3, τότε ο υπολογιστής θα κάνει
μία τυχαία επιλογή(1,2,3) με τη βοήθεια της συνάρτησης rand() και
θα εμφανίζεται στην οθόνη η επιλογή του υπολογιστή και ποιος
κέρδισε. Το παιχνίδι θα επαναλαμβάνεται μέχρι ο χρήστης να 
πληκτρολογήσει 0. Τότε το παιχνίδι θα τερματίζεται τυπώνοντας στην
οθόνη τον αριθμό των συνολικών παιχνιδιών και των νικών του χρήστη.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <locale.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

struct current_game_data {
	int human_selection;
	int computer_selection;
};

struct current_game_data current_game_data =
	{ 0, 0 };

struct total_game_data {
	long games_played;
	long games_won_by_player;
	long games_won_by_computer;
	long game_ties;
	long computer_rock_selections;
	long computer_paper_selections;
	long computer_scissor_selections;
	long player_rock_selections;
	long player_paper_selections;
	long player_scissor_selections;
};

struct total_game_data total_game_data = 
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int  sanity_ok( void );
int  human_turn( void );
int  computer_turn( void );
void print_human_selection( void );
void print_computer_selection( void );
void decide_winner( int player_selection, int computer_selection );
void print_help( void );
void print_instructions_to_player( void );
int	 animate_computer_selection( void );
int	 get_computer_selection( void);
void total_game_analysis( void );

int sanity_ok( ){

	int sanity_status = 1;

	if( !setlocale( LC_CTYPE, "" ) ) {
    	fprintf( stderr, "LC_CTYPE not set! Please set appropriatelly and run again.\n" );
    	sanity_status = 0;
    }

    return sanity_status;
}

void print_help( void ) {

	fprintf( stderr, "ΠΕΖ 2015 - Άσκηση 1η\nΥλοποιήστε το παιχνίδι πέτρα-ψαλίδι-χαρτί ως εξής:\n\nΟ " );
	fprintf( stderr, "χρήστης θα πληκτρολογεί\n* 1 για την επιλογή πέτρα,\n* 2 για την " );
	fprintf( stderr, "επιλογή ψαλίδι,\n* 3 για την επιλογή χαρτί και\n* 0 για να βγεί από ");
	fprintf( stderr, "το παιχνίδι.\n\nΑν ο χρήστης πληκτρολογήσει 1, 2 ή 3, τότε ο υπολογιστής ");
	fprintf( stderr, "θα κάνει μία\nτυχαία επιλογή(1,2,3) με τη βοήθεια της συνάρτησης rand() και ");
	fprintf( stderr, "θα\nεμφανίζεται στην οθόνη η επιλογή του υπολογιστή και ποιος κέρδισε. ");
	fprintf( stderr, "Το\nπαιχνίδι θα επαναλαμβάνεται μέχρι ο χρήστης να πληκτρολογήσει 0. Τότε\nτο ");
	fprintf( stderr, "παιχνίδι θα τερματίζεται τυπώνοντας στην οθόνη τον αριθμό των συνολικών\nπαιχνιδιών ");
	fprintf( stderr, "και των νικών του χρήστη.\n\n" );

}

void print_instructions_to_player( void )
{
	printf( "ΠΕΖ 2015 - Άσκηση 1η - Πέτρα-ψαλίδι-χαρτί\n\nΠαρακαλώ εισάγετε:\n" );
	printf( "* 1 για την επιλογή ");
	printf( "πέτρα\n* 2 για την επιλογή ψαλίδι\n* 3 για την επιλογή χαρτί\n* ");
	printf( "0 για να βγείτε απο το παιχνίδι\n\nΕπιλογή: ");
	return;
}

int	 animate_computer_selection( void )
{
	// setup a counter
	int counter = 1;
	// wait for 1 second to switch

	while( counter-- > 0 ) {
		fprintf( stderr, "|");
		sleep( 1 );
		fprintf( stderr, "\b/" );
		sleep( 1 );
		fprintf( stderr, "\b-" );
		sleep( 1 );
		fprintf( stderr, "\b\\" ); 
		sleep( 1 );
		fprintf( stderr, "\b");
	}

	return 0;
}

int	 get_computer_selection( void)
{

	time_t t;

	// Intialize random number generator
	srand( (unsigned) time( &t ) );

	return (rand() % 3) + 1;
}

void	 print_computer_selection( void )
{
	printf( "\n---------\nComputer has selected: %d\n---------\n\n", 
		current_game_data.computer_selection );
	return;
}

int computer_turn( void )
{
	animate_computer_selection( );
	current_game_data.computer_selection = get_computer_selection( );

#ifdef DEBUG
	print_computer_selection( );
#endif

	switch( current_game_data.computer_selection  ) {
		case 1:
			total_game_data.computer_rock_selections++;
			break;
		case 2:
			total_game_data.computer_paper_selections++;
			break;
		case 3:
			total_game_data.computer_paper_selections++;
			break;
		default:
			break;
	}

	return current_game_data.computer_selection ;
}

void print_human_selection( void ) 
{
	printf( "\n---------\nPlayer has selected: %d\n---------\n\n", 
		current_game_data.human_selection );
}

int human_turn( void )
{
	int returned_characters = 0;
	char *stdin_buffer = malloc( sizeof( long ) );

	print_instructions_to_player( );
	fgets( stdin_buffer, sizeof( stdin_buffer ), stdin );
	// store player selection to compare with computer selection
	returned_characters = sscanf( stdin_buffer, "%d", &(current_game_data.human_selection) );

#ifdef DEBUG
	print_human_selection( );
#endif

	switch( current_game_data.human_selection ) {
		case 0:
			break;
		case 1:
			total_game_data.player_rock_selections++;
			break;
		case 2:
			total_game_data.player_paper_selections++;
			break;
		case 3:
			total_game_data.player_scissor_selections++;
			break;
		default:
			printf( "\n---------\nΗ επιλογή αυτή δεν είναι δυνατή. " );
			printf( "Παρακαλώ, προσπαθήστε ξανά\n---------\n\n");
			current_game_data.human_selection = -1;
			break;
	}

	return current_game_data.human_selection;
}

void decide_winner( int player_selection, int computer_selection )
{
	if( player_selection == computer_selection ){
		fprintf( stdout, "Open the pod bay doors, HAL.\n\n" );
		total_game_data.game_ties++;
	}
	else if( player_selection > computer_selection ) {
		fprintf( stdout, "Stupid machine! I win again!\n\n");
		total_game_data.games_won_by_player++;
	}
	else if( player_selection < computer_selection ) {
		fprintf( stdout, "EXTERMINATE! EXTEREMINATE! THE DALEKS ARE SUPERIOR!\n\n");
		total_game_data.games_won_by_computer++;
	}

	return;
}

void total_game_analysis( void )
{
	fprintf( stdout, "Ανάλυση παιχνιδιού: \n");
	fprintf( stdout, "Παίχτηκαν %ld παιχνίδια\n", total_game_data.games_played );
	fprintf( stdout, "Games won by player:   %ld\n", total_game_data.games_won_by_player );
	fprintf( stdout, "Games won by computer: %ld\n", total_game_data.games_won_by_computer );
	fprintf( stdout, "Game ties:             %ld\n", total_game_data.game_ties );
	fprintf( stdout, "+------------------------------+---------------------------+\n" );
	fprintf( stdout, "| Human player breakdow        | Computer player breakdown |\n" );
	fprintf( stdout, "+------------------------------+---------------------------+\n" );
	fprintf( stdout, "| rock | paper | scissors |    | rock | paper | scissors   |\n");
	fprintf( stdout, "| %ld  |  %ld  |  %ld     |    |  %ld | %ld   |  %ld       |\n", 
		total_game_data.player_rock_selections,   total_game_data.player_paper_selections,   total_game_data.player_scissor_selections,
		total_game_data.computer_rock_selections, total_game_data.computer_paper_selections, total_game_data.computer_scissor_selections ); 
	fprintf( stdout, "+---------------------------------------------------------+\n");

	fprintf( stdout, "\n" );
	fflush( stdout );

	return;
}

int main( int argc, char *argv[] )
{
	int player_selection = -1;
	int computer_selection = 0;

	if( !sanity_ok( ) ) {
		exit( EXIT_FAILURE );
	}

	if( argc > 1 ) {
		assert( argv[1] );
		print_help( );
		exit( EXIT_SUCCESS );
	}

	while( 0 != player_selection ) {

		player_selection = human_turn( );
		if( -1 == player_selection ) {
			continue;
		}
		else if( 0 == player_selection ){
			break;
		}
		computer_selection = computer_turn( );
		decide_winner( player_selection, computer_selection );
		total_game_data.games_played++;

	}

	total_game_analysis( );

	exit( EXIT_SUCCESS );
}