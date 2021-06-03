package com.example.demo.controller;

import com.example.demo.Entity.Student;
import com.example.demo.service.StudentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.HashMap;
import java.util.Map;

@RestController
public class HomeController {
    
    @Autowired
    private StudentService studentService;
    
    @PostMapping("/register")
    public Map<String, Object> registerNewUser(@RequestBody Map<String, String> remap) {
        String username = remap.get("username");
        String password = remap.get("password");
        Map<String, Object> map = new HashMap<>();
        try {
            Student student = new Student(username, password);
            Student student1 = studentService.selectStudentByUsername(student.getUsername());
            if (student1 != null) {
                map.put("success", false);
                map.put("message", "用户名已注册！");
            } else {
                studentService.registerNewStudent(student);
                map.put("success", true);
                map.put("message", "用户注册成功！");
            }
        } catch (Exception e) {
            e.printStackTrace();
            map.put("success", false);
            map.put("message", "用户注册失败！");
        }
        return map;
    }
}
