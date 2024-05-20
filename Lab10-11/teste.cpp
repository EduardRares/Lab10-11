#include "teste.h"
#include <vector>
#include <fstream>
#include <assert.h>
#include <sstream>

void Test::test_all()
{
	test_add();
	test_delete();
	test_update();
	test_search();
	test_filter_destination();
	test_filter_price();
	test_sort_name();
	test_sort_destination();
	test_sort_type(); 
	test_exceptions();
	test_afisare();
	test_add_cart();
	test_clear_cart();
	test_export();
	test_save();
	test_undo();
	srv.~Service();
}
void Test::test_add()
{
	srv.add_offer_serv("Promo", "Egipt", "mare", 2000);
	vector <Offer> lista = srv.get_offers_serv();
	assert(lista.size() == 1);
	srv.add_offer_serv("Promo", "Spania", "mare", 1500);
	srv.add_offer_serv("Promo", "Italia", "mare", 1500);
	srv.add_offer_serv("Promo", "Grecia", "mare", 1000);
	lista = srv.get_offers_serv();
	assert(lista.size() == 4);
	
}

void Test::test_delete()
{
	vector <Offer> lista = srv.get_offers_serv();
	assert(lista.size() == 4);
	srv.delete_offer_serv("Promo", "Egipt");
	lista = srv.get_offers_serv();
	assert(lista.size() == 3);
}

void Test::test_update()
{
	 srv.update_offer_serv("Promo", "Italia", 2000);
	 vector <Offer> lista = srv.get_offers_serv();
	 assert(lista[1].getPrice() == 2000);
}

void Test::test_search()
{
	vector <Offer> lista = srv.get_offers_serv();
	assert(lista.size() == 3);
	srv.search_offer_serv("Promo", "Italia");
	lista = srv.get_offers_serv();
	assert(lista[1].getPrice() == 2000);
}

void Test::test_filter_destination()
{
	vector <Offer> lista = srv.filter_destination_serv("Italia");
	assert(lista.size() == 1);
}

void Test::test_filter_price()
{
	vector <Offer> lista = srv.filter_price_serv(1500);
	assert(lista.size() == 2);
}

void Test::test_sort_name()
{
	srv.add_offer_serv("ACUM", "Turcia", "mare", 1250);
	vector <Offer> lista = srv.sort_name_serv();
	assert(lista[0].getName() == "ACUM");
}

void Test::test_sort_destination()
{
	vector <Offer> lista = srv.sort_destination_serv();
	assert(lista[0].getDestination() == "Grecia");
}

void Test::test_sort_type() 
{
	srv.add_offer_serv("ACUM", "Austria", "Cultural", 2500);
	vector <Offer> lista = srv.sort_type_price_serv();
	assert(lista[0].getDestination() == "Austria");
	assert(lista[1].getDestination() == "Grecia");
}

void Test::test_exceptions()
{
	ofstream g("test.txt");
	try {
		srv.add_offer_serv("1", "2", "3", -2000);
	}
	catch (const OfferException& ex)
	{
		g << ex << "\n";
		assert(true);
	}
	try {
		srv.delete_offer_serv("Promo", "Belgia");
	}
	catch (const string& ex)
	{
		assert(ex == "Nu exista oferta!");
	}
	try {
		srv.update_offer_serv("Promo", "Macedonia", -2000);
	}
	catch (const string& ex)
	{
		assert(ex == "Nu exista oferta!");
	}
	try {
		srv.search_offer_serv("Promo", "Macedonia");
	}
	catch (const string& ex)
	{
		assert(ex == "Nu exista oferta!");
	}
	try {
		srv.add_offer_serv("Promo", "Spania", "mare", 1500);
	}
	catch (const string& ex)
	{
		assert(ex == "Exista deja aceasta oferta!");
	}
	try {
		vector <Offer> cart;
		srv.add_cart_serv(100);}
	catch (const string& ex) {
		assert(ex == "Numar invalid!");
	}
}
void Test::test_afisare() {
	ofstream g("test.txt");
	vector <Offer> lista = srv.get_offers_serv();
	for (const auto& o : lista) {
		g << o.getName() << " " << o.getDestination() << " " << o.getType() << " " << o.getPrice() << endl;
	}
}

void Test::test_add_cart() {
	vector <Offer> cart;
	srv.add_cart_serv(1);
	srv.add_cart_serv(3);
	cart = srv.get_cart_serv();
	assert(cart.size() == 2);
	srv.add_cart_serv(2);
	cart = srv.get_cart_serv();
	assert(cart.size() == 3);

}

void Test::test_clear_cart() {
	vector <Offer> cart = srv.get_cart_serv();
	assert(cart.size() == 3);
	srv.cart_clear_serv();
	cart = srv.get_cart_serv();
	assert(cart.size() == 0);
}

void Test::test_export() {
	vector <Offer> cart, v1;
	srv.add_cart_serv(1);
	srv.add_cart_serv(3);
	srv.exportare_serv("test_export");
	ifstream f("test_export");
	string line, name, destination, type;
	int price;
	while (getline(f, line))
	{
		stringstream ss;
		ss << line;
		ss >> name >> destination >> type >> price;
		Offer m(name, destination, type, price);
		v1.push_back(m);
		name = name;
	}
	assert(v1.size() == 2);
}

void Test::test_save()
{
	vector <Offer> lista = srv.get_offers_serv(), v1;
	srv.save_to_file_serv("test_save");
	ifstream f("test_save.txt");
	string line, name, destination, type;
	int price;
	while (getline(f, line))
	{
		stringstream ss;
		ss << line;
		ss >> name >> destination >> type >> price;
		Offer m(name, destination, type, price);
		v1.push_back(m);	}
	assert(v1.size() == 5);
}

void Test::test_undo()
{
	srv.add_offer_serv("ACUM", "Egipt", "mare", 1250);
	vector <Offer> lista = srv.get_offers_serv();
	assert(lista.size() == 6);
	srv.update_offer_serv("ACUM", "Egipt", 2000);
	srv.delete_offer_serv("ACUM", "Egipt");
	srv.undo_serv();
	srv.undo_serv();
	srv.undo_serv();
	lista = srv.get_offers_serv();
	assert(lista.size() == 5);
}


