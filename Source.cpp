#include <iostream>
#include "C:\Users\chris\source\repos\PM_OPDR4_2\PM_OPDR4_2\Header.h"

using namespace std;

game::game() {
	infobericht();
	getuserinput();
	AI* Computerh;
	Computerh = new AI;
	Computer = Computerh;
	cout << Computer << endl;
	een = new speler;
	Gobord = make_gobord();
	if ( (hoeveel > 4) && (isAIAanZet == 2)) {
		showandtell = false;
	}
	if (showandtell == true) {
		Gobord->drukaf();
	}
}

int game::gethoeveel() {
	return hoeveel;
}

void game::endgame() {
	Statestieken.beurten_verstreken++;
	if(Gobord->gelijkspelcondities() == true){
		Statestieken.this_gelijkspel = true;
	}
	wincondities();
}

void stats::stash_winnings() {
	if (this_gelijkspel == true) {
		gelijkspellen++;
	}else {
		place_win_in_JSON();
	}
}

void stats::place_win_in_JSON() {
	if (ingang == NULL) {
		ingang = new JSON(NULL, 0);
	}else {
		ingang->walktoturn(beurten_verstreken);
	}
}

void JSON::walktoturn(int beurten_verstreken) {
	JSON* helper = this;
	int x = 0;
	while (x <= beurten_verstreken) {
		if (helper->volgende == NULL) {
			JSON* hulp = new JSON(helper, x);
			helper->volgende = hulp;
			helper = helper->volgende;
		}else {
			helper = helper->volgende;
		}
		x++;
	}
	helper->hoeveelkeergewonnen++;
}

void game::printlist() {
	Statestieken.printlist();
}

void stats::printlist() {
	JSON* helper = ingang;
	int beurt = 0;
	int hoeveelkeergewonnen = 0;

	while (helper->volgende != NULL) {
		helper->getinfo(beurt, hoeveelkeergewonnen);
		cout << beurt; 
		if (beurt < 10) {
			cout << "   ";
		}
		else if (beurt < 100) {
			cout << "  ";
		}
		else if (beurt < 1000) {
			cout << " ";
		}
		cout << ": " << hoeveelkeergewonnen << endl;
		helper = helper->volgende;
	}
	helper->getinfo(beurt, hoeveelkeergewonnen);
	cout << beurt;
	if (beurt < 10) {
		cout << "   ";
	}
	else if (beurt < 100) {
		cout << "  ";
	}
	else if (beurt < 1000) {
		cout << " ";
	}
	cout << ": " << hoeveelkeergewonnen << endl;
}

void JSON::getinfo(int& beurtpss, int& hoeveelkeergewonnenpss) {
	beurtpss = beurt;
	hoeveelkeergewonnenpss = hoeveelkeergewonnen;
}

JSON::JSON(JSON* vorigepss, int place) {
	vorige = vorigepss;
	beurt = place;
}

void game::Thanos() {
	Statestieken.stash_winnings();
	Statestieken.beurten_verstreken = 0;
	Zet->setmassdestruct(true);
	delete Zet;
	Zet = NULL;
	delete Gobord;
	Gobord = NULL;

}

void game::wincondities() {
	int hulpx = Zet->getinfoplace(1);
	int hulpy = Zet->getinfoplace(2);

	Gobord->winnenit(hulpx, hulpy);
}

int game::outputMenu() {
	int help;
	cout << "___________________________________________________________________________" << endl;
	cout << "|Wilt U een zet zetten? Of naar het speciale menu?........................|" << endl;
	cout << "|zetten: 1...................... Speciale menu: 333.......................|" << endl;
	cout << "|_________________________________________________________________________|" << endl;
	cin >> help;
	return help;
}

char game::speciaalMenu() {
	char hulp;
	cout << "____________________________________________________________________" << endl;
	cout << "|Wilt U een zet terug nemen, undo, of terug naar het vorige menu?..|" << endl;
	cout << "|T voor terug nemen, U voor undo, V voor vorige menu...............|" << endl;
	cout << "|__________________________________________________________________|" << endl;
	cin >> hulp;
	return hulp;
}

bool game::SMuitvoeren(char hulp, bool & dontdoit) {
	bool getmeout = false;
		switch (hulp) {
		case 'T':
			if (Zet->getvorige() != NULL) {
				Gobord->doe(Zet->getinfoplace(1), Zet->getinfoplace(2), 'x');
				Zet = Zet->getvorige();
			}else {
				Gobord->doe(Zet->getinfoplace(1), Zet->getinfoplace(2), 'x');
				cout << "Pas iets weg halen als je iets hebt gezet..." << endl;
			}
				Gobord->drukaf();
			return getmeout;
			break;
		case 'U':
			if (Zet->getvolgende() != NULL) {
				if ((Zet->getvorige() == NULL) && (dontdoit == false)) {
					Gobord->doe(Zet->getinfoplace(1), Zet->getinfoplace(2), Zet->getinfochar(1));
					dontdoit = true;
				}else {
					Zet = Zet->getvolgende();
					Gobord->doe(Zet->getinfoplace(1), Zet->getinfoplace(2), Zet->getinfochar(1));
					dontdoit = false;
				}
					Gobord->drukaf();
			}else {
				cout << "Pas iets terug plaaste als je iets hebt weg gehaalt..." << endl;
			}
			return getmeout;
			break;
		case 'V':
			Zet->cleanup();
			getmeout = true;
			return getmeout;
			break;
		}
	}

void zetten::cleanup() {
	zetten* help = this;
	while (help->volgende != NULL) {
		help = help->volgende;
	}
	while (help != this) {
		zetten* helper = help;
		help = help->vorige;
		delete helper;
	}
}

zetten* zetten::getvorige() {
	return vorige;
}

zetten* zetten::getvolgende() {
	return volgende;
}

void game::menu() {
	int help;
	if (isAIAanZet == 2 || isAIAanZet == 5) {
		help = 1;
	}else {
		help = outputMenu();
	}
	char hulp;
	bool dontdoit = false;
	switch (help) {
	case 333:
		do {
			hulp = speciaalMenu();
		} while (SMuitvoeren(hulp, dontdoit) == false);
		break;
	case 1:
		Zet = make_zetten();
		adyen();
		if (showandtell == true) {
			Gobord->drukaf();
		}
		Gobord->aantalZettenPP();
		break;
	default:
		break;
	}
}

void game::makegobordpub() {
	Gobord = make_gobord();
}

void gobord::aantalZettenPP() {
	aantalzetten++;
}

void gobord::winnenit(int hulpx, int hulpy) {
	bordvakje* hulp = vindvakje(hulpx, hulpy);
	for (int x = 0; x < 4; x++) {
		int counter = 1;
		bordvakje* helper = hulp;
		while((helper->buren[x] != NULL) && (helper->buren[x]->kleur == helper->kleur)) {
			helper = helper->buren[x];
		}
		while ((helper->buren[x + 4] != NULL) && (helper->buren[x + 4]->kleur == helper->kleur)) {
			helper = helper->buren[x + 4];
			counter++;
			if (counter >= wingetal) {
				winnen = true;
				return;
			}
		}
		counter = 0;
	}
}

int gobord::getaantalZetten() {
	return aantalzetten;
}

void game::adyen() {
	if ((isAIAanZet / 3) > 0) {
		isAIAanZet -= 3;
	}
	else {
		isAIAanZet += 3;
	}

	int hulpx = Zet->getinfoplace(1);
	int hulpy = Zet->getinfoplace(2);
	char hulpkl = Zet->getinfochar(1);
	Gobord->doe(hulpx, hulpy, hulpkl);
}

void gobord::drukaf() {
	bordvakje* i = ingang; //begint bij de ingang
	if (hoogte > 10) {
		cout << "   ";
	}
	else {
		cout << "  ";
	}
	for (int a = 0; a < breedte; a++) {
		cout << a % 10 << " ";
	} //nu we de spaties gehad hebben
	cout << endl;
	for (int y = 0; y < hoogte; y++) {
		bordvakje* j = i;
		if (hoogte > 10 && y < 10) {
			cout << y << "  ";
		}
		else {
			cout << y << " ";
		} //de cijfertjes
		for (int x = 0; x < breedte; x++) {
			cout << j->kleur << " "; //de kleurtjes
			j = j->buren[2];
		}//for2
		cout << endl;
		i = i->buren[4]; //door schuiven
	}//for1
	// TODO
}//gobord::drukaf

void gobord::doe(int hulpx, int hulpy, char helpkl) {
	bordvakje* hulp = vindvakje(hulpx, hulpy);
	hulp->kleur = helpkl;
}

bordvakje* gobord::vindvakje(int hulpx, int hulpy) {
	bordvakje* hulp = ingang;
	for (int x = 0; x < hulpx; x++) {
		hulp = hulp->buren[2];
	}
	for (int y = 0; y < hulpy; y++) {
		hulp = hulp->buren[4];
	}
	return hulp;
}

gobord* game::make_gobord() {
	gobord* Gobord;
	Gobord = new gobord(breedte, hoogte, wingetal);
	return Gobord;
}


zetten* game::make_zetten() {
	zetten* zetter;
	zetter = new zetten(isAIAanZet, breedte, hoogte, Computer, een, Zet);
	Zet->fix(zetter);
	Zet = zetter;
	return Zet;
}

void game::infobericht() {
	cout << "__________________________________________________________________________________" << endl;
	cout << "|Dit is een versie van het spel Gomoku...........................................|" << endl;
	cout << "|U zult zo een aantal opties zien, speel met uw vrienden, tegen een robot of.....|" << endl;
	cout << "|Laat twee robots tegen elkaar spelen en geniet alleen van de data aan het einde.|" << endl;
	cout << "|Als u een input geeft die buiten het velt valt komt u in een speciaal menu......|" << endl;
	cout << "|Speel het spel om erachter te komen wat daar te vinden valt.....................|" << endl;
	cout << "|Veel plezier....................................................................|" << endl;
	cout << "|________________________________________________________________________________|" << endl;
}

void game::getuserinput() {
	cout << "Wat wilt U dat de hoogte van het bord is?" << endl;
	cin >> hoogte;
	cout << "Wat wilt U dat de breedte van het bord is?" << endl;
	cin >> breedte;
	cout << "Hoeveel AI's wilt u dat er spelen? A: 0/1/2" << endl;
	cin >> isAIAanZet;
	cout << "hoeveel spellen wilt U dat er gespeeld wordem?" << endl;
	cin >> hoeveel;
	cout << "Hoeveel stenen moet naast elkaar om te winnen?" << endl;
	cin >> wingetal;
}

bool game::getboolwinnen() {
	return Gobord->getboolwinnen();
}

game::~game() {

}

// gobord

gobord::gobord(int breedtepss, int hoogtepss, int wingetalpss) {
	breedte = breedtepss;
	hoogte = hoogtepss;
	wingetal = wingetalpss;
	bouwbord();
}

bool gobord::getboolwinnen() {
	return winnen;
}

void gobord::bouwbord() { //it's all coming together now
	bordvakje* boven = maakrij(); //we pakken onze rij
	ingang = boven; //we krijgen onze ingang
	bordvakje* onder; //nooit alleen lopen!
	for (int i = 1; i < hoogte; i++) { //over de lengte
		onder = maakrij(); //rij over de breete
		rits(boven, onder); //rits het aan elkaar
		boven = onder; //zoef zoef hossel de hossel het kan weer overniew
	}
}

bordvakje* gobord::maakrij() { //een pad van 1000 stappen begint met 1 rij
	bordvakje* rijingang = new bordvakje(); //of eigenlijk bij het begin
	bordvakje* temp = rijingang; //ff handje helpen alleen lopen is saai
	for (int x = 0; x < breedte; x++) { //nou heel de x afstand lopen
		temp->buren[2] = new bordvakje();
		temp->buren[2]->buren[6] = temp;
		temp = temp->buren[2];
	}
	return rijingang; //anders weet je de weg terug niet meer
}

void gobord::rits(bordvakje* boven, bordvakje* onder) {
	for (int i = 0; i < breedte; i++) { //hoe de vakjes aan elkaar worden geritst
		boven->buren[4] = onder;
		onder->buren[0] = boven;
		if (i > 0) {
			boven->buren[5] = onder->buren[6];
			onder->buren[7] = boven->buren[6];
		}
		if (i < breedte - 1) {
			boven->buren[3] = onder->buren[2];
			onder->buren[1] = boven->buren[2];
		}
		boven = boven->buren[2];
		onder = onder->buren[2];
	}
}

gobord::~gobord() {
	bordvakje* hulp = ingang; //zie helper
	bordvakje* helper = hulp; //je komt nergens zonder hulp
	vakjesterror(6, hulp, helper); //terristische aanval op de vakjes
	while (hulp->buren[0] != NULL) { //tot je je neus stoot
		hulp = hulp->buren[0]; //schuiven
		if (hulp->buren[6] == NULL) { //ik heb je neus
			vakjesterror(2, hulp, helper); //vakjes worden geterroriseerd
		}
		else { //massa moord
			vakjesterror(6, hulp, helper);
		}
	}
}

void gobord::vakjesterror(int x, bordvakje*& hulp, bordvakje*& helper) {
	while (hulp->buren[x] != NULL) { //tot je je neus stoot
		helper = hulp; //schuiven
		hulp = hulp->buren[x]; //schuiven
		delete helper; //OOF RIP vakje
	}
}

void zetten::fix(zetten* hulp) {
	if (this != NULL) {
		this->volgende = hulp;
	}
}

char zetten::getinfochar(int hulp) {
	switch (hulp) {
	case 1:
		return kleur;
		break;
	}
}

bool gobord::gelijkspelcondities() {
	if (aantalzetten >= hoogte * breedte) {
		winnen = true;
		return true;
	}
	return false;
}

int zetten::getinfoplace(int help) {
	switch (help) {
	case 1:
		return xc;
	case 2:
		return yc;
	}
}

zetten::zetten(int isAIAanZet, int breedte, int hoogte, AI* Computerpss, speler* eenpss, zetten*& Zetpss) {
	Computer = Computerpss;
	een = eenpss;
	vorige = Zetpss;

	int x = 0;
	int y = 0;

	if ((isAIAanZet / 3) > 0) { //3 = zwart
		kleur = 'Z';
		isAIAanZet -= 3;
	}
	else {
		kleur = 'W';
	}
	bool dubbel = false;
	do {
		switch (isAIAanZet) {
		case 0:
			een->doe(x, y);
			break;
		case 1:
			if (kleur == 'Z') {
				Computer->denken(x, y, breedte, hoogte);
			}
			else {
				een->doe(x, y);
			}
			break;
		case 2:
			Computer->denken(x, y, breedte, hoogte);
			break;
		}
		dubbel = check(x, y);
	} while ((x > breedte) || (y > hoogte) || (dubbel == true));
	xc = x;
	yc = y;
	Computer->denkeniteration(xc, yc, kleur);

}

void AI::denkeniteration(int hulpx, int hulpy, char hulpkl) {
	denkbord->doe(hulpx, hulpy, hulpkl);
	denkenhulp += denkbord->gowinnit(hulpx, hulpy);
}


bool zetten::check(int x, int y) {
	zetten* helper = this;
	while (helper->vorige != NULL) {
		helper = helper->vorige;
		if ((helper->xc == x) && (helper->yc == y)) {
			return true;
		}
	}
	return false;
}


void AI::denkbordsetup(int breedte, int hoogte, int wingetalpss) {
	denkbord = makedenkbord(breedte, hoogte, wingetalpss);
}

gobord* AI::makedenkbord(int breedte, int hoogte, int wingetalpss) {
	gobord* denkbordh;
	denkbordh = new gobord(breedte, hoogte, wingetalpss);
	return denkbordh;
}

zetten::~zetten() {
	if (massdestruct == true) {
		zetten* help = this;
		Computer->clean();
		if (help->vorige != NULL) {
			help->massdestruct = true;
			delete help->vorige;
		}
	}
}

void AI::clean() {
	if (this->denkbord != NULL) {
		delete denkbord;
		denkbord = NULL;
	}
	denkenhulp = 0;
}


void zetten::setmassdestruct(bool yesorno){
	if (yesorno == true) {
		massdestruct = true;
	}
}



//bordvakje

bordvakje::bordvakje() { //constructor
	for (int i = 0; i < 8; i++) //gelijk beginnen met NULL
		buren[i] = NULL;
	kleur = 'x'; //Kleur ook ff reseten
}

bordvakje::~bordvakje() {

}

//speler

void speler::doe(int& x, int& y) {
	std::cout << "Geef nu uw x coordinaat op" << endl;
	cin >> x;
	std::cout << "Geef nu uw y coordinaat op" << endl;
	cin >> y;
}

//AI

void AI::doe(int& x, int& y, int breedte, int hoogte) {
	x = rand() % breedte;
	y = rand() % hoogte;
}

void AI::denken(int& hulpx, int& hulpy, int breedte, int hoogte) {

	//denkt nog maar 1 kant op 
	
	if (denkenhulp > 0) {
		denkenhulp += denkbord->zoekO(hulpx, hulpy);
	}
	else {
		doe(hulpx, hulpy, breedte, hoogte);
	}
}

int gobord::zoekO(int&x, int&y) {
	bordvakje* helper = ingang;
	bordvakje* hulper = ingang;
	int hulpy = 0;
	int hulpx = 0;
	bool stop = false;
	while (hulper->buren[4] != NULL) {
		while (helper->buren[2] != NULL) {
			if (helper->kleur == 'O') {
				x = hulpx;
				y = hulpy;
				helper->kleur = 'x';
				return -1;
			}
			hulpx++;
			helper = helper->buren[2];
		}
		hulpy++;
		hulpx = 0;
		hulper = hulper->buren[4];
		helper = hulper;

	}
	return -1;
}

void gobord::plaatsdeOOHs(bordvakje* hulp, bordvakje* helper, bordvakje* waar[8], bool winnend[8]) {
	for (int x = 0; x < 8; x++) {
		winnend[x] = false;
		helper = hulp;
		bool OOH = false; //is de OOH geplaast?
		while ((helper->buren[x] != NULL) && (OOH == false)) {
			if (helper->buren[x]->kleur == hulp->kleur) {
				helper = helper->buren[x];
			}
			else if (helper->buren[x]->kleur == 'x') {
				helper->buren[x]->kleur = 'O';
				helper = helper->buren[x];
				waar[x] = helper;
				OOH = true;
			}
			else if ((helper->buren[x]->kleur != hulp->kleur) && (helper->buren[x]->kleur != 'x')) {
				waar[x] = NULL;
				OOH = true;
			}
		}
	}
}

void gobord::loopop(bordvakje* hulp, bordvakje* helper, bool winnend[8], int x, int& count, bool& OOH) {
	while ((helper->buren[x] != NULL) && (count > 0)) {
		if (helper->buren[x]->kleur == hulp->kleur) {
			helper = helper->buren[x];
			count++;
		}
		else if ((helper->buren[x]->kleur == 'O') && OOH == false) {
			helper = helper->buren[x];
			count++;
			OOH = true;
		}
		else {
			count = 0;
		}
		if (count >= wingetal) {
			winnend[x] = true;
		}
	}
}

void gobord::loopterug(bordvakje* hulp, bordvakje* helper, bool winnend[8], int x, int& count, bool& OOH) {
	while ((OOH == true) && (helper->buren[x + 4] != NULL)) {
		if (helper->kleur == 'O') {
			OOH = false;
			helper = helper->buren[x + 4];
			count = 1;
		}
		else {
			helper = helper->buren[x + 4];
		}
	}
}

void gobord::loopaf(bordvakje* hulp, bordvakje* helper, bool winnend[8], int x, int& count, bool& OOH) {
	while ((helper->buren[x + 4] != NULL) && (count > -1)) {
		if (helper->buren[x + 4]->kleur == 'O') {
			helper = helper->buren[x + 4];
			count++;
		}
		else if (helper->buren[x + 4]->kleur == hulp->kleur) {
			helper = helper->buren[x + 4];
			count++;
		}
		else {
			count = -1;
		}
		if (count >= wingetal) {
			winnend[x + 4] = true;
		}
	}
}

void gobord::zoekdewinnendeOOHs(bordvakje* hulp, bordvakje* helper, bool winnend[8]) {
	for (int x = 0; x < 4; x++) {
		bool OOH = false; //is de OOH geplaast?
		int count = 1;
		helper = hulp;
		loopop(hulp, helper, winnend, x, count, OOH);
		loopterug(hulp, helper, winnend, x, count, OOH);
		loopaf(hulp, helper, winnend, x, count, OOH);		
	}
}

int gobord::hoeveelOOHs(bordvakje* waar[8], bool winnend[8]) {
	int hoeveel = 0;
	for (int x = 0; x < 8; x++) {
		if ((winnend[x] == false) && (waar[x] != NULL)) {
			waar[x]->kleur = 'x';
		}
		else if (winnend[x] == true) {
			hoeveel++;
		}
	}
	return hoeveel;
}

int gobord::gowinnit(int hulpx, int hulpy) {
	bordvakje* hulp = vindvakje(hulpx, hulpy);
	bordvakje* helper = hulp;
	bordvakje* waar[8] = { };
	bool	   winnend[8] = {};

	plaatsdeOOHs(hulp, helper, waar, winnend);
	
	zoekdewinnendeOOHs(hulp, helper, winnend);

	int hoeveel = hoeveelOOHs(waar, winnend);
	return hoeveel;
}

void game::denkbordsetup() {
	Computer->denkbordsetup(breedte, hoogte, wingetal);
}