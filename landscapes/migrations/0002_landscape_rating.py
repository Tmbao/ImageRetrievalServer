# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('landscapes', '0001_initial'),
    ]

    operations = [
        migrations.AddField(
            model_name='landscape',
            name='rating',
            field=models.FloatField(default=0, null=True, blank=True),
        ),
    ]
