#include "UI.h"
#include <iostream>

using namespace std;

void Console::show_ui() {
	bool ok = true;
	while (ok) {
		cout << "1. Adaugare oferta noua." << endl;
		cout << "2. Stergere oferta." << endl;
		cout << "3. Modificare oferta." << endl;
		cout << "4. Afisare oferte." << endl;
		cout << "5. Cautare oferte." << endl;
		cout << "6. Filtrare oferte dupa destinatie." << endl;
		cout << "7. Filtrare oferte dupa pret." << endl;
		cout << "8. Sortare oferte dupa denumire." << endl;
		cout << "9. Sortare oferte dupa destinatie." << endl;
		cout << "10. Sortare oferte dupa pret." << endl;
		cout << "11. Adaugare oferta in gos." << endl;
		cout << "12. Goleste toate ofertele din cos." << endl;
		cout << "13. Genereaza oferte cos." << endl;
		cout << "14. Export cos." << endl;
		cout << "15. Salvare in fisier oferte" << endl;
		cout << "16. Undo" << endl;
		cout << "0. Exit." << endl;
		cout << "Enter your option: ";
		int option;
		cin >> option;
		cin.ignore();
		switch (option) {
		case 1:
			add_offer();
			break;
		case 2:
			delete_offer();
			break;
		case 3:
			update_offer();
			break;
		case 4:
			show_offers();
			break;
		case 5:
			search_offer();
			break;
		case 6:
			filter_destination();
			break;
		case 8:
			sort_name();
			break;
		case 7:
			filter_price();
			break;
		case 9:
			sort_destination();
			break;
		case 10:
			sort_type_price();
			break;
		case 11:
			add_cart();
			break;
		case 12:
			cart_clear();
			break;
		case 13:
			break;
		case 14:
			exportare();
			break;
		case 15:
			save();
			break;
		case 16:
			undo();
			break; 
		case 0:
			ok = false;
			break;
		default:
			cout << "Comanda introdusa nu este corecta!\n";
			break;
		}
	}
}

void Console::add_offer()
{
	string name, destination, type;
	int price;
	cout << "Introduceti numele: ";
	getline(cin, name);
	cout << "Introduceti destinatia: ";
	getline(cin, destination);
	cout << "Introduceti tipul: ";
	getline(cin, type);
	cout << "Introduceti pretul: ";
	cin >> price;
	cin.ignore();
	try {
		srv.add_offer_serv(name, destination, type, price);
	}
	catch (OfferException& msg) {
		cout << msg << "\n";
	}
	catch (string& msg) {
		cout << msg << "\n";
	}
}

void Console::delete_offer()
{
	string name, destination;
	cout << "Introduceti numele: ";
	getline(cin, name);
	cout << "Introduceti destinatia: ";
	getline(cin, destination);
	try {
		srv.delete_offer_serv(name, destination);
	}
	catch (string& msg) {
		cout << msg << "\n";
	}
}

void Console::update_offer()
{
	string name, destination;
	cout << "Introduceti numele: ";
	getline(cin, name);
	cout << "Introduceti destinatia: ";
	getline(cin, destination);
	int price;
	cout << "Introduceti pretul nou: ";
	cin >> price;
	cin.ignore();
	try {
		srv.update_offer_serv(name, destination, price);
	}
	catch (string& msg) {
		cout << msg << "\n";
	}
}

void Console::search_offer()
{
	string name, destination;
	cout << "Introduceti numele: ";
	getline(cin, name);
	cout << "Introduceti destinatia: ";
	getline(cin, destination);
	try {
		Offer o = srv.search_offer_serv(name, destination);
		cout << o.getName() << " " << o.getDestination() << " " << o.getType() << " " << o.getPrice() << endl;

	}
	catch (string& msg) {
		cout << msg << "\n";
	}
}

void Console::show_offers()
{
	vector<Offer> offers = srv.get_offers_serv();
	int i = 1;
	for (const auto& o : offers) {							   
		cout << i << ". " << o.getName() << " " << o.getDestination() << " " << o.getType() << " " << o.getPrice() << endl;
	   i++;
	}
	cout << "\n\n";
}

void Console::filter_destination()
{
	string destination;
	cout << "Introduceti destinatia: ";
	getline(cin, destination);
	vector <Offer> lista = srv.filter_destination_serv(destination);
	for (const auto& o : lista) {
		cout << o.getName() << " " << o.getDestination() << " " << o.getType() << " " << o.getPrice() << endl;
	}
	if(lista.size() == 0)
		cout << "Nu exista oferte pentru aceasta destinatie!\n";
}

void Console::filter_price()
{
	int price;
	cout << "Introduceti pretul maxim: ";
	cin >> price;
	vector <Offer> lista = srv.filter_price_serv(price);
	for (const auto& o : lista) {
		cout << o.getName() << " " << o.getDestination() << " " << o.getType() << " " << o.getPrice() << endl;
	}
	if (lista.size() == 0)
		cout << "Nu exista oferte pentru acest pret!\n";
}

void Console::sort_name()
{
	vector <Offer> lista = srv.sort_name_serv();
	for (const auto& o : lista) {
		cout << o.getName() << " " << o.getDestination() << " " << o.getType() << " " << o.getPrice() << endl;
	}
}

void Console::sort_destination()
{
	vector <Offer> lista = srv.sort_destination_serv();
	for (const auto& o : lista) {
		cout << o.getName() << " " << o.getDestination() << " " << o.getType() << " " << o.getPrice() << endl;
	}
}

void Console::sort_type_price()
{
	vector <Offer> lista = srv.sort_type_price_serv();
	for (const auto& o : lista) {
		cout << o.getName() << " " << o.getDestination() << " " << o.getType() << " " << o.getPrice() << endl;
	}
}

void Console::add_cart()
{
	show_offers();
	cout << "Introduceti numarul ofertei: ";
	int x;
	cin >> x;
	try {
		srv.add_cart_serv(x);
		cout << "Oferta a fost adaugata in cos!\n";
	}
	catch (string& msg) {
		cout << msg << "\n";
	}
}

void Console::cart_clear()
{
	srv.cart_clear_serv();
	cout << "Cosul a fost golit!\n";
}

void Console::exportare()
{
	string filename;
	cout << "Introduceti numele fisierului cu extensia dorita: ";
	getline(cin, filename);
	srv.exportare_serv(filename);
	cout << "Cosul a fost exportat!\n";
}

void Console::save()
{
	string filename;
	cout << "Introduceti numele fisierului cu extensia dorita: ";
	getline(cin, filename);
	srv.save_to_file_serv(filename);
	cout << "Ofertele au fost salvate!\n";
}

void Console::undo()
{
	srv.undo_serv();
}
