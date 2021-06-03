package com.example.demo.service.lmpl;

import com.example.demo.Dao.StudentDao;
import com.example.demo.Entity.Student;
import com.example.demo.service.StudentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class StudentServicelmpl implements StudentService {
    @Autowired
    private StudentDao studentDao;

    @Override
    public Student selectStudentByUsername(String name){
        return studentDao.selectStudentByUsername(name);
    }

    @Override
    public void registerNewStudent(Student student){
        studentDao.registerNewStudent(student);
    }
}
