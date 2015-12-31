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

> record   1: Flight: OA344 Seats: 100 Passengers:  80

> record   2: Flight: OA421 Seats:  84 Passengers:  37

> record   3: Flight: OA830 Seats:  78 Passengers:  34

> record   4: Flight: OA123 Seats:  24 Passengers:  21

> record   5: Flight: OA343 Seats: 490 Passengers: 482

> record   6: Flight: OA478 Seats: 300 Passengers:  40

> record   7: Flight: OA398 Seats: 897 Passengers: 432

> record   8: Flight: OA189 Seats:  73 Passengers:  27

> record   9: Flight: OA208 Seats:  84 Passengers:  37

> record  10: Flight: OA981 Seats: 348 Passengers:  99

> record  11: Flight: OA378 Seats:  37 Passengers:  36

> Total passengers on all flights:  1325

> There are 5 airlines booked at capacity.

> The airlines booked at capacity are: OA344 OA123 OA343 OA378

# Λειτουργία:

Η λειτουργία χωρίζεται στα εξείς μέρη:

1. Ανάλυση των επιλογών της γραμμής εντολών
2. Αν υπάρχουν επιλογές τις επεξεργαζόμαστε. Η κυρίως επιλογή είναι το αρχείο από όπου θα διαβάσουμε
3. Διαβάζουμε το αρχείο με τα στοιχεία
4. Το επεξεργαζόμαστε σε δομές
5. Τυπώνουμε τις επεξεργαζμένες δομές
6. Στέλνουμε τις δομές σε δική τους συνάρτηση για να αρθρήσουμε τους επιβάτες, σε ενα απλό while() loop
7. Στέλνουμε τις δομές σε δεύτερη συνάρτηση για να ανακαλύψουμε πληρότητα
8. Έξοδος από το πρόγραμμα
