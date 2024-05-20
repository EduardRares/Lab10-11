#include "repo.h"

void RepoMemo::add_offer_repo(const Offer& offer)
{
	this->lista.push_back(offer);
}

Offer RepoMemo::delete_offer_repo(const string& name, const string& destination)
{
	int i = 0;
	for (auto& oferta : lista)
	{
		if (name == oferta.getName() && destination == oferta.getDestination()) {
			Offer aux = oferta;
			lista.erase(lista.begin() + i);
			return aux;
		}
		i++;
	}
	throw string("Nu exista oferta!");
}

Offer RepoMemo::update_offer_repo(const string& name, const string& destination, const int& price)
{
	for (auto& oferta : lista)
		if (name == oferta.getName() && destination == oferta.getDestination()) {
			Offer o = oferta;
			oferta.setPrice(price);
			return o;
		}
	throw string("Nu exista oferta!");
}

Offer RepoMemo::search_offer_repo(const string& name, const string& destination)
{
	vector<Offer>::iterator it;
	it = find_if(lista.begin(), lista.end(), [name, destination](const Offer& o) {return o.getName() == name && o.getDestination() == destination; });
	if (it != lista.end())
		return *it;
	throw string("Nu exista oferta!");}

void RepoMemo::duplicate(const string& name, const string& destination, const string& type)
{
	for (const auto& oferta : lista)
		if (name == oferta.getName() && destination == oferta.getDestination() && type == oferta.getType()) {
			throw string("Exista deja aceasta oferta!");
		}
}

void RepoMap::add_offer_repo(const Offer& offer)
{
	this->map[make_pair(offer.getName(), offer.getDestination())] = offer;
}

Offer RepoMap::delete_offer_repo(const string& name, const string& destination)
{
	auto it = map.find(make_pair(name, destination));
	if (it == map.end())
		throw string("Nu exista oferta!");
	Offer aux = it->second;
	map.erase(it);
	return aux;
}

Offer RepoMap::update_offer_repo(const string& name, const string& destination, const int& price)
{
	auto it = map.find(make_pair(name, destination));
	if (it == map.end())
		throw string("Nu exista oferta!");
	Offer o = it->second;
	o.setPrice(price);
	map.erase(it);
	map.insert(make_pair(make_pair(name, destination), o));
	return o;
}

Offer RepoMap::search_offer_repo(const string& name, const string& destination)
{
	auto it = map.find(make_pair(name, destination));
	if (it == map.end())
		throw string("Nu exista oferta!");
	return it->second;
}

vector<Offer> RepoMap::get_all() const
{
	vector<Offer> all;
	for (const auto& o : map)
		all.push_back(o.second);
	return all;
}

void RepoMap::duplicate(const string& name, const string& destination, const string& type)
{
	auto it = map.find(make_pair(name, destination));
	if (it != map.end())
		throw string("Exista deja aceasta oferta!");
}

void RepoFile::load_from_file() {
	ifstream f(filename);
	string str;
	string line, name, destination, type;
	int price;
	while (getline(f, line))
	{
		stringstream ss;
		ss << line;
		ss >> name >> destination >> type >> price;
		Offer m(name, destination, type, price);
		RepoMemo::add_offer_repo(m);
	}
	f.close();
}

void RepoFile::save_to_file() {
	ofstream g(filename);
	for (auto& it : RepoMemo::get_all()) {
		g << it.getName() << " " << it.getDestination() << " " << it.getType() << " " << it.getPrice() << "\n";
	}
	g.close();
}
