#include "pch.h"

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;   

// Forward declaration of classes
class Cont;
class Comanda;
class Client;

class Cont {
public:
    string nume;
    string email;
    string tel;
    Cont(string nume, string email, string tel) {
        this->email = email;
        this->nume = nume;
        this->tel = tel;
    }
};

enum TipColet{ ColetMic, ColetMediu, ColetMare, ColetFoarteMare };

class Comanda {
public:
    TipColet colet;
    string AWB;
    string adresa;
    string detaliiComanda;
    string data;
    Comanda(TipColet colet, string AWB, string adresa, string detaliiComanda, string dataComanda){
        this->colet = colet;
        this->AWB = AWB;
        this->adresa = adresa;
        this->detaliiComanda = detaliiComanda;
        this->data = dataComanda;
    }
    TipColet getTipColet() {
        return colet;
    }
};


enum FirmaCurierat { FanCourier, DPD, Posta_Romana, SameDay };

class Curier : Cont{
private:
    FirmaCurierat firma;
public:
    Comanda* comanda;
    Curier(string nume, string email, string tel, string adresa, FirmaCurierat firma) : Cont(nume, email, tel), firma(firma) {}
    void actualizareStatusComanda() {

    }
    string getCurier() {
         return nume;
    }
};

class SistemPlata {
public:
    int sumaCard;
    SistemPlata(int sumaCard) {
        this->sumaCard = sumaCard;
    }
    int calculSuma(Comanda& comanda) {
        int pret = 0;
        switch (comanda.getTipColet()) {
        case ColetMic:
            pret = 10;
            break;
        case ColetMediu:
            pret = 15;
            break;
        case ColetMare:
            pret = 20;
            break;
        case ColetFoarteMare:
            pret = 25;
            break;
        default:
            pret = 10;
        }
        return pret;
    }
    bool efecutarePlata(float suma) {
        if (sumaCard > suma)
            return true;
        return false;
    }
};

// Class representing a Customer
class Client : Cont{
private:
    string adresaExpeditor;
public:
    Comanda* comanda;
    Curier* curier;
    Client(string nume, string email, string tel, string adresa) : Cont(nume, email, tel), adresaExpeditor(adresa) {}
    void setComanda(Comanda* c) {
        comanda = c;
    }
    string getComanda() {
        if (comanda) {
            return comanda->AWB;
        }
        else return "Nu a creat nicio comanda";
    }
    void setCurier(Curier* c) {
        curier = c;
    }
    string getCurier() {
        if (curier) {
            return curier->getCurier();
        }
        else return "Nu a fost asociat un curier";
    }
    void afisareClient() {
        cout << "Clientul " << nume << "a efectuat comanda " << getComanda() << "la data " << comanda->data << "si i s-a asociat curierul " << getCurier() << endl;
    }
};

string makeAWB() {
    int n = 10;
    string awb;
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            awb+= to_string(rand() % n);
        }
    }
    return awb;
}

int main() {
  
    // Instantiere obiecte folosind constructorul Curier
    Curier curier1("Marian", "marian.bodoc@gmail.com", "0765489765", "Strada Florilor nr. 10 Sector 2, București", FirmaCurierat::FanCourier);
    Curier curier2("Ana", "ana.popescu@example.com", "0723123456", "Bulevardul Libertății nr. 25, Sector 3, București", FirmaCurierat::FanCourier);
    Curier curier3("Alexandru", "alexandru.ionescu@example.com", "0736112233", "Aleea Fericirii nr. 7, Sector 4, București", FirmaCurierat::Posta_Romana);
    Curier curier4("Elena", "elena.vasile@example.com", "0744556677", "Calea Victoriei nr. 30, Sector 1, București", FirmaCurierat::SameDay);
    Curier curier5("Adrian", "adrian.pop@example.com", "0766778899", "Strada Speranței nr. 15, Sector 5, București", FirmaCurierat::SameDay);
    Curier curier6("Cristina", "cristina.andrei@example.com", "0722889900", "Bulevardul Unirii nr. 2, Sector 3, București", FirmaCurierat::DPD);

    // Instantiere obiecte folosind constructorul Client
    Client client1("Marius", "marius.popescu@gmail.com", "0789654632", "Strada Pictor Arthur Verona nr. 4, Sector 1, București");
    Client client2("Andreea", "andreea.ionescu@example.com", "0765432198", "Bulevardul Decebal nr. 20, Sector 2, București");
    Client client3("Gabriel", "gabriel.stoica@example.com", "0721987654", "Aleea Mihai Eminescu nr. 15, Sector 3, București");
    Client client4("Laura", "laura.dumitrescu@example.com", "0732123456", "Calea Dorobanților nr. 30, Sector 4, București");
    Client client5("Radu", "radu.iliescu@example.com", "0742567890", "Strada Splaiul Unirii nr. 10, Sector 5, București");
    Client client6("Ioana", "ioana.popa@example.com", "0765432109", "Bulevardul Victoriei nr. 5, Sector 6, București");

    // Instantiere obiecte folosind constructorul Comanda
    Comanda comanda1(TipColet::ColetFoarteMare, makeAWB(), "Strada Mihai Eminescu nr. 15, Apartament 3, Bloc A4, Municipiul Cluj-Napoca, Județul Cluj", "Am nevoie urgenta de acest produs, maxim 2 zile", "04/04/2024");
    Comanda comanda2(TipColet::ColetMic, makeAWB(), "Strada Revoluției nr. 10, Apartament 5, Bloc B2, Municipiul Timișoara, Județul Timiș", "Produsul să fie ambalat cu grijă", "10/05/2024");
    Comanda comanda3(TipColet::ColetMediu, makeAWB(), "Bulevardul Independenței nr. 25, Apartament 7, Bloc C3, Municipiul Iași, Județul Iași", "Livrare la ușă", "08/05/2024");
    Comanda comanda4(TipColet::ColetMic, makeAWB(), "Strada Libertății nr. 30, Apartament 2, Bloc D1, Municipiul Constanța, Județul Constanța", "Livrare doar în intervalul 14:00-18:00", "05/05/2024");
    Comanda comanda5(TipColet::ColetFoarteMare, makeAWB(), "Aleea Victoriei nr. 5, Apartament 1, Bloc E4, Municipiul Craiova, Județul Dolj", "Contactați-mă înainte de livrare", "01/05/2024");
    Comanda comanda6(TipColet::ColetMic, makeAWB(), "Bulevardul Unirii nr. 20, Apartament 4, Bloc F2, Municipiul Galați, Județul Galați", "Livrare la adresa specificată", "12/05/2024");
    Comanda comanda7(TipColet::ColetMare, makeAWB(), "Strada Dorobanților nr. 10, Apartament 6, Bloc G1, Municipiul Sibiu, Județul Sibiu", "Livrare rapidă", "11/05/2024");

    // Asocierea clientilor cu curieri
    client1.setCurier(&curier2);
    client2.setCurier(&curier2);
    client3.setCurier(&curier3);
    client4.setCurier(&curier6);
    client5.setCurier(&curier4);
    client6.setCurier(&curier5);

    // Asocierea clientilor cu comenzile
    client1.setComanda(&comanda2);
    client2.setComanda(&comanda4);
    client3.setComanda(&comanda6);
    client4.setComanda(&comanda7);
    client5.setComanda(&comanda3);
    client6.setComanda(&comanda1);

    // Instantiere suma clienti
    SistemPlata plata1(100);
    SistemPlata plata2(140);
    SistemPlata plata3(9);
    SistemPlata plata4(500);
    SistemPlata plata5(350);
    SistemPlata plata6(340);

    return 0;
}
