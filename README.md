# Gome

Gome is an implementation of a subset of the game [Go](https://en.wikipedia.org/wiki/Go_(game)) that you can find [here](https://github.com/ClaudiuHBann/Gome/blob/master/Proiect-1-IS-2023.pdf).

The project consists of a server that is temporary located in the [Tests](https://github.com/ClaudiuHBann/Gome/tree/master/Tests) solution and the client that is located in the [Go](https://github.com/ClaudiuHBann/Gome/tree/master/Go) solution and both of those are dependent of the project [Gome](https://github.com/ClaudiuHBann/Gome/tree/master/Gome) and finally we use 2 more dependencies that are included in the project and are ASIO for networking and nlohmann JSON for (de)serializing data.
	
The server needs a configuration file like [this](https://github.com/ClaudiuHBann/Gome/blob/master/Tests/rules.cfg).

The client connects to the local server automatically.

The server has a command line interface and looks like this:
![image](https://github.com/ClaudiuHBann/Gome/assets/78564392/3c344737-9052-447a-8b16-019d17330e7a)


The client has a command line interface and looks like this:
![image](https://github.com/ClaudiuHBann/Gome/assets/78564392/4663ff5d-d9ab-480e-bf8f-2f7d68be9fed)

Have fun!
