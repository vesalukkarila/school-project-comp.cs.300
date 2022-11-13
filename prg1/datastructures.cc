// Datastructures.cc
//
// Student name:
// Student email:
// Student number:

#include "datastructures.hh"

#include <random>

#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)


//Rakentaja
Datastructures::Datastructures():
stations_umap_(), station_vector_(), regions_umap_(), region_vector_(), all_subregions_(), all_stations_for_regions_()

{

}

//Purkaja, osoittimille purut if needed
Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}



//Toimii
unsigned int Datastructures::station_count()
{    
    return stations_umap_.size();
}




//Jos osoittimia tulee purkajan kutsu? ----------HUOM---------
//Ei mukana tehokkuuskisoissa
void Datastructures::clear_all()
{
    stations_umap_.clear();
    station_vector_.clear();
    regions_umap_.clear();
    region_vector_.clear();
    all_subregions_.clear();
    all_stations_for_regions_.clear();

}


//Toimii GUIssa
//Ei mukana tehokkuuskisoissa, mielivaltainen järjestys.
std::vector<StationID> Datastructures::all_stations()
{
    return station_vector_;

}

//Toimii GUIssa, tehokkuus epäselvä
bool Datastructures::add_station(StationID id, const Name& name, Coord xy)
{
    station_struct value = {id, name, xy, {}};          //lisätty trainset alustus {}
    if ( stations_umap_.insert({id, value}).second ){   //jos true, kts kuva jos joku vialla
        station_vector_.push_back(id);                  //attribuuttivektori jota alphabetically ja distance_increasing:ssä järjestellään
        return true;
    }
    return false;
}


//Toimii, tehokkuus epäselvä
//KUTSUTAAN USEIN, OPTIMOINTIA VAATINEE. find, contains, count,
Name Datastructures::get_station_name(StationID id)
{
    auto search = stations_umap_.find(id);  //suoraan if perään?, seuraavassa myös jos
    if (search != stations_umap_.end())
        return search->second.name;
    return NO_NAME;
}



//Toimii, tehokkuus epäselvä
//USEIN
//Jos korjattavaa niin korjaa ylläoleva myös, samat toiminnot
Coord Datastructures::get_station_coordinates(StationID id)
{
    auto search = stations_umap_.find(id);
    if (search != stations_umap_.end())
        return search->second.coordinates;
    return NO_COORD;
}




//TOIMII GUISSA, TEHOKKUUDESTA EI VIELÄ TIETOA, attribuuttivektori käytössä

//vektoriin pelkkä stationid:t ja lambdan avulla järjestää unordered mapin tiedoilla
//useampi tietorakenne map jota voi järjestää
//tietorakenne jossa osoittimia unorderemappiin
std::vector<StationID> Datastructures::stations_alphabetically()
{
    auto sort_vector = [this] (auto& a, auto& b )                       //lambda jolla...
    {return stations_umap_.at(a).name < stations_umap_.at(b).name;};

    sort(station_vector_.begin(), station_vector_.end(), sort_vector);              //..sortataan vektorin stationid:t umapin avulla

    return station_vector_;
}




//VIKAA GRADERISSA JA GUISSAKIN EI SORTTAA, KATO EUKLIDINEN JA OHJEISTUS!!!!!!!!!!!! ----------------------------
//TEHOKKUUDESTA EI VIELÄ TIETOA. attribuuttivektori käytössä
//Tässä sama mekanismi kuin yllä, jos lagaa kumpikin lagaa
std::vector<StationID> Datastructures::stations_distance_increasing()
{
    auto sort_vector = [this] (auto& a, auto& b )                                   //lambda jolla...
    {return sqrt((stations_umap_.at(a).coordinates.x)^2 + (stations_umap_.at(a).coordinates.y)^2)
                < sqrt((stations_umap_.at(b).coordinates.x)^2 + (stations_umap_.at(b).coordinates.y)^2);};

    sort(station_vector_.begin(), station_vector_.end(), sort_vector);              //..sortataan vektorin stationid:t umapin avulla

    return station_vector_;
}



//Toimii, tehokkuudesta ei tietoa
StationID Datastructures::find_station_with_coord(Coord xy)
{
    auto search = [&xy] (auto& kv ) {return kv.second.coordinates == xy;};
    auto iterator = find_if(stations_umap_.begin(), stations_umap_.end(), search);
    if (iterator != stations_umap_.end())
        return iterator->first;
    return NO_STATION;
}


//Kannattaako yllä olevalla tavalla jatkaa?, tehty kuitenkin samoin ihan vain testiks. Kato paremmin
bool Datastructures::change_station_coord(StationID id, Coord newcoord)
{
    auto search = [&id] (auto& kv ) {return kv.first == id;};
    auto iterator = find_if(stations_umap_.begin(), stations_umap_.end(), search);
    if (iterator != stations_umap_.end()) {
        iterator->second.coordinates = newcoord;
        return true;
    }

    return false;
}




//KYSYMYS: KUN ACCESSOIDAAN UMAPIN SISÄLLÄ OLEVAA SETTIÄ JA TEHDÄÄN OPERAATIOITA NIIN MITEN TEHOKKUUDET YNNÄTÄÄN???????????+

//JUNALÄHDÖT 3kpl, kaikki toimii GUIssa
//(departures after joku hyvä algoritmi, puolitushaku tms ehkä, jos normiiterointi liian kallista)
bool Datastructures::add_departure(StationID stationid, TrainID trainid, Time time)
{


    if (stations_umap_.count(stationid) == 1){                                      //jos avain olemassa
        return stations_umap_.at(stationid).trains_set.insert({time, trainid}).second; //insert.second == true, setin vuoksi tulee false jos jo olemassa
    }
    return false;
}

//Toimii GUIssa
bool Datastructures::remove_departure(StationID stationid, TrainID trainid, Time time)
{
    if (stations_umap_.count(stationid) == 1                                          //jos asema olemassa ja
            && stations_umap_.at(stationid).trains_set.count({time, trainid}) == 1){  //jos pair olemassa, tässä at koska [ ] lisää uuden umappiin jos ei olemassa ainakin joissain tapauksissa
        stations_umap_.at(stationid).trains_set.erase({time, trainid});
        return true;
    }
    return false;
}


/*toimii GUIssa */
std::vector<std::pair<Time, TrainID>> Datastructures::station_departures_after(StationID stationid, Time time)
{

    vector<std::pair<Time, TrainID>> re_vector;

    if (stations_umap_.count(stationid) != 1) {
        re_vector.push_back({NO_TIME, NO_TRAIN});
    }

    else {
    for (auto& [f,s]: stations_umap_.at(stationid).trains_set){
        if (f >= time)
            re_vector.push_back({f, s});
    }

    }
    return re_vector;
}




//REGIONIT
// We recommend you implement the operations below only after implementing the ones above

bool Datastructures::add_region(RegionID id, const Name &name, std::vector<Coord> coords)
{
    region_struct value = {id, name, coords, {}, {}, 0};    //alustetaan parent 0:ksi
    if ( regions_umap_.insert({id, value}).second ){   //jos true
        region_vector_.push_back(id);                  //vectori jossa pelkästään regionid
                                                        //TÄHÄN jos lisää region id osoituksia varten toiseen tietorakenteeseen!!!!
        return true;
    }
    return false;
}

//Toimii GUIssa
std::vector<RegionID> Datastructures::all_regions()
{
    return region_vector_;
}


//Toimii GUIssa
Name Datastructures::get_region_name(RegionID id)
{
    auto search = regions_umap_.find(id);  //suoraan if perään?, seuraavassa myös jos
    if (search != regions_umap_.end())
        return search->second.name;
    return NO_NAME;
}


//Ei omaa komentoa GUIssa, kts graderit
std::vector<Coord> Datastructures::get_region_coords(RegionID id)
{
    auto search = regions_umap_.find(id);
    if (search != regions_umap_.end())
        return search->second.coordinates_vector;
    vector<Coord> v = {NO_COORD};                   //pitää palauttaa vektori jonka ainoa alkio nocoord, ei voi siis olla aseman structista löytyvä
    return v;


}






/*Nämä 3 vaatii puutietorakenteen, osoittimia ja regionille mahdollisesti ylimääräisen tietorakenteen jossa osoittimia 2-suuntaan*/

//regionit stabiilissa tietorakenteessa jossa toisena pointteri yläalueeseen
bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid)
{
    if (regions_umap_.count(id) == 0 || regions_umap_.count(parentid) == 0) //if jompikumpi ei löydy
        return false;

    if (all_subregions_.insert(id).second) {                    //jos ei ennestään alialueena, lisäys attribuuttiin tapahtuu jos true
        regions_umap_.at(parentid).subregions.insert(id);       //lisätään parentin alialue-uusettiin
        regions_umap_.at(id).parent = parentid;             //TÄSSÄ MAHDOLLISUUS virheeseen JOS TESTATAAN VOIKO LAITTAA MONTA PARENTTIA IFFILLÄ JOTENKIN KIERTO
        return true;
        }

    return false;




    /* VANHAA VARUILTA TALLELLA, PAREMPI SYSTEEMI TUO YLLÄ OLEVA
    //loopin voi kiertää jos attribuuttina unordered_set josa jo lapsiksi lisätyt regionid:t, tsekkaa onko siellä ja lisää sinne lapsen truevaihessa
    for (auto& [key , value] : regions_umap_){                  //tehokkaampaa tapaa loopata??????
        if (value.children.count(id) == 1)                       //jos on jo alialueena
            return false;
    } */
}



//EI TOIMI
bool Datastructures::add_station_to_region(StationID id, RegionID parentid)
{

    if (regions_umap_.count(parentid) == 0 || stations_umap_.count(id) == 0)
        return false;

    if (all_stations_for_regions_.insert(id).second){ //ajatuksena: jos insertointi onnistuu attribuuttiin joka pitää kirjaa alistetuista asemista
        regions_umap_.at(parentid).stations.insert(id); //lisätään asema regionsin asemiin
        return true;
    }
    return false;                                       //jos löytyy jos lisätyistä asemista niin palauttaa false eikä lisää regionin asemiin


}





//Palauttafa kaikki alueet joihin asema kuuluu, rekursiivinen apufunkku? triviaali:parent_ptr = nullptr, muutoin lisää regionid viitevektoriin
std::vector<RegionID> Datastructures::station_in_regions(StationID id)
{
    vector<RegionID> v;
    if (all_stations_for_regions_.count(id) == 0)   //jos asema ei kuulu mihinkään alueeseen palautetaan tyhjä vektori
        return v;

    if (stations_umap_.count(id) == 0 ) {//ohjeessa "jos id:llä ei asemaa, palautetaan vektori jonka alkiona no_region??????????
        v.push_back(NO_REGION);
        return v;
    }

                                //pitää löytää region johon asema kuuluu
                                //lisätä regionid vektoriin
                                //kutsua rekursiivista
    for (auto& [key, value] : regions_umap_){

        if (value.stations.count(id) == 1){
            v.push_back(key);
            recursive_parent_regions(key, v);
            break;
        }
    }
    return v;
}


//Paluuarvo nyt bool?????
bool Datastructures::recursive_parent_regions(const RegionID &id, vector<RegionID> &v)
{
    if (regions_umap_.at(id).parent == 0)   //parent alustettu 0:ksi addregionissa
        return true;
    v.push_back(regions_umap_.at(id).parent);   //Lisää parentin vektoriin, yllä tarkistettu sen olemassa olo
    recursive_parent_regions(regions_umap_.at(id).parent, v);   //rekursiokutsu parentin id:llä
    return true;
}




// EI-PAKOLLISET Non-compulsory operations

std::vector<RegionID> Datastructures::all_subregions_of_region(RegionID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("all_subregions_of_region()");
}

std::vector<StationID> Datastructures::stations_closest_to(Coord /*xy*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("stations_closest_to()");
}

bool Datastructures::remove_station(StationID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("remove_station()");
}

RegionID Datastructures::common_parent_of_regions(RegionID /*id1*/, RegionID /*id2*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("common_parent_of_regions()");
}




