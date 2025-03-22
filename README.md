# Windows build

(require mingw)

`mkdir build`
`cd build`
`cmake -G "MinGW Makefiles" ..`
`mingw32-make`

## Run

`.\Windows\bin\raycast.exe ..\config\polygon.txt 201 290`
`.\Windows\bin\raycast.exe ..\config\polygon.txt -400 -100`
etc

## Linux build

(requires cmake)

`mkdir build`
`cd build`
`cmake ..`
`make`

## Run

`.\Linux\bin\raycast ..\config\polygon.txt 201 290`
`.\Linux\bin\raycast ..\config\polygon.txt -400 -100`
etc