// Datastructures.hh


#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <unordered_map>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>

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

    // Estimate of performance: O(1)
    // Short rationale for estimate: Only size algorithm used
    unsigned int station_count();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Clear used twice
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Transfer top vector only
    std::vector<StationID> all_stations();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Adding value is O(n) and count is O(1)
    bool add_station(StationID id, Name const& name, Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Return only stations name by given value
    Name get_station_name(StationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Return only stations coordinates by given value
    Coord get_station_coordinates(StationID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n^2logn)
    // Short rationale for estimate: For loop and push_back twice and sort once
    std::vector<StationID> stations_alphabetically();

    // Estimate of performance: O(n^2logn)
    // Short rationale for estimate: For loop and push_back twice and sort once
    std::vector<StationID> stations_distance_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Search by value
    StationID find_station_with_coord(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Search by key
    bool change_station_coord(StationID id, Coord newcoord);

    // Estimate of performance: O(n)
    // Short rationale for estimate: For loop, searches by value are O(1) and push_back is O(1)
    bool add_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance: O(n)
    // Short rationale for estimate: For loop, searches by value are O(1) and erase by value is O(1)
    bool remove_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: For loop, searches are O(1) and push_back is O(n)
    std::vector<std::pair<Time, TrainID>> station_departures_after(StationID stationid, Time time);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: Adding value is O(n) and count is O(1)
    bool add_region(RegionID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: O(n)
    // Short rationale for estimate: For loop and push_back to vector
    std::vector<RegionID> all_regions();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Return only stations name by given value
    Name get_region_name(RegionID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Check for id and then return coordinates
    std::vector<Coord> get_region_coords(RegionID id);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: Search with key twice
    bool add_subregion_to_region(RegionID id, RegionID parentid);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: For loop and search for value in vector
    bool add_station_to_region(StationID id, RegionID parentid);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: For loop and push_back in while loop
    std::vector<RegionID> station_in_regions(StationID id);

    // Non-compulsory operations

    // Estimate of performance: O(n*log(n))
    // Short rationale for estimate: For loop and push_back in while loop
    std::vector<RegionID> all_subregions_of_region(RegionID id);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: 2x for loop and sort and push_back
    std::vector<StationID> stations_closest_to(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: For loop, search by value and erase by value
    bool remove_station(StationID id);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: 2x while loop
    RegionID common_parent_of_regions(RegionID id1, RegionID id2);

private:
    // Lets make struct that has station information
    struct station_information
    {
        Name station_name;
        Coord coord;
        std::vector<std::pair<Time, TrainID>> departures;
        RegionID belongs_to = NO_REGION;
    };

    // Then a map that contains id as key and information as value
    std::unordered_map<StationID, station_information> station;

    // Next we make data structure for regions
    struct region_information
    {
        Name region_name;
        std::vector<Coord> region_coords;
        RegionID parent_id;
    };

    // Then map for it
    std::unordered_map<RegionID, region_information> region;

    //vector where key is name and value id
    std::vector<std::pair<Name, StationID>> station_names;

};

#endif // DATASTRUCTURES_HH
