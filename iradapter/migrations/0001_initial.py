# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations
import django.contrib.postgres.fields


class Migration(migrations.Migration):

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='RequestImage',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('content', models.ImageField(upload_to=b'images/%Y/%m/%d')),
                ('request_at', models.DateTimeField(auto_now_add=True)),
            ],
        ),
        migrations.CreateModel(
            name='ResponseRankedList',
            fields=[
                ('id', models.AutoField(verbose_name='ID', serialize=False, auto_created=True, primary_key=True)),
                ('status', models.CharField(blank=True, max_length=3, null=True, choices=[(b'P', b'Pending'), (b'C', b'Completed')])),
                ('content', django.contrib.postgres.fields.ArrayField(size=None, null=True, base_field=models.CharField(max_length=200), blank=True)),
                ('request', models.OneToOneField(related_name='response', null=True, blank=True, to='iradapter.RequestImage')),
            ],
        ),
    ]
