from django.forms import widgets
from rest_framework import serializers
from landscapes.models import Landscape, LandscapeResource


class LandscapeResourceSerializer(serializers.ModelSerializer):
    request = serializers.StringRelatedField()

    class Meta:
        model = LandscapeResource
        fields = ('id', 'Landscape', 'type', 'content')


class LandscapeSerializer(serializers.ModelSerializer):
    response = serializers.StringRelatedField()
    resources = LandscapeResourceSerializer(many=True)

    class Meta:
        model = Landscape
        fields = ('id', 'name', 'description', 'resources', 'latitude', 'longitude')
