from django.forms import widgets
from rest_framework import serializers
from iradapter.models import RequestImage, ResponseRankedList


class RequestImageSerializer(serializers.ModelSerializer):
    response = serializers.StringRelatedField()

    class Meta:
        model = RequestImage
        fields = ('id', 'content', 'request_at', 'response')


class ResponseRankedListSerializer(serializers.ModelSerializer):
    request = serializers.StringRelatedField()

    class Meta:
        model = ResponseRankedList
        fields = ('id', 'request', 'get_status', 'content')
