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



Datastructures::Datastructures():
stations_umap_(), station_vector_()

{

}


Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}



//Toimii
unsigned int Datastructures::station_count()
{    
    return stations_umap_.size();
}




//LISÄÄ TÄHÄN REGIONIN TYHJENNYS
//Ei mukana tehokkuuskisoissa
void Datastructures::clear_all()
{
    stations_umap_.clear();
    station_vector_.clear();
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
    station_struct value = {id, name, xy, {}};      //lisätty trainset alustus {}
    bool insert_ok = stations_umap_.insert({id, value}).second; //second palauttaa booleanin jos onnistui
    station_vector_.push_back(id);  //attribuuttivektori jota alphabetically ja distance_increasing:ssä järjestellään
    if ( insert_ok )
        return true;
    return false;
}


//Toimii, tehokkuus epäselvä
//KUTSUTAAN USEIN, OPTIMOINTIA VAATINEE. find, contains, count,
//Sama minkä ottaa niin const ja & jottei kopioi
//Tarviiko attribuutti_umap olla viite, voiko olla, kopioiko koko attribuutin kun käyttää algoritmia jos ei ole &?????
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





// We recommend you implement the operations below only after implementing the ones above


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




//VIKAA GRADERISSA JA GUISSAKIN EI SORTTAA, KATO EUKLIDINEN JA OHJEISTUS!!!!!!!!!!!!
//TEHOKKUUDESTA EI VIELÄ TIETOA. attribuuttivektori käytössä
//Tässä sama mekanismi kuin yllä, jos lagaa kumpikin lagaa
std::vector<StationID> Datastructures::stations_distance_increasing()
{
    auto sort_vector = [this] (auto& a, auto& b )                                   //lambda jolla...
    {return stations_umap_.at(a).coordinates < stations_umap_.at(b).coordinates;};

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


/*toimii GUIssa, kun setistä ei löydy myöhäsempää junaa, palauttaa "No such station (NO_TIME, NO_TRAIN returned)"
Osaa lajitella aseman mukaan jos time yhtäsuuri*/
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
    if (re_vector.size() == 0)
        re_vector.push_back({NO_TIME, NO_TRAIN});
    }
    return re_vector;
}




//REGIONIT
// We recommend you implement the operations below only after implementing the ones above

bool Datastructures::add_region(RegionID /*id*/, const Name &/*name*/, std::vector<Coord> /*coords*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("add_region()");
}

std::vector<RegionID> Datastructures::all_regions()
{
    // Replace the line below with your implementation
    throw NotImplemented("all_regions()");
}

Name Datastructures::get_region_name(RegionID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("get_region_name()");
}

std::vector<Coord> Datastructures::get_region_coords(RegionID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("get_region_coords()");
}

bool Datastructures::add_subregion_to_region(RegionID /*id*/, RegionID /*parentid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("add_subregion_to_region()");
}

bool Datastructures::add_station_to_region(StationID /*id*/, RegionID /*parentid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("add_station_to_region()");
}

std::vector<RegionID> Datastructures::station_in_regions(StationID /*id*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("station_in_regions()");
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
