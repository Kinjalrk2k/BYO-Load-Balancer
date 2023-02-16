# BYO-Load-Balancer

> (Bring Your Own) Load Balancer

## Blog

Read the blog post about this application [here](https://blog.kinjal.dev/bring-your-own-load-balancer)

## Developing

- To initialize or clean the build directory

```sh
./scripts/clean.sh
```

- To make a clean build and run the application with the config file

```sh
./scripts/run.sh
```

## Testing

3 types of test servers are present in the `tests/` directory

- local: Run multiple instances of a basic ExpressJS server locally
  - Install the dependencies with `npm i` first then run them with `npm start`
- echo: Run multiple instances of the [Echo-Server](https://github.com/Ealenn/Echo-Server.git)
  - Run the `setup.sh` file to clone the repository
  - Run the `npm start` command to start the servers
- docker: Run the same echo server but in docker along with the load balancer

Modify the `byolb.config` file to point to the correct host and ports. Run the server:

```sh
CONFIG_FILE=/path/to/byolb.config ./build/src/lb
```
