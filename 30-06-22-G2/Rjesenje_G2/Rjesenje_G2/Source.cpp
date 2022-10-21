#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <regex>
#include <exception>
#include <memory>
#include <fstream>
using namespace std;

const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U, "
"OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE "
"POMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"10.SVE NEDOZVOLJENE RADNJE TOKOM ISPITA CE BITI SANKCIONISANE!\n"
"11. ZA POTREBE TESTIRANJA, U MAINU, BUDITE SLOBODNI DODATI TESTNIH PODATAKA (POZIVA FUNKCIJA) KOLIKO GOD SMATRATE DA JE POTREBNO!\n"
"-------------------------------------------------------------------------------\n";
const char* crt = "\n-------------------------------------------\n";
enum Karakteristike { NARUDZBA, KVALITET, PAKOVANJE, ISPORUKA };

ostream& operator<<(ostream& cout, Karakteristike& k)
{
    switch (k)
    {
    case NARUDZBA: cout << "NARUDZBA";
        break;
    case KVALITET: cout << "KVALITET";
        break;
    case PAKOVANJE: cout << "PAKOVANJE";
        break;
    case ISPORUKA: cout << "ISPORUKA";
        break;
    }
    return cout;
}
template<class T1, class T2, int max>
class Rjecnik {
    T1* _elementi1[max];
    T2* _elementi2[max];
    int* _trenutno;
    bool _omoguciDupliranje;

public:
    Rjecnik(bool omoguciDupliranje = true) {
        _trenutno = new int(0);
        _omoguciDupliranje = omoguciDupliranje;
    };
    Rjecnik(const Rjecnik& obj)
    {
        _omoguciDupliranje = obj._omoguciDupliranje;
        _trenutno = new int(*obj._trenutno);
        for (size_t i = 0; i < *_trenutno; i++)
        {
            _elementi1[i] = new T1(*obj._elementi1[i]);
            _elementi2[i] = new T2(*obj._elementi2[i]);
        }
    }
    Rjecnik& operator =(const Rjecnik& obj)
    {
        if (this != &obj) {
            delete _trenutno;
            for (size_t i = 0; i < *_trenutno; i++)
            {
                delete[] _elementi1[i]; _elementi1[i] = nullptr;
                delete[] _elementi2[i]; _elementi2[i] = nullptr;
            }
            _omoguciDupliranje = obj._omoguciDupliranje;
            _trenutno = new int(*obj._trenutno);
            for (size_t i = 0; i < *_trenutno; i++)
            {
                _elementi1[i] = new T1(*obj._elementi1[i]);
                _elementi2[i] = new T2(*obj._elementi2[i]);
            }
        }
        return *this;
    }
    T1& getElement1(int lokacija)const { return *_elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return *_elementi2[lokacija]; }
    int getTrenutno() { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, const Rjecnik& obj) {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }

    void AddElement(const T1& el1, const T2& el2)
    {

        if (!_omoguciDupliranje)
            for (size_t i = 0; i < *_trenutno; i++)
            {
                if (*_elementi1[i] == el1 || *_elementi2[i] == el2)
                    throw exception("Nije dozvoljeno dupliranje elemenata.");
            }
        if (*_trenutno == max)
            throw exception("Kolekcija je puna.");
        _elementi1[*_trenutno] = new T1(el1);
        _elementi2[*_trenutno] = new T2(el2);
        (*_trenutno)++;
    }

    Rjecnik<int, int, max> RemoveAt(int lokacija)
    {
        Rjecnik<int, int, max> temp;
        temp.AddElement(*_elementi1[lokacija], *_elementi2[lokacija]);
        for (size_t i = lokacija; i < *_trenutno - 1; i++)
        {
            _elementi1[i] = _elementi1[i + 1];
            _elementi2[i] = _elementi2[i + 1];
        }
        (*_trenutno)--;
        return temp;
    }
};
class Datum {
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
    }
    Datum(const Datum& d)
    {
        _dan = new int(*d._dan);
        _mjesec = new int(*d._mjesec);
        _godina = new int(*d._godina);
    }
    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }
};

char* GetNizKaraktera(const char* str)
{
    if (str == nullptr)
        return nullptr;
    int vel = strlen(str) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, str);
    return temp;
}
class ZadovoljstvoKupca {
    char* _komentar;
    //uz komentar, kupci mogu ocijeniti svaku od karakteristika proizvoda, a int se odnosi na ocjenu u rasponu od 1 - 10.
    //onemoguciti dupliranje karakteristika tj. svaki karakteristika se moze ocijeniti samo jednom...u suprotnom baciti objekat tipa exception
    Rjecnik<Karakteristike, int, 4>* _ocjeneKarakteristika;
public:
    ZadovoljstvoKupca(const char* komentar = "") {
        //kreirajte funkciju GetNizKaraktera ili na drugi adekvatan nacin izvrsite inicijalizaciju pokazivaca
        _komentar = GetNizKaraktera(komentar);
        _ocjeneKarakteristika = nullptr;
    }
    ZadovoljstvoKupca(const ZadovoljstvoKupca& obj) {
        _komentar = GetNizKaraktera(obj._komentar);
        _ocjeneKarakteristika = new  Rjecnik<Karakteristike, int, 4>(*obj._ocjeneKarakteristika);
    }
    ZadovoljstvoKupca& operator= (const ZadovoljstvoKupca& obj) {
        if (this != &obj)
        {
            delete[] _komentar;
            delete _ocjeneKarakteristika;
            _komentar = GetNizKaraktera(obj._komentar);
            _ocjeneKarakteristika = new  Rjecnik<Karakteristike, int, 4>(*obj._ocjeneKarakteristika);
        }
        return *this;
    }
    ~ZadovoljstvoKupca() {
        delete[] _komentar; _komentar = nullptr;
        delete _ocjeneKarakteristika; _ocjeneKarakteristika = nullptr;
    }
    char* GeKomentar() { return _komentar; }
    Rjecnik<Karakteristike, int, 4>* GetOcjeneKarakteristika() const { return _ocjeneKarakteristika; }

    friend ostream& operator<<(ostream& cout, const ZadovoljstvoKupca& z)
    {
        cout << "Komentar: " << z._komentar << endl;
        for (size_t i = 0; i < z._ocjeneKarakteristika->getTrenutno(); i++)
        {
            cout << "\nKarakteristika: " << z._ocjeneKarakteristika->getElement1(i) << "\tOcjena: " << z._ocjeneKarakteristika->getElement2(i) << endl;
        }
        return cout;
    }

    void AddOcjenuKarakteristike(Karakteristike k, int ocjena)
    {
        if (_ocjeneKarakteristika == nullptr)
            _ocjeneKarakteristika = new Rjecnik<Karakteristike, int, 4>;
        if (_ocjeneKarakteristika->getTrenutno() != 0)
        {

            for (size_t i = 0; i < _ocjeneKarakteristika->getTrenutno(); i++)
            {
                if (_ocjeneKarakteristika->getElement1(i) == k)
                    throw exception("\nKarakteristika je vec ocijenjena.");
            }
        }
        _ocjeneKarakteristika->AddElement(k, ocjena);
    }
};

bool ValidirajJedinstveniKod(string br)
{
    return regex_match(br, regex("\\[[A-Z]{1,2}\\][0-9]{3,4}[-]?\\s?\\{[a-z]{2}\\}"));
}
unique_ptr<char[]> GetNisKarakteraUNPTR(const char* str)
{
    if (str == nullptr)
        return nullptr;
    int vel = strlen(str) + 1;
    unique_ptr<char[]> temp(new char[vel]);
    strcpy_s(temp.get(), vel, str);
    return temp;
}
class Kupac {
    unique_ptr<char[]>_imePrezime;
    string _emailAdresa;
    string _jedinstveniKod;
public:
    Kupac(const char* imePrezime, string emailAdresa, string jedinstveniKod) {
        _imePrezime = GetNisKarakteraUNPTR(imePrezime);
        _emailAdresa = emailAdresa;
        _jedinstveniKod = ValidirajJedinstveniKod(jedinstveniKod) ? jedinstveniKod : "NOT VALID";
    }
    Kupac(const Kupac& obj) {
        _imePrezime = GetNisKarakteraUNPTR(obj._imePrezime.get());
        _emailAdresa = obj._emailAdresa;
        _jedinstveniKod = obj._jedinstveniKod;
    }
    string GetEmail() { return _emailAdresa; }
    string GetJedinstveniKod() { return _jedinstveniKod; }
    char* GetImePrezime() { return _imePrezime.get(); }

    friend ostream& operator<< (ostream& COUT, const Kupac& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._jedinstveniKod << endl;
        return COUT;
    }
};

mutex m;
class Kupovina {
    Datum _datumKupovine;
    //jedna kupovina moze podrazumjevati isporuku proizvoda vecem broju kupaca
    //onemoguciti dodavanje kupaca sa istom email adresom ili jedinstvenim kodomu okviru jedne kupovine
    vector<Kupac> _kupaci;
    //za svaku kupovinu se moze ostaviti samo jedan komentar odnosno ocjena zadovoljstva, bez obzirana broj kupaca
    ZadovoljstvoKupca _zadovoljstvoKupca;
    void posaljiMail(string mail, float prosjek)
    {
        m.lock();
        cout << "To: " << mail << endl;
        cout << "Prosjek: " << prosjek << endl;
        m.unlock();
    }

    float Prosjek() const
    {
        float prosjek = 0;
        if (_zadovoljstvoKupca.GetOcjeneKarakteristika()->getTrenutno() == 0)
            return prosjek;
        for (int i = 0; i < _zadovoljstvoKupca.GetOcjeneKarakteristika()->getTrenutno(); i++)
        {
            prosjek += _zadovoljstvoKupca.GetOcjeneKarakteristika()->getElement2(i);
        }
        return float(prosjek / _zadovoljstvoKupca.GetOcjeneKarakteristika()->getTrenutno());
    }


public:
    Kupovina(Datum& datum, Kupac& kupac) : _datumKupovine(datum) {
        _kupaci.push_back(kupac);
    }
    Kupovina(const Kupovina& obj) : _datumKupovine(obj._datumKupovine), _kupaci(obj._kupaci), _zadovoljstvoKupca(obj._zadovoljstvoKupca)
    {
    }
    vector<Kupac>& GetKupci() { return _kupaci; }
    ZadovoljstvoKupca GetZadovoljstvoKupca() { return _zadovoljstvoKupca; }
    friend ostream& operator<< (ostream& COUT, Kupovina& obj) {
        COUT << crt << "Kupovina " << obj._datumKupovine << " za kupce: " << endl;
        for (size_t i = 0; i < obj._kupaci.size(); i++)
        {
            COUT << "\t" << i + 1 << "." << obj._kupaci[i];
        }
        cout << crt << "Zadovoljstvo kupca: " << endl << obj._zadovoljstvoKupca << crt;
        return COUT;
    }

    bool AddKupca(Kupac& k)
    {
        for (auto& kupac : _kupaci)
        {
            if (kupac.GetEmail() == k.GetEmail() || kupac.GetJedinstveniKod() == k.GetJedinstveniKod())
                return false;
        }
        _kupaci.push_back(k);
        return true;
    }

    void SetZadovoljstvoKupca(ZadovoljstvoKupca z)
    {
        _zadovoljstvoKupca = z;
        int brojac = 0;
        for (size_t i = 0; i < z.GetOcjeneKarakteristika()->getTrenutno(); i++)
        {
            if (z.GetOcjeneKarakteristika()->getElement2(i) < 5)
                brojac++;
        }
        if (brojac >= 2)
        {
            for (auto& k : _kupaci)
            {
                thread t(&Kupovina::posaljiMail, this, k.GetEmail(), this->Prosjek());
                t.join();
            }
        }
    }

    tuple<int, int, int> GetBrojZnakova(const char* putanja)
    {
        ifstream fajl;
        int razmak = 0;
        int M = 0;
        int V = 0;
        string s;
        char znak;
        while (fajl.get(znak))
        {
            string s(1, znak);
            if (s == " ")
                razmak++;
            else if (regex_search(s, regex("[A-Z]")))
                V++;
            else if (regex_search(s, regex("[a-z]")))
                M++;
        }
        tuple<int, int, int> temp = make_tuple(razmak, V, M);
        return temp;
    }
};
const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> \Nabrojite i ukratko pojasnite osnovne ios modove koji se koriste u radu sa fajlovima?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Pojasnite prednosti i nedostatke visestrukog nasljedjivaja, te ulogu virtualnog nasljedjivanja u tom kontekstu?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}

void main() {

    cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();

    Datum datum30062022(30, 6, 2022);

    const int rijecnikTestSize = 9;
    Rjecnik<int, int, rijecnikTestSize> rijecnik1(false);

    for (int i = 0; i < rijecnikTestSize - 1; i++)
        rijecnik1.AddElement(i, i);//dodaje vrijednosti u rijecnik

    try {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement treba baciti objekat tipa exception
        rijecnik1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    rijecnik1.AddElement(9, 9);

    try
    {
        //ukoliko je rijecnik popunje, metoda AddElement treba baciti objekat tipa exception
        rijecnik1.AddElement(10, 10);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }

    cout << rijecnik1 << crt;

    // /* metoda RemoveAt treba da ukloni i vrati (kao povratnu vrijednost)clanoverijecnika koji se nalaze na lokaciji definisanoj prvim parametrom.
    // * Nakon izvrsenja metode RemoveAt, objekat rijecnik1 bi trebao posjedovati sljedeci sadrzaj:
    // * 0  0
    // * 1  1
    // * 3  3
    // * 4  4
    // * ....
    // *
    // * a objekat rijecnik2 samo jedan par:
    // *  2  2
    // */
    Rjecnik<int, int, rijecnikTestSize> rijecnik2 = rijecnik1.RemoveAt(2);
    cout << rijecnik2 << crt;


    // /*
    // * za validaciju broja pasosa koristiti funkciju ValidirajBrojPasosa koja treba, koristeci regex, osigurati postivanje
    // sljedeceg formata:
    // - pocetak sadrzi jedan ili dva velika slova unutar uglastih zagrada
    // - nakon toga slijede tri ili cetiri broja
    // - nakon toga moze, a ne mora, doci znak crtica (-) ili razmak ( )
    // - nakon toga slijede dva mala slova unutar viticastih zagrada

    // pomenutu funkciju iskoristiti u konstruktoru klase Kupac, te ukoliko jedinstveni kod  nije u validnom formatu onda njegova vrijednost treba biti postavljena na NOT VALID
    // */

    if (ValidirajJedinstveniKod("[BH]235-{mo}"))
        cout << "Jedinstveni kod validan" << endl;
    if (ValidirajJedinstveniKod("[MO]235{sa}"))
        cout << "Jedinstveni kod validan" << endl;
    if (ValidirajJedinstveniKod("[B]2356 {ih}"))
        cout << "Jedinstveni kod validan" << endl;
    if (!ValidirajJedinstveniKod("[s]2356{ih}"))
        cout << "Jedinstveni kod NIJE validan" << endl;
    if (!ValidirajJedinstveniKod("[BH]2356{h}"))
        cout << "Jedinstveni kod NIJE validan" << endl;
    if (!ValidirajJedinstveniKod("BH2356{ih}"))
        cout << "Jedinstveni kod NIJE validan" << endl;


    Kupac denis("Denis Music", "denis@fit.ba", "[BH]235-{mo}");
    Kupac jasmin("Jasmin Azemovic", "jasmin@fit.ba", "[MO]235{sa}");
    Kupac adel("Adel Handzic", "adel@edu.fit.ba", "[B]2356 {ih}");
    Kupac jedinstveniKodNotValid("Ime Prezime", "korisnik@klix.ba", "BH2356{ih}");//_jedinstveniKod = NOT VALID

   // //kupovini  se prilikom kreiranja mora dodijeliti kupac koji je kreator kupovine
    Kupovina kupovina(datum30062022, denis);
    if (kupovina.AddKupca(jasmin))
        cout << "Kupac uspjesno dodan!";

    ZadovoljstvoKupca zadovoljstvoKupca("Nismo pretjerano zadovoljni kvalitetom, a ni pakovanjem");
    zadovoljstvoKupca.AddOcjenuKarakteristike(NARUDZBA, 7);
    zadovoljstvoKupca.AddOcjenuKarakteristike(KVALITET, 4);

    try {
        zadovoljstvoKupca.AddOcjenuKarakteristike(KVALITET, 4); //kakrakteristika je vec ocjenjena
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }

    zadovoljstvoKupca.AddOcjenuKarakteristike(PAKOVANJE, 3);
    zadovoljstvoKupca.AddOcjenuKarakteristike(ISPORUKA, 6);

    // //u okviru kupovine postavlja vrijednost atributa _zadovoljstvoKupca
    kupovina.SetZadovoljstvoKupca(zadovoljstvoKupca);

    // //ukoliko se kupovini  doda zadovoljstvo koji sadrzi najmanje dvije karakteristike sa ocjenom manjom od 5, svim kupcima, 
    // //koji su dodati u kupovinu, u zasebnom thread-u, se salje email sa sljedecim sadrzajem:
    ///*
    //    To: denis@fit.ba;jasmin@fit.ba;
    //    Subject: Informacija

    //    Postovani,

    //    Zaprimili smo Vase ocjene, a njihova prosjecna vrijednost je X.X.
    //    Zao nam je zbog toga, te ce Vas u najkracem periodu kontaktirati nasa Sluzba za odnose sa kupcima.

    //    Nadamo se da cete i dalje poslovati sa nama
    //    Puno pozdrava
    //*/

    ////ispisuje sve podatke o kupovini, kupcima, komentar, ocjene pojedinih karakteristika i prosjecnu ocjenu.
    cout << kupovina << endl;
    // /* Primjer ispisa:
    //    -------------------------------------------
    //    Kupovina 30.6.2022 za kupce:
    //            1.Denis Music denis@fit.ba [BH]235-{mo}
    //            2.Jasmin Azemovic jasmin@fit.ba [MO]235{sa}
    //    -------------------------------------------
    //    Zadovoljstvo kupca:
    //    Nismo pretjerano zadovoljni kvalitetom, a ni pakovanjem.
    //          NARUDZBA(7)
    //          KVALITET(4)
    //          PAKOVANJE(3)
    //          ISPORUKA(6)
    //    -------------------------------------------
    //    Prosjecna ocjena -> 5
    //*/

    Kupovina kupovinaSaAdelom = kupovina;
    if (kupovinaSaAdelom.AddKupca(adel))
        cout << "Kupac uspjesno dodan!";
    if (!kupovinaSaAdelom.AddKupca(denis))
        cout << "Kupac je vec dodan!";

    cout << kupovinaSaAdelom << endl;

    // /*metoda GetBrojZnakova treba prebrojati koliko se unutar fajla, cije ime je proslijedjeno kao parametar, nalazi: velikih slova, malih slova i razmaka..*/
    tuple<int, int, int> brojac = kupovinaSaAdelom.GetBrojZnakova("sadrzaj.txt");
    cout << "Velikih slova: " << get<0>(brojac) << endl;
    cout << "Malih slova: " << get<1>(brojac) << endl;
    cout << "Razmaka: " << get<2>(brojac) << endl;
    // /*
    // ukolikoo je sadrzaj fajla npr. "Denis Music" povratne vrijednosti metode GetBrojZnakova bi trebale biti 2 8 1. za potrebe testiranja kreirajte fajl sa zeljenim sadzajem
    // */

    cin.get();
    system("pause>0");
}



