#include "domain.h"
#include <iostream>

ostream& operator<<(ostream& out, const OfferException& ex) {
	for (const auto& message : ex.message) {
		out << message << "\n";
	}
	return out;
}

Offer::Offer(const string& name, const string& destination, const string& type, const int& price) {
	this->name = name;
	this->destination = destination;
	this->type = type;
	this->price = price;
}
bool letters(const string& s) {
	for (auto& letter : s) {
		if (('a' <= letter && letter <= 'z') || ('A' <= letter && letter <= 'z')) {
			return true;
		}
	}
	return false;
}
void Validator::validate(const string& name, const string& destination, const string& type, const int& price) {
	vector<string> message;
	if (!letters(name)) {
		message.push_back("Numele trebuie sa contina minim o litera!");
	}
	if (!letters(destination)) {
		message.push_back("Destinatia trebuie sa contina minim o litera!");
	}
	if (!letters(type)) {
		message.push_back("Tipul trebuie sa contina minim o literar!");
	}
	if (price <= 0) {
		message.push_back("Pretul nu poate fi un numar negativ sau 0!");
	}
	if (!message.empty()) {
		throw OfferException(message);
	}
}

void Offer::setPrice(const int& newPrice)
{
	this->price = newPrice;
}

//
//Offer::Offer(const Offer& ot) {
//	this->name = ot.name;
//	this->destination = ot.destination;
//	this->type = ot.type;
//	this->price = ot.price;
//	cout << "COPIE!\n";
//}