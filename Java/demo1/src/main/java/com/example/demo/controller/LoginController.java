package com.example.demo.controller;

import com.example.demo.Entity.Student;
import com.example.demo.service.StudentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.HashMap;
import java.util.Map;
import java.util.Objects;

@RestController
public class LoginController {
    @Autowired
    private StudentService studentService;
    
    @PostMapping("/login")
    public Map<String, Object> UserLogin(@RequestBody Map<String, String> remap) {
        String username = remap.get("username");
        String password = remap.get("password");
        Map<String, Object> map = new HashMap<>();
        try {
            Student student = new Student(username, password);
            Student student1 = studentService.selectStudentByUsername(student.getUsername());
            if (student1 == null) {
                map.put("success", false);
                map.put("message", "用户不存在！");
            }
            else if (Objects.equals(student1.getPassword(), password)) {
                map.put("success", true);
                map.put("message", "用户登录成功！");
            }
        } catch (Exception e) {
            e.printStackTrace();
            map.put("success", false);
            map.put("message", "用户登录失败！");
        }
        return map;
    }
}

