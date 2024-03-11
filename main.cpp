#include <string>
#include <iostream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <bitset>
#include <sstream>
#include <fstream>

using namespace std;

// Lire la longeur du fichier, est utilis� pour naviguer dans le fichier. 
long longueurFichier(const string& nom_fichier)
{
	// On ouvre le fichier en mode binaire et en mode input
	std::ifstream fichier(nom_fichier, std::ios::binary | std::ios::in);
	long taille; // La variable qui contiendra la taille du fichier

	if (fichier) // Si l'ouverture a r�ussi
	{
		// On se place � la fin du fichier
		fichier.seekg(0, std::ios::end);
		// On r�cup�re la position actuelle, qui correspond � la taille du fichier
		taille = (long)fichier.tellg();
		// On ferme le fichier
		fichier.close();
	}
	else // Si l'ouverture a �chou�
	{
		cout << "Erreur : impossible d'ouvrir le fichier." << std::endl;
		taille = -1; // On renvoie une valeur n�gative pour indiquer l'erreur
	}
	return taille; 
}

// Lire 30 caractere ce trouvent dans un fichier sous forme binaire.
void lire30caractereFichier(const string& nom_fichier, int position,long longeurFichier, string& resultat)
{
	// Ouvrir le fichier binaire en mode lecture
	ifstream fichier(nom_fichier, ios::binary);
	int nbcaractere{ 30 };
		
	// Si la fin du fichier -30 alors la longeur seras le restant de la longeur avant la fin. 
	if (position > longeurFichier - 30)
	{
		nbcaractere = longeurFichier-position;
	}
	// V�rifier si le fichier est ouvert
	if (fichier.is_open())
	{		
		// Se d�placer � la position indiqu�e
		fichier.seekg(position);

		// Cr�er un tableau de 30 caract�res
		char buffer[30];

		// Lire 30 caract�res � partir du fichier
		fichier.read(buffer, nbcaractere);

		// Convertir le tableau en cha�ne de caract�res
		resultat = std::string(buffer, nbcaractere);

		fichier.close();		
	}
	else
	{
		// Afficher un message d'erreur
		std::cerr << "Impossible d'ouvrir le fichier " << nom_fichier << std::endl;
	}
}

// �crire 30 caractere dans un fichier, prend en paramettre la position et la longeur du fichier.
int ecrire30caractereFichier(const std::string& nom_fichier, int position,long longeurFichier, const std::string& resultat)
{
	// On ouvre le fichier en mode binaire et en mode append
	ofstream fichier(nom_fichier, std::ios::binary | std::ios::app);
	if (fichier) 
	{
		// On se positionne � l'endroit voulu dans le fichier
		fichier.seekp(position);

		// On v�rifie que la cha�ne � �crire ne d�passe pas 30 caract�res
		if (resultat.size() <= 30)
		{
			// On �crit les donn�es binaires dans le fichier
			fichier.write(resultat.c_str(), resultat.size());
			// On ferme le fichier
			fichier.close();
		}
		else // Si la cha�ne est trop longue
		{
				cout << "Erreur : la cha�ne � �crire d�passe 30 caract�res." << std::endl;
		}
	}
	else 
	{
		cout << "Erreur : impossible d'ouvrir le fichier." << std::endl;
	}

	return 0;
}

// Si la longeur de la string est sup�rieur � 20 alors return false sinon true.
bool verifierLongeurString(string inputString)
{	
	int longueur = int(inputString.length());

	if (inputString.length() > 20)
	{
		cout << "Erreur: Vous avez depasse la longeur maximum pour votre chaine de caractere, 20 caractere maximum." << endl;
		return false;
	}
	else if(inputString.length() < 5) 
	{
		cout << "Erreur: Vous devez entrer une chaine de caractere superieur a 5.";
		return false;
	}
	else
	{
		return true;
	}

	return true; 
}

// Si le caractere ne se trouve pas dans la table ansi alors return false sinon true. 
bool verifierAnsiString(string inputString)
{
	int i{0};
	while (inputString.length()>i)
	{
		if ((int)inputString[i] < 32 || (int)inputString[i] > 126)
		{
			cout << "Erreur: Vous devez entrer une valeur valid dans la table ansi. ";
			return false;
		}
		i++;
	}
	return true; 
}

// Utiliser les fonction verifierLongeur et verifierAnsi pour verifier la string.
bool verifierString(string inputString)
{
	if (verifierLongeurString(inputString) && verifierAnsiString(inputString))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

string inputUtilisateur(string message)
{
	string password{ "" };
	cout << message;

	while (true)
	{
		cin >> setw(50) >> password;
		if (verifierString(password))
		{
			return password;
		}
	}
}

int affichageMenu()
{
	cout << "Bienvenue dans le programme d encodage et de decodage de fichiers." << endl;
	cout << "Ce programme vous permet d encoder ou de decoder un fichier a l aide d un password." << endl;
	cout << "Veuillez suivre les instructions a l ecran." << endl << endl;
	cout << "1. Encoder votre fichier" << endl;
	cout << "2. Decoder votre fichier" << endl; 
	cout << "3. Quitter" << endl << endl;
	cout << "Entrez votre choix: ";

	return 0;
}

// Verifier si c'est un nombre compris entre 1 et 5 en demandant � l'utilisateur un nombre, et si ce n'est pas une chaine de caractere.
int inputVerifierNumber(int entree)
{
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Erreur : Vous devez entrer un chiffre." << endl;
		return false;
	}
	else if (entree < 1 || entree > 3)
	{
		cout << "Erreur : Vous devez entrer un chiffre entre 1 et 3." << endl;
		return false;
	}
	return true;
}

int inputNombreEntre1Et3()
{
	int nombre;
	while (true)
	{
		cin >> setw(5) >> nombre;
		if (inputVerifierNumber(nombre))
		{
			return nombre;
		}
	}
	return 0;
}

// Fonction qui convertit un caract�re en binaire hexad�cimal
string charToHex(char c) 
{
	std::stringstream ss;
	ss << std::hex << std::bitset<8>(c).to_ulong();
	return ss.str();
}

// Fonction qui convertit une cha�ne de caract�res en binaire hexad�cimal
string stringToHex(string const& str) {
	std::string hex = "";
	for (char const& c : str) {
		hex += charToHex(c);
	}
	return hex;
}

// Inversion d'une chaine de caract�re binaire en utilisant une port xor sois 1 si a et b = 0 ou 0 si un des deux a =1 ou b =1;
void invertHex(string& hex) {
	string invert = "";
	for (char const& c : hex) {
		// Convertir le caract�re hexad�cimal en entier
		long long n = stoi(string(1, c), nullptr, 16);
		// Appliquer le XOR avec 15 (0xf) pour inverser les bits
		n = n ^ 15;
		// Convertir l'entier invers� en caract�re hexad�cimal
		char c = "0123456789abcdef"[n];
		// Ajouter le caract�re � la cha�ne invers�e
		invert += c;
	}
	hex= invert;
}

// Permet d'inverser une chaine de caract�re avec la porte not
void inverseNot(string& chaine, string hashage ) {
	// Parcourir chaque caract�re de la cha�ne
	for (int i = 0; i < chaine.length(); i++)
	{
		// Appliquer l'op�rateur NOT sur le caract�re
		if ((int)hashage[i] % 2 == 0)
		{
			chaine[i] = ~chaine[i];
		}
	}
}

// Additionner les valeur de la cl�e dans la string 
void addClee(string& chaine, string hashage)
{
	string result{ "" };
	for (int i = 0; i < chaine.length(); i++)
	{
		result += (int)chaine[i] + (int)hashage[i];
	}
	chaine = result;
}

// Supprimer les valeur de la cl�e dans la string
void subClee(string& chaine, string hashage)
{
	string result{ "" };
	for (int i = 0; i < chaine.length(); i++)
	{
		result += (int)chaine[i] - (int)hashage[i];
	}
	chaine = result;
}
// Permet de prendre le premier le dernier caractere de la chaine pour le mettre en avant pour inverser le sens de la string
void d�calageHex(string& hex)
{
	string invert = "";
	for (long long i = hex.length() - 1; i >= 0; i--)
	{
		invert += hex[i];
	}
	hex = invert;
}

void hashModulo(string& hex)
{
	const int MODULO{ 256 };
	
	string result{""};

	for (char carac : hex)
	{
		result += to_string((int)carac % MODULO);
	}
	hex = result;
}

void hashMultiplicative(string& hex)
{
	int multiplicative{ 1 };

	string result{ "" };

	for (char carac : hex)
	{
		result += to_string((int)carac * multiplicative);
		multiplicative++;
	}

	hex = result;
}

// M�langer les donn�es d'une string
void melangeurDonnerHash(string& hex)
{
	string result{ "" };
	string str1{ "" };
	string str2{ "" };
	int i{ 0 };
	for (int i{ 0 }; i < hex.length(); i += 2)
	{
		str1 += hex[i];
	}
	for (int i{ 1 }; i < hex.length(); i += 2)
	{
		str2 += hex[i];
	}
	hex = str1+str2;
}

// Fonction qui reconstitue la cha�ne originale � partir de la cha�ne m�lang�e
void demelangeurDonnerHex(string& hash)
{
	string result{ "" };
	string str1{ "" };
	string str2{ "" };
	long long i{ 0 };
	long long n = hash.length();

	// S�parer la cha�ne en deux parties �gales
	for (i = 0; i < n / 2; i++)
	{
		str1 += hash[i];
	}
	for (i = n / 2; i < n; i++)
	{
		str2 += hash[i];
	}

	// Fusionner les deux parties en alternant les caract�res
	for (i = 0; i < n / 2; i++)
	{
		result += str1[i];
		result += str2[i];
	}

	// Changer la valeur du hash pour la nouvelle valeur
	hash= result;
}

void supressionMotierHash(string& hex)
{
	string result{ "" };
	int i{ 0 };
	for(int i{0};i<hex.length();i=i+2)
	{
		result += hex[i];
	}

	hex = result;
}

// Ajouter des donn�es pour rendres la chaine de caractere a 30.
void ajouterDonn�es(string& hex)
{
	string result{ "" };
	int i{ 0 };
	bool boucle{ true };
	long long longueurChaine{ 0 };
	while (boucle)
	{
		longueurChaine = result.length() + hex.length();
		if (longueurChaine == 30)
		{
			hex += result;
			boucle = false;
		}
		else if (hex.length() < 30)
		{
			result += hex[i];	
		}
		
		i++;
	}
}

// Utilisation du hash pour encod� le fichier, est comparable � une cl�.
string hashage(string password)
{
	int i{ 0 };
	bool boucle{ true };
	// Conversion en binaire hexad�cimal
	string passwordHex = stringToHex(password);
	while (i < 11)
	{
		boucle = true; 
		// M�langeur donn�e 
		for (int i = 0; i < 10; i++)
		{
			melangeurDonnerHash(passwordHex);
		}
		// Inversion binaire avec porte xor
		invertHex(passwordHex);
		// Inversion de la chaine de caractere
		d�calageHex(passwordHex);
		// Hash additive
		hashModulo(passwordHex);
		// multiplicative
		hashMultiplicative(passwordHex);
		// Supression 
		while (boucle)
		{
			if (passwordHex.length() >= 30)
			{
				supressionMotierHash(passwordHex);
			}
			else
			{
				boucle = false;
			}
		}
		i++;
	}
	// remplis les donn�es pour le rendre a 30
	ajouterDonn�es(passwordHex);
	// M�langeur donn�e 
	for (int i = 0; i < 10; i++)
	{
		melangeurDonnerHash(passwordHex);
	}

	// Affichage du r�sultat
	cout << "La cha�ne " << passwordHex << endl;
	return passwordHex;
}

// Le hash est utiliser pour encod�e le fichier. 
void encodage(string hashagecle, string& chaine, int& i)
{ 
	// Ajouter des couches de chiffrement, utiliser l'algorithme de hashage pour generer une clee differente 
	// pour chacune des couches.
	for (int k = 0; k < 22; k++)
	{
		// Si le nombre est paire alors tu inverse la chaine de caract�re sinon tu fait rien.
		if (i == 30)
		{
			i = 0;
		}
		else if ((int)hashagecle[i] % 2 == 0)
		{
			d�calageHex(chaine);
		}
		// Inversion avec la porte not si le nombre de la cl� est paire 
		inverseNot(chaine, hashagecle);
		addClee(chaine, hashagecle);

		// Melanger les donnees 50 fois
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < chaine.length(); j++)
			{
				// Si l'op�rateur de l'index i est paire alors tu melange les donnees. 
				if ((int)hashagecle[j] % 2 == 0)
				{
					melangeurDonnerHash(chaine);
				}
			}
			//string passwordhash = hashage(hashagecle);
			//hashagecle = passwordhash;
		}
	}
	i++;
}
// Sans la bonne cl�e le programme ne seras pas correctement d�cod�.
// Le hash est utiliser somme cl� pour le d�codage
void decodage(string hashagecle, string & chaine, int& i)
{
	// Enleve chaqu'une des couches de chiffrement
	for (int k = 0; k < 22; k++)
	{
		// Demelanger les donnees 50 fois
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < chaine.length(); j++)
			{
				// Si l'op�rateur de l'index i du hashage est paire alors tu demelange les donn�es. 
				if ((int)hashagecle[j] % 2 == 0)
				{
					demelangeurDonnerHex(chaine);
				}
			}
			//string passwordhash = hashage(hashagecle);
			//hashagecle = passwordhash;
		}

		subClee(chaine, hashagecle);

		// Inversion avec la porte not si le nombre de la cl� est paire 
		inverseNot(chaine, hashagecle);

		// Si le nombre est paire alors tu inverse la chaine de caract�re sinon tu fait rien.
		if (i == 30)
		{
			i = 0;
		}
		else if ((int)hashagecle[i] % 2 == 0)
		{
			d�calageHex(chaine);
		}
	}
	i++;	
}

void traitementFichier(int menu,string hashagecle, string fichierEntrer, string fichierSortie)
{
	long taille{ longueurFichier(fichierEntrer) };
	string result{ 0 };
	long position{ 0 };
	bool boucle{ true };
	int i{0};

	// Logique de traitement du fichier. 
	while (boucle)
	{
		lire30caractereFichier(fichierEntrer, position, taille, result);
		
		// Gestion du menu d�codage ou encodage. 
		if (menu == 1)
		{
			encodage(hashagecle, result, i);
		}
		else if (menu == 2)
		{
			decodage(hashagecle, result, i);
		}
		
		// Ecrire les caracteres encod� ou decode dans le fichier.
		ecrire30caractereFichier(fichierSortie, position,taille, result);
		cout << result << " " << position << endl;
		position += 30;

		// Si la position est plus grande que la taille alors fin de la boucle. 
		if (position > taille)
		{
			boucle = false;
		}	
	}
}

int ControleMenu(int menu, string& password,string& fichierEntrer,string&fichierSortie, bool& fin)
{
	string message{ "" };
	string message2{ "" };
	string message3{ "Entrer le fichier de sortie : "  };

	switch (menu)
	{
		case 1: message = "Nouveaux mots de passe: ";
				message2 = "Entrer le fichier que vous voulez chiffrer : ";
			break;
		case 2: message = "Entrer votre mots de passe: ";
			    message2 = "Entrer le fichier que vous voulez dechiffrer : ";
			break;
		case 3:
			fin = false;
			return 0;
	}
	
    password = inputUtilisateur(message);
	string passwordH{hashage(password)};
	password = passwordH;

    fichierEntrer = inputUtilisateur(message2);
    fichierSortie = inputUtilisateur(message3);

	return 0;
}

int main()
{
	bool fin{ true };
	while (fin)
	{	
		affichageMenu();

		int nombreMenuInput{ inputNombreEntre1Et3() };
		string password{ "" };
		string fichierEntrer{ "" };
		string fichierSortie{ "" };

		ControleMenu(nombreMenuInput, password, fichierEntrer, fichierSortie, fin);
		if (nombreMenuInput == 3)
		{
			return 0;
		}
		traitementFichier(nombreMenuInput, password, fichierEntrer, fichierSortie);		
	}	
}