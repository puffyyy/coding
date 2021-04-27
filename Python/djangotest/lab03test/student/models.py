from django.db import models


class Student(models.Model):
    name = models.CharField(max_length=100)
    password = models.CharField(max_length=15)


class GradeList(models.Model):
    name = models.CharField(max_length=100)
    course = models.CharField(max_length=20)
    grade = models.FloatField(max_length=4)
