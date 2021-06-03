package com.example.demo.service;

import com.example.demo.Entity.Student;
import org.apache.ibatis.annotations.Mapper;
import org.springframework.stereotype.Service;

public interface StudentService {
    public Student selectStudentByUsername(String name);

    public void registerNewStudent(Student student);
}
