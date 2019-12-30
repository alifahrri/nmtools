# Numerical Tools
A generic codes collection on Numerical Methods.   

| Branch 	| Build Status                                                                                                                      	|
|--------	|-----------------------------------------------------------------------------------------------------------------------------------	|
| `master` 	| [![Build Status](https://travis-ci.org/alifahrri/nmtools.svg?branch=master)](https://travis-ci.org/alifahrri/nmtools) 	|
|  `devel` 	|  [![Build Status](https://travis-ci.org/alifahrri/nmtools.svg?branch=devel)](https://travis-ci.org/alifahrri/nmtools) 	|   


## Quick Start
Requirement :
- Docker
### To build Docker Image
Run the build script (position independent, could be run from any directory), 
```
$ docker/build.sh
```
in this example, the script was being run from repo root dir. After successful build, you should have `numeric_tools` image in your local docker registry.
### To run Unit Tests from Container
Run the provided script (for convinience),
```
$ docker/run.sh
```

## Examples
**TODO**. In the meantime please look at unit tests files located at `tests` directory.

## Reference  
```
Chapra SC, Canale RP. Numerical methods for engineers. New York: Mcgraw-hill; 1998.
```
