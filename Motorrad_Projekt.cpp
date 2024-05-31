

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Klasse zur Verwaltung der Kundendaten
class Kunde
{
public:

    // Kundendaten
    string vorname;
    string nachname;
    string strasse;
    int hausnummer;
    int plz;
    string ort;
    int geburtsjahr;
    string telefon;
    bool fuehrerschein;
    string motorrad;

    Kunde* next; // Zeiger auf den nächsten Kunden in der verketteten Liste

    Kunde() : next(NULL), hausnummer(0), plz(0), geburtsjahr(0), fuehrerschein(false) {} // Konstruktor zur Initialisierung

    // Überladen des Ausgabeoperators
    friend ostream& operator<<(ostream& aus, const Kunde& k);
    // Überladen des Eingabeoperators
    friend istream& operator>>(istream& ein, Kunde& k);
};

// Definition des Ausgabeoperators
ostream& operator<<(ostream& aus, const Kunde& k)
{
    aus << k.vorname << " " << k.nachname << " " << k.strasse << " " << k.hausnummer << " "
        << k.plz << " " << k.ort << " " << k.geburtsjahr << " " << k.telefon << " "
        << (k.fuehrerschein ? "Ja" : "Nein") << " " << k.motorrad;
    return aus;
}

// Definition des Eingabeoperators
istream& operator>>(istream& ein, Kunde& k)
{
    cout << "Vorname: ";          ein >> k.vorname;
    cout << "Nachname: ";         ein >> k.nachname;
    cout << "Strasse: ";          ein >> k.strasse;
    cout << "Hausnummer: ";       ein >> k.hausnummer;
    cout << "PLZ: ";              ein >> k.plz;
    cout << "Ort: ";              ein >> k.ort;
    cout << "Geburtsjahr: ";      ein >> k.geburtsjahr;
    cout << "Telefon: ";          ein >> k.telefon;
    cout << "Fuhrerschein Klasse A (1 = Ja, 0 = Nein): ";   ein >> k.fuehrerschein;

    if (k.fuehrerschein)
    {
        cout << "Verfugbare Motorrader: \n"
                "1. Suzuki GSX-8S\n"
                "2. Honda TransAlp\n"
                "3. BMW F 650 GS\n"
                "4. Ducati Streetfighter V4\n";
        cout << "Wahlen Sie ein Motorrad (geben Sie die Nummer ein): ";
        int auswahl;
        ein >> auswahl;
        switch (auswahl)
        {
            case 1:  k.motorrad = "Suzuki_GSX-8S";           break;
            case 2:  k.motorrad = "Honda_TransAlp";          break;
            case 3:  k.motorrad = "BMW_F_650_GS";            break;
            case 4:  k.motorrad = "Ducati_Streetfighter_V4"; break;
            default: k.motorrad = "Unbekannt"; break;
        }
    }
    return ein;
}

// Klasse zur Verwaltung der Motorradreservierungen
class Motorradverwaltung
{
private:
    Kunde* kund; // Zeiger auf den ersten Kunden in der verketteten Liste
    const string dateiname; // Dateiname für die Speicherung der Kundendaten

public:
    // Konstruktor, der die Datei lädt
    Motorradverwaltung(const string& datei) : kund(NULL), dateiname(datei)
    {
        ladenVonFolder();
    }

    // Destruktor, der die Datei speichert und die Liste löscht
    ~Motorradverwaltung()
    {
        speichernZuFolder();
        loschen();
    }

    // Methode zum Hinzufügen eines neuen Kunden
    void Kundefugen()
    {
        Kunde* neuerKunde = new Kunde();
        cin >> *neuerKunde;
        if (!neuerKunde->fuehrerschein)
        {
            cout << "Kein Fuhrerschein von Klasse A. Reservierung nicht moglich." << endl;
            cout << endl;
            delete neuerKunde;
            return;
        }

        // Überprüfen, ob das Motorrad bereits reserviert ist
        Kunde* temp = kund;
        while (temp)
        {
            if (temp->motorrad == neuerKunde->motorrad)
            {
                cout << "Reservierung nicht moglich, schon reserviert." << endl;
                cout << endl;
                delete neuerKunde;
                return;
            }
            temp = temp->next;
        }
        cout << "Motorrad reserviert " << endl;
        cout << endl;
        neuerKunde->next = kund;
        kund = neuerKunde;
        speichernZuFolder();
    }

    // Methode zum Entfernen eines Kunden anhand des Namens
    void Kundeloschen()
    {
        if (!kund)
        {
            cout << "Keine Kunden vorhanden." << endl;
            return;
        }

        string vorname, nachname;
        cout << "Vorname von Kunden: "; cin >> vorname;
        cout << "Nachname von Kunden: "; cin >> nachname;

        Kunde* temp = kund;
        Kunde* vorherige = NULL;

        // Suchen des Kunden in der Liste
        while (temp && (temp->vorname != vorname || temp->nachname != nachname))
        {
            vorherige = temp;
            temp = temp->next;
        }

        if (!temp)
        {
            cout << "Kunde nicht gefunden." << endl;
            return;
        }

        // Entfernen des Kunden aus der Liste
        if (vorherige)
        {
            vorherige->next = temp->next;
        } else
        {
            kund = temp->next;
        }

        delete temp;
        speichernZuFolder();
        cout << "Kunde entfernt." << endl;
        cout << endl;
    }

    // Methode zur Ausgabe aller Kunden
    void Kundenausdrucken() const
    {
        Kunde* temp = kund;

        while (temp)
        {
            cout << "Kunde: " << temp->vorname <<", " <<temp->nachname <<", " <<temp->strasse <<". "  <<temp->hausnummer <<", "
                 <<temp->plz <<", "  <<temp->ort <<", "  <<temp->geburtsjahr <<", "  << temp->telefon <<", "  << temp->fuehrerschein << endl;
            cout << "Motorrad: "<<temp->motorrad << endl;
            temp = temp->next;
        }
        cout << endl;
    }

private:
    // Methode zum Speichern der Kundenliste in die Datei
    void speichernZuFolder() const
    {
        ofstream datei(dateiname);
        Kunde* temp = kund;
        while (temp)
        {
            datei << temp->vorname << " " << temp->nachname << " " << temp->strasse << " "
                  << temp->hausnummer << " " << temp->plz << " " << temp->ort << " "
                  << temp->geburtsjahr << " " << temp->telefon << " "
                  << temp->fuehrerschein << " " << temp->motorrad << endl;
            temp = temp->next;
        }
    }

    // Methode zum Laden der Kundenliste aus der Datei
    void ladenVonFolder()
    {
        ifstream datei(dateiname);

        loschen(); // stellt sicher, dass die aktuelle Liste leer ist.
        Kunde* last = NULL;

        while (!datei.eof()) // Bedinung : true zurückgibt, wenn der End-of-File-Zustand erreicht ist.
        {
            // Einlesen der Kundendaten aus der Datei
            Kunde* neuerKunde = new Kunde();
            datei >> neuerKunde->vorname >> neuerKunde->nachname >> neuerKunde->strasse
                  >> neuerKunde->hausnummer >> neuerKunde->plz >> neuerKunde->ort
                  >> neuerKunde->geburtsjahr >> neuerKunde->telefon >> neuerKunde->fuehrerschein
                  >> neuerKunde->motorrad;

            // Überprüfung, ob alle Felder korrekt eingelesen wurden
            if (neuerKunde->vorname.empty() || neuerKunde->nachname.empty() || neuerKunde->strasse.empty() ||
                neuerKunde->hausnummer <= 0 || neuerKunde->plz <= 0 || neuerKunde->ort.empty() ||
                neuerKunde->geburtsjahr <= 0 || neuerKunde->telefon.empty()) {
                delete neuerKunde; // Wenn das Einlesen fehlschlägt, den neuen Kunden löschen
                break;
            }

            // Neuer Kunde wird zur Liste hinzugefügt
            if (last)
            {
                last->next = neuerKunde;
            } else
            {
                kund = neuerKunde;
            }
            last = neuerKunde;
        }
    }

    // Methode zum Löschen der Kundenliste
    void loschen()
    {
        while (kund)
        {
            Kunde* temp = kund;
            kund = kund->next;
            delete temp;
        }
    }
};

int main() {
    Motorradverwaltung verwaltung("Motorrad_reservierungen.txt");

    int wahl;
    do {// Menüauswahl
        cout << " 1. Kunde hinzufugen\n 2. Kunde entfernen\n 3. Kunden anzeigen\n 0. Beenden\n";
        cout << "Ihre Wahl: "; cin >> wahl;
        cout<<endl;

        switch (wahl) {
            case 1:
                verwaltung.Kundefugen();        //neue Kunde einfügen
                break;
            case 2:
                verwaltung.Kundeloschen();      //Kunde löschen
                break;
            case 3:
                verwaltung.Kundenausdrucken();  // alle Kunden ausdrucken
                break;
            case 0:
                break;
            default:
                cout << "Ungultige Wahl. Bitte erneut versuchen." << endl;
        }
    } while (wahl != 0);

    return 0;
}

/*
 //TODO Ausgabe:
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