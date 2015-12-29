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

----

# Πως να το κατεβάσετε:

> git clone https://github.com/georgemarselis/c_programming_project.git && cd c_programming_project; cd c_programming_project/exercise_5 && make clean && make debug;

# Επιλογές:
* -h | --help
* -f <αρχείο> αρχείο απο όπου διαβάζονται τα στοιχεία

# Παραδείγματα:

> ./airline_reservation_system              : υπολογισμός κρατήσεων με στοιχεία από τον χρήστη
> ./airline_reservation_system -f data.txt 	: υπολογισμός κρατήσεων με στοιχεία απο αρχείο
> ./airline_reservation_system < data.txt   : ισοδύναμο

# Δείγματα αποτελέσματος

> [gmarselis@wintermute exercise_5 (master)]$ clear; ./airline_reservation_system

> [gmarselis@wintermute exercise_5 (master)]$ clear; ./airline_reservation_system -f data.txt

> [gmarselis@wintermute exercise_5 (master)]$ clear; ./airline_reservation_system < data.txt #molis teleiwsei ayto, na to antigrapsw kai stis alles askhseis, kai meta na sbhsw ayto to sxolio.



# Λειτουργία:

Η λειτουργία χωρίζεται στα εξείς μέρη:

1. Ανάλυση των επιλογών της γραμμής εντολών
2. Αν υπάρχουν επιλογές
