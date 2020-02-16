#pragma once
#pragma once
#pragma once
//classes

class bordvakje {
public:
	char kleur;//de kleur geeft ... 7 0 1 ... de oplichende steen 
	bordvakje* buren[8];  //layout: 6   2
	bordvakje(); // constructor     5 4 3
	~bordvakje();
private:

};

class speler {
public:
	void doe(int&, int&);
private:

};

class JSON {
public:
	JSON* volgende = NULL;
	JSON* vorige = NULL;

	JSON(JSON*, int);
	void walktoturn(int);
	void getinfo(int& beurt, int& hoeveelkeergewonnen);

private:
	int hoeveelkeergewonnen = 0;
	int beurt = 0;
};

class stats {
public:
	int beurten_verstreken = 0;
	bool this_gelijkspel = false;
	void stash_winnings();
	void printlist();
private:
	JSON* ingang = NULL;
	int gelijkspellen = 0;

	void place_win_in_JSON();
};

class gobord {
public:
	gobord(int, int, int);
	~gobord();

	void drukaf();
	void doe(int hulpx, int hulpy, char kleur);
	void aantalZettenPP();
	bool gelijkspelcondities();
	void winnenit(int x, int y);
	int zoekO(int& x, int& y);
	int getaantalZetten();
	int  gowinnit(int x, int y);
	bool getboolwinnen();
private:
	bordvakje* ingang;
	bool winnen = false;
	int breedte = 0;
	int hoogte = 0;
	int wingetal = 0;
	int aantalzetten = 0;

	void bouwbord();
	void vakjesterror(int x, bordvakje*& hulp, bordvakje*& helper);
	void plaatsdeOOHs(bordvakje*, bordvakje*, bordvakje* waar[8], bool winnend[8]);
	void zoekdewinnendeOOHs(bordvakje* hulp, bordvakje* helper, bool winnend[8]);
	void loopop(bordvakje* hulp, bordvakje* helper, bool winnend[8], int x, int& count, bool& OOH);
	void loopterug(bordvakje* hulp, bordvakje* helper, bool winnend[8], int x, int& count, bool& OOH);
	void loopaf(bordvakje* hulp, bordvakje* helper, bool winnend[8], int x, int& count, bool& OOH);
	int hoeveelOOHs(bordvakje* waar[8], bool winnend[8]);
	void rits(bordvakje*, bordvakje*);

	bordvakje* maakrij();
	bordvakje* vindvakje(int x, int y);
};

class AI {
public:

	void denkbordsetup(int, int, int);
	void denkeniteration(int hulpx, int hulpy, char hulpkl);
	void denken(int&, int&, int, int);
	void clean();

private:
	gobord* denkbord = NULL;
	gobord* makedenkbord(int, int, int);
	int denkenhulp = 0;
	int wingetal = 0;
	void doe(int&, int&, int breedte, int hoogte);

};

class zetten {
public:
	//menu's
	zetten(int, int breedte, int hoogte, AI*, speler*, zetten*&);
	~zetten();

	int getinfoplace(int);
	char getinfochar(int);
	void fix(zetten* hulp);
	void cleanup();
	void setmassdestruct(bool);

	zetten* getvorige();
	zetten* getvolgende();
private:
	speler* een = NULL;
	AI* Computer= NULL;
	zetten* vorige = NULL;
	zetten* volgende = NULL;

	char kleur;
	int xc;
	int yc;

	bool massdestruct = false;

	bool check(int x, int y);
};

class game {
public:
	game();
	~game();

	bool getboolwinnen();
	int gethoeveel();
	void menu();
	void endgame();
	void makegobordpub();
	void denkbordsetup();
	void Thanos();
	void printlist();

private:
	gobord* Gobord = NULL;
	zetten* Zet = NULL;
	AI* Computer = NULL;
	speler* een = NULL;
	stats Statestieken;

	bool showandtell = true;

	int breedte = 0;
	int hoogte = 0;
	int wingetal;
	int hoeveel;
	int isAIAanZet = 0; //0 = 0 AI, 1 is 1 AI, 2 is 2 AI + 3 is splr 2 is aan zet

	void infobericht();
	void getuserinput();
	void adyen();
	void wincondities();
	bool SMuitvoeren(char hulp, bool&);

	int outputMenu();

	char speciaalMenu();

	gobord* make_gobord();
	zetten* make_zetten();
};