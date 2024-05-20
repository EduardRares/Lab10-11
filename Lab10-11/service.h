#ifndef SERVICE_H
#define SERVICE_H
#include "domain.h"
#include "repo.h"
#include <iostream>
#include <vector>
#include "undo.h"
#include <map>

using namespace std;

class Service {
public:
	//constructor
	Service(Repo* repo) : repo{ repo } {};
	//copy-constructor
	Service(const Service& srv) = delete;
	//destructor
	~Service();
	//functia creeaza un obiect cu parametrii primiti si il transmite in repo pentru adaugare
	void add_offer_serv(const string& name, const string& destination, const string& type, const int& price);
	//functia returneaza o lista cu toate ofertele primite de la repo
	vector<Offer> get_offers_serv() const { return repo->get_all(); }
	//functia transmite datele primite de la UI spre repo pentru a fi stersa oferta
	void delete_offer_serv(const string& name, const string& destination);
	//functia modifica pretul unei oferte identificate dupa nume si destinatie
	void update_offer_serv(const string& name, const string& destination, const int& price);
	//functia cauta o oferta in repo dupa name si destination
	Offer search_offer_serv(const string& name, const string& destination);
	//functia filtreaza lista dupa destination
	vector<Offer> filter_destination_serv(const string& destination);
	//functia filtreaza lista dupa un pret maxim
	vector<Offer> filter_price_serv(const int& price);
	//functia sorteaza lista dupa nume
	vector<Offer> sort_name_serv();
	//functia sorteaza lista dupa destinatie
	vector<Offer> sort_destination_serv();
	//functia sorteaza lista dupa tip si pret
	vector<Offer> sort_type_price_serv();
	void save_to_file_serv(string filename);
	void undo_serv();
	//metoda adauga o oferta in cosul de cumparaturi
	void add_cart_serv(int x);
	//metoda goleste cosul de cumparaturi
	void cart_clear_serv();
	vector<Offer> get_cart_serv() const { return cart; }
	//functia exporteaza cosul de cumparaturi in fisierul specificat
	void exportare_serv(string filename);
	map<pair<string, string>, int> raport_serv();

private:
	Repo* repo;
	vector<UndoAction*> UndoVector;
	vector <Offer> cart;
};

#endif // !SERVICE_H
