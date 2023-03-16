//MULTILEVEL INHERITANCE USED//
#include<iostream>
#include<string>
#include<fstream>
#include<map>
using namespace std;

class food;
class bill;

class tour{
    public:
    char checkin[10],checkout[10];
    int adults,kids;
    tour(){
        adults=kids=0;
    }
    ~tour(){}
};

class details : public tour{
    public:
    string fname,lname,phno,adhaarnum;
    int age;
    char gender;
};


class hotel : public details{
    public:
    string roomtype;
};

class food : public hotel{
    public:
    string type,dates;
    int times;
    friend void pushToFile(bill,food,string,string);
};

class bill{   //INDEPENDENT CLASS// NOT INHERITED// 
    public:
    int roomBill;
    int foodBill;
    int hotelServiceTax;
    int gst;
    bill(){
        roomBill = 0;
        foodBill = 0;
        hotelServiceTax = 0;
        gst = 0;
    }
    friend void pushToFile(bill,food,string,string);

};


void pushToFile(bill b1, food f, string city, string hotel){
    cout<<"\n\n~~~~~ Please enter the reqired details ~~~~~\n\n";
    cout << "  >>Checkin date (dd/mm/yyyy): ";
    cin >> f.checkin;
    cout << "  >>Checkout date (dd/mm/yyyy): ";
    cin >> f.checkout;

    //system("cls");

    st:
    int n,m,excp;
    cout<<"\n";
    try{
        cout << "  >>Enter adults: ";
        cin >> f.adults;
        cout << "  >>Enter kids under 15 yrs: ";
        cin >> f.kids;
        n = f.adults;
        m = f.kids;
        if(n==0){
            throw excp;
        }
    }
    catch(int e){
        system("clear");
        cout<<"\nAtleast 1 adult needed to add kids\n";
        cout<<"Invalid request...\n";
        goto st;
    }
    details adult[n];
    details kid[m];
    cout<<"\n\n";
    for (int i = 0; i < n; i++){
        cout << "~Enter first name for Person " << i+1 << ": ";
        cin >> adult[i].fname;
        cout << "~Enter last name for Person " << i+1 << ": ";
        cin >> adult[i].lname;
        
        cout << "~Enter Phone number for Person " << i+1 << ": ";
        cin >> adult[i].phno;
        cout << "~Enter age for Person "<< i+1 << ": ";
        cin >> adult[i].age;
    
        cout << "~Enter aadhar number for Person "<< i+1 << ": ";
        cin >> adult[i].adhaarnum;;
        
        cout << "~Enter gender for Person "<< i+1 << ": ";
        cin >> adult[i].gender;
        //system("cls");
    }

    cout<<"\n\n";
    for (int i = 0; i < m; i++){
        cout << "~Enter first name for kid " << i+1 << ": ";
        cin >> kid[i].fname;
        cout << "~Enter last name for kid " << i+1 << ": ";
        cin >> kid[i].lname;
        cout << "~Enter age for kid "<< i+1 << ": ";
        cin >> kid[i].age;
    
        cout << "~Enter aadhar number for kid "<< i+1 << ": ";
        cin >> kid[i].adhaarnum;
        
        cout << "~Enter gender for kid "<< i+1 << ": ";
        cin >> kid[i].gender;
        //system("cls");
    }
    map<string,int>roomCost;
    map<string, int>foodCost;

//FOOD TYPE
    string foodhotelText[9];
    int foodChoice;
    ifstream food("foodData.txt");
    cout<<"\n\n";
    cout.width(25);
    cout<<"-------------"<<endl;
    cout.width(25);
    cout<<"|  CUSINES  |"<<"\n";
    cout.width(25);
    cout<<"-------------"<<"\n"<<endl;

    for (int i = 0; i <9; i++){
        getline(food,foodhotelText[i]);
        foodCost[foodhotelText[i]] = 1500+(rand()%900);
        cout<<"  >>"<< i+1 << "." << foodhotelText[i] << endl;
    }
    cout.width(34);
    cout<<"\n-----------------------------------------------\n";
    map<string, int> :: iterator it2 = foodCost.begin();
    cout.width(40);
    cout<<"The food pricing are as follows:"<<"\n\n";
    int serial = 1;
    while (it2 != foodCost.end()){
        cout << "<" << serial << ">";
        cout.width(22);
        cout << it2->first << " Price: ";
        cout.width(6);
        cout <<"₹"<< it2->second << endl;
        ++it2;
    }
    cout<<endl;
    cout<<"Enter option: ";
    cin >> foodChoice;
    for (int i = 1; i <9; i++){
        if (foodChoice == i){
            f.type = foodhotelText[i-1];
            auto itr2 = foodCost.find(foodhotelText[i-1]);
            cout <<"\nChoosen :: "<< itr2->first << ": " << itr2->second;
            b1.foodBill = itr2->second;
            //cout << b1.foodBill << endl;
            break;
        }
    }
    // system("cls");

//ROOM TYPE
    string roomhotelText[9];
    int roomChoice;
    ifstream room("roomData.txt");
    cout<<"\n\n";
    cout.width(25);
    cout<<"---------------"<<endl;
    cout.width(25);
    cout<<"|  ROOM TYPE  |"<<"\n";
    cout.width(25);
    cout<<"---------------"<<"\n"<<endl;
    //cout << "Enter type of Room:" << endl;
    for (int i = 0; i <9; i++){
        getline(room,roomhotelText[i]);
        roomCost[roomhotelText[i]] = 3000+(rand()%990);
        cout<<"  >>"<< i+1 << "." << roomhotelText[i] << endl;
    }
    cout.width(34);
    cout<<"\n-----------------------------------------------\n";
    map<string, int> :: iterator it1 = roomCost.begin();
    cout.width(40);
    int serial = 1;
    cout<<"The room pricing are as follows: "<<"\n\n";
    while (it1 != roomCost.end()){
        cout << "<" << serial << ">";
        cout.width(22);
        cout << it1->first << " Price: ";
        cout.width(6);
        cout <<"₹"<< it1->second << endl;
        ++it1;
    }
    cout<<endl;
    cout<<"Enter option: ";
    cin >> roomChoice;
    for (int i = 1; i <9; i++){
        if (roomChoice == i){
            f.roomtype = roomhotelText[i-1];
            
            auto itr1 = roomCost.find(roomhotelText[i-1]);
            cout<<"\nChoosen :: " << itr1->first << ": " << itr1->second;
            b1.roomBill = itr1->second;
            
            // cout << b1.roomBill;
            break;
        }}

    void showBill(bill);
        showBill(b1);

    //system("cls");

    ofstream myFile, myFile2 ,myFile3;
    myFile.open("database.csv",ios::app);
    myFile2.open("customerDatabaseAdults.csv",ios::app);
    myFile3.open("customerDatabaseKids.csv",ios::app);

    myFile3 << endl;
    myFile2 << endl;
    myFile << endl;

    myFile << city <<  ',';
    myFile << f.checkin<< ',';
    myFile << f.checkout<<  ',';
    myFile << f.adults <<  ',';
    myFile << f.kids << ',';

    for(int i = 0; i < n; i++){
        myFile2 << adult[i].fname << ',';
        myFile2 << adult[i].lname << ',';
        myFile2 << adult[i].phno << ',';
        myFile2 << adult[i].age << ',';
        myFile2 << adult[i].adhaarnum << ',';
        myFile2 << adult[i].gender;
        myFile2 << endl;
    }
    
    for(int i = 0; i < m; i++){
        myFile3 << kid[i].fname << ',';
        myFile3 << kid[i].lname << ',';
        myFile3 << kid[i].age << ',';
        myFile3 << kid[i].adhaarnum << ',';
        myFile3 << kid[i].gender;
        myFile3 << endl;
    }
    myFile <<  hotel <<  ',';
    myFile << f.roomtype << ',';
    myFile << f.type <<  ',';

}
void showBill(bill x){
    int gst;
    gst = (x.roomBill + x.foodBill + x.hotelServiceTax)*0.18 + (x.roomBill + x.foodBill + x.hotelServiceTax);
    cout<<endl;
    cout.width(34);
    cout<<"-----------------------------------------------\n";
    cout.width(10);
    cout<<"Room Bill: ";
    cout.width(20);
    cout<<"₹"<<x.roomBill;
    cout<<endl;
    cout.width(10);
    cout<<"Food Bill: ";
    cout.width(20);
    cout<<"₹"<<x.foodBill;
    cout<<endl;
    cout.width(10);
    cout<<"Hotel Bill: ";
    cout.width(19);
    cout<<"₹"<<x.hotelServiceTax;
    cout<<endl;
    cout.width(34);
    cout<<"-----------------------------------------------\n";
    cout.width(10);
    cout<<"TOTAL: ";
    cout.width(21);
    cout<<"₹"<<gst;
    cout<<endl;
}


int main(){
    bill b;
    srand(time(0));
    // cost c;
    map<string, int>hotelCost;

    food f;
    string cityChoice;
    int hotelChoice,opt,flag=0;
    string hotelText[7];
    cout.width(40);
    cout<<"----------------------------------------"<<endl;
    cout.width(40);
    cout << "|  WELCOME TO HOTEL MANAGEMENT SYSTEM  |" << endl;
    cout.width(40);
    cout<<"----------------------------------------"<<"\n"<<endl;

    cout.width(25);
    cout<<"------------"<<"\n";
    cout.width(25);
    cout<<"|  CITIES  |"<<endl;
    cout.width(25);
    cout<<"------------"<<"\n"<<endl;
    cout << "Currently serving: " << endl;
    cout << "  >>1.Mumbai" << endl;
    cout << "  >>2.Delhi" << endl;
    cout << "  >>3.Chennai" << endl;
    cout << "  >>4.Kolkata" << endl;
    cout << "Enter option: ";
    cin >> opt;

    //system("cls");
   
    switch(opt){
    case 1:{
        cityChoice = "Mumbai";
        ifstream hotel("mumbai.txt");
        cout<<"\n\n";
        cout.width(25);
        cout<<"------------"<<"\n";
        cout.width(25);
        cout<<"|  HOTELS  |"<<endl;
        cout.width(25);
        cout<<"------------"<<"\n"<<endl;
        //cout << "Available Hotels:" << endl;
        for (int i = 0; i <7; i++){
            getline(hotel,hotelText[i]);
            hotelCost[hotelText[i]] = 1800+(rand()%1000);
            cout<<"  >>"<< i+1 << "." << hotelText[i] << endl;

        }
        map<string, int> :: iterator it = hotelCost.begin();
        cout.width(34);
        cout<<"\n-----------------------------------------------\n";
        cout.width(40);
        cout<<"The hotel pricing are as follows:"<<"\n\n";
        int serial = 1;
        while (it != hotelCost.end()){
            cout << "<" << serial << ">";
            cout.width(22);
            cout << it->first << " Price: ";
            cout.width(6);
            cout <<"₹"<< it->second << endl;
            ++it;
        }

        
        cout << "Enter option: ";
        cin >> hotelChoice;
        auto itr3 = hotelCost.find(hotelText[hotelChoice-1]);
        b.hotelServiceTax = itr3->second;
        cout <<"Choosen :: "<< itr3->first << ": " << itr3->second;
        pushToFile(b,f,cityChoice,hotelText[hotelChoice-1]);
        // system("clear");
       
        flag=1;
        break;
    }


    case 2:{
        cityChoice = "Delhi";
        ifstream hotel("delhi.txt");
        cout<<"\n\n";
        cout.width(25);
        cout<<"------------"<<"\n";
        cout.width(25);
        cout<<"|  HOTELS  |"<<endl;
        cout.width(25);
        cout<<"------------"<<"\n"<<endl;
        //cout << "Available Hotels:" << endl;
        for (int i = 0; i <7; i++){
            getline(hotel,hotelText[i]);
               hotelCost[hotelText[i]] = 1150+(rand()%1000);
            cout<<"  >>"<< i+1 << "." << hotelText[i] << endl;
        }
            map<string, int> :: iterator it = hotelCost.begin();
            cout.width(34);
            cout<<"\n-----------------------------------------------\n";
            cout.width(40);
            cout<<"The hotel pricing are as follows:"<<"\n\n";
            int serial = 1;
            while (it != hotelCost.end()){
                cout << "<" << serial << ">";
                serial++;
                cout.width(22);
                cout << it->first << " Price: ";
                cout.width(6);
                cout << "₹" << it->second << endl;
                ++it;
            }
        cout << "Enter option: ";
        cin >> hotelChoice;
            auto itr3 = hotelCost.find(hotelText[hotelChoice-1]);
            b.hotelServiceTax = itr3->second;
            cout<<"Choosen :: " << itr3->first << ": " << itr3->second;
        pushToFile(b,f,cityChoice, hotelText[hotelChoice-1]);
        // system("clear");
        flag=1;
        break;
    }


    case 3:{
        cityChoice = "Chennai";
        ifstream hotel("chennai.txt");
        cout<<"\n\n";
        cout.width(25);
        cout<<"------------"<<"\n";
        cout.width(25);
        cout<<"|  HOTELS  |"<<endl;
        cout.width(25);
        cout<<"------------"<<"\n"<<endl;
        for (int i = 0; i <7; i++){
            getline(hotel,hotelText[i]);
                hotelCost[hotelText[i]] = 800+(rand()%1000);
            cout<<"  >>"<< i+1 << "." << hotelText[i] << endl;
        }
  map<string, int> :: iterator it = hotelCost.begin();
      cout.width(34);
    cout<<"\n-----------------------------------------------\n";
    cout.width(40);
        cout<<"The hotel pricing are as follows:"<<"\n\n";
        int serial = 1;
    while (it != hotelCost.end()){
        cout << "<" << serial << ">";
        cout.width(22);
        cout << it->first << " Price: ";
        cout.width(6);
        cout << "₹"<< it->second << endl;
        ++it;
        }
        cout << "Enter option: ";
        cin >> hotelChoice;
        auto itr3 = hotelCost.find(hotelText[hotelChoice-1]);
        b.hotelServiceTax = itr3->second;
        cout <<"Choosen :: " << itr3->first << ": " << itr3->second;
        pushToFile(b,f,cityChoice, hotelText[hotelChoice-1]);
        // system("clear");
        flag=1;
        break;
    }


    case 4:{
        cityChoice = "Kolkata";
        ifstream hotel("kolkata.txt");
        cout<<"\n";
        cout.width(25);
        cout<<"------------"<<"\n";
        cout.width(25);
        cout<<"|  HOTELS  |"<<endl;
        cout.width(25);
        cout<<"------------"<<"\n"<<endl;
        //cout << "Available Hotels:" << endl;
        for (int i = 0; i <7; i++){
            getline(hotel,hotelText[i]);
       hotelCost[hotelText[i]] = 565+(rand()%1000);
            cout<<"  >>"<< i+1 << "." << hotelText[i] << endl;
        }
  map<string, int> :: iterator it = hotelCost.begin();
      cout.width(34);
        cout<<"\n-----------------------------------------------\n";
        cout.width(40);
        cout<<"The hotel pricing are as follows:"<<"\n\n";
        int serial = 1;
    while (it != hotelCost.end()){
    cout << "<" << serial << ">";
    cout.width(22);
    cout << it->first << " Price: ";
    cout.width(6);
    cout << "₹"<< it->second << std::endl;
    ++it;
    }
        cout << "Enter option: ";
        cin >> hotelChoice;
        auto itr3 = hotelCost.find(hotelText[hotelChoice-1]);
        b.hotelServiceTax = itr3->second;
        cout<<"Choosen :: " << itr3->first << ": " << itr3->second;
        pushToFile(b,f,cityChoice, hotelText[hotelChoice-1]);
        // system("clear");
        flag=1;
        break;
    }


    default:{
    cout<<"\n\n";
    cout.width(38);
    cout << "<><><><><><><><><><><><><><><><><>\n";
    cout.width(27);
    cout << "Invalid option!" << endl;
    cout.width(38);
    cout << "<><><><><><><><><><><><><><><><><>\n";
    cout<<"\n"<<endl;
    break;
    }

    }
    if(flag==1){

    cout<<"\n\n";
    cout.width(38);
    cout << "<><><><><><><><><><><><><><><><><>\n";
    cout.width(33);
    cout << "Ticket Successfully booked" << endl;
    cout.width(38);
    cout << "<><><><><><><><><><><><><><><><><>\n";
    cout<<"\n"<<endl;
    }
return 0;
}
