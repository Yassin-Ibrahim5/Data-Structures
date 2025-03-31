#include <iostream>
using namespace std;



class Guests{
private:
    string name;
    string contact;
    string iftar_date;
public:
    Guests() : name(""), contact(""), iftar_date(""){};

    Guests(string name, string contact, string iftar_date)
    {
        this->name = name;
        this->contact = contact;
        this->iftar_date = iftar_date;
    };
    void displayGeust(){
        cout << "Guests: " << name << ", ";
        cout << "Contact: " << contact << ", ";
        cout << "Iftar Date: " << iftar_date << endl;
    }

    void update_invitation(string new_date){
        iftar_date = new_date;
    }

    string getName(){
        return name;
    }

    string getIftarDate(){
        return iftar_date;
    }

    string get_contact(){
        return contact;
    }


};

const int MAX_G = 100;

class IftarManager {
private:
    Guests* guestsRecord;
    int noGuests;

public:
    IftarManager() {
        guestsRecord = new Guests[MAX_G];
        noGuests = 0;
    }

    void addGuest(Guests& guest) {
        if (noGuests < MAX_G) {
            guestsRecord[noGuests] = guest;
            noGuests++;
        }
    }

    void removeGuest(string name){
        for(int i = 0; i < noGuests; i++){
            if(guestsRecord[i].getName() == name){
                for(int j = i; j < noGuests - 1; j++){
                    guestsRecord[j] = guestsRecord[j + 1];
                }
                noGuests--;
                cout << "Guests " << name << " removed." << endl;
                return;
            }
        }
        cout << "Guests " << name << " not found." << endl;
    }


    void displayAll() {
        for (int i = 0; i < noGuests; i++) {
            guestsRecord[i].displayGeust();
        }
        cout << endl;
    }

    void updateInvitation(string name, string new_date) {
        for (int i = 0; i < noGuests; i++) {
            if (guestsRecord[i].getName() == name) {
                cout << "Updating invitation for " << name << "..." << endl;
                cout << endl;
                guestsRecord[i].update_invitation(new_date);
            }
        }
    }

    void sendReminder(string date) {
        cout << "Sending reminder..." << endl;
        for (int i = 0; i < noGuests; i++) {
            if (guestsRecord[i].getIftarDate() == date) {
                cout << "Reminder sent to " << guestsRecord[i].getName() << ": Your Iftar invitation is on " << guestsRecord[i].getIftarDate() << "!" << endl;
            }
        }
        cout << endl;
    }

    void sortGuestList() {
        for (int i = 1; i < noGuests; i++) {
            Guests key = guestsRecord[i];
            int j = i - 1;
            while (j >= 0 && guestsRecord[j].getName() > key.getName()) {
                guestsRecord[j + 1] = guestsRecord[j];
                j = j - 1;
            }
            guestsRecord[j + 1] = key;
        }
    }

    ~IftarManager() {
        delete[] guestsRecord;
    }
};



int main() {
    IftarManager manager = IftarManager();

    Guests guest1 = Guests("Aisha", "aisha@example.com", "2025-03-15");
    Guests guest2 = Guests("Omar", "omar@example.com", "2025-03-18");
    Guests guest3 = Guests("Zainab", "zainab@example.com", "2025-03-20");

    manager.addGuest(guest1);
    manager.addGuest(guest2);
    manager.addGuest(guest3);

    manager.displayAll();

    manager.updateInvitation("Omar", "2025-03-15");

    manager.displayAll();

    manager.sendReminder("2025-03-15");

    manager.removeGuest("Omar");

    manager.displayAll();

    cout << "May your Iftar gatherings be full of warmth and blessings!" << endl;


    return 0;
}