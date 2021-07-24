package com.lk.helloworld.entity;

import com.fasterxml.jackson.annotation.JsonFormat;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;
import java.util.Date;

@AllArgsConstructor
@NoArgsConstructor
@Data
public class Book implements Serializable {
    private static final long serialVersionUID = -1262101806308479243L;
    private String name;
    private String author;
    @JsonFormat(pattern = "yyyy-MM-dd")
    private Date publicationDate;
    private String description;
    
}
