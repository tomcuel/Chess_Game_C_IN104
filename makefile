all: realclean

realclean:
	make -C tests_SDL_basics clean
	make -C Tests/First_Chessboard_Display realclean
	make -C Tests/Test_Conversion realclean
	make -C Tests/Test_Log realclean
	make -C Tests/Test_Piece/Test_Piece_Movement realclean
	make -C V1 realclean
	make -C V2 realclean
	make -C V3 realclean

.PHONY:realclean