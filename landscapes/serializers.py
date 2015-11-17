from django.forms import widgets
from rest_framework import serializers
from landscapes.models import Landscape, LandscapeResource


class LandscapeResourceSerializer(serializers.ModelSerializer):
    class Meta:
        model = LandscapeResource
        fields = ('id', 'landscape', 'type', 'content')


class LandscapeSerializer(serializers.ModelSerializer):
    resources = LandscapeResourceSerializer(many=True)

    class Meta:
        model = Landscape
        fields = ('id', 'name', 'code', 'description', 'rating', 'resources', 'latitude', 'longitude')
