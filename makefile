all:
	make -C tests_SDL_basics
	make -C Tests/First_Chessboard_Display 
	make -C Tests/Test_Conversion 
	make -C Tests/Test_Log 
	make -C Tests/Test_Captured_Pieces
	make -C Tests/Test_Undo
	make -C V1 
	make -C V2 
	make -C V3
	make -C V4

realclean:
	make -C tests_SDL_basics realclean
	make -C Tests/First_Chessboard_Display realclean
	make -C Tests/Test_Conversion realclean
	make -C Tests/Test_Log realclean
	make -C Tests/Test_Captured_Pieces realclean
	make -C Tests/Test_Undo realclean
	make -C V1 realclean
	make -C V2 realclean
	make -C V3 realclean
	make -C V4 realclean

.PHONY:realclean