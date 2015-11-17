# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Landscape',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('code', models.CharField(max_length=20, null=True, blank=True)),
                ('name', models.CharField(max_length=100, null=True, blank=True)),
                ('description', models.TextField(null=True, blank=True)),
                ('latitude', models.FloatField(default=0, null=True, blank=True)),
                ('longitude', models.FloatField(default=0, null=True, blank=True)),
            ],
        ),
        migrations.CreateModel(
            name='LandscapeResource',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('type', models.CharField(max_length=20, null=True, blank=True)),
                ('content', models.CharField(max_length=500, null=True, blank=True)),
                ('landscape', models.ForeignKey(related_name='resources', blank=True, to='landscapes.Landscape', null=True)),
            ],
        ),
    ]
