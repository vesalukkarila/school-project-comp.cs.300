// Datastructures.cc


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

Datastructures::Datastructures()
{

}

Datastructures::~Datastructures()
{

}

/**
* @brief Datastructures::station_count count all stations
* @return size of map
*/
unsigned int Datastructures::station_count()
{
    // Return count of maps keys
    return station.size();
}

/**
 * @brief Datastructures::clear_all clears both maps
 */
void Datastructures::clear_all()
{
    // Clears both maps from all values
    station.clear();
    region.clear();
    station_names.clear();
}

/**
 * @brief Datastructures::all_stations gets every station and adds to vector
 * @return vector with station ids
 */
std::vector<StationID> Datastructures::all_stations()
{
    // For loop to get every key in the map and then it returns them
    std::vector<StationID> stations;
    std::transform(station.begin(), station.end(), std::back_inserter(stations), [](auto &station){return station.first;});
    // Returns all station ids
    return stations;
}

/**
 * @brief Datastructures::add_station adds new station to map
 * @param id stations id
 * @param name stations name
 * @param xy stations coordinates
 * @return true if succeed, otherwise false
 */
bool Datastructures::add_station(StationID id, const Name& name, Coord xy)
{
    // First check if it already exist
    if (station.find(id) != station.end()){
        return false;
    }

    // Mpas data
    station[id].station_name = name;
    station[id].coord = xy;

    // Vectors data
    station_names.push_back(std::make_pair(name, id));

    return true;
}

/**
 * @brief Datastructures::get_station_name takes stations name
 * @param id is stations id
 * @return name of wanted station
 */
Name Datastructures::get_station_name(StationID id)
{
    // Check if it is in map
    if (station.find(id) != station.end()){
        return station[id].station_name;
    }
    // Else return NO_NAME
    return NO_NAME;
}

/**
 * @brief Datastructures::get_station_coordinates gets wanted stations coordinates
 * @param id stations id
 * @return coordinates of wanted station
 */
Coord Datastructures::get_station_coordinates(StationID id)
{
    // Check if it is in map
    if (station.find(id) != station.end()){
        return station[id].coord;
    }
    // Else return NO_COORD
    return NO_COORD;
}

/**
 * @brief Datastructures::stations_alphabetically takes every station and puts them to alphabetical order
 * @return all station ids in order
 */
std::vector<StationID> Datastructures::stations_alphabetically()
{
    // sort vector of station names
    std::sort(station_names.begin(), station_names.end());
    // Add ids to new vector
    std::vector<StationID> ids;

    for (auto const& map:station_names){
        ids.push_back(map.second);
    }

    // Return vector
    return ids;
}

/**
 * @brief Datastructures::stations_distance_increasing takes every station and puts them to coordinate order
 * @return all station ids in order
 */
std::vector<StationID> Datastructures::stations_distance_increasing()
{
    // Make unordered map where coordinates are keys
    std::vector<std::pair<float, StationID>> distance_vec;

    // Add all values to new map from station map
    for (auto const&map: station){
        float x_value = map.second.coord.x;
        float y_value = map.second.coord.y;

        float distance = sqrt((x_value*x_value)+(y_value*y_value));
        distance_vec.push_back(std::make_pair(distance, map.first));
    }

    // Sort vector
    std::sort(distance_vec.begin(), distance_vec.end());

    // Make new vector with only ids
    std::vector<StationID> ids;

    // Add ids to new vector
    for (auto const& map:distance_vec){
        ids.push_back(map.second);
    }

    // Then return vector
    return ids;

}

/**
 * @brief Datastructures::find_station_with_coord find station with given coordinate
 * @param xy coordinates
 * @return station id if found
 */
StationID Datastructures::find_station_with_coord(Coord xy)
{

    // Lets go trough coords vector
    // If values are same, return station i

    auto it = std::find_if(station.begin(), station.end(), [&xy](const std::pair<StationID, station_information> &value) ->bool {return value.second.coord == xy;});

    if (it != station.end()){
        return it->first;
    }

    // Else return NO_STATION
    return NO_STATION;
}
/**
 * @brief Datastructures::change_station_coord changes stations coordinates
 * @param id stations id
 * @param newcoord stations new coordinates
 * @return true if succesful, otherwise false
 */
bool Datastructures::change_station_coord(StationID id, Coord newcoord)
{
    // First check if station even exist
    auto it = station.find(id);
    if (it != station.end()){
        // Then change value
        it->second.coord = newcoord;
        return true;
    }
    // Return false if not found
    return false;
}

/**
 * @brief Datastructures::add_departure adds new departure to station
 * @param stationid stations id
 * @param trainid trains id
 * @param time time when train arrives
 * @return true if succesful, otherwise false
 */
bool Datastructures::add_departure(StationID stationid, TrainID trainid, Time time)
{
    // Check if station exist
    if (station.count(stationid)){
        // Then check if train is added
        for (unsigned long int i = 0; i < station.at(stationid).departures.size(); i++){
            if(station[stationid].departures[i].first == time){
                // Also check if time is same
                if(station[stationid].departures[i].second == trainid){
                    // Then return false
                    return false;
                }
            }
        }
        // If departure is not there yet, let's add it
        station[stationid].departures.push_back(std::make_pair(time, trainid));

        // And then return true
        return true;

    }
    // Otherwise return false
    return false;
}

/**
 * @brief Datastructures::remove_departure removes old departure
 * @param stationid wanted station
 * @param trainid wanted train
 * @param time wanted time
 * @return true if succesful, otherwise false
 */
bool Datastructures::remove_departure(StationID stationid, TrainID trainid, Time time)
{
    // Check if station exist
    if (station.count(stationid)){
        // then check if trainid exist
        for (unsigned long int i = 0; i < station.at(stationid).departures.size(); i++){
            if(station.at(stationid).departures.at(i).first == time){
                // Also check if time is same
                if(station.at(stationid).departures.at(i).second == trainid){
                    // Then remove value from vector
                    station.at(stationid).departures.erase(station.at(stationid).departures.begin()+i);

                    // And return true
                    return true;
                }
            }
        }
    }
    // Otherwise return false
    return false;
}

/**
 * @brief Datastructures::station_departures_after gets every departure after given time
 * @param stationid wanted station
 * @param time other departures after this time
 * @return vector with all departures after time
 */
std::vector<std::pair<Time, TrainID>> Datastructures::station_departures_after(StationID stationid, Time time)
{
    // Vector for all departures after given time
    std::vector<std::pair<Time, TrainID>> departures_after;

    // First check if station exist
    if (station.count(stationid)){
        // Station exist so lets add every departure after given time
        // First go throught every every departure and add only them with higher time to new vector
        for (unsigned long int i = 0; i < station[stationid].departures.size(); i++){
            // Check if time is higher or equal than given time
            if (station[stationid].departures[i].first >= time){
                // Then add it to new vector
                Time time2 = station[stationid].departures[i].first;
                StationID trainid = station[stationid].departures[i].second;
                departures_after.push_back(std::make_pair(time2, trainid));
            }
        }
        // Return vector in sorted order
        sort(departures_after.begin(), departures_after.end());

        return departures_after;
    }

    // Otherwise return {NO_TIME, NO_TRAIN}
    departures_after.push_back(std::make_pair(NO_TIME, NO_TRAIN));
    return departures_after;
}

/**
 * @brief Datastructures::add_region adds new region
 * @param id id of region
 * @param name of region
 * @param coords of region
 * @return true if succesful, false otherwise
 */
bool Datastructures::add_region(RegionID id, const Name &name, std::vector<Coord> coords)
{
    // First check if region already exist
    if (region.count(id)){
        return false;
    }
    // Otherwise add new region

    // If doesnt contain then add new region and return true
    // Set parent id empty because it isn't given yet
    region_information new_information = {name,coords,NO_REGION};
    region.insert({id, new_information});

    return true;
}

/**
 * @brief Datastructures::all_regions gets every region
 * @return every region
 */
std::vector<RegionID> Datastructures::all_regions()
{
    // Empty vector for all regions
    std::vector<RegionID> ids;

    // Add evey region id to vector
    for (auto&map:region){
        ids.push_back(map.first);
    }

    // Return vector
    return ids;
}

/**
 * @brief Datastructures::get_region_name gets name of region
 * @param id of region
 * @return name of wanted region
 */
Name Datastructures::get_region_name(RegionID id)
{
    // First check if id exist
    if (region.count(id)){
        // then return region name
        return (region.at(id).region_name);
    }
    // Else return NO_NAME
    return NO_NAME;
}

/**
 * @brief Datastructures::get_region_coords gets coordinates of region
 * @param id of region
 * @return vector of coordinates
 */
std::vector<Coord> Datastructures::get_region_coords(RegionID id)
{
    // First check if id exist
    if (region.count(id)){
        // then return coordinates
        return (region.at(id).region_coords);
    }
    // Else return vector with one element NO_COORD
    // Make empty vector with value
    std::vector<Coord>no_coord = {NO_COORD};

    // Return it
    return no_coord;
}

/**
 * @brief Datastructures::add_subregion_to_region adds poarenit to region
 * @param id regions id
 * @param parentid is regions parent regions id
 * @return true or false
 */
bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid)
{
    // First check if id is in regions
    if(region.count(id)){
        // then check if regions parent id is empty
        if (region.at(id).parent_id == NO_REGION){
            // Add parent id
            region.at(id).parent_id = parentid;
            return true;
        }
    }

    // Otherwise return false
    return false;
}

/**
 * @brief Datastructures::add_station_to_region adds station to region
 * @param id of station
 * @param parentid is id of region
 * @return true or false
 */
bool Datastructures::add_station_to_region(StationID id, RegionID parentid)
{
    // First check if region and station are found
    if(region.count(parentid)){
        if(station.count(id)){
            // If contain region, return false
            if (station[id].belongs_to != NO_REGION){
                return false;
            }
            // Both region and station are found but station is not in other region
            // So add it to region
            station[id].belongs_to = parentid;
            return true;
        }
    }

    // Otherwise return false
    return false;
}

/**
 * @brief Datastructures::station_in_regions  gets all region where station id
 * @param id is stations id
 * @return vector of regions
 */
std::vector<RegionID> Datastructures::station_in_regions(StationID id)
{
    // First make vector that contains region ids
    std::vector<RegionID> ids;

    // Then check if station exist
    if (station.find(id) != station.end()){
        // First check if is not in any region
        if (station[id].belongs_to == NO_REGION){
            // Return empty vector
            return ids;
        }
        // Make first region as current
        RegionID current_id = station[id].belongs_to;

        // Then add values until no parent region
        while(true){
           // Add current value
           ids.push_back(current_id);

           // Then check if parentid is empty
           // If isn't make it current value and if is break loop
           if (region.at(current_id).parent_id == NO_REGION){
               break;
           }
           current_id = region.at(current_id).parent_id;
       }
       // Then return vector
        return ids;
    }

    // If doesn't exist return NO_REGION
    return {NO_REGION};
}

/**
 * @brief Datastructures::all_subregions_of_region gets all subregions of region
 * @param id is regions id
 * @return vector of regions
 */
std::vector<RegionID> Datastructures::all_subregions_of_region(RegionID id)
{
    // Make vector that contains all subregions
    std::vector<RegionID> ids;


    // Check if region exist
    if (region.count(id)){
        // Then let's add all subregions
        // Go through every region and check if it some parent region is same as given region
        for (auto&map:region){
            RegionID current_id = map.second.parent_id;
            while (true){
                // Check if parent id is empty or same as region
                // otherwise make parent id to current
                if (current_id == id){
                    ids.push_back(map.first);
                }
                else if(current_id == NO_REGION){
                    break;
                }
                // If isn id or NO_REGION, then make parent id as current
                current_id = region.at(current_id).parent_id;
            }
        }
        return ids;
    }

    // Region didn't exist so return NO_REGION
    ids.push_back(NO_REGION);
    return ids;
}

/**
 * @brief Datastructures::stations_closest_to gets station that is closest to coordinates
 * @param xy coordinates
 * @return 3 closest stations to coordinate
 */
std::vector<StationID> Datastructures::stations_closest_to(Coord xy)
{
    // Make vector for coordinates
    std::vector<StationID> closest_stations;

    // Vector thats key is the distance to station
    std::vector<std::pair<float, StationID>> distance_ingreasing;

    // Go through all stations
    for (auto&map: station){
        // Stations x and y values
        int x = map.second.coord.x;
        int y = map.second.coord.y;

        // Given coords values are
        int x2 = xy.x;
        int y2 = xy.y;

        // Add values to vector
        float distance;

        distance = sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
        // Add values to vector
        distance_ingreasing.push_back(std::make_pair(distance, map.first));
    }

    // Order the vector
    sort(distance_ingreasing.begin(), distance_ingreasing.end());

    // Add values to new vector until its size is 3 or until stations are over
    for(auto &map:distance_ingreasing){
        closest_stations.push_back(map.second);
        // check size
        if (closest_stations.size() == 3){
            return closest_stations;
        }
    }

    // Return vector
    return closest_stations;
}

/**
 * @brief Datastructures::remove_station removes station
 * @param id is stations id
 * @return true or false
 */
bool Datastructures::remove_station(StationID id)
{
    // First check if station exits
    if (station.count(id)){
        // Delete station from map
        station.erase(id);

        // Also delete station from vector
        unsigned long int i = 0;
        while(i < station_names.size()){
            if(station_names[i].second == id){
                station_names.erase(station_names.begin()+i);
                break;
            }
            i++;
        }

        // Then return true
        return true;
    }
    // Station didnt exist, return false
    return false;
}

/**
 * @brief Datastructures::common_parent_of_regions gets common parent region of 2 regions
 * @param id1 first region id
 * @param id2 second region id
 * @return common parent
 */
RegionID Datastructures::common_parent_of_regions(RegionID id1, RegionID id2)
{
    // Go through first ids all parent ids and compare them to another ones
    while (true){
        RegionID first_current_id = region.at(id1).parent_id;
        RegionID second_current_id = region.at(id2).parent_id;

        // Compare first ones parent to second ones all parents
        while(true){
            // first check if first parent id is NO_REGION
            if (first_current_id == NO_REGION){
                return NO_REGION;
            }
            // Now compare first parent id to seconds all parent ids
            else if (first_current_id == second_current_id){
                return first_current_id;  
            }
            // If second is NO_REGION, then make first parent one step forward
            // and reset rescond one
            else if(second_current_id == NO_REGION){
                // Make first ids value to next parent
                // and second value back to original parent and it compares again
                first_current_id = region.at(first_current_id).parent_id;
                second_current_id = region.at(id2).parent_id;
            }
            // If not same and it isn't NO_REGION then make second one to next parent_id
            else{
                second_current_id = region.at(second_current_id).parent_id;
            }
        }  
    }
}
