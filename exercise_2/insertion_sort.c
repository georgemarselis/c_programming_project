/*

 Άσκηση 2η
 Ο αλγόριθμος ταξινόμησης με επιλογή (insertion sort) για ένα πίνακα (έστω Α)
 n στοιχείων βασίζεται σε σάρωμα του πίνακα και εφαρμογή επαναληπτικά των ακόλουθων
 τριών βημάτων:

 *   (i) επιλογή του στοιχείου με την ελάχιστη τιμή,
 *  (ii) ανταλλαγή του στοιχείου με το πρώτο στοιχείο Α[0],
 * (iii) επανάληψη των (i), (ii) με τα υπόλοιπα στοιχεία (Α[1]...Α[n-1]).

 Μετά από n-1 επαναλήψεις τα στοιχεία του πίνακα θα είναι διατεταγμένα κατά
 αύξουσα σειρά. Υλοποιήστε τον αλγόριθμο για ένα πίνακα από Ν στοιχεία, όπου
 τόσο τα στοιχεία του πίνακα, όσο και ο αριθμός τους θα πρέπει να δίνεται από
 τον χρήστη (συνεπώς ο πίνακας θα πρέπει να υλοποιηθεί χρησιμοποιώντας δείκτες).


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

void begin_execution( void );
int sanity_ok( void );
void help( void );
char *readfile( const char *filename );
void begin_execution( void );
void insertionsort(int array[], int size);

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

    return;
}


char *readfile( const char *filename )
{
    char   *buff        = NULL;
    FILE   *infile      = NULL;
    struct stat *st     = NULL;

    st = malloc( sizeof( *st ) + 1  );

    if( -1 == stat( filename, st ) ) {
        fprintf( stderr, "Cannot stat file %s . Exiting\n", filename );
        exit( 1 );
    }

    infile = fopen( filename, "r" );
    if( NULL == infile ) {
        fprintf( stderr, "Cannot open file %s . Exiting\n", filename );
        exit( 1 );
    }

    // read file
    buff = malloc( sizeof( char ) * ( st->st_size + 1 ) );
    if( NULL == buff ) {
        fprintf( stderr, "Cannot allocate memory to read input file. Exiting\n" );
        exit( 1 );
    }

    if( 0 == fread( buff, sizeof( char ), st->st_size, infile ) ) {
        fprintf( stderr, "file %s is empty. Exiting\n", filename );
    }

    fclose( infile ); free( st );
    
    return buff;
}

void insertionsort( int *array, int size )
{
    int i;
    int key;
    int j;

    for( i = 1; i < size; i++ ) {
        key = array[ i ];
        j = i - 1;
        while (j >= 0 && array[j] > key ) {
            array[ j + 1] = array[ j ];
            j = j - 1;
        }
        array[ j + 1 ] = key;
    }

    return;
}


void begin_execution( void )
{
    int i = 0;
    int *array = NULL;
    int counter = 0;
    char *file = readfile( "./data.txt" );
    char *tmp = malloc( sizeof( char ) * ( strlen( file ) + 1 ) );
    //    int n, array[1000], c, d, t;

    strcpy( tmp, file );
    for( tmp = strtok( tmp, "\n" ); NULL != tmp; tmp = strtok( NULL, "\n" ) ) {
        ++counter;
    }

    array = malloc( sizeof( int ) * counter );
    tmp = realloc( tmp, sizeof( char ) * ( strlen( file ) + 1 ) );
    strcpy( tmp, file );

    i = 0;
    for( tmp = strtok( tmp, "\n" ); NULL != tmp; tmp = strtok( NULL, "\n" ) ) {
        array[i] = atoi(tmp);
        ++i;
        if( i > counter ) { fprintf( stdout, "count " ); }
    }

#ifdef DEBUG
    for( int kot = 0; kot < counter; kot++ ) {
        printf( "Pre-sort: item: %d\n", array[kot] );
    }
#endif
    insertionsort( array, counter );

    for( int kot = 0; kot < counter; kot++ ) {
        printf( "Sorted: item: %d\n", array[kot] );
    }

    free( file );
    free( array);

    return;
}


int main( void )
{
    // check the status of the terminal
    if( !sanity_ok( ) ) {
        exit( EXIT_FAILURE );
    }

    // in case of emergency grake blass
    begin_execution( );

    return 0;
}

