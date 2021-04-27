package com.lk.helloworld.entity;

import com.fasterxml.jackson.annotation.JsonFormat;

import java.util.Date;

public class Book {
    private String name;
    private String author;
    @JsonFormat(pattern = "yyyy-MM-dd")
    private Date publicationDate;
    private String description;
    
    public String getAuthor() {
        return author;
    }
    
    public void setAuthor(String author) {
        this.author = author;
    }
    
    public Date getPublicationDate() {
        return publicationDate;
    }
    
    public void setPublicationDate(Date publicationDate) {
        this.publicationDate = publicationDate;
    }
    
    public String getDescription() {
        return description;
    }
    
    public void setDescription(String description) {
        this.description = description;
    }
    
    public String getName() {
        return name;
    }
    public void setName(String name){
        this.name = name;
    }
    
}
