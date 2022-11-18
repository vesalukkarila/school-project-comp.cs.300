// Datastructures.cc
//
// Student name: Vesa Lukkarila
// Student email: vesa.lukkarila@tuni.fi
// Student number: 150372523

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


/**
 * @brief Datastructures::Datastructures shows attributes
 */
Datastructures::Datastructures():
stations_umap_(), station_vector_(), coord_as_key_map_(), station_vector_sorted_(false),
regions_umap_(), region_vector_(),
all_subregions_(), all_stations_for_regions_()

{

}

/**
 * @brief Datastructures::~Datastructures no implemetation here
 */
Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}


/**
 * @brief Datastructures::station_count counts the number of stations
 * @return number of stations
 */
unsigned int Datastructures::station_count()
{    
    return stations_umap_.size();
}



/**
 * @brief Datastructures::clear_all clears all datastructures used
 */
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



/**
 * @brief Datastructures::all_stations this function´s work has been done in add station
 * @return all station-id:s in a unsorted vector
 */
std::vector<StationID> Datastructures::all_stations()
{
    return station_vector_;
}


//tekstiä sisällä -------------------------------------------------------------
/**
 * @brief Datastructures::add_station adds data about stations in necessary datastructures
 * @param id, string, id of the station, unique for each station
 * @param name, string, name of the station, not-unique
 * @param xy, type Coord (see .hh file), station coordinates
 * @return true if adding station to datastructure accomplished, otherwise false
 */
bool Datastructures::add_station(StationID id, const Name& name, Coord xy)
{
    station_struct value = {name, xy, {}, NO_REGION};
    if ( stations_umap_.insert({id, value}).second ){           // päätietorakenne asemille
        station_vector_.push_back(id);                          // tietorakenne palautuksia varten, kaikki asemat
        coord_as_key_map_.insert({xy, id});                     // find_station_with_coordia varten
        station_vector_sorted_ = false;                         // stations_alphabetically varten kirjanpito
        return true;
    }
    return false;
}



/**
 * @brief Datastructures::get_station_name searches for station by id and its name
 * @param id, string, id of the station, unique id of the station
 * @return string, stations name if station is found, otherwise NO_NAME(see .hh file)
 */
Name Datastructures::get_station_name(StationID id)
{
    auto search = stations_umap_.find(id);
    if (search != stations_umap_.end())
        return search->second.name;
    return NO_NAME;
}



/**
 * @brief Datastructures::get_station_coordinates searches for station by id and its coordinates
 * @param id, string, id of the station, unique for each station
 * @return Coord (see .hh file), coordinates for station if station is found, otherwise NO_COORD(see .hh file)
 */
Coord Datastructures::get_station_coordinates(StationID id)
{
    auto search = stations_umap_.find(id);
    if (search != stations_umap_.end())
        return search->second.coordinates;
    return NO_COORD;
}



/**
 * @brief Datastructures::stations_alphabetically sorts stations in alphabetical order by their names
 * @return all station-id:s in a vector sorted by their names
 */
std::vector<StationID> Datastructures::stations_alphabetically()
{
    if (station_vector_sorted_ == false){
        auto sort_vector = [this] (auto& a, auto& b )
        {return stations_umap_.at(a).name < stations_umap_.at(b).name;};

        sort(station_vector_.begin(), station_vector_.end(), sort_vector);
        station_vector_sorted_ = true;
    }

    return station_vector_;
}




//HÄN EI TOIMI KUN LAITOIN KOORDINAATIT MAPPIIN, LUULIN ETTÄ JÄRJESTÄÄ SIELLÄ OIKEIN AUTOMAATTISESTI------------------
/**
 * @brief Datastructures::stations_distance_increasing copies station-id:s from map to a vector,
 * stations are allready in ascending order by their coordinates in a map
 * @return all station-id:s in a vector sorted in ascending order byt coordinates
 */
std::vector<StationID> Datastructures::stations_distance_increasing()
{
/*
    vector<StationID> re_vector;
    re_vector.reserve(coord_as_key_map_.size());
    for (auto& key : coord_as_key_map_){
        re_vector.push_back(key.second);
    }
    return re_vector;

    */


    //if stationvectorsortedbycoordinates = true
    auto sort_vector = [this] (auto& a, auto& b )
    {return sqrt((stations_umap_.at(a).coordinates.x)^2 + (stations_umap_.at(a).coordinates.y)^2)
                < sqrt((stations_umap_.at(b).coordinates.x)^2 + (stations_umap_.at(b).coordinates.y)^2);};

    sort(station_vector_.begin(), station_vector_.end(), sort_vector);
    station_vector_sorted_ = false;


    return station_vector_;



    /*
    auto sort_vector = [this] (auto& a, auto& b )                                   //lambda jolla...
       {return sqrt((stations_umap_.at(a).coordinates.x)^2 + (stations_umap_.at(a).coordinates.y)^2)
                   < sqrt((stations_umap_.at(b).coordinates.x)^2 + (stations_umap_.at(b).coordinates.y)^2);}; //

       sort(station_vector_.begin(), station_vector_.end(), sort_vector);
       */

}



/**
 * @brief Datastructures::find_station_with_coord checks if station is found with given coordinates
 * @param xy, Coord (see .hh file), coordinates of the searched station
 * @return string, stations id if station found with coordinates, otherwise NO_STATION(see .hh file)
 */
StationID Datastructures::find_station_with_coord(Coord xy)
{
    auto search = coord_as_key_map_.find(xy);
    if (search != coord_as_key_map_.end())
        return search->second;
    return NO_STATION;
}



/**
 * @brief Datastructures::change_station_coord changes station coordinates in related datatstructures
 * if station exists
 * @param id, string, station we are looking for
 * @param newcoord, new coordinates for the station
 * @return true if station found otherwise false
 */
bool Datastructures::change_station_coord(StationID id, Coord newcoord)
{

    if (auto it = stations_umap_.find(id); it != stations_umap_.end()){
        Coord old_coordinate = it->second.coordinates;
        it->second.coordinates = newcoord;
        coord_as_key_map_.erase(old_coordinate);
        coord_as_key_map_.insert({newcoord, id});

        return true;
    }
    return false;
}



/**
 * @brief Datastructures::add_departure adds train departure-info for given station
 * @param stationid, string, unique for each station
 * @param trainid, string (see .hh file), identification for the train
 * @param time, unsigned short int (see .hh file), departure time of the train
 * @return true if station exists otherwise false
 */
bool Datastructures::add_departure(StationID stationid, TrainID trainid, Time time)
{


    if (stations_umap_.count(stationid) == 1){
        return stations_umap_.at(stationid).trains_set.insert({time, trainid}).second;
    }
    return false;
}



/**
 * @brief Datastructures::remove_departure removes train departure-info if such found
 * @param stationid, string (see .hh file), unique for each station
 * @param trainid, string (see .hh file), identification for the train
 * @param time, unsigned short int (see .hh file), departure time of the train
 * @return true if given station and departure-info found otherwise false
 */
bool Datastructures::remove_departure(StationID stationid, TrainID trainid, Time time)
{
    if (stations_umap_.count(stationid) == 1
            && stations_umap_.at(stationid).trains_set.count({time, trainid}) == 1){
        stations_umap_.at(stationid).trains_set.erase({time, trainid});
        return true;
    }
    return false;
}



/**
 * @brief Datastructures::station_departures_after lists all departures from given station at or after given time
 * @param stationid, string (see .hh file), unique for each station
 * @param time, unsigned short int (see .hh file), departure time of the train
 * @return train-departure info in a vector as pairs, sorted by departure time
 */
std::vector<std::pair<Time, TrainID>> Datastructures::station_departures_after(StationID stationid, Time time)
{
    vector<std::pair<Time, TrainID>> re_vector;

    if (stations_umap_.count(stationid) != 1)
        re_vector.push_back({NO_TIME, NO_TRAIN});    

    else {
        for (auto& [departure_time, train]: stations_umap_.at(stationid).trains_set){
            if (departure_time >= time)
                re_vector.push_back({departure_time, train});
        }

    }

    return re_vector;
}



//sisällä kommentti, vapaaehtoisiin liittyen------------------------------------------
/**
 * @brief Datastructures::add_region adds a region to related datastructures if one doesn´t exist before
 * @param id, integer (see .hh file), unique for each region
 * @param name, string (see .hh file), name of the region
 * @param coords, Coord (see .hh file), region´s coordinates in a vector
 * @return true inserting accomplished otherwise false
 */
bool Datastructures::add_region(RegionID id, const Name &name, std::vector<Coord> coords)
{
    region_struct value = {name, coords, {}, {}, NO_REGION};
    if ( regions_umap_.insert({id, value}).second ){
        region_vector_.push_back(id);
                                                        //TÄHÄN jos lisää region id osoituksia varten toiseen tietorakenteeseen!!!!
        return true;
    }
    return false;
}



/**
 * @brief Datastructures::all_regions work has been done in add_region
 * @return unsorted vector full of regionid´s
 */
std::vector<RegionID> Datastructures::all_regions()
{
    return region_vector_;
}



/**
 * @brief Datastructures::get_region_name checks if region exists returns its name
 * @param id, integer (see .hh file), unique for each region
 * @return regions name if region found by its id otherwise NO_NAME
 */
Name Datastructures::get_region_name(RegionID id)
{
    auto search = regions_umap_.find(id);
    if (search != regions_umap_.end())
        return search->second.name;
    return NO_NAME;
}



/**
 * @brief Datastructures::get_region_coords checks if regions exists and returns its coordinates
 * @param id, integer (see .hh file), unique for each region
 * @return regions coordinatesvector if region found otherwise NO_COORD in a vector
 */
std::vector<Coord> Datastructures::get_region_coords(RegionID id)
{
    auto search = regions_umap_.find(id);
    if (search != regions_umap_.end())
        return search->second.coordinates_vector;
    vector<Coord> v = {NO_COORD};
    return v;
}



/**
 * @brief Datastructures::add_subregion_to_region add info about parent-child relationship to related datastructures
 * @param id, integer (see .hh file), unique for each region, subregion´s id
 * @param parentid, integer (see .hh file), unique for each region, parentregion´s id
 * @return true if both child and parent exist and if child has no parent allready, otherwise false
 */
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



/**
 * @brief Datastructures::add_station_to_region adds info about child-parent
 *  relationship between station and region, station can belong to only 1 region
 * @param id, stationid, string (see .hh file), unique for each station
 * @param parentid, integer (see .hh file), unique for each region, parentregion´s id
 * @return true if station and region exists and insertion accomplished, otherwise false
 */
bool Datastructures::add_station_to_region(StationID id, RegionID parentid)
{
    if (regions_umap_.count(parentid) == 0 || stations_umap_.count(id) == 0)
        return false;

    if (all_stations_for_regions_.insert(id).second){
        regions_umap_.at(parentid).stations.insert(id);
        stations_umap_.at(id).parent_region = parentid;
        return true;
    }
    return false;
}



/**
 * @brief Datastructures::station_in_regions lists all regions given station belongs to
 * either directly or indirectly. Calls recursive_parent_regions()-function
 * @param id, stationid, string (see .hh file), unique for each station
 * @return a vector inholding each region´s regionid given station belong to if station found,
 * if given station is no submitted to any region returns empty vector
 * if station doesn´t exist returns NO_REGION as single element in a vector
 */
std::vector<RegionID> Datastructures::station_in_regions(StationID id)
{
    vector<RegionID> re_vector;
    if (all_stations_for_regions_.count(id) == 0)
        return re_vector;

    if (stations_umap_.count(id) == 0 ) {
        re_vector.push_back(NO_REGION);
        return re_vector;
    }

    re_vector.push_back(stations_umap_.at(id).parent_region);
    recursive_parent_regions(stations_umap_.at(id).parent_region, re_vector);

    return re_vector;
}




/**
 * @brief Datastructures::recursive_parent_regions adds each parentregion to the reference-vector
 * @param id, integer (see .hh file), unique for each region
 * @param re_vector, reference-vector inholding regionid´s
 */
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


//Kato mistä kaikista pitää poistaa, jos toteutat muuta attribuutti joka pitää kirjaa onko station_vectoria muutettu
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




