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
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}

/*!
 * \brief Datastructures::station_count gets the station count
 * \return amount of stations
 */
unsigned int Datastructures::station_count()
{
    return stations_.size();
}

/*!
 * \brief Datastructures::clear_all clears stations_ regions_ and coordsearch_
 */
void Datastructures::clear_all()
{
    stations_.clear();
    regions_.clear();
    coordsearch_.clear();
}

/*!
 * \brief Datastructures::all_stations returns id for all stations
 * \return all station ids in some order
 */
std::vector<StationID> Datastructures::all_stations()
{
    std::vector<StationID> stations(stations_.size());
    auto itr = stations_.begin();
    for(unsigned i = 0; i<stations_.size(); i++){
        stations[i] = ((*itr).second.id);
        itr++;
    }
    return stations;
}

/*!
 * \brief Datastructures::add_station adds all data for a station
 * \param id station id
 * \param name name of the station
 * \param xy coordinates for the station
 * \return 1 if successful 0 if not
 */
bool Datastructures::add_station(StationID id, const Name& name, Coord xy)
{
    if(stations_.find(id) != stations_.end()){return 0;}
    Station station = {id, name, xy, NO_REGION, {}};
    stations_.insert({id, station});
    coordsearch_.insert({xy, id});
    return 1;
}

/*!
 * \brief Datastructures::get_station_name gets the name of the station id
 * \param id selected station id
 * \return name of the selected station or NO_NAME if not found
 */
Name Datastructures::get_station_name(StationID id)
{
    if(stations_.find(id) == stations_.end()){return NO_NAME;}
    return stations_.at(id).name;
}

/*!
 * \brief Datastructures::get_station_coordinates finds out the coordinates of the station id
 * \param id selected station id
 * \return coordinates of the station or NO_COORD if unsuccesful
 */
Coord Datastructures::get_station_coordinates(StationID id)
{
    if(stations_.find(id) == stations_.end()){return NO_COORD;}
    return stations_[id].xy;
}

/*!
 * \brief Datastructures::stations_alphabetically sorts the stations alphabetically according to name
 * \return station ids in alphabetical order
 */
std::vector<StationID> Datastructures::stations_alphabetically()
{
    std::vector<std::pair<Name, StationID>> stations(stations_.size());

    std::unordered_map<StationID, Station>::iterator itr = stations_.begin();
    for (unsigned i = 0; i < stations.size(); i++){
        stations[i] = {(*itr).second.name, (*itr).second.id};
        itr++;
    }
    std::sort(stations.begin(), stations.end());

    std::vector<StationID> stations_final(stations_.size());

    for(unsigned i = 0; i<stations.size(); i++){
        stations_final[i] = stations[i].second;
    }
    return stations_final;
}

/*!
 * \brief Datastructures::stations_distance_increasing stations sorted by distance to 0,0
 * \return stations in the order of distance from coordinates 0,0
 */
std::vector<StationID> Datastructures::stations_distance_increasing()
{
    //Station* stations[stations_.size()];
    std::vector<Station*> stations(stations_.size());
    auto itr = stations_.begin();
    for (unsigned i = 0; i<stations_.size(); i++){
        stations[i] = &(*itr).second;
        itr++;
    }

    std::sort(stations.begin(), stations.end(), [](Station* a, Station* b){
    //std::sort(stations, stations+stations_.size(), [](Station* a, Station* b){
        int ax = a->xy.x;
        int ay = a->xy.y;
        int bx = b->xy.x;
        int by = b->xy.y;
        int alen = (ax*ax) + (ay*ay);
        int blen = (bx*bx) + (by*by);
        //int alen = (a->xy.x*a->xy.x) + (a->xy.y*a->xy.y);
        //int blen = (b->xy.x*b->xy.x) + (b->xy.y*b->xy.y);
        if(alen < blen){return true;}
        if(blen < alen){return false;}
        if(a->xy.y < b->xy.y){return true;}
        return false;});

    std::vector<StationID> stations_final(stations_.size());

    for(unsigned i = 0; i<stations_.size(); i++){
        stations_final[i] = stations[i]->id;
    }

    return stations_final;
}

/*!
 * \brief Datastructures::find_station_with_coord finds the station of the selected coordinate
 * \param xy coordinate of the station that is being searched
 * \return stationid if successful NO_STATION if not
 */
StationID Datastructures::find_station_with_coord(Coord xy)
{
    if(coordsearch_.find(xy) == coordsearch_.end()){return NO_STATION;}
    return coordsearch_[xy];
}

/*!
 * \brief Datastructures::change_station_coord changes the coordinate of a station
 * \param id selected station id
 * \param newcoord new coordinate for selected station
 * \return 1 if successful 0 if no station is found
 */
bool Datastructures::change_station_coord(StationID id, Coord newcoord)
{
    if (stations_.find(id) == stations_.end()){return 0;}
    coordsearch_.erase(stations_[id].xy);
    stations_[id].xy = newcoord;
    coordsearch_.insert({newcoord, id});
    return 1;
}

/*!
 * \brief Datastructures::add_departure adds a train departure to a station
 * \param stationid station from which departs
 * \param trainid train that departs
 * \param time time of departure
 * \return 1 if successful 0 if not
 */
bool Datastructures::add_departure(StationID stationid, TrainID trainid, Time time)
{
    if (stations_.find(stationid) == stations_.end()){return 0;}
    Departure departure{stationid, trainid, time};
    stations_[stationid].departures.push_back(departure);
    return 1;
}

/*!
 * \brief Datastructures::remove_departure removes a train departure from a station
 * \param stationid station where departure is
 * \param trainid train of the departure
 * \param time time of the departure
 * \return 1 if successful 0 if not
 */
bool Datastructures::remove_departure(StationID stationid, TrainID trainid, Time time)
{
    if (stations_.find(stationid) == stations_.end()){return 0;}
    for(unsigned i = 0; i<stations_[stationid].departures.size(); i++){
        if(stations_[stationid].departures[i].trainid == trainid and stations_[stationid].departures[i].time == time){
            stations_[stationid].departures.erase(stations_[stationid].departures.begin() + i);
            return 1;
        }
    }
    return 0;
}

/*!
 * \brief Datastructures::station_departures_after finds all departures from a station after x
 * \param stationid station of which departures are checked
 * \param time departures later than this
 * \return all departures after the time sorted from earliest to latest
 */
std::vector<std::pair<Time, TrainID>> Datastructures::station_departures_after(StationID stationid, Time time)
{
    std::vector<std::pair<Time, TrainID>> departures;
    for(unsigned i = 0; i<stations_[stationid].departures.size(); i++){
        if(stations_[stationid].departures[i].time >= time){
            std::pair<Time, TrainID> pair{stations_[stationid].departures[i].time, stations_[stationid].departures[i].trainid};
            departures.push_back(pair);
        }
    }
    std::sort(departures.begin(), departures.end());
    return departures;
}

/*!
 * \brief Datastructures::add_region adds a new region to the system
 * \param id region id
 * \param name region name
 * \param coords region border coordinates
 * \return 1 if successful 0 if not
 */
bool Datastructures::add_region(RegionID id, const Name &name, std::vector<Coord> coords)
{
    if (regions_.find(id) != regions_.end()){return 0;}
    Region region = {id, name, coords, {}, {}, NO_REGION};
    regions_.insert({id, region});
    return 1;
}

/*!
 * \brief Datastructures::all_regions gets regions in unsorted order
 * \return all of the regions in datastructures
 */
std::vector<RegionID> Datastructures::all_regions()
{
    std::vector<RegionID> regions;
    std::unordered_map<RegionID, Region>::iterator itr;
    for (itr = regions_.begin(); itr != regions_.end(); itr++){
        regions.push_back((*itr).second.id);
    }
    return regions;
}

/*!
 * \brief Datastructures::get_region_name finds the name of the selected region
 * \param id selected region id
 * \return name of the selected region
 */
Name Datastructures::get_region_name(RegionID id)
{
    if(regions_.find(id) == regions_.end()){return NO_NAME;}
    return regions_.at(id).name;
}

/*!
 * \brief Datastructures::get_region_coords find border coordinates for a region
 * \param id selected region id
 * \return coordinates for the border of the region
 */
std::vector<Coord> Datastructures::get_region_coords(RegionID id)
{
    if(regions_.find(id) == regions_.end()){return std::vector<Coord>{NO_COORD};}
    return regions_[id].coords;
}

/*!
 * \brief Datastructures::add_subregion_to_region existing region is added as subregion
 * \param id subregion id
 * \param parentid parentregion id
 * \return 1 if successful 0 if not
 */
bool Datastructures::add_subregion_to_region(RegionID id, RegionID parentid)
{
    if(regions_.find(id) == regions_.end()){return 0;}
    if(regions_.find(parentid) == regions_.end()){return 0;}
    if(regions_[id].parentregion != NO_REGION){return 0;}

    regions_[parentid].subregions.push_back(id);
    regions_[id].parentregion = parentid;
    return 1;
}

/*!
 * \brief Datastructures::add_station_to_region existing station is made part of a region
 * \param id station id
 * \param parentid region id
 * \return 1 if successful 0 if not
 */
bool Datastructures::add_station_to_region(StationID id, RegionID parentid)
{
    if(regions_.find(parentid) == regions_.end()){return 0;}
    if(stations_[id].region != NO_REGION){return 0;}
    regions_[parentid].stations.push_back(id);
    stations_[id].region = parentid;
    return 1;
}

/*!
 * \brief Datastructures::station_in_regions finds regions station is part of
 * \param id station id
 * \return returns all regions the station is within
 */
std::vector<RegionID> Datastructures::station_in_regions(StationID id)
{
    if(stations_[id].region == NO_REGION){return std::vector<RegionID>{};}
    std::vector<RegionID> regions;
    RegionID regionid = stations_[id].region;
    regions.push_back(regionid);
    while(regions_[regionid].parentregion != NO_REGION){
        regionid = regions_[regionid].parentregion;
        regions.push_back(regionid);
    }
    return regions;
}

/*!
 * \brief Datastructures::all_subregions_of_region finds all subregions of region
 * \param id id of the region
 * \return a vector of all its subregions
 */
std::vector<RegionID> Datastructures::all_subregions_of_region(RegionID id)
{
    if(regions_.find(id) == regions_.end()){return std::vector<RegionID>{NO_REGION};}

    std::vector<RegionID> regions_final{id};
    std::vector<RegionID> working_regions = regions_[id].subregions;
    if(working_regions.size() == 0){return std::vector<RegionID>();}

    while(working_regions.size() > 0){
        if(find(regions_final.begin(), regions_final.end(), working_regions[0]) == regions_final.end()){
            regions_final.push_back(working_regions[0]);
            for(unsigned i = 0; i<regions_[working_regions[0]].subregions.size(); i++){
                working_regions.push_back(regions_[working_regions[0]].subregions[i]);
            }
        }
        working_regions.erase(working_regions.begin());
    }
    regions_final.erase(regions_final.begin());
    return regions_final;
}

/*!
 * \brief Datastructures::stations_closest_to finds 3 closest stations to coordinate
 * \param xy coordinate that stations are compared to
 * \return 3 ids of the closest stations
 */
std::vector<StationID> Datastructures::stations_closest_to(Coord xy)
{
    std::map<int, std::vector<StationID>> locs;
    int len;

    for(auto itr = stations_.begin(); itr!=stations_.end(); itr++){
        int x = (xy.x-(*itr).second.xy.x);
        int y = (xy.y-(*itr).second.xy.y);
        len = (x*x) + (y*y);
        if(locs.find(len) == locs.end()){
            locs.insert({len, std::vector<StationID>{(*itr).second.id}});
        }else{
            locs[len].push_back((*itr).second.id);
        }
    }
    std::vector<StationID> final;
    auto itr = locs.begin();
    while(final.size()<3 and final.size()<stations_.size()){
        for(unsigned i = 0; i<(*itr).second.size(); i++){
            final.push_back((*itr).second[i]);
        }
        itr++;
    }
    return final;
}

/*!
 * \brief Datastructures::remove_station removes all data of a station
 * \param id id of the station
 * \return true if successful false if not
 */
bool Datastructures::remove_station(StationID id)
{
    if(stations_.find(id) == stations_.end()){return 0;}
    Coord xy = stations_[id].xy;
    RegionID reg = stations_[id].region;
    stations_.erase(id);
    if(xy != NO_COORD){coordsearch_.erase(xy);}
    if(reg != NO_REGION){
        for(unsigned i = 0; i<regions_[reg].stations.size(); i++){
            if(regions_[reg].stations[i] == id){
                regions_[reg].stations.erase(regions_[reg].stations.begin()+i);
            }
        }
    }
    return 1;
}

/*!
 * \brief Datastructures::common_parent_of_regions finds the common parent of regions
 * \param id1 first region
 * \param id2 second region
 * \return the "lowest" common parent of the two regions
 */
RegionID Datastructures::common_parent_of_regions(RegionID id1, RegionID id2)
{
    RegionID working_region1 = id1;
    RegionID working_region2 = id2;
    if(regions_.find(id1) == regions_.end()){return NO_REGION;}
    if(regions_.find(id2) == regions_.end()){return NO_REGION;}

    while(regions_[working_region1].parentregion != NO_REGION){
        working_region2 = id2;
        while(regions_[working_region2].parentregion != NO_REGION){
            if(regions_[working_region1].parentregion == regions_[working_region2].parentregion){return regions_[working_region1].parentregion;};
            working_region2 = regions_[working_region2].parentregion;
        }
      working_region1 = regions_[working_region1].parentregion;
    }
    return NO_REGION;
}
