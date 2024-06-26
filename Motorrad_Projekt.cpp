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
                cout << "\033[31m" <<"Kein Fuhrerschein von Klasse A. Reservierung nicht moglich."<< "\033[0m" << endl;
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
                    cout <<"\033[31m" << "Reservierung nicht moglich, schon reserviert."<< "\033[0m" << endl;
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
                cout << "\033[31m" << "Keine Kunden vorhanden."<< "\033[0m" << endl;
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
                cout <<  "\033[31m"<<"Kunde nicht gefunden." << "\033[0m" << endl;
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
            cout << "\033[31m"<<"Kunde entfernt."<< "\033[0m" << endl;
            cout << endl;

        }

        // Methode zur Ausgabe aller Kunden
        void Kundenausdrucken() const
        {
            Kunde* temp = kund;

            while (temp)
            {
                cout <<"\033[34m" << "Kunde: " << temp->vorname <<", " <<temp->nachname <<", " <<temp->strasse <<". "  <<temp->hausnummer <<", "
                <<temp->plz <<", "  <<temp->ort <<", "  <<temp->geburtsjahr <<", "  << temp->telefon <<", "  << temp->fuehrerschein << endl;
                cout << "Motorrad: "<<temp->motorrad << "\033[0m"<< endl;
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
                verwaltung.Kundenausdrucken();
                break;
            case 2:
                verwaltung.Kundeloschen();      //Kunde löschen
                verwaltung.Kundenausdrucken();
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
