# Bip-39 implementation for Qt

Following [Bip-39](https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki)

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

You can read the [API reference](https://eddytheco.github.io/QBip39/), or generate it yourself like
```
cmake --build . --target doxygen_docs
```

### From GitHub releases
Download the releases from this repo. 

## Adding the libraries to your CMake project 

```CMake
include(FetchContent)
FetchContent_Declare(
	QBip39
	GIT_REPOSITORY https://github.com/EddyTheCo/QBip39.git
	GIT_TAG v0.1.1 
	FIND_PACKAGE_ARGS 0.1 CONFIG  
	)
FetchContent_MakeAvailable(QBip39)

target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> QBip39::qbip39)
```
