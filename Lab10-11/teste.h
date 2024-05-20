#pragma once
#ifndef TESTE_H
#define TESTE_H
#include "service.h"
#include "repo.h"
#include <iostream>

using namespace std;

class Test {
public:
	Test(Service& srv) :srv{ srv } {};
	Test(const Test& t) = delete;
	~Test() = default;
	void test_all();

private:
	void test_add();
	void test_delete();
	void test_update();
	void test_search();
	void test_filter_destination();
	void test_filter_price();
	void test_sort_name();
	void test_sort_destination();
	void test_sort_type();
	void test_exceptions();
	void test_afisare();
	void test_add_cart();
	void test_clear_cart();
	void test_export();
	void test_save();
	void test_undo();
	Service& srv;

};

#endif // !TESTE_H
