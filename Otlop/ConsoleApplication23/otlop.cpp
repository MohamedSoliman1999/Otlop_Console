#include "otlop.h"
#include <queue>
#include <iostream>
#include<fstream> 
#include <conio.h>
#include <cstdlib>      //to clean system for console
using namespace std;
int to_int(string tmp)         //convert from string to int  using in reading from file
{     
	int x = 0;
	for (int i = 0; i < tmp.size(); i++){
		x *= 10;
		tmp[i] = tmp[i] - '0';
		x += tmp[i];
	}
	return x;
}
users::users()
{
	name = "";
	password = "";
	address = "";

}
 users::users(string n, string p, string adr)
{
	name = n;
	password = p;
	address= adr;
}
 driver::driver()
 {
	 name = "";
	 password = "";
 }
 driver::driver(string n, string p)
 {
	 name = n;
	 password = p;
 }
 string pass(string s)    //for password form
 {
	 char x;
	 int counter = 0;
	 string   ps[100];
	 while (true)
	 {
		 x = _getch();
		 if (x == '\r')break;
		 cout << "*";
		 ps[counter] = x;
		 s.append(ps[counter]); counter++;
	 }
	 return s;
 }
 void otlop::open_ris(string adr) //to open the list of ristaurant to user
 {
	 for (int i = 0; i < ristor.size(); i++)
	 {
		 cout << "press " << i + 1 << " to open the " << ristor[i].name << " ristaurant " << endl;
	 }
	 int ch;
	 int all;
	 cout <<endl<< "enter the number of ristaurant you want "; cin >> ch;
	 cout << "enter the number of all meal in your order you want "; cin >> all;
	 system("cls"); 
	 if (ch <= ristor.size()){ open_meal(ch - 1, all,adr); }
	 else{ cout << "wrong entery please enter the reqirment " << endl;  open_ris(adr); }
 }

 void otlop::open_meal(int num_ofris, int all, string adr)  //to open the list of meal for user  and make order
 {
	order temp;
	meal tp;
	 int repeat,num_ofmeal;
	 int time = 0;
	float total=0;
	 for (int i = 0; i < ristor[num_ofris].mel.size(); i++)
	 {
		 cout << i + 1 << "-the name of meal is " << ristor[num_ofris].mel[i].name << " the price " << ristor[num_ofris].mel[i].price << " the time " << ristor[num_ofris].mel[i].time << endl;
	 }
	 for (int i = 0; i < all; i++)
	 {
		 cout << "enter the number of meal "; cin >> num_ofmeal;
		 cout << "enter the number of repeat this meal "; cin >> repeat;
		 for (int j = 0; j < repeat; j++)
		 {
			 i++;
			 tp.name = ristor[num_ofris].mel[num_ofmeal - 1].name;
			 tp.price = ristor[num_ofris].mel[num_ofmeal - 1].price; total+= ristor[num_ofris].mel[num_ofmeal - 1].price;
			 tp.time = ristor[num_ofris].mel[num_ofmeal - 1].time;
			 temp.mel.push_back(tp);
		 }--i;
		 time += ristor[num_ofris].mel[num_ofmeal - 1].time;
	 }
	 char x;
	 cout << "if you want to cancel your order press n " << endl;
	 cout << "if you want to countinue press y " << endl;
	 cin >> x;
	 if (x == 'y')
	 {
		 temp.time = time; temp.total = total;
		 temp.adr = adr;
		 if (ristor[num_ofris].ordered.empty()){ temp.id = 1; }
		 else{ temp.id = ristor[num_ofris].ordered.size() + 1; }
		 ristor[num_ofris].ordered.push(temp);
		 system("cls");
		 cout << "your order will be done throwing " << temp.time << " and the total price is " << temp.total <<" and the id of order is "<<temp.id<< endl << endl;
		  open(); 		 
	 }
	 else{ system("cls"); cout << "your order is canceled successfully" << endl << endl; open(); }
 }
 void otlop::register_dr()   //register as driver
 {
	 string n, p;
	
	 cout << "enter the name ";
	 getline(cin >> ws, n);
	 cout << "enter the password ";
	 p=pass(p);
	 system("cls");
	 unordered_map<string, driver>::iterator it;
	 unordered_map<string, driver>::iterator it2;
	 it = drv.find(n);
	 it2 = drv1.find(n);
	 
	 if (it == drv.end() && it2 == drv1.end())
	 {
		 driver temp(n,p);
		 drv[temp.name] = temp; cout << "you are register succsefully" << endl; open();
	 }
	 else 
	 {
		 cout << "this acount is already exist press enter to countinue " << endl;
		 register_dr();
	 }
 }
void otlop::login_dr()   //login as a driver
{

	char x;
	string n, p;
	
	cout << "enter the name ";
	getline(cin >> ws, n);
	cout << "enter the password ";
	p=pass(p);
	system("cls");
	unordered_map<string, driver>::iterator it;
	it = drv1.find(n);
	if (it != drv1.end() && it->first == n&&it->second.password==p)
	{
		open_drv(); cout << "you rigester successfully " << endl; open();
	}
	else{ cout << "wrong entry please enter the reqirment " << endl; login_dr(); }
}
void otlop::open_drv() //to open list of order which need to be recived
{
	for (int i = 0; i < ristor.size(); i++)
	{
		
		cout <<i+1 <<"- the name of ristaurant is " << ristor[i].name << endl;
		cout << "the order details which shoud be recived is " << endl;
		cout << "**********************************************" << endl;
		if (ristor[i].ordered.size()>0){
			cout << "the id of order is " << ristor[i].ordered.front().id << endl;
		
			for (int j = 0; j < ristor[i].ordered.front().mel.size(); j++)
			{
				cout << ristor[i].ordered.front().mel[j].name << " the price of meal is " << ristor[i].ordered.front().mel[j].price << endl;
			}
			cout << "the total price is " << ristor[i].ordered.front().total << " the total time is " << ristor[i].ordered.front().time << endl;
			cout << "and the address is " << ristor[i].ordered.front().adr << endl;
		}
		else{ cout <<endl<< "there is no order is ordered " <<endl<< endl; }
		cout << "**********************************************" << endl;
	}int ch;
	cout << "please enter the number of ristaurant you want to work "; cin >> ch;
	system("cls");
	for (int c = 0; c < ristor.size(); c++)
	{
		if (ch - 1 == c){ ristor[c].ordered.pop(); cout << "your update is successfuly " << endl; open(); }
	}
}
void otlop::register_us()    //register as user
{
	string n, p, adr;
	
	cout << "enter the name "; 
	 getline(cin >> ws, n);
	cout << "enter the password ";
	p=pass(p);
	cout <<endl<<"enter the address ";
	getline(cin >> ws, adr);
	
	system("cls");
	unordered_map<string, users>::iterator it;
	it = user.find(n);
	if (it != user.end())
	{
		cout << "this acount is already exist " << endl;
		register_us();
	}
	else {
		users temp(n, p, adr);
		user[temp.name] = temp; cout << "you are register succsefully" << endl; open();
	     }
}
void otlop::cancel_order_user()  //to cancel the order from the user
{
	for (int i = 0; i < ristor.size(); i++)
	{
		cout << "press " << i + 1 << " to open the " << ristor[i].name << " ristaurant " << endl;
	}
	int num;
	cin >> num;
	cout << "Enter the id of order you want to delete" << endl;
	int id;
	cin >> id;
	queue<order> q;
	while (ristor[num - 1].ordered.empty() == false)
	{

		if (ristor[num - 1].ordered.front().id != id)
		{
			q.push(ristor[num - 1].ordered.front());
		}
		else if (ristor[num - 1].ordered.front().id == id)
		{
			order ord = ristor[num - 1].ordered.front();
			cout << "*******************************************" << endl;
			cout << "the total price is " << ord.total << " the total time is " << ord.time << " the id is "<<ord.id << endl;
			for (int i = 0; i < ord.mel.size(); i++)
			{
				cout << "the name of meal is " << ord.mel[i].name << " the price is " << ord.mel[i].price << " the time is " << ord.mel[i].time << endl;
			}
			cout << "and your address is " << ord.adr << endl;
			cout << "*******************************************" << endl;
		}
		ristor[num - 1].ordered.pop();
	}
	ristor[num - 1].ordered = q;
	char c;
	cout << endl << endl<< "enter any key to continue "; cin >> c;
	if (c == '\r'){ system("cls"); open(); }
	else{ system("cls"); open(); }
}
void otlop:: login_us()     //log in as user and show the list of ristaurants
{
	char x;
	string n, p,adr;
	
	cout << "enter the name ";
	getline(cin >> ws, n);
	cout << "enter the password ";
	p=pass(p);
	system("cls");
	unordered_map<string, users>::iterator it;
	it = user.find(n);
	if (it != user.end() && it->first == n&&it->second.password==p)
	{
		char ch;
		cout << "if you want to make order press 1 " << endl;
		cout << "if you want to cancel order press 2 "<<endl; cin >> ch;
		system("cls");
		if (ch == '1'){ open_ris(it->second.address); }
		else if (ch == '2'){ cancel_order_user(); }
		
	}
	else{ cout << "wrong entry please enter the reqirment please press enter to continue" << endl; login_us(); }
}
void otlop::login_ad()     //log in as user and show the list of ristaurants
{
	string n, p;

	cout << "enter the name "; 
	getline(cin >> ws, n);
	cout << "enter the password ";
	p=pass(p);
	system("cls");
	unordered_map<string, string>::iterator it;
	it = admin.find(n);
	if (it!=admin.end()&&it->first == n&&it->second == p)
	{
		function_ad();
	}
	else { cout << "you entery is wrong press enter to continue " << endl; login_ad(); }
}
void otlop::function_ad2(int nr) //to ask the admin ristaurant if he want to add or delet meal
{
	char ch;
	cout << "if you want to add meal press 1" << endl;
	cout << "if you want to delete meal press 2" << endl;
	cout << "if you want to exit press 3" << endl;
	cin>>ch;
	system("cls");
	if (ch == '1'){ add_meal_ofris(nr); }
	else if (ch == '2'){ delete_meal_ofris(nr); }
	else if (ch == '3'){ return; }
	else{ cout << "wrong entry please enter the reqirements " << endl; function_ad2(nr); }

}
void otlop::function_ad()  //list of functions of top admin    //to ask if he want to ad ristaurant or add driver
{
	cout << "please enter 0 if you want to add ristaurant  "<<endl;
	cout << "please press 1 to add driver " << endl;
	string ch;
	cin >> ch;
	system("cls");
	if (ch == "0"){ add_ristaurant(); }
	else if (ch == "1"){ add_drv(); }
	else{ cout << "wrong entery please enter the reqirement and press enter to continue " << endl; function_ad(); }
	
}
void otlop::add_drv() //to accepte the drivers from the top admin
{
	int count = 0;
	if (!drv.empty())
	{
		unordered_map<string, driver>::iterator it = drv.begin();
		for (; it != drv.end(); it++)
		{
			cout << count + 1 << "-the name is " << it->second.name << endl; count++;
		}
	}
	else { cout << "******** there are no new driver ********" << endl<<endl; open(); }
	int num;
	cout << "enter the all number of drivers you want to add "; cin >> num;
	for (int i = 0; i < num; i++)
	{
		int n;
		cout << "enter the ID of the drive from list you want to add "; cin >> n;
		unordered_map<string, driver>::iterator it1; count = 0;
		for (it1 = drv.begin(); it1 != drv.end(); it1++)
		{
			count++;
			if (count == n){ drv1[it1->first] = it1->second; drv.erase(drv.find(it1->second.name)); break; }
		}
	}
	system("cls");
	cout << "your update is successfully " << endl;
	open();
}
void otlop::login_admin_ristor() //login as admin ristaurant 
{
	string name, p;
	
	cout << "enter the name "; getline(cin >> ws, name);
	cout << "enter the password "; p=pass(p);
	int bol = 0;
	int num;
	unordered_map<int, admin_ris>::iterator it;
	for (it = admin_ristor.begin(); it != admin_ristor.end(); it++)
	{
		if (it->second.name == name&&it->second.password == p){ bol =1; num=it->second.num_ofris; }
	}
	system("cls");
	if (bol == 1)
	{
		cout << "if  you want to add or delete meal press 1" << endl;
		cout << "if you want to cancel order press 2" << endl;
		cout << "if you want to see all orders press 3" << endl;
		char c; cin >> c;
		system("cls");
		if (c == '1'){ function_ad2(num - 1); }
		else if (c == '2'){ func_admin_ristor(num - 1); }///////////////////////////////
		else if (c == '3'){ display_order(num - 1); }
	}
	else { cout << "wrong enter please enter the riquerment and press enter to countinue" << endl; login_admin_ristor(); }
}
void otlop::display_order(int num_ofris) //diplay all orders for the admin ristaurant
{
	vector<order>ord;
	int size = ristor[num_ofris].ordered.size();
	for (int i = 0; i <size; i++)
	{
		ord.push_back(ristor[num_ofris].ordered.back()); ristor[num_ofris].ordered.pop();
	}
	cout << "the name of ristaurant is " << ristor[num_ofris].name << endl;
	for (int i = 0; i < ord.size(); i++)
	{
		cout << "************************************************************" << endl;
		cout << "the number of order is " << ord[i].id << endl;
		for (int j = 0; j < ord[i].mel.size(); j++)
		{
			cout << "the name of meal is " << ord[i].mel[j].name << " the price is " << ord[i].mel[j].price << " the time is " << ord[i].mel[j].time << endl;
		}
		cout << "the total price is " << ord[i].total << " the total time is " << ord[i].time << endl;
		cout << "************************************************************" << endl;
		char x;
		cout << "press 1 to return to the main list "; cin >> x;
		if (x == '1'){ system("cls"); open(); }
		else{ system("cls"); open(); }
	}
	for (int i = 0; i < ord.size(); i++)
	{
		ristor[num_ofris].ordered.push(ord[i]);
	}
}
void otlop::func_admin_ristor(int num_ofris) // to delete the cancel from ristaurant as admin ristaurant
{
	vector<order>ord;
	int size = ristor[num_ofris].ordered.size();
	for (int i = 0; i <size; i++)
	{
		ord.push_back(ristor[num_ofris].ordered.back()); ristor[num_ofris].ordered.pop();
	}
	cout<<"the name of ristaurant is "<<ristor[num_ofris].name << endl;
	for (int i = 0; i < ord.size(); i++)
	{
		cout << "************************************************************" << endl;
		cout << "the number of order is " << ord[i].id<< endl;
		for (int j = 0; j < ord[i].mel.size(); j++)
		{
			cout <<j+1 <<"-the name of meal is " << ord[i].mel[j].name << " the price is " << ord[i].mel[j].price << " the time is " << ord[i].mel[j].time << endl;
		}
		cout << "the total price is " << ord[i].total << " the total time is " << ord[i].time << endl;
		cout << "************************************************************" << endl;
	}
	int ch;
	cout << "enter the number of order you want to delete "; cin >> ch;
	ch = ch - 1;
	ord.erase(ord.begin() + ch);
	for (int i = 0; i < ord.size(); i++)
	{
		ristor[num_ofris].ordered.push(ord[i]);
	}
	system("cls");
	cout << "your update is successfuly " << endl << endl;
	open();
}
void otlop::open()      //The opening screen in console
{
	cout << "log in as a top admin press 1" << endl;
	cout << "log in as admin ristuarant 2" << endl;
	cout << "log in as user press 3 " << endl;
	cout << "login as a driver press 4" << endl;
	cout << "register as user press 5" << endl;
	cout << "register as a driver press 6" << endl;
	cout << "if you want to exit press 7" << endl;
	cout << "***************************" << endl;
	char cho;
	cout << "enter your choice  "; 
	cin >> cho;
	system("cls");
	if (cho == '1'){ login_ad(); }
	else if (cho == '2'){ login_admin_ristor(); }
	else if (cho =='3'){ login_us(); }
	else if (cho == '4'){ login_dr(); }
	else if (cho == '5'){ register_us(); }
	else if (cho == '6'){ register_dr(); }
	else if (cho == '7'){ return; }
	else{ cout << "wrong entry please enter the requirment " << endl<<endl; open(); }

}
void otlop::add_meal_ofris(int num_ofristor)    //to add meal to ristaurant as admin ristaurant 
{
	for (int i = 0; i < ristor.size(); i++) 
	{
		if (i ==  num_ofristor)
		{
			meal temp;
		
			cout << "enter the name of meal "; getline(cin >> ws,temp.name);
			cout << "enter the time if meal "; cin >> temp.price;
			cout << "enter the price of meal "; cin >> temp.time;
			ristor[i].mel.push_back(temp); system("cls"); cout << "your update is successfuly " << endl;  open();
		}
	}
}
void otlop::delete_meal_ofris(int num_ofristor) //to delete meal from ristaurant
{
	int counter = 0;///
	for (int i = 0; i < ristor.size(); i++)
	{
		if (i == num_ofristor)
		{
			for (int j = 0; j < ristor[i].mel.size(); j++)
			{
					cout << counter+1 << "-the name of meal is" << ristor[i].mel[j].name << endl; counter++;
			}
			int ch;
		
			cout << "enter the number of meal you want to delete "; cin >> ch;
			if (ch <= ristor[i].mel.size()){ ristor[i].mel.erase(ristor[i].mel.begin() + (ch - 1)); system("cls"); cout << "your update is successfuly " << endl; open(); }
			else{ system("cls"); cout << "wrong entery please enter the reqirment " << endl; delete_meal_ofris(num_ofristor); }
		}
	}

}
void otlop::add_ristaurant() //to add ristaurant as a top admin
{

	string name_ofristor;
	int num_ofmeal;
	ristaurant tmp;
	admin_ris tp;

	cout << "enter the name of admin ristaurant ";getline(cin >> ws, tp.name);
	cout << "enter the password of admin ristaurant "; tp.password = pass(tp.password); cout << endl;
	//cout << "enter the number of  ristaurant "; cin >> tp.num_ofris;
	tp.num_ofris = ristor.size() + 1;
	cout << "enter the name of ristaurant  "; getline(cin>>ws,name_ofristor);
	cout << "enter the number of meal you want to add in ristaurant "; cin >> num_ofmeal;
	admin_ristor[tp.num_ofris] = tp;
	for (int i = 0; i < num_ofmeal; i++)
	{
		string name_ofmeal; int time; float price;
	
		cout << "enter the name meal "; getline(cin >> ws, name_ofmeal);// cout << endl;
		cout << "enter the time of meal "; cin >> time; //cout << endl;
		cout << "enter the price of meal "; cin >> price; //cout << endl;
		meal temp; temp.name = name_ofmeal; temp.price = price; temp.time = time;
		tmp.name = name_ofristor; tmp.mel.push_back(temp);
	}ristor.push_back(tmp);
	system("cls");
	cout << "your adding is successfuly " << endl; open();
}

void otlop::read_file()  //read from all files
{
	ifstream userf; //read from file user
	userf.open("user.txt");  
	while (!userf.eof())
	{
		users tpm;
		int count = 0;
		string n;
		string temp = "";
		getline(userf, n, '\n');
		for (int i = 0; i < n.size(); i++)
		{
			if (n[i] == '/')
			{
				if (count == 0 && temp != ""){ tpm.name = temp; }
				else if (count == 1 && temp != ""){ tpm.password = temp; }
				else if (count == 2 && temp != ""){ tpm.address = temp; }
				count++;
				temp = "";
			}
			else{ temp += n[i]; }
		}
		user[tpm.name] = tpm;
	}
	userf.close();
	/*****************/
	ifstream adminf;  //read from file top admin
	adminf.open("admin.txt");
	while (!adminf.eof())
	{
		int counter = 0;
		string n, temp = "";
		string name, pass;
		getline(adminf, n, '\n');
		for (int i = 0; i < n.size(); i++)
		{
			if (n[i] == '/')
			{
				if (counter == 0 && temp != ""){ name = temp; }
				else if (counter == 1 && temp != ""){ pass = temp; }
				temp = ""; counter++;
			}
			else{ temp += n[i]; }
		}
		admin[name] = pass;
	}
	adminf.close();
	ifstream driverf;    //read from file driver which non accepted
	driverf.open("driver.txt");
	while (!driverf.eof())
	{
		int counter = 0;
		string temp = "", n;
		driver tmp;
		getline(driverf, n, '\n');
		for (int i = 0; i < n.size(); i++)
		{
			if (n[i] == '/')
			{
				if (counter == 0&&temp!=""){ tmp.name = temp; }
				else if (counter == 1 && temp != ""){ tmp.password = temp; drv[tmp.name] = tmp; }
				counter++;
				temp = "";
			}
			else{ temp = temp + n[i]; }
		}
	}
	driverf.close();

	ifstream ristaurantf;   //read from file ristaurant
	ristaurantf.open("all_ristor.txt");
	while (!ristaurantf.eof())
	{
		string n, temp;
		getline(ristaurantf, n, '\n');
		int counter = 0;
		ristaurant tp;
		meal tmp;
		for (int i = 0; i < n.size(); i++)  
		{
			if (n[i] == '/')
			{
				if (counter == 0 &&temp != ""){ tp.name = temp; }
				else if (counter == 1 && temp != ""){ tmp.name = temp;  }
				else if (counter == 2 && temp != ""){ tmp.time = to_int(temp); }
				else if (counter == 3 && temp != ""){ tmp.price = to_int(temp);  counter = 0; tp.mel.push_back(tmp); }
				temp = ""; counter++;
			}
			else { temp += n[i]; }
		}if (tp.name != ""){ ristor.push_back(tp);}
	}
	ristaurantf.close();
	ifstream orderf;       //read from file order
	orderf.open("order.txt");
	
	int count_line = 0;
	while (!orderf.eof())
	{
		string n, temp="";
		int counter=0;
		order tmp;
		meal tp;
		getline(orderf, n, '\n');
		
		for (int i = 0; i < n.size();i++)
		{
			if (n[i] =='\\'){ ristor[count_line].ordered.push(tmp); counter = 0; temp = ""; tmp.mel.clear(); }//return //////////////
			else if (n[i] == '/')
			{
				if (counter == 0 && temp != ""){ tmp.id = to_int(temp); }
				else if (counter == 1 && temp!=""){ tmp.adr = temp; }
				else if (counter == 2 && temp != ""){ tmp.total = to_int(temp); }
				else if (counter == 3 && temp != ""){ tmp.time = to_int(temp); }
				else if (counter == 4 && temp != ""){ tp.name = temp; }
				else if (counter == 5 && temp != ""){ tp.price = to_int(temp); }
				else if (counter == 6 && temp != ""){ tp.time = to_int(temp); counter = 3; tmp.mel.push_back(tp);  }
				counter++; temp = "";
			}
			else{ temp += n[i]; }
			
		}

		count_line++;
	}
	orderf.close();
	ifstream adm;   //to read from file admin ristaurant
	adm.open("admin_ris.txt");
	while (!adm.eof())
	{
		int counter = 0;
		string n, temp="";
		 admin_ris tmp;
		getline(adm, n, '\n');
		for (int i = 0; i < n.size(); i++)
		{
			if (n[i] == '/')
			{
				if (counter == 0&&temp!=""){ tmp.name = temp; }
				else if (counter == 1 && temp != ""){ tmp.password = temp; }
				else if (counter == 2 && temp != ""){ tmp.num_ofris = to_int(temp); admin_ristor[tmp.num_ofris] = tmp; }
				counter++; temp = "";
			}
			else{ temp += n[i]; }
		}
		
	}
	adm.close();
	ifstream driver1;   //ro read from file driver which accepted
	driver1.open("driver1.txt");
	while (!driver1.eof())
	{
		string n, temp = "";
		int count = 0;
		driver1 >> n;
		driver tmp;
		for (int i = 0; i < n.size(); i++)
		{
			if (n[i] == '/')
			{
				if (count == 0 && temp != ""){ tmp.name = temp; }
				else if (count == 1 && temp != ""){ tmp.password = temp; drv1[tmp.name] = tmp; }
				count++; temp = "";
			}
			else{ temp = temp + n[i]; }
		}
		
	}
	driver1.close();
}
void otlop::write_file()
{
	ofstream userf;   //write to file user
	userf.open("user.txt", ios::trunc);
	if (!user.empty())
	{
		unordered_map<string, users>::iterator it;
		for (it = user.begin(); it != user.end(); it++)
		{
			userf << it->second.name << "/" << it->second.password << "/" << it->second.address << "/" << endl;
		}
	}
	userf.close();
	ofstream driverf;  //write to file drivers which non accepted
	driverf.open("driver.txt", ios::trunc);
	if (!drv.empty())
	{
		unordered_map<string, driver>::iterator it1;
		for (it1 = drv.begin(); it1 != drv.end(); it1++)
		{
			driverf << it1->second.name << "/" << it1->second.password << "/" << endl;
		}
	}
	driverf.close();
	ofstream ristaurantf;   //write to file ristaurant
	if (ristor.size() > 0)
	{
		ristaurantf.open("all_ristor.txt", ios::trunc);
		for (int i = 0; i < ristor.size(); i++)
		{
			ristaurantf << ristor[i].name << "/";
			for (int j = 0; j < ristor[i].mel.size(); j++)
			{
				ristaurantf << ristor[i].mel[j].name << "/" << ristor[i].mel[j].time << "/" << ristor[i].mel[j].price << "/";

			}ristaurantf << endl;

		}
		ristaurantf.close();
	}
	ofstream orderf;      //write to file order
	orderf.open("order.txt", ios::trunc);

	for (int i = 0; i < ristor.size(); i++)
	{
		vector<order>temp;
		int x = ristor[i].ordered.size();
		for (int j = 0; j < x; j++) //to contain orders in vector to be easy in file
		{
			temp.push_back(ristor[i].ordered.front());
			ristor[i].ordered.pop();
		}
		for (int j = 0; j < temp.size(); j++) //to return the value after pop the queue
		{
			ristor[i].ordered.push(temp[j]);
		}
		for (int j = 0; j < temp.size(); j++)
		{
			orderf << temp[j].id << "/" << temp[j].adr << "/" << temp[j].total << "/" << temp[j].time << "/";
			for (int k = 0; k < temp[j].mel.size(); k++)//for all meal in one order
			{
				orderf << temp[j].mel[k].name << "/" << temp[j].mel[k].price << "/" << temp[j].mel[k].time << "/";
			}orderf << "\\";
		}orderf << endl;
	}
	orderf.close();
	ofstream adm;   //to write in file admin ristaurant
	if (!admin_ristor.empty())
{
		adm.open("admin_ris.txt", ios::trunc);
	unordered_map<int, admin_ris> ::iterator it;
	for (it = admin_ristor.begin(); it != admin_ristor.end(); it++)
	{
		adm << it->second.name << "/" << it->second.password << "/" << it->second.num_ofris << "/" << endl;
	}
	adm.close();
}
  ofstream driver1;  //to write in file driver which accepted
  driver1.open("driver1.txt", ios::trunc);
  if (!drv1.empty())
  {
	  unordered_map<string, driver>::iterator it3;
	  for (it3 = drv1.begin(); it3 != drv1.end(); it3++)
	  {
		  driver1 << it3->second.name << "/" << it3->second.password << "/" << endl;
	  }
  }
  driver1.close();
}

otlop::~otlop()
{
	write_file();
}
otlop::otlop()
{
	read_file();
}