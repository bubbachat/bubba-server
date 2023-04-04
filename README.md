# Bubba Server

This repo contains the bubba chat server.

# Dependencies

```
sudo apt install install libpqxx-dev libpq-dev
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