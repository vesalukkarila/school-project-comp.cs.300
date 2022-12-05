// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

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
    // Short rationale for estimate: complexity of vector.size() is constant
    unsigned int station_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: complexity of clear() is linear
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: iterating throught loops is linear push_back() constant
    std::vector<StationID> all_stations();

    // Estimate of performance: O(n)
    // Short rationale for estimate: find() has linear complexity
    bool add_station(StationID id, Name const& name, Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: find() has linear complexity
    Name get_station_name(StationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: find() has linear complexity
    Coord get_station_coordinates(StationID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n * log(n))
    // Short rationale for estimate: sort() has linearithmic performance others linear
    std::vector<StationID> stations_alphabetically();

    // Estimate of performance: O(n * log(n))
    // Short rationale for estimate: sort() has linearithmic performance others linear
    std::vector<StationID> stations_distance_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate: All elements are iterated throught
    StationID find_station_with_coord(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: find has linear perf
    bool change_station_coord(StationID id, Coord newcoord);

    // Estimate of performance: O(n)
    // Short rationale for estimate: find has linear perf
    bool add_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance: O(n)
    // Short rationale for estimate: find has linear perf
    bool remove_departure(StationID stationid, TrainID trainid, Time time);

    // Estimate of performance: O(n^2)
    // Short rationale for estimate: Operations within a for loop
    std::vector<std::pair<Time, TrainID>> station_departures_after(StationID stationid, Time time);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: find has linear perf
    bool add_region(RegionID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Same operations for every n
    std::vector<RegionID> all_regions();

    // Estimate of performance: O(n)
    // Short rationale for estimate: find has linear perf
    Name get_region_name(RegionID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: find has linear perf
    std::vector<Coord> get_region_coords(RegionID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: find has linear perf
    bool add_subregion_to_region(RegionID id, RegionID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: find has linear perf
    bool add_station_to_region(StationID id, RegionID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: find has linear perf
    std::vector<RegionID> station_in_regions(StationID id);

    // Non-compulsory operations

    // Estimate of performance: O(n)
    // Short rationale for estimate: Stuff is done
    std::vector<RegionID> all_subregions_of_region(RegionID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: something has loops and things
    std::vector<StationID> stations_closest_to(Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: find() is linear in performance
    bool remove_station(StationID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: iterates throught some things
    RegionID common_parent_of_regions(RegionID id1, RegionID id2);

private:
    // Add stuff needed for your class implementation here
    struct Departure{StationID stationid; TrainID trainid; Time time;};
    struct Station{StationID id; Name name; Coord xy; RegionID region; std::vector<Departure> departures;};
    struct Station_simple{StationID id; Coord xy;};
    struct Region{RegionID id; Name name; std::vector<Coord> coords;
                  std::vector<StationID> stations; std::vector<RegionID> subregions; RegionID parentregion;};
    //struct Train{TrainID id;};

    std::unordered_map<StationID, Station> stations_;
    std::unordered_map<RegionID,Region> regions_;

    std::unordered_map<Coord, StationID, CoordHash> coordsearch_;
};

#endif // DATASTRUCTURES_HH
