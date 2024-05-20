#include "service.h"
#include <algorithm>

using namespace std;

Service::~Service() { 
	while (true) {
		try {
			undo_serv();
		}
		catch (exception)
		{
			break;}
	}
}

void Service::add_offer_serv(const string& name, const string& destination, const string& type, const int& price) {
	Validator::validate(name, destination, type, price);
	repo->duplicate(name, destination, type);
	Offer o{ name, destination, type, price };
	repo->add_offer_repo(o);
	UndoVector.push_back(new UndoAdd(repo, o));
}
void Service::delete_offer_serv(const string& name, const string& destination) {
	Offer o = repo->delete_offer_repo(name, destination);
	UndoVector.push_back(new UndoDelete(repo, o));
}

void Service::update_offer_serv(const string& name, const string& destination, const int& price)
{
	if(price <= 0)
		throw string("Pretul nu poate fi un numar negativ sau 0!");
	Offer o = repo->update_offer_repo(name, destination, price);
	UndoVector.push_back(new UndoModify(repo, o));
}

vector<Offer> Service::filter_destination_serv(const string& destination)
{
	vector <Offer> all = repo->get_all();
	vector <Offer> aux(all.size());
	vector <Offer>::iterator filtered = copy_if(all.begin(), all.end(), aux.begin(), [destination](const Offer& a) {return a.getDestination() == destination; });
	aux.resize(distance(aux.begin(), filtered));
	return aux;
}

vector<Offer> Service::filter_price_serv(const int& price)
{
	vector <Offer> all = repo->get_all();
	vector <Offer> aux(all.size());
	vector <Offer>::iterator filtered = copy_if(all.begin(), all.end(), aux.begin(), [price](const Offer& a) {return a.getPrice() <= price; });
	aux.resize(distance(aux.begin(), filtered));
	return aux;
}

Offer Service::search_offer_serv(const string& name, const string& destination)
{
	return repo->search_offer_repo(name, destination);
}

vector<Offer> Service::sort_name_serv()
{
	vector <Offer> all = repo->get_all();
	sort(all.begin(), all.end(), [](const Offer& a, const Offer& b) {return a.getName() < b.getName(); });
	return all;
}

vector<Offer> Service::sort_destination_serv()
{
	vector <Offer> all = repo->get_all();
	sort(all.begin(), all.end(), [](const Offer& a, const Offer& b) {return a.getDestination() < b.getDestination(); });
	return all;
}

vector<Offer> Service::sort_type_price_serv()
{
	vector <Offer> all = repo->get_all();
	sort(all.begin(), all.end(), [](const Offer& a, const Offer& b) {return a.getType() < b.getType() || a.getType() == b.getType() && a.getPrice() < b.getPrice(); });
	return all;
}

void Service::save_to_file_serv(string filename)
{
	vector <Offer> all = repo->get_all();
	ofstream f(filename);
	for (const auto& o : all)
	{
		f << o.getName() << " " << o.getDestination() << " " << o.getType() << " " << o.getPrice() << "\n";
	}

}

void Service::undo_serv()
{
	if (UndoVector.empty()) {
		throw string("Trebuie sa faci o operatie inainte sa faci undo!");
	}
	UndoAction* act = UndoVector.back();
	act->doUndo();
	UndoVector.pop_back();
	delete act;
}


void Service::add_cart_serv(int x)
{
	vector <Offer> oferte = repo->get_all();
	if (x - 1 >= 0 && x - 1 < oferte.size())
	{
		cart.push_back(oferte[x - 1]);
		return;
	}
	throw string("Numar invalid!");}

void Service::cart_clear_serv()
{
	cart.clear();
}

void Service::exportare_serv(string filename)
{
	filename += ".csv";
	ofstream g(filename);
	for (const auto& o : cart)
	{
		g << o.getName() << "," << o.getDestination() << "," << o.getType() << "," << o.getPrice() << "\n";
	}
	g.close();
}

map<pair<string, string>, int> Service::raport_serv()
{
	map<pair<string, string>, int> raport;
	vector<Offer> all = repo->get_all();
	for (const auto& o : all)
	{
		raport[make_pair(o.getName(), o.getDestination())]++;
	}
	return raport;
}
