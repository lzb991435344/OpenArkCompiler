$(APP_JAR): %.jar : %.java
	$(JAVA2JAR) $(APP_JAR) ${MAPLE_ROOT}/libjava-core/java-core.jar "$(wildcard *.java)"
#输入java文件之前，输入了一个java-core.jar包，这个包就是前面java2jar中的CORE_ALL_JAR