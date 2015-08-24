from django.db import models
from django.contrib.postgres.fields import ArrayField


class Landscape(models.Model):
    code = models.CharField(max_length=20, null=True, blank=True)
    name = models.CharField(max_length=100, null=True, blank=True)
    description = models.TextField(null=True, blank=True)
    latitude = models.FloatField(default=0, null=True, blank=True)
    longitude = models.FloatField(default=0, null=True, blank=True)


class LandscapeResource(models.Model):
    landscape = models.ForeignKey(Landscape, related_name='resources', null=True, blank=True)
    type = models.CharField(max_length=20, null=True, blank=True)
    content = models.CharField(max_length=500, null=True, blank=True)
