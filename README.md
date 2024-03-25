# Bip-39 implementation 


[TOC]

This repo implements methods to work with mnmonic sentences following [Bip-39](https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki)

## Installing the library 

### From source code
```
git clone https://github.com/EddyTheCo/QBip39.git 

mkdir build
cd build
qt-cmake -G Ninja -DCMAKE_INSTALL_PREFIX=installDir -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLES=OFF -DBUILD_TESTING=OFF -DBUILD_DOCS=OFF ../QBip39

cmake --build . 

cmake --install . 
```
where `installDir` is the installation path.
One can choose to build or not the test and the documentation with the `BUILD_TESTING` and `BUILD_DOCS` variables.


### From GitHub releases
Download the releases from this repo. 

## Adding the libraries to your CMake project 

```CMake
include(FetchContent)
FetchContent_Declare(
	QtBip39
	GIT_REPOSITORY https://github.com/EddyTheCo/QBip39.git
	GIT_TAG v0.1.1 
	FIND_PACKAGE_ARGS 0.1 CONFIG  
	)
FetchContent_MakeAvailable(QtBip39)

target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> QtBip39::bip39)
```

## API reference

You can read the [API reference](https://eddytheco.github.io/QBip39/), or generate it yourself like
```
cmake -DBUILD_DOCS=ON ../
cmake --build . --target doxygen_docs
```

## Contributing

We appreciate any contribution!


You can open an issue or request a feature.
You can open a PR to the `develop` branch and the CI/CD will take care of the rest.
Make sure to acknowledge your work, and ideas when contributing.

