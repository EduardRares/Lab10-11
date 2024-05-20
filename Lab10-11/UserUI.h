#pragma once

#include <QWidget>
#include <QListWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QLayout>
#include <QTextBlock>
#include <QTableWidget>
#include <set>
#include <QSlider>
#include <QPainter>
#include <QListView>
#include "ui_UserUI.h"
#include "Service.h"
#include "repo.h"
#include "Observer.h"
#include <sstream>

class UserUI : public QMainWindow
{
    Q_OBJECT
private:
    Service* srv;
    QPushButton* btn_add, * btn_dlt, * btn_upd, * btn_sort_name, * btn_sort_dest, * btn_sort_tp, * btn_filter_dest, * btn_filter_price, * btn_add_cart, * btn_clear_cart, * btn_save, * btn_undo;
    QListWidget* lst_offers, * lst_cart, *btn_types;
    QTableWidget* tab_offers;
    QLineEdit* le_name, * le_dest, * le_type, * le_price;
    QLabel* warning, *values;
    QGridLayout* lists = new QGridLayout{};
    vector<QPushButton*> btns;
    QVBoxLayout* type_layout = new QVBoxLayout;
    Observable windows;
    Observer* w = new mainWindow;
    void initGUI();
    void reloadList(const std::vector<Offer>& offers);
    void reloadList_cart(const std::vector<Offer>& offers);
    void connectSignals();
    void secdialog_save(string text, Observer*); 
    void secdialog_add(string text, Observer*);

public:
    UserUI(QWidget *parent = nullptr);
    ~UserUI();

private:
    Ui::UserUIClass ui;
    
private slots:
};

