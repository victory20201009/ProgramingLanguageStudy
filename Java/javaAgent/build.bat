echo Premain-Class: com.agent.test.HelloAgent > MANIFEST.MF
javac com/agent/test/HelloAgent.java
javac com/agent/test/Hello.java
jar cvmf MANIFEST.MF agent-test.jar com/
java -javaagent:.\agent-test.jar=haha com/agent/test/Hello
pause