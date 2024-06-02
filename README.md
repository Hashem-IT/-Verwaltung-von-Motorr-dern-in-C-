# -Verwaltung-von-Motorr-dern-in-C-
Programm zur Verwaltung von Motorrädern in C++

Aufgabenstellung:

Sie sollen ein Programm zur Verwaltung von Motorrädern in C++ realisieren.

Motorradvermietung

Sie sind für die Verwaltung von Motorrädern zuständig. Da zurzeit alle Vorgänge in Papierform festgehalten werden, sollen Sie ein Programm zur Motorradverwaltung erstellen.

Die Mitarbeiterin soll die Möglichkeit haben, die Kunden zu verwalten und Reservierungen der Motorräder vorzunehmen. Der Kunde kann nur jeweils ein Motorrad reservieren. Es gibt insgesamt 4 Motorräder zur Auswahl: „Suzuki GSX-8S" „Honda TransAlp“, „BMW F 650 GS“ und „Ducati Streetfighter V4“. Stellen Sie sicher, dass ein Motorrad nicht doppelt reserviert wird. Bei der Reservierung muss der Kunde: Name, Vorname, Adresse (Straße, Nr. PLZ, Ort), Geburtsjahr, Telefonnummer und ob er Führerschein der Klasse A besitzt, angeben. Besitzt er kein Führerschein der Klasse A, so kann kein Motorrad für ihn reserviert werden. Sobald die Übergabe des Motorrads erfolgt ist, wird die Reservierung für diesen Kunden storniert. Der Datensatz wird aus der verketteten Liste rausgenommen.

Jedes mal, wenn ein Motorrad reserviert oder herausgegeben wird, soll die Datei geschrieben/aktualisiert werden.

 

Das Programm soll mindestens folgende Anforderungen erfüllen:

 Verwaltung der Kunden:

Daten erfassen. Die Erfassung der Daten soll über istream (>>) Operatorüberladung erfolgen.
Alle Kundendaten ausgeben. Die Ausgabe soll über ostream (<<) Operatorüberladung erfolgen.
Verwaltung der Reservierungen:

Reservierung vornehmen
Motorrad herausgeben (mit der Abfrage des Kundenvor- und nachnamens)
 Dateiverwaltung:

Die Datensätze sollen in einer verketteten Liste gespeichert werden.
Der aktuelle Stand der Reservierungen soll in die Datei „reservierungen.txt“ geschrieben werden. Falls die Datei noch nicht existiert, soll sie angelegt werden. Ansonsten sollen die Daten überschrieben werden.
Beim Starten des Programms soll die Datei gelesen und die verkettete Liste (sofern Datensätze vorhanden sind) mit den Daten befüllt werden.
 

Die Verwaltung der Kunden soll dynamisch erfolgen. Bei Bedarf sollen entsprechende (Fehler-) Meldungen ausgegeben werden. Achten Sie auf eine angemessene Dokumentation Ihres Programms!

------------------------------------------------------------

/*

 //Beschreibung

Das Programm zur Verwaltung von Motorradreservierungen. Es besteht aus zwei Klassen: Kunde und Motorradverwaltung.Das Programm lädt die vorhandenen Kundendaten aus der Datei Motorrad_reservierungen.txt.

Klasse: Kunde
Diese Klasse repräsentiert die Daten eines Kunden und enthält die folgenden Attribute:
Vorname, Nachname, Straße, Hausnummer, PLZ, Ort, Geburtsjahr, Telefon, Führerschein, Motorrad und next (Zeiger auf den nächsten Kunden).
Und Klasse hat zwei überladene Operatoren:
Den Ausgabeoperator (<<), der die Kundendaten formatiert ausgibt.
Den Eingabeoperator (>>), der die Eingabe der Kundendaten vom Benutzer entgegennimmt.

Klasse: Motorradverwaltung
Diese Klasse verwaltet die Liste der Kunden und ihre Motorradreservierungen:
- Konstruktor : Motorradverwaltung(const string& datei)
- Destruktor: Motorradverwaltung()
- Methoden: void Kundefugen(), void Kundeloschen(), void Kundenausdrucken() const,void speichernZuFolder() const, void ladenVonFolder() und void loschen().

 //Ausgabe:
->FALL: Motorrad Reservierung

 1. Kunde hinzufugen
 2. Kunde entfernen
 3. Kunden anzeigen
 0. Beenden
Ihre Wahl: 1

Vorname: Test1
Nachname: Test1
Strasse: berlin
Hausnummer: 1
PLZ: 12345
Ort: berlin
Geburtsjahr: 1999
Telefon: 091234567
Fuhrerschein Klasse A (1 = Ja, 0 = Nein): 1
Verfugbare Motorrader:
1. Suzuki GSX-8S
2. Honda TransAlp
3. BMW F 650 GS
4. Ducati Streetfighter V4
Wahlen Sie ein Motorrad (geben Sie die Nummer ein): 1
Motorrad reserviert

 ->FALL: Motorrad Reservierung

 1. Kunde hinzufugen
 2. Kunde entfernen
 3. Kunden anzeigen
 0. Beenden
Ihre Wahl: 1

Vorname: Test2
Nachname: Test2
Strasse: berlin
Hausnummer: 2
PLZ: 12345
Ort: berlin
Geburtsjahr: 2000
Telefon: 012345567
Fuhrerschein Klasse A (1 = Ja, 0 = Nein): 1
Verfugbare Motorrader:
1. Suzuki GSX-8S
2. Honda TransAlp
3. BMW F 650 GS
4. Ducati Streetfighter V4
Wahlen Sie ein Motorrad (geben Sie die Nummer ein): 2
Motorrad reserviert

 -> Kunden anzeigen FALL

 1. Kunde hinzufugen
 2. Kunde entfernen
 3. Kunden anzeigen
 0. Beenden
Ihre Wahl: 3

Kunde: Test2, Test2, berlin. 2, 12345, berlin, 2000, 012345567, 1
Motorrad: Honda_TransAlp
Kunde: Test1, Test1, berlin. 1, 12345, berlin, 1999, 091234567, 1
Motorrad: Suzuki_GSX-8S

  ->FALL:  Reservierung nicht moglich, schon reserviert
 1. Kunde hinzufugen
 2. Kunde entfernen
 3. Kunden anzeigen
 0. Beenden
Ihre Wahl: 1

Vorname: test3
Nachname: test3
Strasse: berlin
Hausnummer: 3
PLZ: 12345
Ort: berlin
Geburtsjahr: 2000
Telefon: 0124567
Fuhrerschein Klasse A (1 = Ja, 0 = Nein): 1
Verfugbare Motorrader:
1. Suzuki GSX-8S
2. Honda TransAlp
3. BMW F 650 GS
4. Ducati Streetfighter V4
Wahlen Sie ein Motorrad (geben Sie die Nummer ein): 1
Motorrad reserviert

Reservierung nicht moglich, schon reserviert.

->FALL: Kunde entfernen
 1. Kunde hinzufugen
 2. Kunde entfernen
 3. Kunden anzeigen
 0. Beenden
Ihre Wahl: 2

Vorname von Kunden: Test2
Nachname von Kunden: Test2
Kunde entfernt.

 1. Kunde hinzufugen
 2. Kunde entfernen
 3. Kunden anzeigen
 0. Beenden
Ihre Wahl: 3

Kunde: Test1, Test1, berlin. 1, 12345, berlin, 1999, 091234567, 1
Motorrad: Suzuki_GSX-8S

 1. Kunde hinzufugen
 2. Kunde entfernen
 3. Kunden anzeigen
 0. Beenden
Ihre Wahl: 0

->FALL: Kein Fuhrerschein

 1. Kunde hinzufugen
 2. Kunde entfernen
 3. Kunden anzeigen
 0. Beenden
Ihre Wahl: 1

Vorname: test1
Nachname: test1
Strasse: berlin
Hausnummer: 1
PLZ: 12345
Ort: berlin
Geburtsjahr: 1234
Telefon: 124124124
Fuhrerschein Klasse A (1 = Ja, 0 = Nein): 0
Kein Fuhrerschein von Klasse A. Reservierung nicht moglich.

 */
