include = -I../../include 	# directorio de las cabeceras
libpath = -L../../lib		# directorio de la librería dinámica
libs = -lNatNetLibShared	# nombre de la librería sin el prefijo 'lib' y sin el sufijo '.so'

all: build/triggerClient

# función 
build/triggerClient: 
	g++ triggerClient.cpp $(include) $(libpath) $(libs) -o build/triggerClient

.PHONY: clean

# funcion
clean:
	@rm -f ./build/triggerClient
