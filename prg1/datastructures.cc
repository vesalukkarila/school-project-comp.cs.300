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
stations_umap_()

{

}


Datastructures::~Datastructures()
{
    // Write any cleanup you need here
}




unsigned int Datastructures::station_count()
{    
    return stations_umap_.size();
}




//LISÄÄ TÄHÄN REGIONIN TYHJENNYS
//Ei mukana tehokkuuskisoissa
void Datastructures::clear_all()
{
    stations_umap_.clear();
}


//Ok, pitäs olla
//Ei mukana tehokkuuskisoissa, mielivaltainen järjestys.
//Pitääkö olla &station_umap_, tekeekö paikallisen kopion attribuutista ilman &-merkkiä????????
std::vector<StationID> Datastructures::all_stations()
{
    vector<StationID> station_vector;
    for (auto& key : stations_umap_)
        station_vector.push_back(key.first);
    return station_vector;
}



//Tehty miettimättä tiedostosta lukua
// Ei salli &, en tiedä onko tarpeenkaan, pää menee sekaisin kohta semantiikasta
bool Datastructures::add_station(StationID id, const Name& name, Coord xy)
{
    station_struct value = {id, name, xy};
    bool insert_ok = stations_umap_.insert({id, value}).second; //second palauttaa booleanin jos onnistui, first palautti iteraattorin kohtaan joka esti tai missä onnistui
    if ( insert_ok )
        return true;
    return false;



}




//KUTSUTAAN USEIN, OPTIMOINTIA VAATINEE. find, contains, count,
//Sama minkä ottaa niin const ja & jottei kopioi
//Tarviiko attribuutti_umap olla viite, voiko olla, kopioiko koko attribuutin kun käyttää algoritmia jos ei ole &?????
Name Datastructures::get_station_name(StationID id)
{
    //find, laitettu vain viite etsittävän eteen
    auto search = stations_umap_.find(id);
    if (search != stations_umap_.end())
        return search->second.name;
    return NO_NAME;


}



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

std::vector<StationID> Datastructures::stations_alphabetically()
{
    // Replace the line below with your implementation
    throw NotImplemented("stations_alphabetically()");
}

std::vector<StationID> Datastructures::stations_distance_increasing()
{
    // Replace the line below with your implementation
    throw NotImplemented("stations_distance_increasing()");
}

StationID Datastructures::find_station_with_coord(Coord /*xy*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("find_station_with_coord()");
}

bool Datastructures::change_station_coord(StationID /*id*/, Coord /*newcoord*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("change_station_coord()");
}

bool Datastructures::add_departure(StationID /*stationid*/, TrainID /*trainid*/, Time /*time*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("add_departure()");
}

bool Datastructures::remove_departure(StationID /*stationid*/, TrainID /*trainid*/, Time /*time*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("remove_departure()");
}

std::vector<std::pair<Time, TrainID>> Datastructures::station_departures_after(StationID /*stationid*/, Time /*time*/)
{
    // Replace the line below with your implementation
    // Also uncomment parameters ( /* param */ -> param )
    throw NotImplemented("station_departures_after()");
}


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
