package com.agent.test;

public class HelloAgent{
	public static void premain(String agentArgs){
		System.out.println("I am running before main,my args is:"+agentArgs);
	}
}