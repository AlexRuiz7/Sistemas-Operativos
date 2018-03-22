

# Compilación del los ficheros del proyecto
all: cliente servidor proxy

# Compilación separad de clientes.c
cliente:
	gcc clientes.c -o cliente

# Compilación seprada de servidor.c
servidor:
	gcc servidor.c -o servidor

# Compilación separada de proxy.c
proxy:
	gcc proxy.c -o proxy

# Limpieza
clean:
	@echo "Removing executable files..."
	rm cliente servidor proxy

# Limpieza y compresión del proyecto
compress: clean
	@echo "Compressing..."
	tar -zcvf cliente-servidor.tgz *
