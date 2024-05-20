#include "UserUI.h"


UserUI::UserUI(QWidget *parent) : QMainWindow(parent)
{
   Repo* repo = new RepoFile("date.txt");
   srv = new Service{repo};
   initGUI();
   reloadList(srv->get_offers_serv());
   connectSignals();
}

void UserUI::initGUI()
{
	//lst_offers = new QListWidget{};
	tab_offers = new QTableWidget{};
	lst_cart = new QListWidget{};
	btn_add = new QPushButton{ "Add" };
	btn_dlt = new QPushButton{ "Delete" };
	btn_upd = new QPushButton{ "Update" };
	btn_sort_name = new QPushButton{ "Sort by name" };
	btn_sort_dest = new QPushButton{ "Sort by destination" };
	btn_sort_tp = new QPushButton{ "Sort by type" };	
	btn_filter_dest = new QPushButton{ "Filter by destination" };
	btn_filter_price = new QPushButton{ "Filter by price" };
	btn_add_cart = new QPushButton{ "Add to cart" };
	btn_clear_cart = new QPushButton{ "Clear cart" };
	btn_save = new QPushButton{ "Save" };
	btn_undo = new QPushButton{ "Undo" };
	warning = new QLabel{ "" };
	values = new QLabel{ "" };
	setWindowTitle("Lab10-11");
	windows.addObserver(w);
	setCentralWidget(w);
	QVBoxLayout* layout = new QVBoxLayout;
	w->setLayout(layout);


	layout->addWidget(warning);
	QFormLayout* hlayout = new QFormLayout{};
	layout->addLayout(hlayout);
	le_name = new QLineEdit;
	le_dest = new QLineEdit;
	le_type = new QLineEdit;
	le_price = new QLineEdit;
	hlayout->addRow("Name", le_name);
	hlayout->addRow("Destination", le_dest);
	hlayout->addRow("Type", le_type);
	hlayout->addRow("Price", le_price);

	QGridLayout* blayout = new QGridLayout{};
	layout->addLayout(blayout); 
	blayout->addWidget(btn_add, 0, 0);
	blayout->addWidget(btn_dlt, 0, 1);
	blayout->addWidget(btn_upd, 1, 0);
	blayout->addWidget(btn_sort_name, 1, 1);
	blayout->addWidget(btn_sort_dest, 2, 0);
	blayout->addWidget(btn_sort_tp, 2, 1);
	blayout->addWidget(btn_filter_dest, 3, 0);
	blayout->addWidget(btn_filter_price, 3, 1);
	blayout->addWidget(btn_add_cart, 4, 0);
	blayout->addWidget(btn_clear_cart, 4, 1);
	blayout->addWidget(btn_save, 5, 0);
	blayout->addWidget(btn_undo, 5, 1);

	layout->addLayout(lists);
	lists->addWidget(new QLabel("Lista oferte"), 0, 0);
	lists->addWidget(new QLabel("Cos de cumparaturi"), 0, 1);;
	//lists->addWidget(lst_offers, 1, 0);
	lists->addWidget(tab_offers, 1, 0);
	lists->addWidget(lst_cart, 1, 1);
	layout->addLayout(type_layout);
	type_layout->addWidget(values);
}

void UserUI::reloadList(const std::vector<Offer>& offers)
{
	/*lst_offers->clear();
	for (const auto& offer : offers)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(offer.getName() + " - " + offer.getDestination() + " - " + offer.getType() + " - " + std::to_string(offer.getPrice())));
		lst_offers->addItem(item);
	}*/

	QTableWidget* new_tab = new QTableWidget{(int)offers.size(),4};
	delete tab_offers;
	tab_offers = new_tab;
	lists->addWidget(tab_offers, 1, 0);
	int i = 0;
	for (const auto& offer : offers) {
		tab_offers->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(offer.getName())));
		tab_offers->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(offer.getDestination())));
		tab_offers->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(offer.getType())));
		tab_offers->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(std::to_string(offer.getPrice()))));
		i++;
	}
	for (int i = 0; i < btns.size(); i++)
	{
		type_layout->removeWidget(btns[i]);
		delete btns[i];
	}
	btns.clear();
	for (auto type : srv->raport_serv())
	{
		QLabel* l = new QLabel{ QString::fromStdString(type.first.first + " - " + type.first.second) };
		btns.push_back(new QPushButton(l->text()));
		type_layout->addWidget(btns[btns.size() - 1]);
		connect(btns[btns.size() - 1], &QPushButton::clicked, [&, type]() {
			values->setText(QString::fromStdString(std::to_string(type.second)));
			});
	}

}

void UserUI::reloadList_cart(const std::vector<Offer>& offers)
{
	lst_cart->clear();
	for (const auto& offer : offers)
	{
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(offer.getName() + " - " + offer.getDestination() + " - " + offer.getType() + " - " + std::to_string(offer.getPrice())));
		lst_cart->addItem(item);
	}
}

void UserUI::connectSignals()
{					
	connect(lst_offers, &QListWidget::itemSelectionChanged, [&]() {
		warning->setText("");
		values->setText("");
		if (lst_offers->selectedItems().isEmpty())
		{
			le_name->setText("");
			le_dest->setText("");
			le_type->setText("");
			le_price->setText("");
		}
		else {
			//auto item = lst_offers->selectedItems().at(0);
			auto item = lst_offers->currentItem();
			QStringList parts = item->text().split(" - ");
			le_name->setText(parts[0]);
			le_dest->setText(parts[1]);
			le_type->setText(parts[2]);
			le_price->setText(parts[3]);
		}
		});
	connect(tab_offers, &QTableWidget::itemSelectionChanged, [&]() {
		warning->setText("");
		values->setText("");
			//auto item = tab_offers->selectedItems().at(0);
		auto item = tab_offers->currentItem();
			QStringList parts;
			for (int i = 0; i < 4; i++)
				parts.push_back(tab_offers->item(item->row(), i)->text());
			le_name->setText(parts[0]);
			le_dest->setText(parts[1]);
			le_type->setText(parts[2]);
			le_price->setText(parts[3]);
		});
	connect(btn_add, &QPushButton::clicked, [&]() {
		try {
			warning->setText("");
			values->setText("");
			srv->add_offer_serv(le_name->text().toStdString(), le_dest->text().toStdString(), le_type->text().toStdString(), le_price->text().toInt());
			reloadList(srv->get_offers_serv());
		}
		catch (std::string& e) {
			warning->setText(QString::fromStdString(e));
		}
		catch (OfferException& e) {
			stringstream ss;
			ss << e;
			string s = "";
			while (!ss.eof())
			{
				string line;
				getline(ss, line);
				s += line + "\n";
			}
			warning->setText(QString::fromStdString(s));
		}
		});
	connect(btn_dlt, &QPushButton::clicked, [&]() {
		try {
			warning->setText("");
			values->setText("");
			srv->delete_offer_serv(le_name->text().toStdString(), le_dest->text().toStdString());
			reloadList(srv->get_offers_serv());
		}
		catch (std::string& e) {
			warning->setText(QString::fromStdString(e));
		}
		});
	connect(btn_upd, &QPushButton::clicked, [&]() {
		try {
			warning->setText("");
			values->setText("");
			srv->update_offer_serv(le_name->text().toStdString(), le_dest->text().toStdString(), le_price->text().toInt());
			reloadList(srv->get_offers_serv());
		}
		catch (std::string& e) {
			warning->setText(QString::fromStdString(e));
		}
		});
	connect(btn_sort_name, &QPushButton::clicked, [&]() {
		warning->setText("");
		values->setText("");
		reloadList(srv->sort_name_serv());
		});
	connect(btn_sort_dest, &QPushButton::clicked, [&]() {
		warning->setText("");
		values->setText("");
		reloadList(srv->sort_destination_serv());
		});
	connect(btn_sort_tp, &QPushButton::clicked, [&]() {
		warning->setText("");
		values->setText("");
		reloadList(srv->sort_type_price_serv());
		});
	connect(btn_filter_dest, &QPushButton::clicked, [&]() {
		warning->setText("");
		values->setText("");
		reloadList(srv->filter_destination_serv(le_dest->text().toStdString()));
		});
	connect(btn_filter_price, &QPushButton::clicked, [&]() {
		warning->setText("");
		reloadList(srv->filter_price_serv(le_price->text().toInt()));
		});
	connect(btn_add_cart, &QPushButton::clicked, [&]() {
		warning->setText("");
		values->setText("");
		secdialog_add("Introduceti numele fisierului de export", w);
		});
	connect(btn_clear_cart, &QPushButton::clicked, [&]() {
		warning->setText("");
		values->setText("");
		srv->cart_clear_serv();
		reloadList_cart(srv->get_cart_serv());
		});
	connect(btn_save, &QPushButton::clicked, [&]() {
		warning->setText("");
		values->setText("");
		secdialog_save("Introduceti numele fisierului de export", w);
		srv->save_to_file_serv(w->mesaj);
		});
	connect(btn_undo, &QPushButton::clicked, [&]() {
		try {
			warning->setText("");
			values->setText("");
			srv->undo_serv();
			reloadList(srv->get_offers_serv());
		}
		catch (std::string& e) {
			warning->setText(QString::fromStdString(e));
		}
		});
}

void UserUI::secdialog_save(string text, Observer* w)
{
	Observer* ws = new somewindow;
	windows.addObserver(ws);
	ws->resize(250, 100);
	ws->show();
	QVBoxLayout* layout = new QVBoxLayout;
	ws->setLayout(layout);
	QLabel* label = new QLabel(QString::fromStdString(text));
	layout->addWidget(label);
	QLineEdit* text_box = new QLineEdit;
	layout->addWidget(text_box);
	QPushButton* okbtn = new QPushButton("OK");
	layout->addWidget(okbtn);
	connect(okbtn, &QPushButton::clicked, ws, [&, ws, text_box, w]() {
		windows.notify(text_box->text().toStdString());
		windows.removeObserver(ws);
		ws->close();
		srv->save_to_file_serv(w->mesaj);
		});
}

void UserUI::secdialog_add(string text, Observer* w)
{
	Observer* ws = new somewindow;
	windows.addObserver(ws);
	ws->resize(250, 100);
	ws->show();
	QVBoxLayout* layout = new QVBoxLayout;
	ws->setLayout(layout);
	QLabel* label = new QLabel(QString::fromStdString(text));
	layout->addWidget(label);
	QLineEdit* text_box = new QLineEdit;
	layout->addWidget(text_box);
	QPushButton* okbtn = new QPushButton("OK");
	layout->addWidget(okbtn);
	connect(okbtn, &QPushButton::clicked, ws, [&, ws, text_box, w]() {
		windows.notify(text_box->text().toStdString());
		windows.removeObserver(ws);
		ws->close();
		stringstream ss;
		ss << w->mesaj;
		int nr;
		ss >> nr;
		try {
			srv->add_cart_serv(nr);
			reloadList_cart(srv->get_cart_serv());
		}
		catch(std::string& e) {
			warning->setText(QString::fromStdString(e));
		}
		});
}

UserUI::~UserUI()
{}
