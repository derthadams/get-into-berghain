# Makefile format from
# ftp://ftp.gnu.org/old-gnu/Manuals/make-3.79.1/html_chapter/make_2.html



CXX = g++
CXXFLAGS = -std=c++11
objects = main.o dbl_to_string.o getDouble.o getInt.o getMenuChoice.o getString.o Club.o Game.o Item.o Outfit.o Space.o Store.o Street.o


get-into-berghain: $(objects)
	$(CXX) $(CXXFLAGS) -o get-into-berghain $(objects)

main.o: Game.hpp AsciiArt.hpp getMenuChoice.hpp

Game.o: Game.hpp Club.hpp Street.hpp Store.hpp getMenuChoice.hpp AsciiArt.hpp

Club.o: Club.hpp getMenuChoice.hpp Constants.hpp AsciiArt.hpp

Item.o: Item.hpp

Outfit.o: Outfit.hpp Item.hpp AsciiArt.hpp getMenuChoice.hpp

Space.o: Space.hpp Constants.hpp AsciiArt.hpp

Street.o: Street.hpp getMenuChoice.hpp Store.hpp

Store.o: Store.hpp getMenuChoice.hpp AsciiArt.hpp

getMenuChoice.o: getMenuChoice.hpp getInt.hpp getDouble.hpp dbl_to_string.hpp

getDouble.o: getDouble.hpp

getInt.o: getInt.hpp

dbl_to_string.o: dbl_to_string.hpp

getString.o: getString.hpp

.PHONY: clean

clean:
	-rm get-into-berghain $(objects)

