# Bubba Server

This repo contains the bubba chat server.

# Dependencies

## Ubuntu

```bash
sudo apt install libpq-dev protobuf-compiler
```

```bash
# libpqxx - ver. 7.7.5:
git clone https://github.com/jtv/libpqxx
cd libpqxx
git checkout 7.7.5
./configure --disable-documentation CXXFLAGS='-fPIC'
make
sudo make install
```

## Fedora

```bash
sudo dnf install libpq-devel libpqxx-devel protobuf-compiler protobuf-devel
```

# Building

```
mkdir build && cd build
cmake ..
make
```

# Running

To run the server locally, including PostgreSQL, execute:

```bash
sudo docker compose -f docker-compose-local.yml up -d
```
