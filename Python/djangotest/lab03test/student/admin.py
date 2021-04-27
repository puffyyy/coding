from django.contrib import admin
from student.models import *


class StudentAdmin(admin.ModelAdmin):
    list_display = ['id', 'name', 'password']


class GradeListAdmin(admin.ModelAdmin):
    list_grade = ['id', 'name', 'course', 'grade']


admin.site.register(Student, StudentAdmin)
admin.site.register(GradeList, GradeListAdmin)
