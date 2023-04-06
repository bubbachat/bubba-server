# Bubba Server

This repo contains the bubba chat server.

# Dependencies


```
sudo apt install install libpq-dev
```

### libpqxx - ver. 7.7.5:
```
git clone https://github.com/jtv/libpqxx
cd libpqxx
git checkout 7.7.5
./configure --disable-documentation CXXFLAGS='-fPIC'
make
sudo make install
```

# Building

```
mkdir build && cd build
cmake ..
make
```

# Running

To run the server locally, including PostgreSQL, execute:

sudo docker compose -f docker-compose-local.yml up -d