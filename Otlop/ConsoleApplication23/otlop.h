#pragma once
#include <string>
#include <queue>
#include<vector>
#include <iostream>
#include<unordered_map>
using namespace std;
class users
{
public:
	string name;
	string password;
	string address;
	users();
	users(string n, string p, string adr);
};
class driver                //driver
{
public:        
	string name;
	string password;
	driver();
	driver(string n, string p);

};
class meal             //for meal
{
public:
	int time;
	string name;
	float price;
};
class order
{
public:
	int id;
	vector<meal>mel;
	int time = 0;
	float total = 0;
	string adr;
};
class ristaurant       //Ristorant
{
public:
	
	string name;
	vector<meal>mel;
	queue<order>ordered;
};
class admin_ris
{
public:
	int num_ofris;
	string name;
	string password;
};
class otlop            //otlop
{
public:
	unordered_map<int, admin_ris> admin_ristor;   //int beacuse the number if ristaurant is uniqe
	unordered_map<string, driver>drv;
	unordered_map<string, driver>drv1;
	unordered_map<string ,users >user;   //name and password
	unordered_map<string, string>admin;  //name and password
	vector<ristaurant>ristor;
void add_drv();
void register_dr();
void login_dr();
void register_us();    //refister as user
void login_us();
void login_ad();
void open_drv(); 
void open();                                                        //The opening screen in console
//void adddriver(int id, string name);                 //nada task
void add_ristaurant();                    //add ristaurant
void add_meal_ofris(int num_ofristor);                                  //add meals for  ristorants for admin only
void delete_meal_ofris(int num_ofristor);                               //delete meal for restorant for admin only 
void open_ris(string adr);                                                 // list of restaurants
void open_meal(int num_ofris, int all, string adr);                 //take number of ristuarant    //show list of meals in ristuarant
void function_ad();
void function_ad2(int nr);
void login_admin_ristor();
void func_admin_ristor(int num_ofris);
void cancel_order_user();
void display_order(int num_ofris);
	void read_file();
	void write_file();
	~otlop();
	otlop();
};
