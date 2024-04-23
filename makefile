all: realclean

realclean:
	make -C tests_SDL_basics clean
	make -C Tests/First_Chessboard_Display realclean
	make -C Tests/Test_Conversion realclean
	make -C Tests/Test_Log realclean
	make -C V1 realclean

.PHONY:realclean