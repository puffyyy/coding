from django.http import HttpResponseRedirect
from django.shortcuts import render, redirect

from django.urls import reverse
from student.models import *


def home(request):
    username = ''
    message = 'lab03'
    return render(request, 'home.html', {'username': username, 'message': message})


def getGrade(request):
    username = request.session['username']

    if request.method == 'GET':
        grade = GradeList.objects.filter(name=username)
        # print(username)
        code = ""
        # for i in grade:
        #     code = code + ("<tr><td>" + i.course + "</td><td> " + str(i.grade) + " </td ></tr>")
        for i in grade:
            code = code + i.course + " " + str(i.grade) + " "
        return render(request, 'grade.html', {'username': username, 'text': code})

    else:
        return render(request, 'home.html', {'username': username})


def register(request):
    if request.method == 'POST':
        new_username = request.POST.get('username')
        password = request.POST.get('password1')
        rep_password = request.POST.get('password2')
        if len(new_username) == 0:
            return render(request, 'register.html', {'message': '请输入用户名'})
        if len(password) == 0:
            return render(request, 'register.html', {'message': '请输入密码'})
        if len(rep_password) == 0:
            return render(request, 'register.html', {'message': '请再次输入密码'})
        user = Student.objects.filter(name=new_username)
        if not user.exists():
            if password == rep_password:
                new_student = Student()
                new_student.name = new_username
                new_student.password = password
                new_student.save()
                return HttpResponseRedirect('../', {'message': '注册成功'})
                # return render(request, 'home.html', {'message': '注册成功'})
            else:
                return render(request, 'register.html', {'message': '密码不一致'})
        else:
            return render(request, 'register.html', {'message': '该名称已被占用'})
    else:
        return render(request, 'register.html', {})


def login(request):
    if request.method == 'POST':
        username = request.POST.get('username')
        password = request.POST.get('password')
        if len(username) == 0:
            return render(request, 'login.html', {'message': '请输入用户名'})
        else:
            if len(password) == 0:
                return render(request, 'login.html', {'message': '请输入密码'})
            else:
                user = Student.objects.filter(name=username)
                if user.exists():
                    us = user[0]
                    if us.password == password:
                        request.session['username'] = username
                        return render(request, 'home.html', {'username': username, 'message': '登录成功'})
                    else:
                        return render(request, 'login.html', {'message': '密码错误'})
                else:
                    return render(request, 'login.html', {'message': '用户不存在'})
    else:
        return render(request, 'login.html', {})


def logout(request):
    request.session.flush()
    return render(request, 'home.html', {'message': '注销成功'})
