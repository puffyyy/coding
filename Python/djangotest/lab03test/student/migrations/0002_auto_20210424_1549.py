# Generated by Django 3.2 on 2021-04-24 07:49

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('student', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='GradeList',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=100)),
                ('course', models.CharField(max_length=20)),
                ('grade', models.FloatField(max_length=4)),
            ],
        ),
        migrations.AlterField(
            model_name='student',
            name='password',
            field=models.CharField(max_length=15),
        ),
    ]