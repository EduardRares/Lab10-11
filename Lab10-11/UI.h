#ifndef UI_H
#define UI_H
#include "Service.h"

class Console
{
public:
	Console(Service& srv) :srv{ srv } {};
	Console(const Console& ui) = delete;
	~Console() = default;
	void show_ui();

private:
	void add_offer();
	void delete_offer();
	void update_offer();
	void show_offers();
	void search_offer();
	void filter_destination();
	void filter_price();
	void sort_name();
	void sort_destination();
	void sort_type_price();
	void add_cart();
	void cart_clear();
	void exportare();
	void save();
	void undo();
	Service& srv;
};
#endif // !UI_H
