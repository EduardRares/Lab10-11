#ifndef DOMAIN_H
#define DOMAIN_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;
class Offer {
public:
	//constructor
	Offer() = default;
	//copy-constructor
	Offer(const Offer& ot) = default;
	//constructor
	Offer(const string& name, const string& destination, const string& type, const int& price);
	// Offer(const Offer& offer) = default;

	//getters
	string getName() const { return name; }
	string getDestination() const { return destination; }
	string getType() const { return type; }
	int getPrice() const { return price; }
	
	//setters
	void setPrice(const int& price);



private:
	string name, destination, type;
	int price = {};
};
class Validator {
public:
	//constructor
	static void validate(const string& name, const string& destination, const string& type, const int& price);
};
//functia merifica ca s sa contina minim o litera
bool letters(const string& s);

class OfferException {
private:
	vector <string> message;
public:
	//constructor
	explicit OfferException(vector <string> message) : message{ message } {}
	//metoda operator "<<" pentru afisare
	friend ostream& operator<<(ostream& out, const OfferException& ex);
};

ostream& operator<<(ostream& out, const OfferException& ex);
#endif