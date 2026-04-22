#include<iostream>
#include<windows.h>
#include<mmsystem.h>
#include<sstream>
#include<array>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<limits>
#include<vector>
using namespace std;

#define li "*---------------------------------------------------------------------------*"

string genRanID();
string getDateTime();

class sender_details{
protected:
    string sendn, senmob, senadd;
};

class reciever_details{
protected:
    string recn, recmob, recadd;
};

class customer : public sender_details, public reciever_details{
public:
    string ID;
    string dateTime;
    char parctype, mod, deltype;
    float weight;
    float charges;
    friend customer inputcostu();
    friend int book();
};

customer inputcostu(){
        customer c;
        cout<<endl<<"\t\t\t\033[1;37m---Enter Sender's Details---";
        cout<<"\033[1;38;5;205m";
        cout<<endl<<endl<<"Sender's Name :- \033[1;37m";
        getline(cin,c.sendn);

        mobile:
        cout<<endl<<"\033[1;38;5;205mSender's Mobile No :- \033[1;37m";
        getline(cin,c.senmob);

        if(c.senmob.length() != 10){
            cout<<"\n\033[1;37mInvalid Mobile Number\n\n\033[1;38;5;205mAgain, ";
            goto mobile;
        }

        cout<<endl<<"\033[1;38;5;205mSender's Address :- \033[1;37m";
        getline(cin,c.senadd);

        cout<<endl<<"\t\t\t\033[1;37m---Enter receiver's Details---\033[1;38;5;205m";
        cout<<endl<<endl<<"\033[1;38;5;205mReceiver's Name :- \033[1;37m";
        getline(cin,c.recn);

        mobile2:
        cout<<endl<<"\033[1;38;5;205mReceiver's Mobile No :- \033[1;37m";
        getline(cin,c.recmob);

        if(c.recmob.length() != 10){
            cout<<"\n\033[1;37mInvalid Mobile Number\n\n\033[1;38;5;205mAgain, ";
            goto mobile2;
        }

        cout<<endl<<"\033[1;38;5;205mReceiver's Address :- \033[1;37m";
        getline(cin,c.recadd);

        cout<<endl<<"\t\t\t\033[1;37m---Enter Parcel Details---\033[1;38;5;205m";

        Goto2:
        cout<<endl<<endl<<"\033[1;38;5;205mParcel Type : \033[1;37m(Type 'D' for Documents / 'E' for Electronics / 'C' for Clothes / 'F' for Fragile, etc.) :- ";
        cin>>c.parctype;

        c.parctype = toupper(c.parctype);

        if(c.parctype != 'D' && c.parctype != 'E' && c.parctype != 'C' && c.parctype != 'F'){
            cout<<endl<<endl<<"\033[1;37mInvalid Choice, Type Again \n\n\033[1;38;5;205m";
            goto Goto2;
        }

        cout<<endl<<"\033[1;38;5;205mWeight of the parcel in grams :- \033[1;37m";
        cin>>c.weight;
        
        Goto1:
        cout<<endl<<"\033[1;38;5;205mDelivery Type : \033[1;37m(Type 'N' for Normal, 'E' for Express, 'S' for Same-day) :- ";
        cin>>c.deltype;

        c.deltype = toupper(c.deltype);

        if(c.deltype != 'N' && c.deltype != 'E' && c.deltype != 'S'){
            cout<<endl<<endl<<"\033[1;37mInvalid Choice, Type Again\033[1;38;5;205m\n\n";
            goto Goto1;
        }

        cout<<endl<<"\t\t\t\033[1;37m---Enter payment Details---\033[1;38;5;205m";
        cout<<endl<<endl<<"\033[1;38;5;205mMode : \033[1;37m(Type 'C' for Cash on Delivery, 'O' for Online, 'P'for Prepaid) :- ";
        cin>>c.mod;

        c.mod = toupper(c.mod);
        cin.ignore();

        int parcrate, deltypem;
        if(c.parctype == 'D') parcrate = 30;
        else if(c.parctype == 'E') parcrate = 50;
        else if(c.parctype == 'C') parcrate = 40;
        else parcrate = 60;

        if(c.deltype == 'N') deltypem = 1;
        else if(c.deltype == 'E') deltypem = 2;
        else deltypem = 3;

        c.charges = c.weight * parcrate * deltypem;
        cout<<endl<<endl<<"\033[1;38;5;220mCharges calculated automatically based on weight + type...";

        c.ID = genRanID();
        c.dateTime = getDateTime();
        cout<<endl<<"System generated Tracking ID and Booking Date & Time automatically...\n";
        
        return c;
    }

string getDateTime(){
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string datetime = 
        to_string(ltm->tm_mday) + "/" +
        to_string(1 + ltm->tm_mon) + "/" +
        to_string(1900 + ltm->tm_year) + " " +
        (ltm->tm_hour < 10 ? "0" : "") + to_string(ltm->tm_hour) + ":" +
        (ltm->tm_min < 10 ? "0" : "") + to_string(ltm->tm_min) + ":" +
        (ltm->tm_sec < 10 ? "0" : "") + to_string(ltm->tm_sec);

    return datetime;
}

string genRanID() {
    int num = rand() % 9000 + 1000;
    return "S" + to_string(num);
}

int book(){
    customer c = inputcostu();

    ofstream fp;
    fp.open("CourManPro.txt", ios :: app);

    if(!fp){
        cout<<"\n\033[1;37mFile Opening Error...";
        return 1;
    }

    cout<<endl<<endl;

    fp<<"\nTracking ID -> "<<c.ID<<endl;
    fp<<"Booking Date & Time -> "<<c.dateTime<<endl;

    fp<<"\n---Sender Details---\n";
    fp<<"Name -> "<<c.sendn<<endl;
    fp<<"Mobile No -> "<<c.senmob<<endl;
    fp<<"Address -> "<<c.senadd<<endl;

    fp<<"\n---Receiver Details---\n";
    fp<<"Name -> "<<c.recn<<endl;
    fp<<"Mobile No -> "<<c.recmob<<endl;
    fp<<"Address -> "<<c.recadd<<endl;

    fp<<"\n---Parcel Details---\n";
    fp<<"Parcel Type -> "<<c.parctype<<endl;
    fp<<"Weight (in grams) -> "<<c.weight<<endl;
    fp<<"Delivery Type -> "<<c.deltype<<endl;

    fp<<"\n---Payment Details---\n";
    fp<<"Mode -> "<<c.mod<<endl;
    fp<<"Charges -> Rs."<<c.charges<<endl;
    fp<<endl<<li;

    cout<<endl<<"\033[1;37mParcel Booked Successfully\n";
    cout<<"\n\033[1;92mPress enter to Continue.......";
    cin.get();

    fp.close();
    
    return 0;
}

int display(){
    cout<<"\033[1;91m";
    ifstream fp;
    fp.open("CourManPro.txt");

    if(!fp){
        cout<<"\n\033[1;37mFile Opening Error...";
        return 1;
    }

    else if(fp.peek() == EOF){
        cout<<"\n\033[1;37mNo Records found. File is empty...\n";
    }

    else{
        string line;

        cout<<"\033[1;37m"<<endl;

        while(getline(fp,line)){
            size_t pos = line.find("->");
            
            if (pos != string::npos){
                cout<<"\033[1;38;5;220m"<<line.substr(0, pos + 3);
                cout<<"\033[1;37m"<<line.substr(pos + 3)<<endl;
            }
            
            else cout<<line<<endl;
        }
    }

    cout<<"\n\033[1;38;5;205mPress enter to Continue.......";
    cin.get();
    
    fp.close();
    return 0;
}

int search(){
    cout<<"\033[1;34m";
    ifstream fp;
    fp.open("CourManPro.txt");

    if(!fp){
        cout<<"\n\033[1;37mFile Opening Error...";
        return 1;
    }
    
    bool flag = false;
    string trackid,line;
    cout<<endl<<"\033[1;37mEnter Tracking ID of Parcel -> ";
    cin>>trackid;

    cout<<endl;

    trackid = "Tracking ID -> " + trackid;

    while(getline(fp,line)){
        if(line == trackid){
            flag = true;

            size_t pos = line.find("->");

            if (pos != string::npos){
                cout<<"\033[1;38;5;220m"<<line.substr(0, pos + 3);
                cout<<"\033[1;37m"<<line.substr(pos + 3)<<endl;
            }

            while(getline(fp,line) && line != li){
                pos = line.find("->");
                if (pos != string::npos){
                    cout<<"\033[1;38;5;220m"<<line.substr(0, pos + 3);
                    cout<<"\033[1;37m"<<line.substr(pos + 3)<<endl;
                }
                else cout<<line<<endl;
            }
            break;
        }
    }

    if(flag==true) cout<<"\n\033[1;38;5;220mRecord of the Parcel has founded...\n";
    else cout<<"\n\033[1;38;5;220mNo Record has found\n";

    cout<<"\n\033[1;38;5;205mPress enter to Continue.......";
    cin.ignore();
    cin.get();

    fp.close();
    return 0;
}

int update() {
    cout << "\033[1;32m";
    bool record_found = false;
    cout << "\nTo Update the record of any Parcel,\n";
    string trackid_input;
    cout << endl << "\033[1;37mEnter Tracking ID of Parcel -> \033[1;32m";
    cin >> trackid_input;
    cin.ignore();

    string trackid_line_format = "Tracking ID -> " + trackid_input;

    ifstream file("CourManPro.txt");
    ofstream temp_file("sampleee.txt");

    if (!file.is_open() || !temp_file.is_open()) {
        cout << "\n\033[1;37mFile Not Opening, ERROR...";
        return 1;
    }

    string line;
    while (getline(file, line)) {

        if (line == trackid_line_format && !record_found) {
            record_found = true;
            cout << "\n\033[1;37mRecord found...\033[1;32m\n\n";


            vector<string> record_lines;
            record_lines.push_back(line);

            while (getline(file, line) && line != li) {
                record_lines.push_back(line);
            }


            for (string &record_line : record_lines) {
                if (record_line.find("Name ->") != string::npos || record_line.find("Mobile No ->") != string::npos || record_line.find("Address ->") != string::npos || record_line.find("Weight (in grams) ->") != string::npos || record_line.find("Mode ->") != string::npos || record_line.find("Delivery Type ->") != string::npos || record_line.find("Parcel Type ->") != string::npos) {
                    cout << "\nCurrent : " << record_line;
                    cout << "\n\033[1;37mDo you want to update this field? (y/n): ";
                    char choice;
                    cin >> choice;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (tolower(choice) == 'y') {
                        string new_value;
                        invalid_no:
                        cout << "\n\033[1;32mEnter new value -> ";
                        getline(cin, new_value);

                        if(record_line.find("Mobile No ->") != string::npos && new_value.length() != 10){
                                cout<<"\n\033[1;37mInvalid Number\nAgain, ";
                                goto invalid_no;
                        }

                        size_t pos = record_line.find("->");
                        if (pos != string::npos) {
                            record_line = record_line.substr(0, pos + 3) + " " + new_value;
                        }
                    }
                }
            }


            float weight = 0.0;
            char parctype = ' ', deltype = ' ';

            for (const string &record_line : record_lines) {
                size_t pos = record_line.find("->");
                if (pos != string::npos) {
                    string value_str = record_line.substr(pos + 3);
                    
                    if (record_line.find("Weight (in grams) ->") != string::npos) {
                        weight = stof(value_str);
                    }
                    
                    else if (record_line.find("Parcel Type ->") != string::npos) {
                        if (!value_str.empty()) parctype = toupper(value_str[1]);
                    }
                    
                    else if (record_line.find("Delivery Type ->") != string::npos) {
                        if (!value_str.empty()) deltype = toupper(value_str[1]);
                    }
                }
            }


            int parcrate, deltypem;
            if(parctype == 'D') parcrate = 30;
            else if(parctype == 'E') parcrate = 50;
            else if(parctype == 'C') parcrate = 40;
            else parcrate = 60;

            if(deltype == 'N') deltypem = 1;
            else if(deltype == 'E') deltypem = 2;
            else deltypem = 3;

            int new_charges = weight * parcrate * deltypem;


            for (string &record_line : record_lines) {
                if (record_line.find("Charges -> Rs.") != string::npos) {
                    record_line = "Charges -> Rs." + to_string(new_charges);
                    break;
                }
            }
            

            for (const string &output_line : record_lines) {
                temp_file << output_line << endl;
            }

            temp_file << li << endl;

        }
        
        else {
            temp_file << line << endl;
        }
    }

    file.close();
    temp_file.close();

    if (record_found) {
        if (remove("CourManPro.txt") != 0 || rename("sampleee.txt", "CourManPro.txt") != 0) {
            perror("\n\033[1;37mError in Updating the Record of the Parcel...\n");
            return 1;
        } else {
            cout << "\n\033[1;37mRecord of the Parcel has been Updated Successfully...\n";
        }

    }
    
    else {
        cout << "\n\033[1;37mNo Record found...\n";
        remove("sampleee.txt");
    }

    cout << "\n\033[1;92mPress enter to Continue...";
    cin.get();

    return 0;
}


int deleteparcel(){
    cout<<"\033[1;31m";
    bool flag = false;

    cout<<"\nTo Delete the record of any Parcel,\n";
    string trackid,line;
    cout<<endl<<"\033[1;37mEnter Tracking ID of Parcel -> ";
    cin>>trackid;

    trackid = "Tracking ID -> " + trackid;

    ifstream file;
    file.open("CourManPro.txt");
    ofstream fl;
    fl.open("sampleee.txt");

    if(!file || !fl){
        cout<<"\n\033[1;37mFile Not Opening, ERROR...";
        return 1;
    }

    while(getline(file,line)){
        if(line == trackid){
            flag = true;

            while(getline(file,line) && line != li){
                //skip unwanted part to delete
            }
        }

        else fl<<line<<endl;
    }

    file.close();
    fl.close();

    if(flag == true){
        if((remove("CourManPro.txt")) !=0 || (rename("sampleee.txt","CourManPro.txt")) != 0){
            perror("\n\033[1;37mError in Deleting the Record of the Parcel...\n");
            return 1;
        }
        else cout<<"\n\033[1;31mRecord of the Parcel has been Deleted Successfully...\n";
                
    }

    else{
        cout<<"\nNo Record found...\n";
        remove("sampleee.txt");
    }

    cout<<"\n\033[1;92mPress enter to Continue...";
    cin.ignore();
    cin.get();
    return 0;
}

void charges(){
    cout<<endl<<"\033[1;92mCharges have been Calculated automatically according to the Weight and Type of parcel "<<endl;
    char parctype2,deltype2;
    float weight2;

    cout<<endl<<"\t\t\t\033[1;37m---Enter Parcel Details---";

    Goto2:
    cout<<endl<<endl<<"\033[1;35mParcel Type : \033[1;37m(Type 'D' for Documents / 'E' for Electronics / 'C' for Clothes / 'F' for Fragile, etc.) :- \033[1;37m";
    cin>>parctype2;
    parctype2 = toupper(parctype2);

    if(parctype2 != 'D' && parctype2 != 'E' && parctype2 != 'C' && parctype2 != 'F'){
        cout<<endl<<endl<<"\033[1;37mInvalid Choice, Type Again \033[1;35m\n\n";
        goto Goto2;
    }
            
    cout<<endl<<"\033[1;35mWeight of the parcel in grams :- \033[1;37m";
    cin>>weight2;

    Goto1:
    cout<<endl<<"\033[1;35mDelivery Type : \033[1;37m(Type 'N' for Normal, 'E' for Express, 'S' for Same-day) :- ";
    cin>>deltype2;

    deltype2 = toupper(deltype2);
   
    if(deltype2 != 'N' && deltype2 != 'E' && deltype2 != 'S'){
        cout<<endl<<endl<<"\033[1;37mInvalid Choice, Type Again\033[1;35m\n\n";
        goto Goto1;
    }

    int parcrate2, deltypem2;
    if(parctype2 == 'D') parcrate2 = 30;
    else if(parctype2 == 'E') parcrate2 = 50;
    else if(parctype2 == 'C') parcrate2 = 40;
    else parcrate2 = 60;

    if(deltype2 == 'N') deltypem2 = 1;
    else if(deltype2 == 'E') deltypem2 = 2;
    else deltypem2 = 3;

    float charges = weight2 * parcrate2 * deltypem2;
    cout<<endl<<"\033[1;35mTotal Charges -> \033[1;37m"<<charges;

    cout<<"\n\033[1;92m\nPress enter to Continue.......";
    cin.ignore();
    cin.get();
}

void menu(){
    while(1){

        system("CLS");

        cout<<"\033[1;33m";

        char x;

        cout << "\n     COURIER MANAGEMENT SYSTEM";
        cout << "\n==============================";
        cout << "\n1 -> Book a Parcel";
        cout << "\n2 -> Display All Parcels";
        cout << "\n3 -> Search Parcel by Tracking ID";
        cout << "\n4 -> Update Parcel Information";
        cout << "\n5 -> Delete a Parcel";
        cout << "\n6 -> Calculate Delivery Charges";
        cout << "\nAny Key -> Exit\n\n\033[1;37mHere :- ";
        cin>>x;

        cin.ignore();

        cout<<endl;

        int j;

        if(x == '1'){
            j = book();
            if(j==1) return;
        }

        else if(x == '2'){
            j = display();
            if(j==1) return;
        }

        else if(x == '3'){
            j = search();
            if(j==1) return;
        }

        else if(x == '4'){
            j = update();
            if(j==1) return;
        }

        else if(x == '5'){
            j = deleteparcel();
            if(j==1) return;
        }

        else if(x == '6') charges();
        else break;
    }
}

void printMciError(DWORD error) {
    char errorText[256];
    mciGetErrorStringA(error, errorText, sizeof(errorText));
    cout << "MCI Error: " << errorText << endl;
}

void playmusic(){
    string filename = "Akaza_music.mp3";
    string openCommand = "open \"" + filename + "\" type mpegvideo alias myMusic";
    DWORD openError = mciSendStringA(openCommand.c_str(), NULL, 0, NULL);

    if (openError != 0) {
        cout << "Failed to open music file. Make sure '" << filename << "' is in the same folder." << endl;
    } else {
        DWORD playError = mciSendStringA("play myMusic repeat", NULL, 0, NULL);
        if (playError != 0) {
            cout << "Failed to play music." << endl;
            printMciError(playError);
            mciSendStringA("close myMusic", NULL, 0, NULL);
        }
    }
}

string runFiglet(const string &text) {
    string command = "figlet \"" + text + "\"";
    array<char, 256> buffer{};
    string result;
    FILE *pipe = _popen(command.c_str(), "r");
    if (!pipe) return "Error running figlet!";
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr)
        result += buffer.data();
    _pclose(pipe);
    return result;
}

void welcome(){
    system("CLS");

    int width = 160; // Width of terminal screen
    string border(width, '*'); // Top and bottom border's width
    string emptyLine = "*" + string(width - 2, ' ') + "*"; // Empty line with side borders

    // Texts to show
    string subtitle = "Fast - Reliable - Efficient";
    string info1 = "Manage your parcels with ease";
    string info2 = "Book, Track, Update, Search, Display and Calculate Charges";

    // Run Figlet for the big title
    string titleFiglet = runFiglet("Courier Management");

    // Print top border
    cout << "\033[1;33m" << border << "\033[0m" << endl;

    // Empty spacing lines
    for (int i = 0; i < 7; i++) cout << "\033[1;33m" << emptyLine << endl;

    // Print the Figlet title
    stringstream ss(titleFiglet);
    string line;
    while (getline(ss, line)) {
        int pad = (width - 2 - line.length()) / 2;
        if (pad < 0) pad = 0;
        cout << "\033[1;33m*" << string(pad, ' ') << "\033[1;92m" << line << string(width - 2 - pad - line.length(), ' ') << "\033[1;33m*\033[0m" << endl;
    }

    // Space
    cout << "\033[1;33m" << emptyLine << endl;

    // center normal text
    auto printCentered = [width](string text, string colorCode = "\033[1;37m") {
        int padding = (width - 2 - text.length()) / 2;
        if (padding < 0) padding = 0;
        cout << "\033[1;33m*" << string(padding, ' ') << colorCode << text << string(width - 2 - padding - text.length(), ' ') << "\033[1;33m*\033[0m" << endl;
    };

    printCentered(subtitle, "\033[1;91m");
    printCentered(info1, "\033[1;92m");
    printCentered(info2, "\033[1;36m");

    string textVisible = "Developed by Sukhman";
    int padding = (width - 2 - textVisible.length()) / 2;
    if (padding < 0) padding = 0;
    cout << "\033[1;33m*" << string(padding, ' ') << "\033[1;33mDeveloped by \033[1;97mSukhman\033[0m" << string(width - 2 - padding - textVisible.length(), ' ') << "\033[1;33m*" << endl;



    // Empty spacing lines
    for (int i = 0; i < 7; i++) cout << "\033[1;33m" << emptyLine << endl;

    //Print bottom border
    cout << "\033[1;33m" << border << "\033[0m" << endl;

    cout<<"\nPress Enter to Continue.......";
    cin.get();
}

int main(){
    srand(time(0));
    playmusic();
    welcome();
    menu();

    cout<<"\n\n\033[1;91mExisting Program.......";
    return 0;
}