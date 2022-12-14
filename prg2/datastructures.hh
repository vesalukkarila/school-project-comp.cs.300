// Datastructures.hh
//
// Student name:
// Student email:
// Student number:

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <map>
#include <stack>

using namespace std;

// Types for IDs
using StationID = std::string;
using TrainID = std::string;
using RegionID = unsigned long long int;
using Name = std::string;
using Time = unsigned short int;

// Return values for cases where required thing was not found
StationID const NO_STATION = "---";
TrainID const NO_TRAIN = "---";
RegionID const NO_REGION = -1;
Name const NO_NAME = "!NO_NAME!";
Time const NO_TIME = 9999;

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();


// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    //
    // Old assignment 1 operations
    //

    // Estimate of performance:
    // Short rationale for estimate:
    unsigned int station_count();

    // Estimate of performance:
    // Short rationale for estimate:
    void clear_all();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StationID> all_stations();

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_station(StationID id, Name const& name, Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    Name get_station_name(StationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    Coord get_station_coordinates(StationID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StationID> stations_alphabetically();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StationID> stations_distance_increasing();

    // Estimate of performance:
    // Short rationale for estimate:
    StationID find_station_with_coord(Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    bool change_station_coord(StationID id, Coord newcoord);

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::pair<Time, TrainID>> station_departures_after(StationID stationid, Time time);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_region(RegionID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<RegionID> all_regions();

    // Estimate of performance:
    // Short rationale for estimate:
    Name get_region_name(RegionID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<Coord> get_region_coords(RegionID id);

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_subregion_to_region(RegionID id, RegionID parentid);

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_station_to_region(StationID id, RegionID parentid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<RegionID> station_in_regions(StationID id);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<RegionID> all_subregions_of_region(RegionID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StationID> stations_closest_to(Coord xy);

    // Estimate of performance:
    // Short rationale for estimate:
    bool remove_station(StationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    RegionID common_parent_of_regions(RegionID id1, RegionID id2);

    //
    // New assignment 2 operations---------------------------------------------------------------------------------------------
    //

    // Estimate of performance:
    // Short rationale for estimate:
    bool add_train(TrainID trainid, std::vector<std::pair<StationID, Time>> stationtimes);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StationID> next_stations_from(StationID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StationID> train_stations_from(StationID stationid, TrainID trainid);

    // Estimate of performance:
    // Short rationale for estimate:
    void clear_trains();

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::pair<StationID, Distance>> route_any(StationID fromid, StationID toid);




    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::pair<StationID, Distance>> route_least_stations(StationID fromid, StationID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<StationID> route_with_cycle(StationID fromid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::pair<StationID, Distance>> route_shortest_distance(StationID fromid, StationID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<std::pair<StationID, Time>> route_earliest_arrival(StationID fromid, StationID toid, Time starttime);

private:
    // Add stuff needed for your class implementation here

    struct Edge {

                               int distance;        // laskukaava olemassa, jos laskee kaikille lisätyille, saattaa tulla ylimääräisiä ja tehokkuus laskee
 unordered_map <TrainID, Time> trains_on_this_edge;        //time jätetty muttei käytetty vielä, poista jos tarpeeton

    };

    enum Color {white, grey, black};

    struct station_struct{
                               StationID id;    //lisätty next station from testausta varten, ei tarvetta prg1:ssä ja poista jos teet uuden puun
                                  Name name;
                          Coord coordinates;
        set<pair<Time, TrainID>> trains_set;    //juna ei näy täällä jos pääteasema -> addtrain
                     RegionID parent_region;
unordered_map <station_struct*, Edge> to_stations;        //prg2 added, lisätty {} add_station alustukseen vikaks, jos muuttuu poista sieltä
                    set<TrainID> just_trains;   //jos lähtee asemalta, mutta ei lisätä addtrainissa jos pääteasema
             StationID* previous_station;   //stationid vai stationstruct??
                                Color color;
                                StationID previous_statioid;
    };

    struct region_struct{
                                  Name name;
           vector<Coord> coordinates_vector;
        unordered_set <RegionID> subregions;
         unordered_set <StationID> stations;
                            RegionID parent;
    };

                                            //Station related
     unordered_map <StationID, station_struct> stations_umap_;
                            vector<StationID> station_vector_;
                      map<Coord, StationID> coord_as_key_map_;
                                bool stations_alphabetically_;
                               bool stations_distance_sorted_;

                                             //Region related
        unordered_map <RegionID, region_struct> regions_umap_;
                              vector<RegionID> region_vector_;
                     unordered_set <RegionID> all_subregions_;
          unordered_set <StationID> all_stations_for_regions_;


                         //recursive function, called from station_in_regions
       void recursive_parent_regions(RegionID const& id, vector<RegionID>& v);

                   //recursive function, called from all_subregions_of_region
void recursive_subregions_to_regions(RegionID const& id, vector<RegionID>& v);

                            //recursive function for common_parent_of_regions
 RegionID recursive_parentregions(RegionID const& id, set<RegionID>& parents);

                                // Recursive function for train_stations_from
 void recursive_train_stations_from (StationID const& stationid, TrainID const& trainid, vector<StationID>& stations);

                    int distance_between_stations (Coord& coord1, Coord& coord2);

void recursive_route_any (StationID const& fromid, StationID const& station1id, StationID const& station2id, station_struct* const& station2struct, vector<std::pair<StationID, Distance>>& route );
bool recursive_to_stations (StationID fromid, StationID toid, station_struct* const& station2struct, vector<std::pair<StationID, Distance> > &route);
};

#endif // DATASTRUCTURES_HH
