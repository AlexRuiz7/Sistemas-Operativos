#!/bin/bash

# Si no existe
if [ ! -d "/tmp/varios" ]; then
	# Crea el directorio y lo llena
	mkdir "/tmp/varios"
	echo "Directory created"
	elements=10
	counter=0
	while [ $counter -lt $elements ]
	do
		touch "/tmp/varios/core$RANDOM"
		let counter=counter+1
	done
else
	# Elimina los ficheros core dentro de /tmp/varios, almacenando las salida
	# del comando en listacores
	echo "Removing core files ..."
	rm -v /tmp/varios/core* >> listacores
	# Una vez realizada la tarea volvemos a ejecutar el script anexo para 
	# eliminar el directorio /tmp/varios
	rm -rf "/tmp/varios"
fi
