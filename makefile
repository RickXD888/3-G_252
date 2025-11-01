bin/programa : src/main.cpp include/Foco.hpp include/EstadoFoco.hpp 
	c++ src/main.cpp -o bin/programa -I include

run : bin/programa
	./bin/programa

bin/ejemplo : src/ejemplo.cpp
	c++ src/ejemplo.cpp -o bin/ejemplo -lftxui-screen -lftxui-dom -lftxui-component

runEjemplo : bin/ejemplo
	./bin/ejemplo

bin/animacionperrona : src/animacionperrona.cpp include/*.hpp
	@mkdir -p bin
	c++ -Iinclude -o bin/animacionperrona src/animacionperrona.cpp -lftxui-component -lftxui-dom -lftxui-screen

runAnimacionperrona: bin/animacionperrona
	./bin/animacionperrona