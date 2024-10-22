.PHONY: all main words_menu words_menu_thread inverted_index

all: main words_menu words_menu_thread inverted_index

main:
	$(MAKE) -C main

words_menu:
	$(MAKE) -C words_menu

words_menu_thread:
	$(MAKE) -C words_menu_thread

inverted_index:
	$(MAKE) -C inverted_index
