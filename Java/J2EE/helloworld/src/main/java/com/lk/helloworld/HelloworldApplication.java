package com.lk.helloworld;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ConfigurableApplicationContext;

@SpringBootApplication
public class HelloworldApplication {
    
    public static void main(String[] args) {
        //spring boot启动
        ConfigurableApplicationContext run = SpringApplication.run(HelloworldApplication.class, args);
    }
    
}
