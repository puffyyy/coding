package com.lk.helloworld.controller;

import com.fasterxml.jackson.annotation.JsonFormat;
import com.lk.helloworld.entity.Book;
import org.springframework.web.bind.annotation.*;

import java.util.Date;

@RestController
@RequestMapping("test")
public class HelloWorldController {
    @GetMapping("hello")
    public String sayHello() {
        return "Hello World";
    }
    @GetMapping("test")
    public String test(){

        return "for test. addition";
    }
    @ResponseBody
    @GetMapping("/book")
    public Book retBook(){
        return new Book("平凡的世界","dma",new Date(),"bad");
    }
}





