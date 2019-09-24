/* Daniele Pellegrini 285240
 * pasw00401.cpp, ref: https://en.wikipedia.org/wiki/Chess
 */
#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <vector>
using namespace std;

// Costruttore per i diversi tipi di pedine
typedef enum {pawn,rook,bishop,knight,queen,king,noPiece} Pezzo;

// Costruttore per i colori delle pedine
typedef enum {white,black,noColor} Colore;

// Informazioni della Cella
struct Cella {
	Pezzo pezzo;
	Colore colore;
};

//Scacchiera di gioco come matrice 8x8
typedef Cella Scacchiera[8][8];

// Coordinate Scacchistiche
struct Ccoord {
	char col;	// 'a' .. 'h'	da sinistra
	int riga;	//  1 .. 8 		dal "basso"
};

// Coordinate Matrice
struct Mcoord {
	int riga;	// 0 .. 7		dall'alto
	int col;	// 0 .. 7 	da sinistra
};

// Inserisce celle vuote in tutta la scacchiera
void vuotaScacchiera(Scacchiera s);

// Inserisce i vari pezzi nella scacchiera
void inserisciPezzi(Scacchiera s);

// Visualizza la scacchiera (formato di visualizzazione e a scelta)
void visualizzaScacchiera(Scacchiera s);

// Converte in formato Cella un pezzo p rappresentato come char
Cella convertiInCella(char p);

// Converte in char un pezzo p rappresentato in formato Cella
char convertiInChar(Cella p);

//Converte in stringa un pezzo p rappresentato in formato Cella
string convertiInString(Cella p);

//Converte in colore un pezzo p rappresentato in formato Cella
string convertiInColor(Cella p);

// Converte coordinate matrice in coordinate scacchistiche
Ccoord converti(Mcoord);

// Converte coordinate scacchistiche in coordinate matrice
Mcoord converti(Ccoord);

// Verifica la correttezza delle coordinate scacchistiche
bool corretto(Ccoord);

// Verifica la correttezza delle coordinate nella matrice
bool corretto(Mcoord);

// Visualizza Mosse su File
void mosse(Scacchiera s);

int main() {
	Scacchiera s;
	vuotaScacchiera(s);
	inserisciPezzi(s);
	visualizzaScacchiera(s);
	mosse (s);
	return 0;
}

// Inserisce celle vuote in tutta la scacchiera
void vuotaScacchiera(Scacchiera s){
	Cella vuota;
	vuota.pezzo = noPiece;
	vuota.colore = noColor;
	for(int r=0; r<8; r++)
		for(int c=0; c<8; c++)
			s[r][c] = vuota;
}

// Inserisce i vari pezzi nella scacchiera
void inserisciPezzi(Scacchiera s){
	// Pedone 	p
	// Torre	r
	// Cavallo	n
	// Alfiere	b
	// Regina	q
	// Re		k
	// per i pezzi neri stessi caratteri ma maiuscoli
	string sitIniziale;
  ifstream Chess;
  Chess.open("scacchiera.txt"); //Apro il file scacchiera.txt
	string line[8] = {"a", "b", "c", "d", "e", "f", "g", "h"}; //Definisco un array di stringhe
  if (Chess.fail()) { //Controllo l'apertura del File
    cout << "Errore file " << endl;
  }
	for (int i=0; i<=7; i++){   //Con un ciclo aggiungo tutte le celle
	  getline (Chess, line[i]); //della scacchiera del file
		sitIniziale += line[i];   //in un'unica stringa
	}
	// recupero dei caratteri dalla stringa
	int r,q,l;
	l = sitIniziale.size();
	for(int i=0;i<l;i++) {	// per ogni carattere della stringa
		r = i / 8;
		q = i % 8;
		// inserimento pezzi corrispondenti in scacchiera
		s[r][q] = convertiInCella(sitIniziale[i]);
	}
}

// Visualizza la scacchiera (formato di visualizzazione a scelta)
void visualizzaScacchiera(Scacchiera s){
	cout << "Scacchiera di Gioco: \n" << endl;
	for(int r=0;r<8;r++) {
		cout << "-----------------" << endl; //Separatore di righe
		for(int q=0;q<8;q++)
			cout << "|" << convertiInChar(s[r][q]);
		cout << "|" << endl;
	}
	cout << "-----------------\n" << endl; //Separatore di righe
}

// Converte in formato Cella un pezzo p rappresentato come char
Cella convertiInCella(char p){
	Cella pc;
	pc.pezzo = noPiece; pc.colore = noColor;	// default vuoto
	if (p>='a' && p<='z') pc.colore = white;	// bianco
	if (p>='A' && p<='Z') pc.colore = black;	// nero
	p = tolower(p);
	switch (p) {
		case 'p':
			pc.pezzo = pawn; 	break;
		case 'r':
			pc.pezzo = rook; 	break;
		case 'b':
			pc.pezzo = bishop; 	break;
		case 'n':
			pc.pezzo = knight; 	break;
		case 'q':
			pc.pezzo = queen; 	break;
		case 'k':
			pc.pezzo = king; 	break;
	}
	return pc;
}


// Converte in char un pezzo p rappresentato in formato Cella
char convertiInChar(Cella p){
	string pChar = "prbnqk PRBNQK ";	// caratteri dei pezzi
	int pCharPos = p.pezzo;
	if (p.colore == black) pCharPos+=7;	// pezzi neri
	return pChar[pCharPos];
}


//Converte in stringa un pezzo p rappresentato in formato Cella
string convertiInString(Cella p){
	if (p.pezzo == 0)
		return "pawn";
	if (p.pezzo == 1)
		return "rook";
	if (p.pezzo == 2)
		return "bishop";
	if (p.pezzo == 3)
		return "knight";
	if (p.pezzo == 4)
		return "queen";
	if (p.pezzo == 5)
		return "king";
	if (p.pezzo == noPiece)
		return " ";
}

//Converte in colore un pezzo p rappresentato in formato Cella
string convertiInColor(Cella p){
	if (p.colore == 0)
		return "white";
	if (p.colore == 1)
		return "black";
	if (p.colore == 2)
		return "";

}
// Converte coordinate matrice in coordinate scacchistiche
Ccoord converti(Mcoord m){
	Ccoord c;
	c.col = 'a'+ (m.col);
	c.riga = 8 - (m.riga);
	return c;
}


// Converte coordinate scacchistiche in coordinate matrice
Mcoord converti(Ccoord c){
	Mcoord m;
	m.col = (c.col) - 'a';
	m.riga = 8 - (c.riga);
	return m;
}


// Verifica la correttezza delle coordinate scacchistiche
bool corretto(Ccoord c) {
	if (c.col<'a' || c.col>'h') return false;
	if (c.riga<1 || c.riga>8)	return false;
	return true;
}


// Verifica la correttezza delle coordinate nella matrice
bool corretto(Mcoord m){
	if (m.riga<0 || m.riga>7) return false;
	if (m.col <0 || m.col >7) return false;
	return true;
}

//
void mosse(Scacchiera s) {
	fstream f1;
	bool move; //Definisco una variabile booleana per il controllo del movimento,
	char p;    //che sarà falsa (default) ad ogni 'giro' del ciclo, e diventerà vera se
	Mcoord m;  //la pedina considerata potrà compiere almeno una mossa
	Ccoord c;
	//Creo il file mosse.txt
	f1.open("mosse.txt", ios::out);
	f1 << "Daniele Pellegrini 285240" << endl; //Intestazione
	/* f1 << "Pedine Bianche: " << endl; */
	for(int x=7;x>=0;x--) {    //Visualizzo	le mosse di ognuno dei pezzi bianchi
		for(int y=0;y<=7;y++){  //nell’ordine in cui si trovano i pezzi dalla casella a1, a2, … a8 fino alla casella h8
			int dx, dy; //Incremento dei movimenti sui due assi
			move = false;
			m.riga = x; m.col = y; //Coordinate matriciali del pezzo
			c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
			p = convertiInChar(s[x][y]); //Converto il pezzo in carattere

			if (p != ' ' && islower(p)) //Controllo che sia presente una pedina e che sia Bianca
			{
				f1 << convertiInString(s[x][y]) << " - " << convertiInColor(s[x][y]) << " - "<< c.col << c.riga << endl;
				if (p == 'b') //Se la Pedina considerata è un Alfiere Bianco
		    {
		      for (int i=0; i<4; i++) //Eseguo un Ciclo per ciascuna delle 4 direzioni oblique
		      {
						switch (i) {
							case 0: dx =  1; dy =  1; break;
							case 1: dx = -1; dy =  1; break;
							case 2: dx =  1; dy = -1; break;
							case 3: dx = -1; dy = -1; break;
						}
		        while ((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && convertiInChar(s[x+dx][y+dy]) == ' ') //Controllo del Movimento
		        {
							m.riga = x+dx; m.col = y+dy; //Coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
			        f1 << c.col << c.riga << endl; //Scrivo le coordinate scacchistiche
							move = true;
							switch (i) {
								case 0: dx++; dy++; break;
								case 1: dx--; dy++; break;
								case 2: dx++; dy--; break;
								case 3: dx--; dy--; break;
							}
		        }
		        if (((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && isupper(convertiInChar(s[x+dx][y+dy])))) //Controllo che 'mangi'
						{                                                                                                  // una pedina di diverso colore
							m.riga = x+dx; m.col = y+dy; //Nuove coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
		          f1 << convertiInString(s[x+dx][y+dy]) << "*" << c.col << c.riga << endl; //Scrivo le nuove coordinate scacchistiche
							move = true;
						}
		      }
					if (move == false)
						f1 << "no move" << endl;
		    }
				if (p == 'n') //Se la Pedina considerata è un Cavallo Bianco
				{
					for (int i=0; i<8; i++) //Eseguo un Ciclo per ciascuna delle 8 mosse (a L)
		      {
						switch (i) {
							case 0: dx =  2; dy =  1; break;
							case 1: dx =  2; dy = -1; break;
							case 2: dx = -2; dy =  1; break;
							case 3: dx = -2; dy = -1; break;
							case 4: dx =  1; dy =  2; break;
							case 5: dx =  1; dy = -2; break;
							case 6: dx = -1; dy =  2; break;
							case 7: dx = -1; dy = -2; break;
						}
		        if ((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && convertiInChar(s[x+dx][y+dy]) == ' ') //Controllo del Movimento
		        {
							m.riga = x+dx; m.col = y+dy; //Coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
			        f1 << c.col << c.riga << endl; //Scrivo le coordinate scacchistiche del pezzo
							move = true;
		        }
		        if (((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && isupper(convertiInChar(s[x+dx][y+dy])))) //Controllo che 'mangi'
						{                                                                                                  // una pedina di diverso colore
							m.riga = x+dx; m.col = y+dy; //Nuove coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
		          f1 << convertiInString(s[x+dx][y+dy]) << "*" << c.col << c.riga << endl; //Scrivo le nuove coordinate scacchistiche
							move = true;
						}
		      }
					if (move == false)
						f1 << "no move" << endl;
				}
				if (p == 'q') //Se la Pedina considerata è la Regina Bianca
		    {
		      for (int i=0; i<8; i++) //Eseguo un Ciclo per ciascuna delle 8 direzioni (4 oblique + 2 verticali + 2 orizzontali)
		      {
						switch (i) {
							case 0: dx =  1; dy =  1; break;
							case 1: dx = -1; dy =  1; break;
							case 2: dx =  1; dy = -1; break;
							case 3: dx = -1; dy = -1; break;
							case 4: dx =  1; dy =  0; break;
							case 5: dx = -1; dy =  0; break;
							case 6: dx =  0; dy =  1; break;
							case 7: dx =  0; dy = -1; break;
						}
		        while ((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && convertiInChar(s[x+dx][y+dy]) == ' ') //Controllo del Movimento
		        {
							m.riga = x+dx; m.col = y+dy; //Coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate dell Matrice in coordinate scacchistche
			        f1 << c.col << c.riga << endl; //Scrivo le coordinate scacchistihe
							move = true;
							switch (i) {
								case 0: dx++; dy++; break;
								case 1: dx--; dy++; break;
								case 2: dx++; dy--; break;
								case 3: dx--; dy--; break;
								case 4: dx++;			  break;
								case 5: dx--;       break;
								case 6:       dy++; break;
								case 7:       dy--; break;
							}
		        }
		        if (((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && isupper(convertiInChar(s[x+dx][y+dy])))) //Controllo che 'mangi'
						{                                                                                                  // una pedina di diverso colore
							m.riga = x+dx; m.col = y+dy; //Nuove coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
		          f1 << convertiInString(s[x+dx][y+dy]) << "*" << c.col << c.riga << endl; //Scrivo le nuove coordinate scacchistiche
							move = true;
						}
		      }
					if (move == false)
						f1 << "no move" << endl;
		    }
				if (p == 'k') //Se la Pedina considerata è il Re Bianco
		    {
		      for (int i=0; i<8; i++) //Eseguo un Ciclo per ciascuna delle 8 direzioni (4 oblique + 2 verticali + 2 orizzontali)
		      {
						switch (i) {
							case 0: dx =  1; dy =  1; break;
							case 1: dx = -1; dy =  1; break;
							case 2: dx =  1; dy = -1; break;
							case 3: dx = -1; dy = -1; break;
							case 4: dx =  1; dy =  0; break;
							case 5: dx = -1; dy =  0; break;
							case 6: dx =  0; dy =  1; break;
							case 7: dx =  0; dy = -1; break;
						}
		        if ((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && convertiInChar(s[x+dx][y+dy]) == ' ') //Controllo del Movimento
		        {
							m.riga = x+dx; m.col = y+dy; //Coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della matrice in coordinate scacchistiche
			        f1 << c.col << c.riga << endl; //Scrivo le coordinate scacchistiche
							move = true;
		        }
		        if (((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && isupper(convertiInChar(s[x+dx][y+dy])))) //Controllo che 'mangi'
						{                                                                                                  // una pedina di diverso colore
							m.riga = x+dx; m.col = y+dy; //Nuove coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
		          f1 << convertiInString(s[x+dx][y+dy]) << "*" << c.col << c.riga << endl; //Scrivo le nuove coordinate scacchistiche
							move = true;
						}
		      }
					if (move == false)
						f1 << "no move" << endl;
		    }
				if (p == 'r') //Se la Pedina considerata è una Torre Bianca
		    {
		      for (int i=0; i<4; i++) //Eseguo un Ciclo per ciascuna delle 4 direzioni (2 verticali + 2 orizzontali)
		      {
						switch (i) {
							case 0: dx =  1; dy =  0; break;
							case 1: dx = -1; dy =  0; break;
							case 2: dx =  0; dy =  1; break;
							case 3: dx =  0; dy = -1; break;
						}
		        while ((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && convertiInChar(s[x+dx][y+dy]) == ' ') //Controllo del Movimento
		        {
							m.riga = x+dx; m.col = y+dy; //Coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate matriciali in coordinate scacchistiche
			        f1 << c.col << c.riga << endl; //Scrivo le coordinate scacchistiche
							move = true;
							switch (i) {
								case 0: dx++;			  break;
								case 1: dx--;       break;
								case 2:       dy++; break;
								case 3:       dy--; break;
							}
		        }
		        if (((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && isupper(convertiInChar(s[x+dx][y+dy])))) //Controllo che 'mangi'
						{                                                                                                  // una pedina di diverso colore
							m.riga = x+dx; m.col = y+dy; //Nuove coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
		          f1 << convertiInString(s[x+dx][y+dy]) << "*" << c.col << c.riga << endl; //Scrivo le nuove coordinate scacchistiche del pezzo
							move = true;
						}
		      }
					if (move == false)
						f1 << "no move" << endl;
		    }
				if (p == 'p') //Se la Pedina considerata è un Pedone Bianco
		    {
					dx = -1; dy = 0; //Il Pedone si muove sempre dritto
		      if ((x+dx) >= 0 && (x+dx) <= 7 && convertiInChar(s[x+dx][y]) == ' ') //Controllo del Movimento
		      {
						m.riga = x+dx; m.col = y+dy; //Coordinate matriciali del pezzo
					  c = converti(m); //converto le coordinate matrciaili in coordinate scacchistiche
			      f1 << c.col << c.riga << endl; //Scrivo le coordinate scacchistiche
						move = true;
					}
					for (int i = 0; i<2; i++ )
					{
						switch (i) //Il pedone può 'mangiare' una pedina che si trova
						{          //davanti a lui, in diagonale
							case 0: dx =  -1; dy =  1; break;
							case 1: dx =  -1; dy = -1; break;
						}
			      if ((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && isupper(convertiInChar(s[x+dx][y+dy]))) //Controllo che 'mangi'
						{                                                                                                // una pedina di diverso colore
							m.riga = x+dx; m.col = y+dy; //Nuove coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
			      	f1 << convertiInString(s[x+dx][y+dy]) << "*" << c.col << c.riga << endl; //Scrivo le nuove coordinate scacchistiche
							move = true;
						}
					}
					if (move == false)
						f1 << "no move" << endl;
		    }
			}
		}
	}
	/*/ f1 << "---------------------" << endl; //Separatore
	f1 << "Pedine Nere: " << endl; //Inizio Analisi Pedine Nere */
	for(int x=0;x<=7;x++) {     //Visualizza	le mosse di ognuno dei pezzi neri
		for(int y=7;y>=0;y--) {   //nell’ordine in cui si trovano i pezzi dalla casella h8, h7, … h1 fino alla casella a1
			move = false;
			int dx, dy; //Incremento dei movimenti sui due assi
			m.riga = x;	m.col = y; //Coordinate matriciali del pezzo
			c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
			p = convertiInChar(s[x][y]); //Converto il pezzo in carattere

			if (p != ' ' && isupper(p))
			{
				f1 << convertiInString(s[x][y]) << " - " << convertiInColor(s[x][y]) << " - "<< c.col << c.riga << endl;
				if (p == 'B') //Se la Pedina considerata è un Alfiere Nero
		    {
		      for (int i=0; i<4; i++) //Eseguo un Ciclo per ciascuna delle 4 direzioni oblique
		      {
						switch (i) {
							case 0: dx =  1; dy =  1; break;
							case 1: dx = -1; dy =  1; break;
							case 2: dx =  1; dy = -1; break;
							case 3: dx = -1; dy = -1; break;
						}
		        while ((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && convertiInChar(s[x+dx][y+dy]) == ' ') //Controllo del Movimento
		        {
							m.riga = x+dx; m.col = y+dy; //Coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
			        f1 << c.col << c.riga << endl; //Scrivo le coordinate scacchistiche
							move = true;
							switch (i) {
								case 0: dx++; dy++; break;
								case 1: dx--; dy++; break;
								case 2: dx++; dy--; break;
								case 3: dx--; dy--; break;
							}
		        }
		        if (((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && islower(convertiInChar(s[x+dx][y+dy])))) //Controllo che 'mangi'
						{                                                                                                 // una pedina di diverso colore
							m.riga = x+dx; m.col = y+dy; //Nuove coordinate matriciali
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
		          f1 << convertiInString(s[x+dx][y+dy]) << "*" << c.col << c.riga << endl; //Scrivo le nuove coordinate scacchistiche
							move = true;
						}
		      }
					if (move == false)
						f1 << "no move" << endl;
		    }
				if (p == 'N') //Se la Pedina considerata è un Cavallo Nero
				{
					for (int i=0; i<8; i++) //Eseguo un Ciclo per ciascuna delle 8 mosse (a L)
		      {
						switch (i) {
							case 0: dx =  2; dy =  1; break;
							case 1: dx =  2; dy = -1; break;
							case 2: dx = -2; dy =  1; break;
							case 3: dx = -2; dy = -1; break;
							case 4: dx =  1; dy =  2; break;
							case 5: dx =  1; dy = -2; break;
							case 6: dx = -1; dy =  2; break;
							case 7: dx = -1; dy = -2; break;
						}
		        if ((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && convertiInChar(s[x+dx][y+dy]) == ' ') //Controllo del Movimento
		        {
							m.riga = x+dx; m.col = y+dy; //Coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
			        f1 << c.col << c.riga << endl; //Scrivo le coordinate scacchistiche
							move = true;
		        }
		        if (((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && islower(convertiInChar(s[x+dx][y+dy])))) //Controllo che 'mangi'
						{                                                                                                 // una pedina di diverso colore
							m.riga = x+dx; m.col = y+dy; //Nuove coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
		          f1 << convertiInString(s[x+dx][y+dy]) << "*" << c.col << c.riga << endl; //Scrivo le nuove coordinate scacchistiche
							move = true;
						}
		      }
					if (move == false)
						f1 << "no move" << endl;
				}
				if (p == 'Q') //Se la Pedina considerata è la Regina Nera
		    {
		      for (int i=0; i<8; i++) //Eseguo un Ciclo per ciascuna delle 8 direzioni (4 oblique + 2 verticali + 2 orizzontali)
		      {
						switch (i) {
							case 0: dx =  1; dy =  1; break;
							case 1: dx = -1; dy =  1; break;
							case 2: dx =  1; dy = -1; break;
							case 3: dx = -1; dy = -1; break;
							case 4: dx =  1; dy =  0; break;
							case 5: dx = -1; dy =  0; break;
							case 6: dx =  0; dy =  1; break;
							case 7: dx =  0; dy = -1; break;
						}
		        while ((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && convertiInChar(s[x+dx][y+dy]) == ' ') //Controllo del Movimento
		        {
							m.riga = x+dx; m.col = y+dy; //Coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matriche in coordinate scacchistiche
			        f1 << c.col << c.riga << endl; //Scrivo le coordinate scacchistiche
							move = true;
							switch (i) {
								case 0: dx++; dy++; break;
								case 1: dx--; dy++; break;
								case 2: dx++; dy--; break;
								case 3: dx--; dy--; break;
								case 4: dx++;			  break;
								case 5: dx--;       break;
								case 6:       dy++; break;
								case 7:       dy--; break;
							}
		        }
		        if (((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && islower(convertiInChar(s[x+dx][y+dy])))) //Controllo che 'mangi'
						{                                                                                                 // una pedina di diverso colore
							m.riga = x+dx; m.col = y+dy; //Nuove coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
		          f1 << convertiInString(s[x+dx][y+dy]) << "*" << c.col << c.riga << endl; //Scrivo le nuove coordinate scacchistiche
							move = true;
						}
		      }
					if (move == false)
						f1 << "no move" << endl;
		    }
				if (p == 'K') //Se la Pedina considerata è il Re Nero
		    {
		      for (int i=0; i<8; i++) //Eseguo un Ciclo per ciascuna delle 8 direzioni (4 oblique + 2 verticali + 2 orizzontali)
		      {
						switch (i) {
							case 0: dx =  1; dy =  1; break;
							case 1: dx = -1; dy =  1; break;
							case 2: dx =  1; dy = -1; break;
							case 3: dx = -1; dy = -1; break;
							case 4: dx =  1; dy =  0; break;
							case 5: dx = -1; dy =  0; break;
							case 6: dx =  0; dy =  1; break;
							case 7: dx =  0; dy = -1; break;
						}
		        if ((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && convertiInChar(s[x+dx][y+dy]) == ' ') //Controllo del Movimento
		        {
							m.riga = x+dx; m.col = y+dy; //Nuove coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
			        f1 << c.col << c.riga << endl; //Scrivo le nuove coordinate scacchistiche
							move = true;
		        }
		        if (((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && islower(convertiInChar(s[x+dx][y+dy])))) //Controllo che 'mangi'
						{                                                                                                 // una pedina di diverso colore
							m.riga = x+dx; m.col = y+dy; //Nuove coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
		          f1 << convertiInString(s[x+dx][y+dy]) << "*" << c.col << c.riga << endl; //Scrivo le nuove coordinate scacchistiche
							move = true;
						}
		      }
					if (move == false)
						f1 << "no move" << endl;
		    }
				if (p == 'R') //Se la Pedina considerata è una Torre Nera
		    {
		      for (int i=0; i<4; i++) //Eseguo un Ciclo per ciascuna delle 4 direzioni (2 verticali + 2 orizzontali)
		      {
						switch (i) {
							case 0: dx =  1; dy =  0; break;
							case 1: dx = -1; dy =  0; break;
							case 2: dx =  0; dy =  1; break;
							case 3: dx =  0; dy = -1; break;
						}
		        while ((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && convertiInChar(s[x+dx][y+dy]) == ' ') //Controllo del Movimento
		        {
							m.riga = x+dx; m.col = y+dy; //Coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
			        f1 << c.col << c.riga << endl; //Scrivo le coordinate scacchistiche
							move = true;
							switch (i) {
								case 0: dx++;			  break;
								case 1: dx--;       break;
								case 2:       dy++; break;
								case 3:       dy--; break;
							}
		        }
		        if (((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && islower(convertiInChar(s[x+dx][y+dy])))) //Controllo che 'mangi'
						{                                                                                                 // una pedina di diverso colore
							m.riga = x+dx; m.col = y+dy; //Nuove coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
		          f1 << convertiInString(s[x+dx][y+dy]) << "*" << c.col << c.riga << endl; //Scrivo le nuove coordinate scacchistiche
							move = true;
						}
		      }
					if (move == false)
						f1 << "no move" << endl;
		    }
				if (p == 'P') //Se la Pedina considerata è un Pedone Nero
		    {
					dx =  1; dy = 0; //Il pedone si muove sempre dritto
		      if ((x+dx) >= 0 && (x+dx) <= 7 && convertiInChar(s[x+dx][y]) == ' ') //Controllo del Movimento
		      {
						m.riga = x+dx; m.col = y+dy; //Nuove coordinate matriciali del pezzo
					  c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
			      f1 << c.col << c.riga << endl; //Scrivo le nuove coordinate scacchistiche
						move = true;
					}
					for (int i = 0; i<2; i++ )
					{
						switch (i) //Il pedone può decidere di mangiare una pedina
						{          //che si trova davanti a lui, in diagonale
							case 0: dx =   1; dy =  1; break;
							case 1: dx =   1; dy = -1; break;
						}
			      if ((x+dx) >= 0 && (x+dx) <= 7 && (y+dy) >= 0 && (y+dy) <= 7 && islower(convertiInChar(s[x+dx][y+dy]))) //Controllo che 'mangi'
						{                                                                                                // una pedina di diverso colore
							m.riga = x+dx; m.col = y+dy; //Nuove coordinate matriciali del pezzo
							c = converti(m); //Converto le coordinate della Matrice in coordinate scacchistiche
			      	f1 << convertiInString(s[x+dx][y+dy]) << "*" << c.col << c.riga << endl; //Scrivo le nuove coordinate scacchistiche
							move = true;
						}
					}
					if (move == false)
						f1 << "no move" << endl;
		    }
		  }
		}
	}
	f1.close();
}
