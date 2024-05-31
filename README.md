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
