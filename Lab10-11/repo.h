#ifndef REPO_H
#define REPO_H

#include "domain.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>	

using namespace std;

class Repo {
public:
	virtual ~Repo() {};
	virtual void add_offer_repo(const Offer& offer) = 0;
	virtual Offer delete_offer_repo(const string& name, const string& destination) = 0;
	virtual Offer update_offer_repo(const string& name, const string& destination, const int& price) = 0;
	virtual Offer search_offer_repo(const string& name, const string& destination) = 0;
	virtual vector<Offer> get_all() const = 0;
	virtual void duplicate(const string& name, const string& destination, const string& type) = 0;
};

class RepoMemo : public Repo {
public:
	//constructor
	RepoMemo() = default;
	//copy-constructor
	RepoMemo(const RepoMemo& repo) = delete;
	//destructor
	~RepoMemo() override = default;
	//metoda adauga o oferta in repo
	void add_offer_repo(const Offer& offer) override;
	//metoda sterge o oferta in repo si returneaza oferta stearsa
	Offer delete_offer_repo(const string& name, const string& destination) override;
	//metoda modifica pretul unei oferte
	Offer update_offer_repo(const string& name, const string& destination, const int& price) override;
	//metoda cauta o oferta dupa nume si destinatie in repo si returneaza oferta
	Offer search_offer_repo(const string& name, const string& destination) override;
	//metoda returneaza lista cu toate ofertele
	vector<Offer> get_all() const override { return lista; }
	//metoda verifica daca exista deja o oferta cu aceclasi nume si destinatie
	void duplicate(const string& name, const string& destination, const string& type);
protected:
	vector<Offer> lista;
};

class RepoMap :public Repo {
public:
	RepoMap() = default;
	RepoMap(const RepoMap& repo) = delete;
	~RepoMap() = default;
	void add_offer_repo(const Offer& offer) override;
	Offer delete_offer_repo(const string& name, const string& destination) override;
	Offer update_offer_repo(const string& name, const string& destination, const int& price) override;
	Offer search_offer_repo(const string& name, const string& destination) override;
	vector<Offer> get_all() const override;
	void duplicate(const string& name, const string& destination, const string& type);
protected:
		map<pair<string, string>, Offer> map;
};

class RepoFile :public RepoMemo {
public:
	//constructor
	RepoFile(string filename) : filename{ filename } { load_from_file(); }
	//copy-constructor
	RepoFile(const RepoFile& repo) = delete;
	//destructor
	~RepoFile() override = default;
	void add_offer_repo(const Offer& offer) override {
		RepoMemo::add_offer_repo(offer);
		save_to_file();
	};
	Offer delete_offer_repo(const string& name, const string& destination) override {
		Offer m = RepoMemo::delete_offer_repo(name, destination);
		save_to_file();
		return m;
	};
	Offer update_offer_repo(const string& name, const string& destination, const int& price) override {
		Offer m = RepoMemo::update_offer_repo(name, destination, price);
		save_to_file();
		return m;
	};
	Offer search_offer_repo(const string& name, const string& destination) override {
		return RepoMemo::search_offer_repo(name, destination);
	};
	vector<Offer> get_all() const override {
		return RepoMemo::get_all();
	};
	void duplicate(const string& name, const string& destination, const string& type) {
		RepoMemo::duplicate(name, destination, type);
	};
private:
	string filename;
	void load_from_file();
	void save_to_file();

};

#endif // !REPO_H
