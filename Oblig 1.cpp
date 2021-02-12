/*
*   Oblig 1
* 
*	Programmet lager en liste over oppgaver som skal gjennomf�res,
*	tilegner hver oppgave en ansvarlig person, 
*	og mulighet til � lagre hvorvidt oppgavene er gjennomf�rt eller ikke.
* 
*	Funksjonaliteten g�r ut p� at man kan:
*	- Legge til nye oppgaver
*	- Hente en liste over alle oppgaver, med status for oppgavene.
*	- Endre status for allerede eksisterende oppgaver.
*/


#include <iostream> //cin, cout
#include <string>   //string
#include <vector>   //vector 
#include <iomanip>  // setw
#include "LesData2.h" //lesInt, lesChar, lesFloat
using namespace std;

/*
*  Formatet p� structen som skal lagres i arrayen.
*/
struct Oppgave
{
	string beskrivelse,  //Hva oppgaven er
		   ansvarlig;    //Hvem som skal gj�re den
	bool   erFullfort;   //Om oppgaven er gjort.

};

vector <Oppgave*> gOppgaver; //Arrayen som brukes

void fjernAlleOppgaver(); 
void nyOppgave(); 
void oppgaveEndreStatus(); 
void oppgaveEndreStatus(Oppgave & oppgave); 
void oppgaveLesData(Oppgave & oppgave); 
void oppgaveSkrivData(const Oppgave* oppgave); 
void skrivAlleOppgaver(); 
void skrivMeny();

/*
*  Hovedprogrammet
*/
int main()
{
	char kommando;

	skrivMeny();

	kommando = lesChar("\nKommando\n");

	while (kommando != 'Q')
	{
		switch (kommando) {
		case 'N': nyOppgave();            break;
		case 'S': skrivAlleOppgaver();    break;
		case 'E': oppgaveEndreStatus();   break;
		default: skrivMeny();             break;
		}

		kommando = lesChar("\nKommando\n");
	}

	fjernAlleOppgaver();

	return 0;
}

/*
* Skriver ut menyen
*/
void skrivMeny() {
	cout << "N - Ny oppgave\n"
		<< "S - Se alle oppgaver\n"
		<< "E - Endre en oppgave\n"
		<< "Q - Avslutte programmet";
}

/*
* Legger til ny oppgave ved � bruke oppgaveLesData()
*/
void nyOppgave() {
	
	Oppgave* nyOppgave = new Oppgave;        //Lager ny struct av malen Oppgave
	cout << "Ny Oppgave: \n";
	oppgaveLesData(*nyOppgave);
	gOppgaver.push_back(nyOppgave);
	cout << "Den nye oppgaven har nr." << gOppgaver.size() << "\n";
}

/*
* Leser data fra brukerens input som sendes til nyOppgave().
*/
void oppgaveLesData(Oppgave & oppgave) {
	cout << "Hva er oppgaven? \n";
	getline(cin, oppgave.beskrivelse);
	cout << "Hvem er ansvarlig? \n";
	getline(cin, oppgave.ansvarlig);
	oppgave.erFullfort = false;
}

/*
* Skriver ut alle oppgaver ved � kalle p� funksjonen oppgaveSkrivData() flere ganger,
* ved hjelp av variabelen i .
*/
void skrivAlleOppgaver() {
	for (int i = 0; i < gOppgaver.size(); i++) {
		cout << "\nOppgave nr." << setw(2) << i + 1 << ":\n";
		oppgaveSkrivData(gOppgaver[i]);
	}
}

/*
* Skriver ut oppgaver ved hjelp av pointer til arrayen
*/
void oppgaveSkrivData(const Oppgave* oppgave) {
	cout  << "Beskrivelse: " << oppgave->beskrivelse
		<< "   Ansvarlig: " << oppgave->ansvarlig;
	if (oppgave->erFullfort == false) {   //Sjekker om oppgaven er fullf�rt, og skriver ut korresponderende alternativ.
		cout << "   Ikke gjort.\n";
	}
	else {
		cout << "   Gjort.\n";
	}
		
}

/*
* Velger oppgave som �nskes markert som gjennomf�rt.
*/
void oppgaveEndreStatus() {
	oppgaveEndreStatus(*gOppgaver[lesInt("Nummer p� gjennomf�rt oppgave:", 1, gOppgaver.size()) - 1]);
}

/*
* Endrer status p� valgt oppgave fra ikke gjennomf�rt til gjennomf�rt.
*/
void oppgaveEndreStatus(Oppgave& oppgave) {
	cout << "\nOppgaven er markert som gjort.\n";
	oppgave.erFullfort = true;
}

/*
*  Fjerner alle data i arrayen n�r programmet avsluttes
*/
void fjernAlleOppgaver() {
	for (int i = 0; i < gOppgaver.size(); i++)
		delete gOppgaver[i];
	gOppgaver.clear();
	cout << "\n\nArrayen er tom - antallet er: " << gOppgaver.size() << "\n\n";
}