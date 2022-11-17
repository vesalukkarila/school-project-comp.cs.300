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


//Rakentaja
Datastructures::Datastructures():
stations_umap_(), station_vector_(), coord_as_key_map_(),
regions_umap_(), region_vector_(),
all_subregions_(), all_stations_for_regions_()

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




// ----------HUOM---------
//Ei mukana tehokkuuskisoissa
void Datastructures::clear_all()
{
    stations_umap_.clear();
    station_vector_.clear();
    coord_as_key_map_.clear();

    regions_umap_.clear();
    region_vector_.clear();

    all_subregions_.clear();
    all_stations_for_regions_.clear();

}


//Toimii GUIssa
//"Excellent! Your code appears to perform better than the reference implementation. Well done. (10/10)"
std::vector<StationID> Datastructures::all_stations()
{
    return station_vector_;

}


//Toimii GUIssa, tehokkuus epäselvä
bool Datastructures::add_station(StationID id, const Name& name, Coord xy)
{
    station_struct value = {id, name, xy, {}, NO_REGION};       //Alustettu region_id no_regioniksi
    if ( stations_umap_.insert({id, value}).second ){   //lisäys umappiin
        station_vector_.push_back(id);                  //lisäys vektoriin
        coord_as_key_map_.insert({xy, id});
        return true;
    }
    return false;
}


//Toimii
//Tehokkuus: "The performance of your code is close to the reference implementation. Well done. (10/10)"
//KUTSUTAAN USEIN, OPTIMOINTIA VAATINEE. find, contains, count,
Name Datastructures::get_station_name(StationID id)
{
    auto search = stations_umap_.find(id);
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




//TOIMII
//Tehokkuus:
//"Your code appears to have O(n log n) complexity which is the minimum required.  (3/10)"----------------------------------
//"Perftest Timeout during performance tests for stations_distance_increasing. Your code needs optimization.--------"
//sama mekanismi kuin alla, jos lagaa kumpikin lagaa

//JÄRJESTÄNKÖ VEKTORIA JOSKUS TARPEETTOMASTI-----

std::vector<StationID> Datastructures::stations_alphabetically()
{
    auto sort_vector = [this] (auto& a, auto& b )                       //lambda jolla...
    {return stations_umap_.at(a).name < stations_umap_.at(b).name;};

    sort(station_vector_.begin(), station_vector_.end(), sort_vector);              //..sortataan vektorin stationid:t umapin nimien avulla

    return station_vector_;
}




//Toimii graderissa
//Tehokkuus?
//"Your code appears to have O(n log n) complexity which is the minimum required.  (3/10)"------------------------------------
//"Perftest: Timeout during performance tests for stations_distance_increasing. Your code needs optimization."
//Tässä sama mekanismi kuin yllä, jos lagaa kumpikin lagaa

//JÄRJESTÄNKÖ VEKTORIA JOSKUS TARPEETTOMASTI--------
//ajatus: if lause returniin, euklidinen miniehto(?), tsekkaa kriteerit etäisyysehdoista
//JOS KÄYTTÄÄ COORDASKAYUMAPPIA JÄRJESTÄMISEEN, edelleen timout
std::vector<StationID> Datastructures::stations_distance_increasing()
{
    /*
    //auto sort_by_coord = [](){}
    auto sort_vector = [this] (auto& a, auto& b )                                   //lambda jolla...
    {return sqrt((stations_umap_.at(a).coordinates.x)^2 + (stations_umap_.at(a).coordinates.y)^2)
                < sqrt((stations_umap_.at(b).coordinates.x)^2 + (stations_umap_.at(b).coordinates.y)^2);}; //

    sort(station_vector_.begin(), station_vector_.end(), sort_vector);              //..sortataan vektorin stationid:t umapin koord. avulla

    return station_vector_;
    */
    //uutta coordaskeymap hyödyntäen, EDELLEEN TIMEOUT PERFTESTISSÄ??????????????????????????????
    vector<StationID> re_vector;
    re_vector.reserve(coord_as_key_map_.size());
    for (auto& key : coord_as_key_map_){
        re_vector.push_back(key.second);
    }
    return re_vector;
}



//Toimii
//Tehokkuus:
//"Excellent! Your code appears to perform better than the reference implementation. Well done. (10/10)"
StationID Datastructures::find_station_with_coord(Coord xy)
{
    /*
    auto search = [&xy] (auto& kv ) {return kv.second.coordinates == xy;};
    auto iterator = find_if(stations_umap_.begin(), stations_umap_.end(), search);
    if (iterator != stations_umap_.end())
        return iterator->first;
        */


    /*eka parannusyritys, edelleen 6/10
    for (auto&[k,v]:stations_umap_){
        if(v.coordinates == xy)
            return k;
    }
    */

    //toinen yritys iteroiden, vieläkin 6/10, looppi/iteraatiooptimointi!?!?!, for_each, videoneuvot, harjoitustehtävät
    /*
     * for(auto it = stations_umap_.begin(); it != stations_umap_.end(); ++it){

        if(it->second.coordinates == xy)
            return it->first;
    }
    */

    //3 yritys, coordaskeyumap lisätty attribuutiksi
    auto search = coord_as_key_map_.find(xy);      //eli etsii coordaskeyumapista xy jos löytyy palauttaa hkuormana olevan stationid:n
    if (search != coord_as_key_map_.end())
        return search->second;
    return NO_STATION;
}



//Toimii
//Tehokkuus 10/10
bool Datastructures::change_station_coord(StationID id, Coord newcoord)
{

    if (auto it = stations_umap_.find(id); it != stations_umap_.end()){ //jos löytyy stumapista, löytyy myös coordumapista...
        Coord old_coordinate = it->second.coordinates;          //vanha koord talteen coordaskeyumapista poistoa varten
        it->second.coordinates = newcoord;      //päätietorakenne
        coord_as_key_map_.erase(old_coordinate);   //vanhan poisto
        coord_as_key_map_.insert({newcoord, id});  //.. ja coordaskeyumappiin muutos myös

        return true;
    }


    return false;
}




//JUNALÄHDÖT 3kpl, kaikki toimii GUIssa
//Toimii
//Tehokkuus? "The performance of your code is close to the reference implementation. Well done. (10/10)"
bool Datastructures::add_departure(StationID stationid, TrainID trainid, Time time)
{


    if (stations_umap_.count(stationid) == 1){
        return stations_umap_.at(stationid).trains_set.insert({time, trainid}).second;
    }
    return false;
}


//Toimii
//Tehokkuus:
//"The performance of your code is close to the reference implementation. Well done. (10/10)"
bool Datastructures::remove_departure(StationID stationid, TrainID trainid, Time time)
{
    if (stations_umap_.count(stationid) == 1
            && stations_umap_.at(stationid).trains_set.count({time, trainid}) == 1){
        stations_umap_.at(stationid).trains_set.erase({time, trainid});
        return true;
    }
    return false;
}


//Toimii
//Tehokkuus:
//"The performance of your code is close to the reference implementation. Well done. (10/10)"
std::vector<std::pair<Time, TrainID>> Datastructures::station_departures_after(StationID stationid, Time time)
{

    vector<std::pair<Time, TrainID>> re_vector;

    if (stations_umap_.count(stationid) != 1) {
        re_vector.push_back({NO_TIME, NO_TRAIN});
    }

    else {
    for (auto& [departure_time, train]: stations_umap_.at(stationid).trains_set){
        if (departure_time >= time)
            re_vector.push_back({departure_time, train});
    }

    }
    return re_vector;
}




//REGIONIT

//Toimii
//Tehokkuus?
bool Datastructures::add_region(RegionID id, const Name &name, std::vector<Coord> coords)
{
    region_struct value = {id, name, coords, {}, {}, NO_REGION};    //alustetaan parentregion no_regioniksi
    if ( regions_umap_.insert({id, value}).second ){   //jos true
        region_vector_.push_back(id);                  //vectori jossa pelkästään regionid
                                                        //TÄHÄN jos lisää region id osoituksia varten toiseen tietorakenteeseen!!!!
        return true;
    }
    return false;
}


//Toimii
//Tehokkuus?
std::vector<RegionID> Datastructures::all_regions()
{
    return region_vector_;
}


//Toimii
//Tehokkuus: "The performance of your code is close to the reference implementation. Well done. (10/10)"
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
    vector<Coord> v = {NO_COORD};
    return v;


}


//Toimii
bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid)
{
    if (regions_umap_.count(id) == 0 || regions_umap_.count(parentid) == NO_REGION)
        return false;

    if (all_subregions_.insert(id).second) {
        regions_umap_.at(parentid).subregions.insert(id);
        regions_umap_.at(id).parent = parentid;
        return true;
        }

    return false;
}



//Toimii
//Tehokkuus?
bool Datastructures::add_station_to_region(StationID id, RegionID parentid)
{

    if (regions_umap_.count(parentid) == 0 || stations_umap_.count(id) == 0)
        return false;

    if (all_stations_for_regions_.insert(id).second){
        regions_umap_.at(parentid).stations.insert(id);     //asema sijoitetaan regionin "lapsiin"
        stations_umap_.at(id).parent_region = parentid;     //stationumappiin aseman struct-hyötykuormassa region aseman "vanhemmaksi"
        return true;
    }
    return false;


}

/*station structiin lisäkenttä <regionid>parentregion DONE,
 * tämän huomiointi kun add_station parametrina DONE,
 * add_station_to_region parentregionille parentid DONE
 * station_in_region for loopin muutto. rekursiivista voinee käyttää sellaisenaan*/

//Toimii
//Tehokkuus:
//"Your code performs worse than O(n log n). No points. (0/10)" ---------------------------------------------------------------------
//parent stationstructiin
std::vector<RegionID> Datastructures::station_in_regions(StationID id)
{
    vector<RegionID> re_vector;
    if (all_stations_for_regions_.count(id) == 0)   //jos ei löydy attribuutista johon lisätty kaikki regioneille alistetut asemat
        return re_vector;                           //palautetaan tyhjä vektori

    if (stations_umap_.count(id) == 0 ) {           //jos id:llä ei ole asemaa palautetaan no_region
        re_vector.push_back(NO_REGION);
        return re_vector;
    }
/* VANHA RATKAISU ennen stationstructin muuttamista
    for (auto& [key, value] : regions_umap_){

        if (value.stations.count(id) == 1){
            re_vector.push_back(key);
            recursive_parent_regions(key, re_vector);
            break;
        }
    }
    */
    re_vector.push_back(stations_umap_.at(id).parent_region);
    recursive_parent_regions(stations_umap_.at(id).parent_region, re_vector);   //haetaaan station umapista useasti sama tieto->muuttujaan?

    return re_vector;
}


//Apufunktio ylläolevalle
//Toimii
//Tehokkuus ja miten ynnätään kutsuvan funkun kanssa yhteen?
void Datastructures::recursive_parent_regions(const RegionID &id, vector<RegionID> &re_vector)
{
    if (regions_umap_.at(id).parent == NO_REGION)   //parent alustettu no_regioniksi add_regionissa
        return;
    re_vector.push_back(regions_umap_.at(id).parent);   //Lisää parentin vektoriin, yllä tarkistettu sen olemassa olo
    recursive_parent_regions(regions_umap_.at(id).parent, re_vector);   //rekursiokutsu parentin id:llä
    return;
}





// NON-COMPULSORY

//Pitäs onnistua, alialueet löytyy regions_umap.at(id).subregions (usetistä)
//suoraan rekursio funkkuun? joku parempi tapa kuin loopata jokaista subregionsista löytyvää, kaikki ne on käytävä läpi, lineaarista hommaa kai??
//NlogN veikkaan, rekursion vuoksi
std::vector<RegionID> Datastructures::all_subregions_of_region(RegionID id)
{
    vector<RegionID> re_vector;
    recursive_subregions_to_regions(id, re_vector);
    return re_vector;
}

//Apufunkku yllä olevalle
void Datastructures::recursive_subregions_to_regions(const RegionID &id, vector<RegionID> &re_vector)
{
    if (regions_umap_.at(id).subregions.empty())
        return;
    for (auto& value : regions_umap_.at(id).subregions){
        re_vector.push_back(value);
        recursive_subregions_to_regions(value, re_vector);
    }
    return;
}


std::vector<StationID> Datastructures::stations_closest_to(Coord /*xy*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("stations_closest_to()");
}


//Kato mistä kaikista pitää poistaa
bool Datastructures::remove_station(StationID id)
{
    if (stations_umap_.count(id) == 0)
        return false;
    stations_umap_.erase(id);

    //Jos löytyy tietorakenteesta johon on listattu kaikki alueille alistetut asemat..
    if (all_stations_for_regions_.count(id) == 1){
        //..poistetaan..
        all_stations_for_regions_.erase(id);
        //..jolloin löytyy myös jonkin region tietorakenteen hyötykuormasta.stations
        for ( auto& [k,v] : regions_umap_){
            if ( v.stations.count(id) == 1){
                v.stations.erase(id);
            }
        }
    }
    return true;
}



RegionID Datastructures::common_parent_of_regions(RegionID /*id1*/, RegionID /*id2*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("common_parent_of_regions()");
}




