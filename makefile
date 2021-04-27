Monster.o: src/Monster.cpp include/Monster.h
	g++ -c $<

Item.o: src/Item.cpp include/Item.h
	g++ -c $<

Inventory.o: src/Inventory.cpp include/Inventory.h include/Item.h
	g++ -c $<

Character.o: src/Character.cpp include/Character.h include/Inventory.h
	g++ -c $<

Events.o: src/Events.cpp include/Events.h include/Character.h include/Inventory.h include/Item.h include/Monster.h
	g++ -c $<

Game.o: src/Game.cpp include/Game.h include/Events.h include/Character.h include/Inventory.h include/Item.h
	g++ -c $<

main.o: main.cpp include/Game.h
	g++ -c $<

main: Game.o main.o Events.o Character.o Inventory.o Item.o Monster.o
	g++ $^ -o $@
