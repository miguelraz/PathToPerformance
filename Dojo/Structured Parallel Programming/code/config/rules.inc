include ../../../config/config.inc

run:	$(TARGET)
	./$(TARGET)

build: $(TARGET)

ifndef CPLUS
$(TARGET):
	@ echo "Please set CPLUS=(your compiler) near top of config/config.inc"
else
ifndef CPLUS_FLAGS
$(TARGET):
	@ echo "CPLUS is $(CPLUS) which is not a supported compiler"
else
$(TARGET): ../../../config/config.inc ../../../config/rules.inc
	$(CPLUS) $(CPLUS_FLAGS) $(INCLUDE_KEY).. $(SRC) $(LIBS) $(EXE_KEY)$(TARGET)
endif
endif	
 
clean:	
	$(RM) *.o *.obj $(TARGET)

