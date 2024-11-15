// Datastructures.cc
//
// Student name: Vesa Lukkarila
// Student email: vesa.lukkarila@tuni.fi
// Student number: 150372523

#include "datastructures.hh"

#include <random>
#include <QDebug>
#include <QString>
#include <cmath>
#include <iostream>

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


/**
 * @brief Datastructures::Datastructures shows attributes
 */
Datastructures::Datastructures():
stations_umap_(), station_vector_(), coord_as_key_map_(),
stations_alphabetically_(false), stations_distance_sorted_(false),
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
 * @brief Datastructures::clear_all clears all 7 datastructures used
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




/**
 * @brief Datastructures::add_station adds data about stations in necessary datastructures
 * @param id, string, id of the station, unique for each station
 * @param name, string, name of the station, not-unique
 * @param xy, type Coord (see .hh file), station coordinates
 * @return true if adding station to datastructure accomplished, otherwise false
 */
bool Datastructures::add_station(StationID id, const Name& name, Coord xy)
{
    //HUOM -------------- LISÄTTY ID ESTRUCTIN KAKS NEXT_STATION_FROM TESTAILUA VARTEN, POISTA JOS TARPEETON -----------------------------
    station_struct value = {id, name, xy, {}, NO_REGION, {}, {}, white, NO_STATION};   //
    if ( stations_umap_.insert({id, value}).second ){           // päätietorakenne asemille
        station_vector_.push_back(id);                          // tietorakenne palautuksia varten, kaikki asemat
        coord_as_key_map_.insert({xy, id});                     // find_station_with_coordia varten
        stations_alphabetically_ = false;                       // stations_alphabetically varten kirjanpito
        stations_distance_sorted_ = false;                      // stations_distance_increasing varten kirjanpito
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
    if (stations_alphabetically_ == false){
        auto sort_vector = [this] (auto& a, auto& b )
        {return stations_umap_.at(a).name < stations_umap_.at(b).name;};

        sort(station_vector_.begin(), station_vector_.end(), sort_vector);
        stations_alphabetically_ = true;
        stations_distance_sorted_ = false;
    }

    return station_vector_;
}




/**
 * @brief Datastructures::stations_distance_increasing copies station-id:s from map to a vector,
 * stations are allready in ascending order by their coordinates in a map
 * @return all station-id:s in a vector sorted in ascending order byt coordinates
 */
std::vector<StationID> Datastructures::stations_distance_increasing()
{

    if (stations_distance_sorted_ == false) {

        auto sort_vector = [this] (auto& a, auto& b )
        {   int first_x = stations_umap_.at(a).coordinates.x;
            int first_y = stations_umap_.at(a).coordinates.y;
            int second_x = stations_umap_.at(b).coordinates.x;
            int second_y = stations_umap_.at(b).coordinates.y;
            int calcute_first = sqrt ( pow(first_x,2) + pow(first_y, 2));
            int calculate_second = sqrt ( pow(second_x,2) + pow(second_y, 2) );

            if ( calcute_first == calculate_second ){
                if (first_y < second_y)
                    return true;
                else
                    return false;
            }
            if ( calcute_first < calculate_second)
                return true;
            else
                return false; ; };


        sort(station_vector_.begin(), station_vector_.end(), sort_vector);
        stations_alphabetically_ = false;
        stations_distance_sorted_ = true;
    }

    return station_vector_;

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
        stations_distance_sorted_ = false;

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
        //lisätään kunkin aseman alle tieto (just_trains) joka junasta, prg2 train_stations_from tarkistusta varten..
        return (stations_umap_.at(stationid).trains_set.insert({time, trainid}).second &&
                stations_umap_.at(stationid).just_trains.insert(trainid).second);   //..tämä siis
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

    if (stations_umap_.count(id) == 0 ) {
        re_vector.push_back(NO_REGION);
        return re_vector;
    }

    if (all_stations_for_regions_.count(id) == 0)
        return re_vector;


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
    if (regions_umap_.at(id).parent == NO_REGION)
        return;
    re_vector.push_back(regions_umap_.at(id).parent);
    recursive_parent_regions(regions_umap_.at(id).parent, re_vector);
    return;
}





// NON-COMPULSORY

/**
 * @brief Datastructures::all_subregions_of_region
 * @param id
 * @return if no region found with given param.return NO_REGION in a vector,
 * if region has no subregions returns an empty vector
 * otherwise return a vector holding all regionid:s to subregions in non-spesific order
 */

std::vector<RegionID> Datastructures::all_subregions_of_region(RegionID id)
{
    vector<RegionID> re_vector;

    if (regions_umap_.count(id) == 0){
        re_vector.push_back(NO_REGION);
        return re_vector;
    }

    if (regions_umap_.at(id).subregions.empty())
        return re_vector;

    recursive_subregions_to_regions(id, re_vector);
    return re_vector;

}



/**
 * @brief Datastructures::recursive_subregions_to_regions recursively goes through every region´s
 * subregion adding them to a vector
 * @param id, integer (RegionID see .hh file), individual id for region
 * @param re_vector, referenced vector from calling function holdin RegionID:s
 */
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




/**
 * @brief Datastructures::remove_station, if station exists removes it from all datastructures where it´s found
 * @param id, string (StationId, kts .hh), unique id for station
 * @return true if removal accomplished otherwise false
 */
bool Datastructures::remove_station(StationID id)
{
    if (stations_umap_.count(id) == 0)
        return false;
    //Asemien päätietorakenne
    stations_umap_.erase(id);
    //Poisto vektorista jossa kaikki asemat
    for (auto it = station_vector_.begin(); it != station_vector_.end(); ++it){
        if (*it == id){

            station_vector_.erase(it);
            break;
        }
    }

    // Poisto koordinaattien mukaan järjestetystä tietorakenteesta
    for (auto& [k,v] : coord_as_key_map_){
        if (v == id){
            coord_as_key_map_.erase(k);
            break;
        }
    }

    //Jos löytyy tietorakenteesta johon on listattu kaikille alueille alistetut asemat..
    if (all_stations_for_regions_.count(id) == 1){
        //..poistetaan..
        all_stations_for_regions_.erase(id);
        //..jolloin löytyy myös jonkin region tietorakenteen hyötykuormasta
        for ( auto& [k,v] : regions_umap_){
            if ( v.stations.count(id) == 1){
                v.stations.erase(id);
                break;
            }
        }
    }
    return true;
}




/**
 * @brief Datastructures::stations_closest_to finds three closest station to given coordinates
 * @param xy, struct that inholds integers as x- and y-coordinates
 * @return a vector with max three stationid:s sorted ascendically by distance from given coordinates
 */
std::vector<StationID> Datastructures::stations_closest_to(Coord xy)
{
    vector <StationID> re_vector;
    auto distance_between = [&xy, this](auto& a, auto& b)
    {
        int given_x = xy.x;
        int given_y = xy.y;
        int first_x = stations_umap_.at(a).coordinates.x;
        int first_y = stations_umap_.at(a).coordinates.y;
        int sec_x = stations_umap_.at(b).coordinates.x;
        int sec_y = stations_umap_.at(b).coordinates.y;
        int first_distance = sqrt( pow(given_x - first_x, 2) +
                                   pow(given_y - first_y, 2) );
        int second_distance = sqrt( pow(given_x - sec_x, 2) +
                                    pow(given_y - sec_y, 2) );

        if (first_distance == second_distance)
            return first_y < sec_y;
        if (first_distance < second_distance)
            return true;
        return false;

        ;};

    sort(station_vector_.begin(), station_vector_.end(), distance_between);
    stations_alphabetically_ = false;
    stations_distance_sorted_ = false;
    int counter = 0;
    for (auto it = station_vector_.begin(); it != station_vector_.end(); ++it){
        re_vector.push_back(*it);
        ++counter;
        if (counter >2)
            break;
    }

    return re_vector;
}




/**
 * @brief Datastructures::common_parent_of_regions finds the first common parent of given regions if such exists
 * @param id1,  unsigned long long int, unique id for each region
 * @param id2,  unsigned long long int, unique id for each region
 * @return regionid to the first common parent if found, otherwise NO_REGION
 */
RegionID Datastructures::common_parent_of_regions(RegionID id1, RegionID id2)
{
    //outoa, palauttaa id1:n joissain

    if (regions_umap_.count(id1) == 0 || regions_umap_.count(id2) == 0)
        return NO_REGION;

    set <RegionID> id1_parents;
    recursive_parentregions(id1, id1_parents);
    return recursive_parentregions(id2, id1_parents);

}




/**
 * @brief Datastructures::recursive_parentregions tries to add parent in referenced
 * datastructure, if insertion fails the first common parent has been found
 * @param id, unsigned long long int, unique id for each region
 * @param parents, referenced set with regionid:s
 * @return regionid of first common parent if such found toherwise NO_REGION
 */
RegionID Datastructures::recursive_parentregions(const RegionID &id, set<RegionID> &parents)
{
    RegionID parent = regions_umap_.at(id).parent;
    if ( parent == NO_REGION)
        return NO_REGION;
    if ( parents.insert(parent).second)
        return recursive_parentregions(parent, parents);

    return parent;

}




//PRG2------------------------------------------------------------------------------------------------------------------------

/**
 * @brief Datastructures::clear_trains clears traind departures from all datastructures needed
 */
void Datastructures::clear_trains()
{

    for (auto & station : stations_umap_){
        station.second.trains_set.clear();
        station.second.just_trains.clear();
        station.second.to_stations.clear();

    }


}


/**
 * @brief Datastructures::add_train adds traindepartures to given stations in given times
 * @param trainid, string, unique to each train
 * @param stationtimes, vector holding stationid´s and departure times
 * @return true if succeeded, false if either trainid or stationid doesn´t exist
 */
bool Datastructures::add_train(TrainID trainid, std::vector<std::pair<StationID, Time> > stationtimes)
{


    unsigned long int first_index = 0;
    unsigned long int second_index = 1;


    StationID first_station = stationtimes.at(first_index).first;
    StationID second_station = stationtimes.at(second_index).first;

    while( first_index < stationtimes.size()){

        bool train_added_to_edge = false;

        Time time = stationtimes.at(first_index).second;


        if (first_index == stationtimes.size() -1){
            Edge payload;
            payload.distance = 0;
            payload.trains_on_this_edge.insert({NO_TRAIN, stationtimes.at(first_index).second});

            stations_umap_.at(stationtimes.at(first_index).first).to_stations.insert({nullptr, payload});
            return true;
        }


        else if (add_departure(stationtimes.at(first_index).first, trainid, time)){


                for(auto& key_value : stations_umap_.at(stationtimes.at(first_index).first).to_stations){

                    if(key_value.first != nullptr){
                        if (key_value.first->id == stationtimes.at(second_index).first){
                            key_value.second.trains_on_this_edge.insert({trainid, stationtimes.at(first_index).second});
                            train_added_to_edge = true;
                            break;
                        }
                    }
                }


                if (!train_added_to_edge){
                    Edge payload;
                    payload.distance = distance_between_stations(
                                stations_umap_.at(stationtimes.at(first_index).first).coordinates,
                                stations_umap_.at(stationtimes.at(second_index).first).coordinates);
                    payload.trains_on_this_edge.insert({trainid, stationtimes.at(first_index).second});


                    station_struct* pointer = &stations_umap_.at(stationtimes.at(second_index).first);
                    stations_umap_.at(stationtimes.at(first_index).first).to_stations.insert({pointer, payload});
                }

                first_index +=1;
                second_index += 1;
            }

        else
            return false;

    }

    return true;
}



/**
 * @brief Datastructures::distance_between_stations calculates distance between station, called from add_train.
 * @param coord1, struct Coord, coordinates to first station
 * @param coord2, struct Coord, coordinates to second station
 * @return integer, the distance between two stations
 */
int Datastructures::distance_between_stations(Coord& coord1, Coord& coord2)
{
    int dist = sqrt( pow(coord1.x-coord2.x, 2) + pow(coord1.y - coord2.y, 2) );
    return dist;
}





/**
 * @brief Datastructures::next_stations_from finds stations a trainconnection is established from the given station
 * @param id, string, stationid unique to each station
 * @return vector holding stationid´s next from the given station. if station doesn´t exist-> no_station as only element
 */
std::vector<StationID> Datastructures::next_stations_from(StationID id)
{
    vector<StationID> next_stations;

    if (stations_umap_.count(id) == 0){
        next_stations.push_back(NO_STATION);
        return next_stations;
    }

    if (stations_umap_.at(id).to_stations.empty())
        return next_stations;

    for (auto const &key_value : stations_umap_.at(id).to_stations)
        if(key_value.first != nullptr)
            next_stations.push_back(key_value.first->id);

    return next_stations;

}





/**
 * @brief Datastructures::train_stations_from finds station the given train travels through
 * @param stationid, string, unique to each station
 * @param trainid, string, unique to each train
 * @return vector holding stationd´s the given train travels through. If station doesn´t exist no_station as only element
 */
std::vector<StationID> Datastructures::train_stations_from(StationID stationid, TrainID trainid)
{
    vector <StationID> stations;
    if (stations_umap_.count(stationid) == 0 || stations_umap_.at(stationid).just_trains.count(trainid) == 0)
        stations.push_back(NO_STATION);

    else{
        recursive_train_stations_from(stationid, trainid, stations);
    }
    return stations;

}





/**
 * @brief Datastructures::recursive_train_stations_from recursively finds stations trainconnection is established to
 * @param stationid, string, unique id to each station
 * @param trainid, string, unique to each train
 * @param stations, referenced vector holding stationid´s
 */
void Datastructures::recursive_train_stations_from(const StationID &stationid, const TrainID &trainid, vector<StationID> &stations)
{
    for (auto const& key_value : stations_umap_.at(stationid).to_stations){
        if (key_value.second.trains_on_this_edge.count(trainid) == 1){
            stations.push_back(key_value.first->id);
            recursive_train_stations_from(key_value.first->id, trainid, stations);
            return;
        }
    }
    return;
}




/**
 * @brief Datastructures::route_any with the help of two recursive function does a depth-first type-of search,
 * finds if it´s possible to travel from starting stationg to end station which are given as parameters
 * @param fromid, string, unique to erach station, staring station
 * @param toid, strin, unique to each station, end station
 * @return a vector holding stationid´s and distance so far, if either one of stations doesn´t exist
 * no-station, no_distance as only element, otherwise empty vector
 */
std::vector<std::pair<StationID, Distance>> Datastructures::route_any(StationID fromid, StationID toid)
{

    vector<pair<StationID, Distance>> route;
    if (stations_umap_.count(fromid) == 0 || stations_umap_.count(toid) == 0){
        route.push_back({NO_STATION, NO_DISTANCE });
        return route;
    }
    for (auto& station : stations_umap_){

       station.second.color = white;
       station.second.previous_stationid = NO_STATION;
    }


    if (!stations_umap_.at(fromid).just_trains.empty()){


        for (auto& station : stations_umap_.at(fromid).to_stations){

            if (station.first != nullptr && station.first->color == white  ){

                station.first->color = grey;
                station.first->previous_stationid = fromid;
                recursive_to_stations(fromid, toid, fromid, station.first->id, station.first, route);

                if ( !route.empty() ) {
                    auto totaldistance = 0;
                    vector <pair<StationID, Distance>> final;
                    for (auto it = route.rbegin(); it != route.rend(); ++it){
                        totaldistance += it->second;
                        final.push_back({it->first, totaldistance});
                    }
                    return final;
                }
            }
        }
      }

    return route;
}


/**
 * @brief Datastructures::recursive_to_stations recursively loops through to_station unorderedmap,
 * calls recursive_end_station_found if end station is found
 * @param fromid, stationid (string), starting station
 * @param toid, stationid (string, end station
 * @param station1id, stationid (string), unique to each station
 * @param station2id, stationid (string), unique to each station
 * @param station2struct, pointer to station_struct which is a key in to_station (unordered_map)
 * @param route, referenced vector
 */
void Datastructures::recursive_to_stations(StationID & fromid, StationID & toid, StationID & station1id, StationID & station2id,
                                           station_struct* station2struct, vector<std::pair<StationID, Distance> > &route)
{
    station2struct->previous_stationid = station1id;

    if (station2id == toid) {
        recursive_end_station_found(fromid, station1id, station2id, station2struct, route);
        return;
    }

    if ( ! station2struct->just_trains.empty()){

        for(auto& jatkoasema : station2struct->to_stations){

            if (jatkoasema.first != nullptr && jatkoasema.first->color == white ){

                jatkoasema.first->color = grey;
                jatkoasema.first->previous_stationid = station2id;
                return recursive_to_stations(fromid, toid, station2id, jatkoasema.first->id, jatkoasema.first, route);
            }
        }
    }
    return;
}




/**
 * @brief Datastructures::recursive_end_station_found backtracks from end station to starting station pushing
 * stations and distances to referenced vector which is finalized in route_any
 * @param fromid, stationid (string), starting station
 * @param station1id, stationid (string), unique to each station
 * @param station2id, stationid (string), unique to each station
 * @param station2struct, pointer to station_struct which is a key in to_station (unordered_map)
 * @param route, referenced vector holding stationid´s and distances between stations
 */
void Datastructures::recursive_end_station_found(const StationID &fromid, StationID const& station1id, StationID const& station2id,
                                         station_struct* const & station2struct, vector<std::pair<StationID, Distance> > &route)
{

    if ( station2id != fromid ) {

        int distance_to_this_station = stations_umap_.at(station1id).to_stations.at(station2struct).distance;
        route.push_back ({station2id, distance_to_this_station});


        if (stations_umap_.at(station1id).previous_stationid != NO_STATION){

            recursive_end_station_found(fromid, stations_umap_.at(station1id).previous_stationid, station1id, &stations_umap_.at(station1id), route);
            return;
        }

        else{

            route.push_back({station1id, 0});
            return;
        }
    }
    return;
}









//NON-COMPULSORY--------------------------------------------------------------------------------------------------------------------------
std::vector<std::pair<StationID, Distance>> Datastructures::route_least_stations(StationID /*fromid*/, StationID /*toid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("route_least_stations()");
}

    //DFS ainakin selvittää silmukan
std::vector<StationID> Datastructures::route_with_cycle(StationID /*fromid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("route_with_cycle()");
}


//Dijkstra
std::vector<std::pair<StationID, Distance>> Datastructures::route_shortest_distance(StationID /*fromid*/, StationID /*toid*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("route_shortest_distance()");
}

std::vector<std::pair<StationID, Time>> Datastructures::route_earliest_arrival(StationID /*fromid*/, StationID /*toid*/, Time /*starttime*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("route_earliest_arrival()");
}
