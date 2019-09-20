$(APP_MPL): %.mpl : %.jar $(JBC2MPL_BIN)
	$(JBC2MPL_BIN) --mplt $(LIB_MPLT) -injar $(APP_JAR) -out $(APP)
#输入一个LIB_MPLT文件，也就是一个mplt的格式的库，该库缺失