# school-project-comp.cs.300
- Datastructures & algorithms -course. Individual project, autumn -22.
- Overall grade for the course: 4

## Project description
This project, Railroads, was assignment for the COMP.CS.300 Data Structures and Algorithms course. Its primary aim is to provide hands-on practice with algorithms and data structures, particularly focusing on creating efficient implementations. The project simulates a railway system where users can input data about stations, train departures, and regions (such as municipalities or states) surrounding each station.

Use instructions for application can be found at the end of assignment.pdf  

## Usage

### Run locally
This project was a two-parter, prg1 and prg2.  
Generate Makefile with qmake  
```sh
qmake -o Makefile prg1.pro
```
(..alternatively prg2.pro)  

Then build
```sh
make
```
.. and run the executable  
- on macOs
```sh
open prg1.app
```
- non-macOs, check Makefile´s "TARGET" to see where it places the executable and run
```sh
./prg1
```




