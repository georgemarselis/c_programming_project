# ΠΕΖ2015: Άσκηση 3η

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


----

# Πως να το κατεβάσετε:

> git clone https://github.com/georgemarselis/c_programming_project.git && 
cd c_programming_project; cd c_programming_project/exercise_3 && make clean && make;

Επιλογές:
* -h Προβολή βοήθειας 
* -f <αρχειο> Επιλογή αρχείου για αναζήτηση (προεπιλογή: *"lorem_ipsum.txt"*
* -t <λέξη>   Όρος αναζήτησης

# Παραδείγματα: 

> ./sentence_table -f lorem_bacon.txt -t round : Ψάχνει το αρχείο *lorem_bacon.txt* για τη λέξη *"round"* ( υπάρχει )
> ./sentence_table -f lorem_bacon.txt -t κοκο  : Ψάχνει το αρχείο *lorem_bacon.txt* για τη λέξη *"κοκο"*  ( δεν υπάρχει )
> ./sentence_table -f lorem_ipsum.txt -t solo  : Ψάχνει το αρχείο *lorem_ipsum.txt* για τη λέξη *"solo"*  ( υπάρχει )
> ./sentence_table -f lorem_ipsum.txt -t bar   : Ψάχνει το αρχείο *lorem_ipsum.txt* για τη λέξη *"λαλα"*  ( δεν υπάρχει )
> ./sentence_table -f lorem_bacon.txt          : Αναζητά στο αρχείο *lorem_ipsum.txt* όποιον όρο εισάγει δυναμικά ο χρήστης
> ./sentence_table 	                           : Αναζητά τον όρο που δυναμικά θα εισάγει ο χρήστης στο προεπιλεγμένο αρχείο *lorem_ipsum.txt*

# Δείγμα αποτελέσματος
> [gmarselis@wintermute exercise_3 (master)]$ ./sentence_table -f lorem_ipsum.txt -t solo

> Words counted 390

> Sentence: 0 / Token is: Lucas ipsum dolor sit amet binks kit naboo skywalker calrissian wedge bespin alderaan skywalker biggs

> Sentence: 1 / Token is:  Mon vader sidious ewok darth thrawn amidala padmé

> Sentence: 2 / Token is:  Mothma darth yoda mon antilles solo anakin calrissian

> Sentence: 3 / Token is:  Maul moff lando organa dantooine leia lando jawa

> Sentence: 4 / Token is:  Qui-gonn mace skywalker jango darth fett greedo

> Sentence: 5 / Token is:  Darth sebulba vader padmé skywalker

> Sentence: 6 / Token is:  Anakin antilles hutt skywalker grievous bespin c-3p0 alderaan

> Sentence: 7 / Token is:  Organa dantooine solo luke organa leia

> Sentence: 8 / Token is:  Vader moff droid twi'lek wedge tatooine qui-gon

> Sentence: 9 / Token is:  Ahsoka ahsoka watto mara moff skywalker

> Sentence: 10 / Token is:  Lando darth tatooine luke skywalker organa

> Sentence: 11 / Token is:  Yavin yoda wookiee antilles twi'lek windu

> Sentence: 12 / Token is:  Baba moff droid windu maul

> Sentence: 13 / Token is:  Antilles bespin wookiee darth solo kit watto

> Sentence: 14 / Token is:  Ewok han obi-wan maul skywalker mon dagobah ackbar mandalore

> Sentence: 15 / Token is:  Naboo darth hoth kessel moff hutt organa antilles utapau

> Sentence: 16 / Token is:  C-3po boba yavin calamari c-3po coruscant calamari aayla

> Sentence: 17 / Token is:  Tusken raider maul leia dooku skywalker ventress mustafar kashyyyk

> Sentence: 18 / Token is:  Darth obi-wan lobot zabrak luke kenobi

> Sentence: 19 / Token is:  Mothma fett hutt zabrak

> Sentence: 20 / Token is:  Skywalker lobot mace han chewbacca obi-wan dooku hoth darth

> Sentence: 21 / Token is: Darth solo boba windu organa antilles skywalker

> Sentence: 22 / Token is:  Padmé jinn darth tatooine kessel binks tatooine

> Sentence: 23 / Token is:  Moff hutt chewbacca mon mace yavin tatooine

> Sentence: 24 / Token is:  Hutt sith yoda grievous

> Sentence: 25 / Token is:  Organa dagobah palpatine kessel leia

> Sentence: 26 / Token is:  Biggs fett wampa secura

> Sentence: 27 / Token is:  Wedge luuke darth sidious dantooine solo sidious c-3p0

> Sentence: 28 / Token is:  Thrawn r2-d2 mon amidala jango

> Sentence: 29 / Token is:  Kessel qui-gon hutt chewbacca amidala solo fett organa moff

> Sentence: 30 / Token is:  Antilles tatooine luke darth moff moff luuke zabrak darth

> Sentence: 31 / Token is:  Hutt fisto amidala greedo yoda kit mandalorians

> Sentence: 32 / Token is:  Antilles aayla sidious tatooine

> Sentence: 33 / Token is:  Hutt windu hoth jade solo dooku darth

> Sentence: 34 / Token is:  Bespin windu palpatine organa dooku

> Sentence: 35 / Token is:  Greedo mon thrawn solo solo wedge droid moff moff

> Sentence: 36 / Token is:  Antilles solo ponda jade boba jade biggs binks

> Sentence: 37 / Token is:  Darth yoda ben hutt

> Sentence: 38 / Token is:  C-3po kamino moff jinn vader jango tatooine moff

> Sentence: 39 / Token is:  Antilles windu coruscant amidala darth organa padmé

> Sentences counted: 40

> "solo" appears in sentences 2, 7, 13, 21, 27, 29, 33, 35, 36


# Λειτουργία:

Η λειτουργία χωρίζεται στα εξείς μέρη:

1. Ανάλυση των επιλογών της γραμμής εντολών
2. Αν υπάρχουν επιλογές για αρχείο ή όρο αναζήτηση, τις χρησιμοποιούμε αυτούσιες
3. Αν δεν υπάρχουν, χρησιμοποιούμε τα προεπιλεγμένα και ρωτάμε τον χρήστη για ότι δεν καλύπτεται
4. Δεν ζητάμε από τον χρήστη εισαγωγή κειμένου, καθώς αυτό είναι χρονοβόρο και δύσκολο στην δοκιμή.
5. **Μετρηση λέξεων:** Θεωρούμε ότι οι λέξεις χωρίζονται απο κένα. Οπότε με την χρησιμοποίηση της strtok(), σπάμε την αλφαριθμητική μεταβλητή σειρά όλου του αρχείο σε 'λέξεις'. Στον τελικό αριθμό, προσθέτουμε 2 για την αρχική και τελική λέξη, καθώς δεν έχουμ κενά πριν της αρχικής και μετά την τελική λέξη. 
6. **Απαρίθμηση προτάσεων**: Ως γραμματική πρόταση Θεωρούμε μια αλφαριθμητική σειρά που τελειώνει σε τελεία (BNF sentence := [A-Za-z][0-9]\.$). Σπάμε τη κάθε σειρά του αρχείου σε προτάσεις, χρησιμοποιόντας την strtok(). Αποθηκεύουμε τις προτάσεις σε ένα προσωρινό χώρο μνήμης. Μετά, τυπώνουμε τον αριθμό τις κάθε προτάσης, με βάση το 0, όχι το 1. Ψάχνουμε για *την πρώτη εμφάνιση της κάθε λέξης σε κάθε πρόταση*: διπλοτυπία δεν έχει σημασία, καθώς δεν παρατάσουμε την συχνότητα της εμφάνιση της κάθε λέξης μέσα σε κάθε πρόταση. Στο τέλος τυπώνουμε αυτές τις προτάσεις που υπάρχει η πρώτη εμφάνιση της αναζητούμενης λέξης.
7. Έξοδος από το πρόγραμμα.